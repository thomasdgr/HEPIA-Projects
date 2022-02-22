#include "matrix.h"

matrix init_tab(int m, int n){
    matrix mat;
    if(m <= 0 || n<= 0){
        mat.m = -1;
        mat.n = -1;
        mat.data = NULL;
    }
    mat.m = m;
    mat.n = n;
    mat.data = malloc(m * sizeof(double*));
    mat.data[0]= malloc(n * m * sizeof(double));
    for(int i = 0; i < m; i++){
        mat.data[i] = mat.data[0] + i * n;
        for(int j = 0; j < n; j++){
            if(i == 0 || (j == n-1 && i != m-1)){
                mat.data[i][j] = 1.0;
            } else {
                mat.data[i][j] = 0.0;
            }
        }
    }
    return mat;
}

void free_tab(matrix* mat){
    free(mat->data[0]);
    free(mat->data);
    mat->m = -1;
    mat->n = -1;
    mat->data = NULL;
}

void copy_tab(matrix* mat1, matrix mat2){
    if(mat1->m == mat2.m && mat1->n == mat2.n){
        for(int i = 0; i < mat1->m; i++){
            for(int j = 0; j < mat1->n; j++){
                mat1->data[i][j] = mat2.data[i][j];
            }
        }
    }
}

void print_tab(matrix mat){
    for(int i = 0; i < mat.m; i++){
        for(int j = 0; j < mat.n; j++){
            printf("\t%.2f ", mat.data[i][j]);
        }
        printf("\n");
    }
}

void vector_push(vector *v, double element) {
    if (v->capacity == v->length){
        v->capacity *= 2;
        v->content = realloc(v->content, (v->capacity * 2) * sizeof(double));
    }
    v->content[v->length] = element;
    v->length++;
}

matrix read_file(char * filename){
    FILE * f = fopen(filename, "r");
    if(!f){
        printf("Error while opening the file\n");
        exit(EXIT_FAILURE);
    }
    int ligne = 0;
    char * ligne_buffer = NULL;
    size_t num_buffer = 0;
    int count = 0;
    char * token;
    vector v;
    v.length = 0;
    v.capacity = 4;
    v.content = malloc(v.capacity * sizeof(double));
    while((ligne = getline(&ligne_buffer, &num_buffer, f)) > 0){
        token = strtok(ligne_buffer, " ");
        count = 0;
        do{
            vector_push(&v, atof(token));
            count += 1;
        }while((token = strtok(NULL, " ")) != NULL);
    }
    vector_push(&v, count);
    int numColumns = (v.length - 2*v.content[v.length-1])/2;
    int numLines = v.content[v.length-1] + 2;
    matrix mat = init_tab(numLines, numColumns);
    for(int i = 0; i <= numLines; i++){
        mat.data[0][i] = v.content[i];
        mat.data[numLines-1][i] = v.content[i + numLines + 1];
    }
    for(int i = 1; i < numColumns-2; i++){
        mat.data[i][0] = v.content[i + (2*numLines) + 1];
        mat.data[i][numColumns-1] = v.content[i + (2*numLines) + numColumns - 2];
    }
    v.capacity = 0;
    v.length = 0;
    free(v.content);
    v.content = NULL;
    fclose(f);
    return mat;
}

void write_file(char *filename, matrix mat){
    FILE *f = fopen (filename, "w+");
    if(f){
        for(int i = 0; i < mat.m; i++){
            for(int j = 0; j < mat.n; j++){
                fprintf(f, "%.2f", mat.data[i][j]);
                if(j+1 < mat.n){
                    fprintf(f, " ");
                }
            }
            fprintf(f, "\n");
        }
        fclose(f);
    }
}

void apply_laplace(matrix* mat, double* bufRecv1, double* bufRecv2){
    matrix U_temp = init_tab(mat->m, mat->n);
    copy_tab(&U_temp, *mat);
    if(bufRecv1 != NULL){
        for(int j = 0; j < mat->n; j++){
            U_temp.data[mat->m-1][j] = bufRecv1[j];
        }
    }
    if(bufRecv2 != NULL){
        for(int j = 0; j < mat->n; j++){
            U_temp.data[0][j] = bufRecv2[j];
        }       
    }
    for(int i = 1; i < mat->m-1; i++){
        for(int j = 1; j < mat->n-1; j++){
            U_temp.data[i][j] = 0.25 * (mat->data[i-1][j] + mat->data[i+1][j] + mat->data[i][j-1] + mat->data[i][j+1]);
        }
    }
    copy_tab(mat, U_temp);
    free_tab(&U_temp);
}

int* compute_lines(int m, int n, int nProc){
    int *nbLines = malloc(nProc*sizeof(int));
    for(int i = 0; i < nProc; i++){
        int nb = m / nProc;
        if(m % nProc > i){
            nb++;
        }
        if((i == 0 || i == nProc - 1) && nProc > 1){
            nb++;
        } else if(nProc > 1){
            nb+=2;
        }
        nbLines[i] = nb * n;
    }
    return nbLines;
}

int* compute_displacement(int rank, int nProc, int* nbLines, int size){
    int* displacement = malloc(nProc*sizeof(int));
    if(rank == 0){
        for(int i = 0; i < nProc; i++){
            if(i == 0){
                displacement[i] = 0;
            } else{
                displacement[i] = displacement[i-1] + (nbLines[i-1]  - 2 * size);
            }
        }
    }
    return displacement;
}

void update_lines(int* nbLines, int nProc, int size){
    for(int j = 0; j < nProc; j++){
        if(j != 0 || j == nProc -1){
            nbLines[j] = nbLines[j] - size*2;
        } else {
            nbLines[j] = nbLines[j] - size;
        }
    }
}

void update_displacement(int* displacement, int* nbLines, int nProc, int rank){
    if(rank == 0){
        for(int j = 1; j < nProc; j++){
            displacement[j] = displacement[j-1] + (nbLines[j-1]);
        }
    }
}

double* get_line(matrix mat, int index){
    double* buf = malloc(mat.n * sizeof(double));
    for(int i = 0; i < mat.n; i++){
        buf[i] = mat.data[index][i];
    }
    return buf;
}

double* get_missing_line(matrix mat, int index, int voisin1, int voisin2, int tag1, int tag2){
    MPI_Status status[2];
    MPI_Request request[2];
    double* bufSend = get_line(mat, index);
    double* bufRecv = malloc(mat.n * sizeof(double));
    MPI_Isend(bufSend, mat.n, MPI_DOUBLE, voisin1, tag1, MPI_COMM_WORLD, &request[0]);
    MPI_Irecv(bufRecv, mat.n, MPI_DOUBLE, voisin2, tag2, MPI_COMM_WORLD, &request[1]);
    MPI_Waitall(2, request, status);
    free(bufSend);
    return bufRecv;
}