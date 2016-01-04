/* Code pour le serveur*/
#include <fcntl.h>
#include <unistd.h>
#include <malloc.h>
#include <stdio.h>

#include "../constantes.h"

/*Il faudra mettre ici la bonne déclaration de la fonction j'ai la flemme de la mettre*/
int initMap(int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR], char* fichierNiveau){
    int fd;
    char *car = malloc(sizeof(char));
    int x = 0;
    int y = 0;

    /* Nous ouvrons le fichier */
    if((fd = open(fichierNiveau, O_RDONLY)) == -1){
        printf("Ouverture Impossible\n");
       return -1;
    }

    /*On va lire le fichier caractere par caractere jusqu'a la fin du fichier */
    while(read(fd,car,1) != 0){
            if(*car == '\n'){
                x = 0;
                y++;
            }
            else{
                carte[x][y] = (int) *car - 48;
                x++;
            }
        }
        close(fd);
        free(car);
        return 0;
}
