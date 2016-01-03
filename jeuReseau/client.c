#include "client.h"

void error(char *msg) {
    perror(msg);
    exit(0);
}

void connexionToServer(Client* client) {

  client->sockfd = socket(PF_INET, SOCK_STREAM, 0);
  if(client->sockfd < 0) {
    error("ERROR opening socket");
  }

  client->serverAddr.sin_family = AF_INET;
  client->serverAddr.sin_addr.s_addr = inet_addr(IP_SERVER);
  client->serverAddr.sin_port = htons(PORT);
  memset(&client->serverAddr.sin_zero, 0, sizeof(client->serverAddr.sin_zero));

  if(connect(client->sockfd, (struct sockaddr*)&client->serverAddr, sizeof(client->serverAddr)) < 0) {
    error("ERROR connecting to server");
  }
}

void sendToServer(Client client, char* msg) {
  int msgSize = strlen(msg);
  if(msgSize > BUFF_SIZE_SEND) {
    error("ERROR message too long to send");
  }
  else {
    verif = write(client.sockfd, msg, msgSize);
    if (n < 0) {
      error("ERROR writing to socket");
    }
  }
}

char* receiveFromServer(Client client) {
  char* msg = malloc(BUFF_SIZE_RECV*sizeof(char));
  int check = read(client.sockfd, msg, BUFF_SIZE_RECV);
  if (check < 0) {
    error("ERROR reading from socket or connexion lost");
    return NULL;
  }
  if(strlen(msg) > BUFF_SIZE_RECV) {
    error("ERROR message received too long");
    msg = "long"
  }

  return msg;
}

void deconnexionFromServer(Client* client) {
  close(client->sockfd);
}
