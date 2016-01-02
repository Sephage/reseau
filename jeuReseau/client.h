#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>

/* default values */
#define PORT 31337 // Port the server is listening to
#define IP_SERVER 127.0.0.1 // IP of the server
#define BUFF_SIZE_SEND 40 // max Size of the sent message
#define BUFF_SIZE_RECV 1024 // max Size of the received message

typedef struct {
  struct sockaddr_in serverAddr;
  socklen_t addr_size;
  int sockfd;
}Client;

void connexionToServer(Client client);
void sendToServer(Client client);
char* receiveFromServer(Client client);
void deconnexionFromServer(Client client);
