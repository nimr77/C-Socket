#include "CONNECTINGTO.h"

int ConnectToSockets(int *sClient,char ip[],int Port,int *ret_fct){
     int c;
     struct sockaddr_in  addrServeur;
     int longMessage;

	 /* Pour gérer la liste des descripteurs à surveiller */
     fd_set ensemble;
     int flags;

      printf("resiving Data From User....");
	 /* Création du socket client */
     (*sClient)=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
     if (*(sClient)==ERROR){ afficheErrorSortie("socket()");  exit(1);}

	 /* Infos serveur */
     addrServeur.sin_family = AF_INET;
     addrServeur.sin_port   = htons(PORT);

	 /* Pour tester l'application avec un serveur sur une machine en réseau
	    il faut mettre l'adresse ip du serveur ici */
     addrServeur.sin_addr.s_addr=inet_addr(ip);
     printf("Connection....");
     /* connection +  gestion d'erreur */
     *ret_fct=connect(*sClient,(struct sockaddr*)&addrServeur,sizeof(struct sockaddr));
     if(ret_fct==ERROR){return (c=0);}

        
        flags = fcntl(sClient,F_GETFL,0);
    fcntl(sClient,F_SETFL,flags | O_NONBLOCK);
	 /* Le clavier et non bloquant */
     flags = fcntl(STDIN_FILENO,F_GETFL,0);
     fcntl(STDIN_FILENO,F_SETFL,flags | O_NONBLOCK);
     printf("done \n");
     return (c=1);
}
//-----------------------------------------------------------------------------------------------------------
void Chat(int sClient,int ret_fct){
int flags;
int longMessage;
fd_set ensemble;
char msg[TAILLEMESSAGE+1];
struct timeval tmp={0, 500000};
printf("starting chat with the Server..\n");
     flags = fcntl(STDIN_FILENO,F_GETFL,0);
     fcntl(STDIN_FILENO,F_SETFL,flags | O_NONBLOCK);
       while(1){
       
		     /* Ici select surveille en lecture le socket de dialogue uniquement */
	     FD_ZERO(&ensemble);
             FD_SET(sClient,&ensemble);

             ret_fct = select((sClient)+1,&ensemble,NULL,NULL,&tmp);
             if(ret_fct==ERROR)
                  afficheErrorSortie("select()");
             else{
                if(FD_ISSET(sClient,&ensemble)){

                	longMessage=read(sClient,msg,TAILLEMESSAGE+1);
                	printf("\nMessage --> %s  (%d octets) \n",msg,longMessage);
                    if(!strcmp(msg,"q") || !strcmp(msg,"Q")) break;
                 }
                 if(gets(msg)){ /* La fonction gets retourne NULL si aucune chaine de caractères n'est saisie */
					printf("\nTapez du texte : ");
					write(sClient,msg,strlen(msg)+1);

                    if(!strcmp(msg,"q") || !strcmp(msg,"Q")) break;

                 }
           }

    }




}
//-------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------
void afficheErrorSortie(char *nomFct) {
     printf("\n %s -> %s ", nomFct, strerror(errno));
     exit(1);
}
//-------------------------------------------------------------------------------------------------------------
void IPADDRESS(char IPv4[]){
//printf("give me your address in which is like 000.000.000.000 :");
//gets(IPv4);
//printf("done \n");
printf("Getting the IP of the HOST....");
char hostbuffer[256];
char *ipbuffer;
struct hostent *host_entry;
int hostname;
hostname = gethostname(hostbuffer,sizeof(hostbuffer));
host_entry = gethostbyname(hostbuffer);
ipbuffer = inet_ntoa(*((struct in_addr *)host_entry->h_addr_list[0]));
printf("done \n");
printf("host IP : %s \n",ipbuffer);
strcpy(IPv4,ipbuffer);
}
//-------------------------------------------------------------------------------------------------------------
int GivePort(int n){
int Port = n;
printf("Port : %d \n",Port);
//scanf("%d",&Port);
//printf("done \n");
return Port;
}
//-------------------------------------------------------------------------------------------------------------
int menu(){
int c;
printf("\n           Menu\n");
printf("1------------Upload\n");
printf("2------------Dawnload As Admin\n");
printf("3------------Normal Dawnload\n");
printf("4------------Show My Data\n");
printf("0------------exit\n");
printf("Order:");
scanf("%d",&c);

return c;
}

//--------------------------------------------------------------------------------------------------------------
int login(sClient){
    
int r=0,A=0,B=0;
char Name[30],PASS[30],buffer[100];
bzero(Name,sizeof(Name));
bzero(PASS,sizeof(PASS));
    
A = read(sClient,buffer,sizeof(buffer));
printf("%s",buffer);
bzero(buffer,sizeof(buffer));
A = read(sClient,buffer,sizeof(buffer));
printf("%s\n",buffer);
bzero(buffer,sizeof(buffer));

scanf("%s",Name);
printf("Sending Name...");

    
    
A = write(sClient,Name,strlen(Name));
A = read(sClient,&B,sizeof(B));
    
if(B==1){
printf("User Password :");
scanf("%s",PASS);
}
//A = write(sClient,PASS,strlen(PASS));
//A = read(sClient,&B,sizeof(B));
if(B==1){
r=1;
}else{
r=0;
}
return r;
}

/////////////////////////////////////////////////OP\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

int upload(int sock,char UserName[],int SizeofN){
    
    char LO[1000];
    char FileName[40];
    char c;
    FILE *F;
    char *FileText;
    int Stop=0,r=0;
    int cc=0;
    int i =0;
    int Size=0;
    /***************************To User Directorl***************************************/
    write( sock , UserName , SizeofN);
    /***************************Scaning the Address of the File ************************/
    printf("The Address Of your File:");
    scanf("%s",LO);
    F = fopen(LO,"r");
    fseek(F, 0L, SEEK_END); 
    Size= ftell(F);
    if(F==NULL){
        r = 0;
        printf("ERROR With Opening File ! \n");
        return r;
    }
    /************************************Scaning the FIle Name *****************************/
        printf("File Name:");
        scanf("%s",FileName);
    printf("Reading...%s ,%d bit\n",FileName,Size);
    //File Size
    if(Size>2097152){
        printf("Too Much Size cant Upload .... End Opration\n");
        return 0;
    }
    fclose(F);
    //Sending the File name
    if( (write( sock , FileName , strlen(FileName))) < 0){
        printf("ERROR WITH SENDING FILE");
    }
  //  puts(FileName);
    /************************************Scaning the FIle Text and Send it  *****************************/
    printf("Sending File....");
    F = fopen(LO,"r");
    while((c =getc(F))!=EOF){
        cc++;
        
    }
    fclose(F);
    FileText = (char *)malloc(cc*sizeof(char));
    F = fopen(LO,"r");
   // bzero(c,sizeof(c));
    while((c =getc(F))!=EOF){
        (*(FileText + i)) = c;
        i++;
       // printf("%c",c);
    }
    write( sock , &cc, sizeof(cc));
    write( sock , FileText, cc);
    printf("done\n");
    fclose(F);
    free(FileText);
    return r;
}
//-----------------------------------------------------
int Download(int sock){
    
    char FolderName[40];
    char FileName[50];
    char *UsersFolders,*UserFiles,*FileText;
    int FileLong,tall;
    FILE *F;
    int r=0;
    //reciving the Tail of the users List
    
    if(recv( sock , &tall , sizeof(tall),0)<0){
        printf("Error Receving \n");
        return 0 ;
    }
    
    //printf("%d",tall);
    UsersFolders = (char *)malloc(tall);
    
    if(recv( sock , UsersFolders , tall,0)<0){
        printf("Error Receving \n");
        return 0 ;
        
    }
    puts(UsersFolders);
    
    printf("\nUserName: ");
    scanf("%s",FolderName);
    write(sock , FolderName , 40);
    
    if(recv( sock , &tall , sizeof(tall),0)<0){
        printf("Error Receving \n");
        return 0 ;
        
    }
    
    UserFiles = (char *)malloc(tall);
    if(recv( sock , UserFiles , tall,0)<0){
        printf("Error Receving \n");
        return 0 ;
    }
    puts(UserFiles);
    printf("\nFileName: ");
    scanf("%s",FileName);
  if(  write(sock , FileName , 40) > 0){
    F = fopen(FileName,"w+");
  }
    if(recv( sock , &tall , sizeof(tall),0)<0){
        printf("Error Receving \n");
        return 0 ;
    }
    FileText = (char *)malloc(tall);
    
    
      if(recv( sock , FileText , tall,0)<0){
        printf("Error Receving \n");
        return 0 ;
    }
    
    fprintf(F ,"%s",FileText);
    
    
    free(FileText);
    free(UserFiles);
    free(UsersFolders);
    fclose(F);
    //Commante everything 
    return r;
}
//----------------------------------------------------
int ShowUserFiles(int sock,char FolderName[],int SizeofN){
    
    int tall;
    int r = 0;
    char *UserFiles;
    
   r =  write(sock , FolderName , SizeofN);
  
    puts(FolderName);
    // printf("%d\n",r);
    
   if(recv( sock , &tall , sizeof(tall),0)<0){
        printf("Error Receving \n");
        return 0 ;
        
    }
    //printf("%d",tall);
    UserFiles = (char *)malloc(tall);
    if(recv( sock , UserFiles , tall,0)<0){
        printf("Error Receving \n");
        return 0 ;
    }
    puts(UserFiles);
    
    
    return r ;
}
//----------------------------------------------------
int NormalDownload(int sock,char FolderName[],int SizeofN){
    
    char FileName[50];
    char *UserFiles,*FileText;
    int FileLong,tall;
    FILE *F;
    int r=0;
    //reciving the Tail of the users List
    
    write(sock , FolderName , SizeofN);
    
    if(recv( sock , &tall , sizeof(tall),0)<0){
        printf("Error Receving \n");
        return 0 ;
        
    }
    
    UserFiles = (char *)malloc(tall);
    if(recv( sock , UserFiles , tall,0)<0){
        printf("Error Receving \n");
        return 0 ;
    }
    puts(UserFiles);
    printf("\nFileName: ");
    scanf("%s",FileName);
  if(  write(sock , FileName , 40) > 0){
    F = fopen(FileName,"w+");
  }
    if(recv( sock , &tall , sizeof(tall),0)<0){
        printf("Error Receving \n");
        return 0 ;
    }
    FileText = (char *)malloc(tall);
    
    
      if(recv( sock , FileText , tall,0)<0){
        printf("Error Receving \n");
        return 0 ;
    }
    
    fprintf(F ,"%s",FileText);
    
    
    free(FileText);
    free(UserFiles);
    //free(UsersFolders);
    fclose(F);
    //Commante everything 
    return r;
    
}
