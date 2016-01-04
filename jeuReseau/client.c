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
  client->serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  client->serverAddr.sin_port = htons(PORT);
  memset(&client->serverAddr.sin_zero, 0, sizeof(client->serverAddr.sin_zero));

  if(connect(client->sockfd, (struct sockaddr*)&client->serverAddr, sizeof(client->serverAddr)) < 0) {
    error("ERROR connecting to server");
  }
}

void sendToServer(Client client, char* msg) {
  int msgSize = strlen(msg);
  int verif;
  if(msgSize > BUFF_SIZE_SEND) {
    error("ERROR message too long to send");
  }
  else {
    verif = write(client.sockfd, msg, msgSize);
    if (verif < 0) {
      error("ERROR writing to socket");
    }
  }
}

int* receiveFromServer(Client client) {
  int* msg = malloc(BUFF_SIZE_RECV*sizeof(int));
  int check = read(client.sockfd, msg, BUFF_SIZE_RECV);
  if (check < 0) {
    error("ERROR reading from socket or connexion lost");
    return NULL;
  }
  return msg;
}

void deconnexionFromServer(Client* client) {
  close(client->sockfd);
}
