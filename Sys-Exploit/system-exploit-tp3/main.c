/*****************************************************************************
		     ____
           /____ \         | Projet : TP sur les modules 
           | _ _`\|        |        
    .-.   `| O O |         | Auteur : Thomas DAGIER
    | |   (- /_  -)        |
    | |    |     |         | Descripition : Utiliser les notions abordées en
(___)  )\/  \_____/  ~\.   |                cours pour comprendre comment
(___) . \   `         `\   |                fonctionnent les modules / périph
 (__)-    ,/        (   |  |
      `--~|         |   |  |  Version : 1.0
          |         |   |  |  Date : 24/06/2021

*****************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

/* objectifs: lecture de notre periphérique et petits tests sur l'écriture, 
 * entrées: rien
 * sorties: rien
 * limites des arguments: rien
 * conditions / effets de bords: rien
 */

int main() {
    // ouverture du fichier de periphérique
    int file = open("/dev/abcd", O_RDWR);

    char *data = malloc(sizeof(char) * 50);

    // test de lecture de 5 caractères -> devrait retourner "abcde"
    ssize_t v = read(file, data, 5);
    printf("read %d char -> %s\n", v, data);

    // test d'ecriture de 5 caractères -> devrait remplacer "fghij" par "12345"
    char input[5] = "12345";
    v = write(file, input, 5);
    printf("wrote %d char\n", v);

    // test de lecture de 10 caractères -> devrait retourner "klmnopqrst"
    v = read(file, data, 10);
    printf("read %d char -> %s\n", v, data);

    // test de lecture de 10 caractères -> devrait retourner "uvwxyz" et rien
    // de plus puisque l'offset atteint le max du buffer
    v = read(file, data, 10);
    printf("read %d char -> %s\n", v, data);

    // test de lecture de tout le buffer
    v = read(file, data, 26);
    printf("read %d char -> %s\n", v, data);

    // fin du programme
    free(data);
    close(file);
    return 0;
}