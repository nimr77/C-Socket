
#ifndef CONNECTINGTO_H
#define CONNECTINGTO_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>

#define ERROR 	(-1)
#define TAILLEMESSAGE 256
#define PORT 9988
#define IPADRESSE "127.0.0.1"

void afficheErrorSortie(char *nomFct);
void IPADDRESS (char IPv4[]);
int GivePort(int n);
int ConnectToSockets(int *sClient,char ip[],int Port,int *ret_fct);
void Chat(int sClient,int ret_fct);
int menu();
int login(int sClient);
int upload(int sock,char UserName[],int SizeofN);
int Download(int sock);
int ShowUserFiles(int sock,char FolderName[], int SizeofN);
int NormalDownload(int sock,char FolderName[],int SizeofN);
#endif 

