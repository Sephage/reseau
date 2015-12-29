#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "server.h"
#include "client.h"

static void init(void)
{
#ifdef WIN32
		WSADATA wsa;
		int err = WSAStartup(MAKEWORD(2, 2), &wsa);
		if(err < 0)
		{
				puts("WSAStartup failed !");
				exit(EXIT_FAILURE);
		}
#endif
}

static void end(void)
{
#ifdef WIN32
		WSACleanup();
#endif
}

static void app(void)
{
		SOCKET sock = init_connection();
		char buffer[BUF_SIZE];
		/* the index for the array */
		int actualClient = 0;
		int max = sock;
		/* an array for all clients */
		Client clients[MAX_CLIENTS];

		fd_set rdfs;

		while(1)
		{
				FD_ZERO(&rdfs);

				/* add STDIN_FILENO */
				FD_SET(STDIN_FILENO, &rdfs);

				/* add the connection socket */
				FD_SET(sock, &rdfs);

				if(select(max + 1, &rdfs, NULL, NULL, NULL) == -1){
						perror("select()");
						exit(errno);
				}

				/* something from standard input : i.e keyboard */
				if(FD_ISSET(STDIN_FILENO, &rdfs)){
						/* stop process when type on keyboard */
						break;
				}
				else if(FD_ISSET(sock, &rdfs)){
						/* new client */
						SOCKADDR_IN csin = { 0 };

						/* a client is talking */
						read_client(sock, &csin, buffer);
						/*If client doesn't exist we can create it*/
						if(!check_if_client_exists(clients, &csin, actualClient)){
								if(actualClient != MAX_CLIENTS){
										Client c = { csin };
										strncpy(c.name, buffer, BUF_SIZE - 1);
										clients[actualClient] = c;
										actualClient++;
								}
						}
						/*If he exists, we have to send the map*/
						else{
								Client *client = get_client(clients, &csin, actualClient);
								if(client == NULL) 
										continue;
								send_map(sock, clients, client, actualClient, buffer, 0);
						}
				}
		}

		end_connection(sock);
}

static int check_if_client_exists(Client *clients, SOCKADDR_IN *csin, int actualClient)
{
		int i = 0;
		for(i = 0; i < actualClient; i++)
		{
				if(clients[i].sin.sin_addr.s_addr == csin->sin_addr.s_addr
								&& clients[i].sin.sin_port == csin->sin_port)
				{
						return 1;
				}
		}

		return 0;
}

static Client* get_client(Client *clients, SOCKADDR_IN *csin, int actualClient)
{
		int i = 0;
		for(i = 0; i < actualClient; i++)
		{
				if(clients[i].sin.sin_addr.s_addr == csin->sin_addr.s_addr
								&& clients[i].sin.sin_port == csin->sin_port)
				{
						return &clients[i];
				}
		}

		return NULL;
}

static void remove_client(Client *clients, int to_remove, int *actualClient)
{
		/* we remove the client in the array */
		memmove(clients + to_remove, clients + to_remove + 1, (*actualClient - to_remove) * sizeof(Client));
		/* number client - 1 */
		(*actualClient)--;
}

static void send_map(int sock, Client *clients, Client *sender, int actualClient, const char *buffer, char from_server)
{
		int i = 0;
		char message[BUF_SIZE];
		message[0] = 0;
		for(i = 0; i < actualClient; i++){
				/* we don't send message to the sender */
				if(sender != &clients[i]){
						if(from_server == 0){
								strncpy(message, sender->name, BUF_SIZE - 1);
								strncat(message, " : ", sizeof message - strlen(message) - 1);
						}
						strncat(message, buffer, sizeof message - strlen(message) - 1);
						write_client(sock, &clients[i].sin, message);
				}
		}
}

static int init_connection(void)
{
		/* UDP so SOCK_DGRAM */
		SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
		SOCKADDR_IN sin = { 0 };

		if(sock == INVALID_SOCKET)
		{
				perror("socket()");
				exit(errno);
		}

		sin.sin_addr.s_addr = htonl(INADDR_ANY);
		sin.sin_port = htons(PORT);
		sin.sin_family = AF_INET;

		if(bind(sock,(SOCKADDR *) &sin, sizeof sin) == SOCKET_ERROR)
		{
				perror("bind()");
				exit(errno);
		}

		return sock;
}

static void end_connection(int sock)
{
		closesocket(sock);
}

static int read_client(SOCKET sock, SOCKADDR_IN *sin, char *buffer)
{
		int n = 0;
		size_t sinsize = sizeof *sin;

		if((n = recvfrom(sock, buffer, BUF_SIZE - 1, 0, (SOCKADDR *) sin, &sinsize)) < 0)
		{
				perror("recvfrom()");
				exit(errno);
		}

		buffer[n] = 0;

		return n;
}

static void write_client(SOCKET sock, SOCKADDR_IN *sin, const char *buffer)
{
		if(sendto(sock, buffer, strlen(buffer), 0, (SOCKADDR *) sin, sizeof *sin) < 0)
		{
				perror("send()");
				exit(errno);
		}
}

int main(int argc, char **argv)
{
		init();

		app();

		end();

		return EXIT_SUCCESS;
}
