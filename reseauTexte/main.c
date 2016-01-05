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
									if(jouer(character) == 1) {
										printf("Fin de la partie, vous avez gagné !");
									}
									else {
										printf("Fin de la partie, vous avez perdu !");
									}
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

int jouer(Character character[2]){
		Client client;
		int *info = malloc(BUFF_SIZE_RECV * sizeof(int));

		int map[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = {0};
		int continuer,i,j, verif;

		char choix = '\0';

		connexionToServer(&client);
		system("clear");
		printf("\t\tWaiting for another client\t\t\n");


		continuer = 1;
		verif = 1;
		while(continuer){
				
				if((info = receiveFromServer(client)) == -1) {
					printf("Connexion Lost\n");
					deconnexionFromServer(&client);
					continuer = 0;
					return 0;
				}
				if(info[0] == 30 && info[1] == 35) {
					if(info[3] == 0) {
						deconnexionFromServer(&client);
						continuer = 0;
						return 1;
					}
					else if(info[3] == 1) {
						deconnexionFromServer(&client);
						continuer = 0;
						return 0;
					}
				}
				else {
					for(i = 0; i < 300; i++) {
						if(!(info[i] < 9 || info[i] == 18)) {
							printf("Invalid data received Map\n");
							verif = 0;
						}
					}
					if(info[300] > 10 || info[301] > 10 || info[302] > 10 ||
					info[305] > 10 || info[306] > 10 || info[307] > 10 ||
				  info[303] > 19 || info[308] > 19 || info[304] > 14 || info[309] > 14 ||
			    info[303] < 0 || info[308] < 0 || info[304] < 0 || info[309] < 0) {
						printf("Invalid data received players\n");
						verif = 0;
					}

					if(verif == 0) {
						printf("Game finished because of trickery\n");
						deconnexionFromServer(&client);
						continuer = 0;
						return 0;
					}
					else {
						convertInfo(info, character, map);
						display(map, character);
					}
				}

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
						case 'P':
						case 'p':
							sendToServer(client, EXIT);
							break;
						default:
								printf("ERROR : BAD INPUT\n");
								break;
				}
			}
	deconnexionFromServer(&client);
	return 0;
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
				character[i]->x = info[k++];
				character[i]->y = info[k++];
		}
}
