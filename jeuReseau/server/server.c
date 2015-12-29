#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <netinet.h>
#include <unistd.h>


int main(){
		int s_ecoute, s_dial, cli_len;
		int option = 1;
		struct sockaddr_in serv_addr, cli_addr;

		char buf[2];
		int bufferMap[20][20];
		int i;

		int so_reuseaddr = 1;

		int actualNumberClient = 0;
		int nb_client_aff = 0;
		int descmax = 0;
		int client[FD_SETSIZE];

		struct timeval compte_rebours;

		compte_rebours.tv_usec = 0;
		compte_rebours.tv_sec = 600;
		/*********/
		/*********/

		serv_addr.sin_family = AF_INET;
		ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
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
				for(i=0;i<actualNumberClient,i++){
						FD_SET(client[i], &readfds);
				}
				if(s_dial > descmax){
						descmax = s_dial:
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
		initGame();
		/*Tant que l'un des joueurs n'a pas gagné ou perdu...*/
		while(continuer){
			FD_ZERO(&readfds);
				FD_SET(s_ecoute, &readfds);
				descmax = s_ecoute;
				for(i=0;i<actualNumberClient,i++){
						FD_SET(client[i], &readfds);
				}
				if(s_dial > descmax){
						descmax = s_dial:
				}

					nb_client_aff = select(descmax + 1, &readfds, NULL, NULL, &compte_rebours);

					/*Lorsque nb_client_aff > 0, un des descripteur surveillé a reçu quelque chose*/
					if(nb_client_aff){
							/*Lecture des touches */
							for(i = 0;i<actualNumberClient;i++){
									if(FD_ISSET(client[i], &readfds)){
											bzero(buf,2);
											if(read(client[i], buf, 2) == -1){
													perror("Erreur lors de la lecture de la socket\n");
													return -1;
											}
											/*Traitement des touches que l'on recoit 
											 * i=J1 ou J2 (prendre i+1) */
											deplacer_personnage();
									}
							}
					}
		}
}

		}
}
