#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>

#include "../main.h"
#include "server.h"

int main(){
		int s_ecoute, s_dial, cli_len;
		int option = 1;
		struct sockaddr_in serv_addr, cli_addr;
		fd_set readfds;
		/*buf contient le déplacement (compris entre 0 et 3)
		 * map contient la map (qu'il faudra renvoyer à chaque changement
		 * character contiendra les états des deux personnages, 0 sera le premier arrivé
		 */
		int buf[1] = {0};
		int map[20][15] = {(0,0)};
		int bufMapJoueur[310] ={0};
		int i,j,k;
		int continuer = 1;

		Character character[2];
		for(i=0;i<2;i++){
			character[i] = malloc(sizeof(struct character));
			character[i]->position = malloc(sizeof(SDL_Rect*));
		}

		int so_reuseaddr = 1;

		int actualNumberClient = 0;
		int nb_client_aff = 0;
		int descmax = 0;
		int client[2];

		struct timeval compte_rebours;

		compte_rebours.tv_usec = 0;
		compte_rebours.tv_sec = 600;
		/*********/
		/*********/

		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
		serv_addr.sin_port = htons(31337);
		memset(&serv_addr.sin_zero, 0, sizeof(serv_addr.sin_zero));

		s_ecoute = socket(PF_INET, SOCK_STREAM, 0);
		setsockopt(s_ecoute, SOL_SOCKET, SO_REUSEADDR, &so_reuseaddr, sizeof so_reuseaddr);

		bind(s_ecoute, (struct sockaddr *)&serv_addr, sizeof serv_addr);
		listen(s_ecoute, 5);

		/*Premiere boucle afin de récupérer le bon nombre de joueur*/
		while(actualNumberClient < 2){
				FD_ZERO(&readfds);
				FD_SET(s_ecoute, &readfds);
				descmax = s_ecoute;
				for(i=0;i<actualNumberClient;i++){
						FD_SET(client[i], &readfds);
				}
				if(s_dial > descmax){
						descmax = s_dial;
				}

					nb_client_aff = select(descmax + 1, &readfds, NULL, NULL, &compte_rebours);

					/*Lorsque nb_client_aff > 0, un des descripteur surveillé a reçu quelque chose*/
					if(nb_client_aff){
								if(FD_ISSET(s_ecoute, &readfds)){
										cli_len = sizeof cli_addr;
										s_dial = accept(s_ecoute, (struct sockaddr *)&cli_addr,
														(socklen_t *)&cli_len);
										printf("Le client %s s'est connecte\n", inet_ntoa
														(cli_addr.sin_addr),
														ntohs(cli_addr.sin_port));
										client[actualNumberClient] = s_dial;
										actualNumberClient++;
								}
					}
		}
		/*Initialisation de la map et des joueurs
		 * A completer */
		initGame(character, map);
		k = 0;
		while(k < 300) {
			for(i=0;i<NB_BLOCS_LARGEUR;i++){
				for(j=0;j<NB_BLOCS_HAUTEUR;j++){
					bufMapJoueur[k] = map[i][j];
					k++;
				}
			}
		}
		bufMapJoueur[300] = character[0]->life;
		bufMapJoueur[301] = character[0]->key;
		bufMapJoueur[302] = character[0]->gold;
		bufMapJoueur[303] = character[0]->position->x;
		bufMapJoueur[304] = character[0]->position->x;

		bufMapJoueur[305] = character[1]->life;
		bufMapJoueur[306] = character[1]->key;
		bufMapJoueur[307] = character[1]->gold;
		bufMapJoueur[308] = character[1]->position->x;
		bufMapJoueur[309] = character[1]->position->y;

		printf("Envoi des données en cours\n");
		for(i=0;i<2;i++){
			write(client[i],bufMapJoueur,310*sizeof(int));
		}
		printf("Envoi des données fini\n");

		/*Tant que l'un des joueurs n'a pas gagné ou perdu...*/
		while(continuer){
			FD_ZERO(&readfds);
				FD_SET(s_ecoute, &readfds);
				descmax = s_ecoute;
				for(i=0;i<actualNumberClient;i++){
						FD_SET(client[i], &readfds);
				}
				if(s_dial > descmax){
						descmax = s_dial;
				}

					nb_client_aff = select(descmax + 1, &readfds, NULL, NULL, &compte_rebours);

					/*Lorsque nb_client_aff > 0, un des descripteur surveillé a reçu quelque chose*/
					if(nb_client_aff){
							/*Lecture des touches */
							for(i = 0;i<actualNumberClient;i++){
									if(FD_ISSET(client[i], &readfds)){
											//printf("Un client est en train de parler\n");
											bzero(buf,1);
											if(read(client[i], buf, 1) == -1){
												perror("Erreur lors de la lecture de la socket\n");
													return -1;
											}
											/*Traitement des touches que l'on recoit
											 * i=J1 ou J2 (prendre i+1) */
											if(buf[0] == 5) {

												bufMapJoueur[0] = 30;
												bufMapJoueur[1] = 35;
												bufMapJoueur[3] = 0;

												write(client[i],bufMapJoueur,310*sizeof(int));

												bufMapJoueur[0] = 35;
												bufMapJoueur[1] = 30;
												bufMapJoueur[3] = 1;


												for(j=0;j<2;j++){
													if(j != i) {
														write(client[j],bufMapJoueur,310*sizeof(int));
													}
												}
												continuer = 0;
											}
											else {
												deplacer_personnage(map, buf[0], character[i]);
												if(character[i]->life == 0 || character[i]->gold == 10) {

													bufMapJoueur[0] = 30;
													bufMapJoueur[1] = 35;
													bufMapJoueur[3] = 0;

													write(client[i],bufMapJoueur,310*sizeof(int));

													bufMapJoueur[0] = 35;
													bufMapJoueur[1] = 30;
													bufMapJoueur[3] = 1;


													for(j=0;j<2;j++){
														if(j != i) {
															write(client[j],bufMapJoueur,310*sizeof(int));
														}
													}
													continuer = 0;
												}
												else {
													k = 0;
													while(k < 300) {
														for(i=0;i<NB_BLOCS_LARGEUR;i++){
															for(j=0;j<NB_BLOCS_HAUTEUR;j++){
																bufMapJoueur[k] = map[i][j];
																k++;
															}
														}
													}
													bufMapJoueur[300] = character[0]->life;
													bufMapJoueur[301] = character[0]->key;
													bufMapJoueur[302] = character[0]->gold;
													bufMapJoueur[303] = character[0]->position->x;
													bufMapJoueur[304] = character[0]->position->x;

													bufMapJoueur[305] = character[1]->life;
													bufMapJoueur[306] = character[1]->key;
													bufMapJoueur[307] = character[1]->gold;
													bufMapJoueur[308] = character[1]->position->x;
													bufMapJoueur[309] = character[1]->position->y;
												}

												printf("Envoi des données en cours\n");
												for(i=0;i<2;i++){
													write(client[i],bufMapJoueur,310*sizeof(int));
												}
												printf("Envoi des données fini\n");
											}
									}
							}
					}
					/*Il faut renvoyer les données de la map, les données des deux joueurs
					 * (life/key/gold/position
					 * aux deux joueurs
					 * Ou renvoyer une indication de fin de jeu si l'un des personnages
					 * a gagné et mettre continuer à 0 */
		}
}
