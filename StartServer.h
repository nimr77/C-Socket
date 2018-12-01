
#ifndef StartServer_H
#define StartServer_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <fcntl.h>
#include <pthread.h> 
#include <arpa/inet.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <dirent.h>
#define ERROR 	(-1)
#define TAILLEMESSAGE 256
#define NBRECON 10
#define PORT 9988


typedef struct userList
{
char  id[30];
char pass[30];
char name[30];
char firstname[30];
char lastname[30];
char  V[30];

struct userList *next;
}userList;

typedef struct userinfo
{
char INFO[50];
struct userinfo *next;
}userinfo;

//--------------------------------------------------------------------------------------------------------------
void TheDEV();
//--------------------------------------------------------------------------------------------------------------
userList *GiveInput(userList *head,int id );
bool MakingFile();
void ToStock(char tt[],char t[]);
userList *GiveID(int id,userList *L);
userList *Validation(int n,userList *L);
void MakingNewUser(userList *HEAD,int R);
int listeningMode(int *sServeur,int *sClient);
int menu();
int checkUsername(char NewT[]);
int Vtoi(char Text[],int n);
void CLOSE(int *sServeur,int *sClient);
//--------------------------------------------------------------------------------------------------------------
userList * Loading(char NameFile[],char indixn[],char indixp[],char indixfn[],char indixln[],char indixd[],char indixv[],int *R,userList *L);
void ShowUsers(userList *L);
void changePR(userList *L);
void printer(char TP[],int n);
int removeUser(userList ** head);
void showDataBase(char NameDB[]);
void RefrichDataBase(userList *L);
void EditUser(userList *L);
void TAXTIG(userList *HEAD,char text[]);
int CheckspaceName(char T[],int n);
userList * LoadingWithoutOutPut(char NameFile[],char indixn[],char indixp[],char indixfn[],char indixln[],char indixd[],char indixv[],userList *L);
//--------------------------------------------------------------------------------------------------------------
//Note about your data ip , put it in a database so you can call it from a list when a connection is of remove its ip,creat new procser for NON Connect anyMore,do the Dawnload and Upload first 
//---------------------------------------------------------------------------------------------------------------

void aff_addr(struct sockaddr_in addr);
void afficheErrorSortie(char *nomFct);
void *connection_handler(void *socket_desc);
int Download (int sock );
int Upload (int sock);
int ShowUserFiles (int sock);
int NormalDownload(int sock);
#endif
