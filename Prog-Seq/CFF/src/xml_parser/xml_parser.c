/*******************************************************************************
			 ____
           /____ \               |  Projet : C_FF
           | _ _`\|              |
    .-.   `| O O |               |  Auteur : Thomas Dagier
    | |   (- /_  -)              |
    | |    |     |               |  Descripition : librairie de fonctions
 __/  |    | \__/|               |    utilisées pour lire un fichier xml et stocker
(___) \.  _.\__. `\___           |    les données dans une matrice d'adjacence
(___)  )\/  \_____/  ~\.         |    et une liste d'adjacence
(___) . \   `         `\         |   
 (__)-    ,/        (   |        |
      `--~|         |   |        |  Version : 1.0
          |         |   |		 |	Date :	03/06/2020

\******************************************************************************/

#include "xml_parser.h"

void city_xml_parser(xmlNode * a_node, lst_city* v) {
    xmlNode *cur_node = NULL;
    for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {
            if(!strcmp((const char*)cur_node->name,"Ville")){
                xmlNode * sub = cur_node->children;
                city c;  // no malloc needed values are copied
                strncpy(c.name, (const char*)sub->next->children->content, NAME_LEN-1);
                c.longitude = atoi((const char*)sub->next->next->next->children->content);
                c.latitude = atoi((const char*)sub->next->next->next->next->next->children->content);
                c.next = NULL;
                lst_city_push(v, &c);
            }
        }
        city_xml_parser(cur_node->children, v);
    }
}

void graph_xml_parser(xmlNode * a_node, lst_city* v, lst_connection* tab, matrix* mat){
    xmlNode *cur_node = NULL;

    for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {
            if(!strcmp((const char*)cur_node->name,"Liaison")){
                xmlNode * sub = cur_node->children;

                char src[NAME_LEN];
                char dst[NAME_LEN];
                strncpy(src, (const char*)sub->next->children->content, NAME_LEN-1);
                strncpy(dst, (const char*)sub->next->next->next->children->content, NAME_LEN-1);
                int duration = atoi((const char*)sub->next->next->next->next->next->children->content);
                int i = get_index(src, v);
                int j = get_index(dst, v);
                if(i == -1 || j == -1){
                    printf("ceci est facheux\n");
                    exit(0);
                }
                connection elem1 = {j, duration, NULL};
                connection elem2 = {i, duration, NULL};
                lst_connection_push(&tab[i], &elem1);
                lst_connection_push(&tab[j], &elem2);
                mat->data[i][j] = duration;
                mat->data[j][i] = duration;
            }
        }
        graph_xml_parser(cur_node->children, v, tab, mat);
    }
}

int read_xml(const char * filename, lst_city* v, lst_connection** tab, matrix* mat){
    // Init libxml
    xmlInitParser();
    LIBXML_TEST_VERSION

    // create a parser context
    xmlParserCtxtPtr ctxt;
    xmlDocPtr doc = NULL;
    ctxt = xmlNewParserCtxt();

    if (ctxt == NULL) {
        fprintf(stderr, "Failed to allocate parser context\n");
        return EXIT_FAILURE;
    }

    // parse the file, without error validation
    doc = xmlCtxtReadFile(ctxt, filename, NULL, XML_PARSE_NOERROR);
    // check if parsing suceeded
    if (doc == NULL) {
        fprintf(stderr, "Failed to parse %s\n", filename);
    } else {
        /* check if validation suceeded */
        if (ctxt->valid == 0)
            fprintf(stderr, "Failed to validate %s\n", filename);
    }

    xmlNode *root_element = xmlDocGetRootElement(doc);

    // get cities from xml
    city_xml_parser(root_element, v);
    // get graph from xml
    lst_tab_connection_init(tab, v->length);
    matrix_resize(mat,v->length,v->length);
    matrix_fill(*mat, INT_MAX);
    graph_xml_parser(root_element, v, *tab, mat);
    // free the document
    xmlFreeDoc(doc);
    // free up the parser context
    xmlFreeParserCtxt(ctxt);

    return EXIT_SUCCESS;
}

int get_index(char* name, lst_city* v){
    city *crt = v->head;
    for(int i = 0; i < v->length; i++){
        if(strcmp(name, crt->name) == 0){
            return i;
        }
        crt = crt->next;
    }
    return -1;
}

matrix convert_lst_to_matrix(lst_connection** v, lst_city* v2){
    matrix mat = matrix_create(v2->length,v2->length);
    matrix_fill(mat, INT_MAX);
    for(int k = 0; k < v2->length; k++){
        connection *tmp = (*v)[k].head;
        while (tmp != NULL){
            mat.data[k][tmp->neighbor] = tmp->weight;
            mat.data[tmp->neighbor][k] = tmp->weight;
            tmp = tmp->next;
        }
    }
    return mat;
}

lst_connection* convert_matrix_to_lst(matrix* mat, lst_city* v2){
    lst_connection* tab;
    lst_tab_connection_init(&tab, v2->length);
    for(int i = 0; i < mat->m; i++){
        for(int j = 0; j < mat->n; j++){
            if(mat->data[i][j] != INT_MAX){
                connection elem1 = {j, mat->data[i][j], NULL};
                lst_connection_push(&tab[i], &elem1);
            } else if (mat->data[j][i] != INT_MAX){
                connection elem2 = {i, mat->data[j][i], NULL};
                lst_connection_push(&tab[j], &elem2);
            }
        }
    }
    return tab;
}