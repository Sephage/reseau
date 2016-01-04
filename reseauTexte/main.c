#include <stdio.h>
#include <stdlib.h>

#include "client.h"
#include "constantes.h"
#include "player.h"
#include "main.h"

int main(){
		int continuer = 1;
		Character character[2];
		int i;
		int choix;
		for(i =0;i<2;i++){
				character[i] = malloc(sizeof(struct character));
		}

		while(continuer){
				printf("-----------------------Menu----------------------\n");
				printf("1- Se connecter à un serveur\n");
				printf("2- Quitter\n");
				while(choix != 1 && choix != 2){
				scanf("%d",&choix);
					switch(choix){
							case 1:
									jouer(character);
									break;
							case 2:
									system("clear");
									printf("Merci d'avoir participé, à bientot\n");
									continuer = 0;
									break;
							default:
									printf("Commande invalide");
									break;
					}
				}
		}
		return EXIT_SUCCESS;
}

void jouer(Character character[2]){
		Client client;
		int *info = malloc(BUFF_SIZE_RECV * sizeof(int));

		int map[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = {0};
		int continuer,i,j;

		char choix = '\0';

		connexionToServer(&client);
		system("clear");
		printf("\t\tWaiting for another client\t\t\n");


		continuer = 1;
		while(continuer){
				info = receiveFromServer(client);
				convertInfo(info, character, map);
				display(map, character);

				printf("Rentrez une touche (Z Q S D, A pour les bombes)\n");
				scanf("%c", &choix);
				switch(choix){
						case 'z':
						case 'Z':
								sendToServer(client, HAUT);
								break;
						case 'S':
						case 's':
								sendToServer(client, BAS);
								break;
						case 'Q':
						case 'q':
								sendToServer(client, GAUCHE);
								break;
						case 'D':
						case 'd':
								sendToServer(client, DROITE);
								break;
						case 'A':
						case 'a':
								sendToServer(client, BOMBE);
								break;
						default:
								printf("ERROR : BAD INPUT\n");
								break;
				}
					}
	deconnexionFromServer(&client);
}

void convertInfo(int *info, Character character[2], int map[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR]){
		int k = 0, m = 0, l = 0;
		int i;
		while((k<300) && (m < 20)){
				for(l = 0; l<15;l++){
						map[m][l] = info[k];
						k++;
				}
				m++;
		}
		for(i = 0;i<2;i++){
				character[i]->life = info[k++];
				character[i]->key = info[k++];
				character[i]->gold = info[k++];
		}
}
