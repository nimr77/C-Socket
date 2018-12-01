
#include "StartServer.h"

//-------------------------------------------------------------------------------------------------------------------
int Download(int sock);
int Upload (int sock);
int ShowUserFiles (int sock);
int NormalDownlaod(int sock);
void *connection_handler(void *socket_desc)
{
	int sock = *(int*)socket_desc;
	int read_size,RES;
    int X1 =0,V=0,OP,R=0;
	char *message , client_message[2000];
    userList *L3;
    int ROP;
    char USERSFOLDER[2500];
    int pid2 = fork();
    int KeepMeIn,CUT=1;
    
L3 = LoadingWithoutOutPut ("UsersData.dat","NAME:","PASS:","USERFIRSTNAME:","USERLASTNAME:","USERID:","USERVARIFICTION:",L3);
    
   strcpy(USERSFOLDER,"Users"); 
    RES = mkdir(USERSFOLDER, 0777); 
    
//First PID FOR Login and Oprations 
    
    if(pid2 == 0){
	//*************************************Login******************************************//
    
	//Receive a message from client
	if( (read_size = recv(sock , client_message , 2000 , 0)) > 0 )
	{
        //printf("User In \n");
        
        //---------------------------------------------------------Looking For user
        while(L3!=NULL){
            if(0==strncmp(L3->name,client_message,strlen(L3->name))){
                X1 = 1;
                break;
            }
            L3 = L3->next;
        }
        if(X1==0){
           // puts("Client out ---> disconnected");
            fflush(stdout);
            //read_size = 0;
        }
		//Send the message back to client
		write(sock , &X1 , sizeof(X1));
        X1 = 0;
        //------------------------------------------------------CHACKING PASS
    if((read_size = recv(sock , client_message , 2000 , 0)) > 0){
        if(0==strncmp(L3->pass,client_message,strlen(L3->pass))){
                X1 = 1;
            }
    }
        if(read_size == 0)
	{
		//puts("Client disconnected");
		fflush(stdout);
       // break;
    }
         write(sock , &X1 , sizeof(X1));
    //----------------------------------------------------------SENDING VALIDATION
        if(X1==1){
            /*To change from char to int */
          V = Vtoi(L3->V,strlen(L3->V));
           write(sock , &(V), sizeof(V));
            if(V==0){
           // puts("Client out ---> disconnected");
            fflush(stdout);
            //read_size = 0;
            }
        }else{
            //puts("Client out ---> disconnected");
            fflush(stdout);
            read_size = 0;
          //  break;
        }
        X1 = 0;
        if(read_size == -1){
        perror("recv failed");
        }
       // X1 = 0;
  }
    //*******************************************/Oprations/**********************************************/
while (CUT = recv(sock , &KeepMeIn, sizeof(KeepMeIn), 0) > 0){
            
   if( recv(sock , &OP, sizeof(OP), 0) < 0)
		{
			puts("recv failed");
		}
    
   //printf("%d",OP);
    /**********************************************Upload*************************************************/
    
    if(OP==1){
        Upload(sock);

    }
    /**********************************************DOWNLOAD***********************************************/
    
    if(OP==2){
        //printf("dawnload");
        Download(sock);

    }
    //*****************************************Normal Download**************************************//
    if(OP == 3){
        NormalDownload(sock);
    }
    //*****************************************SHOW MY FILES***************************************//
    if(OP == 4){
        ShowUserFiles(sock);
    }
    }
       // kill(pid,SIGKILL);
    } 
    //KILL THIS ZOMBIE
    if(CUT == 0){
        return 0;
    }
    
/*********************************************NEW USERs******************************************/
    if(pid2 != 0){
	if(read_size == 0)
	{
		//puts("Client disconnected");
		fflush(stdout);
	}
	else if(read_size == -1)
	{
		perror("recv failed");
	}
		
	//Free the socket pointer
	free(socket_desc);

	return 0;
}
}
//-------------------------------------------------------------------------------------------------------------------
int Download (int sock ){
    
    DIR *d;
    DIR *D;
    struct dirent *dir,*dirr;
    char *AllUsers,*AllFiles,*TextFile;
    int AllUsersNum=0,Filesnbr=0,FT = 0,k=0;
    int tall;
    char UserFolderName[40];
    char FDir[100];
    char FolderName[40];
    char FolderAddress[200];
    char rc;
    FILE *DF;
    int read_size;
    int R=0;
    
    
        d = opendir("Users");
        if(d){
            //printf("dawnload");
            while((dir = readdir(d)) != NULL){
                
                AllUsersNum++;
              // printf("%s ",dir->d_name);

               // printf("%d", AllUsersNum);
            }closedir(d);
        }
            AllUsers = (char *)malloc(AllUsersNum * 40 * sizeof(char));
            d = opendir("Users");
            tall = AllUsersNum * 40 * sizeof(char);
            write(sock , &tall , sizeof(tall));
           // printf("%d",tall);
           
        
            if(d){
               // printf("test1");
               while((dirr = readdir(d)) != NULL){
                    strcat(AllUsers ,"\t");
                    strcat(AllUsers , dirr ->d_name);
                   // printf("test2");
                    //puts(AllUsers);
                }closedir(d);
            }
           // puts(AllUsers);
        
            //bzero(dir,sizeof(dir));
            write( sock , AllUsers , tall);
            
           if( (read_size = recv( sock , UserFolderName , 40, 0)) < 0){
           printf("ERROR WITH RECIVING Name");
           }
        strcpy(FDir,"Users/");
        strcat(FDir,UserFolderName);
         D = opendir(FDir);
       // puts(FDir);
        
         if(D){
             while((dir = readdir(D)) != NULL){
                 Filesnbr ++;
                // printf("%d",Filesnbr);
             }closedir(D);
             
             
         }
      //  bzero(dir,sizeof(dir));
        AllFiles = (char * )malloc(Filesnbr * 30 * sizeof(char));
        tall = Filesnbr * 30 * sizeof(char);
        write( sock , &tall , sizeof(tall));
        
        D = opendir(FDir);
        
         if(D){
             //printf("test3");
             while((dir = readdir(D)) != NULL){
                 //printf("test4");
                 strcat(AllFiles , "\t");
                 strcat(AllFiles , dir->d_name);
             }closedir(D);
         }
      //  bzero(dir,sizeof(dir));
       // puts(AllFiles);
        write( sock , AllFiles , tall);
        
         if( (read_size = recv( sock , FolderName , 40, 0)) < 0){
           printf("ERROR WITH RECIVING Name");
           }
        strcpy(FolderAddress,"Users/");
        strcat(FolderAddress,UserFolderName);
        strcat(FolderAddress,"/");
        strcat(FolderAddress,FolderName);
        DF = fopen(FolderAddress , "r");
       // puts(FolderAddress);
        if(DF == NULL){
            //free(socket_desc);
            return R;
        }
        
        while ((rc = getc(DF)) != EOF){
            FT++;
            
        }fclose(DF);
        
        TextFile = (char *)malloc(FT * sizeof(char));
        tall = FT * sizeof(char);
        
        write( sock , &tall , sizeof(tall));
        DF = fopen(FolderAddress , "r");
        
        while((rc = getc(DF)) != EOF){
            (*(TextFile + k)) = rc;
            k++;
        }
        write (sock , TextFile , FT);
        free(TextFile);
    R = 1;
    return R;
}
int Upload (int sock){
    
    int read_size,RES;
    int X1 =0,V=0,OP;
	char *message , client_message[2000];
    
    int R=0;
    char FileName[40];
    char FileDIR[1000];
    FILE *UF;
    char *FileText;
    int LongFileText;
    char USERSFOLDER[2500];
    
    
        if((read_size = recv(sock , client_message , 2000 , 0)) > 0){
            //Making the Dirtory
           
        }
       if( (read_size = recv( sock , FileName , 40, 0)) < 0){
           printf("ERROR WITH RECIVING FILE");
           }
        strcat(USERSFOLDER,"/");
        strcat(USERSFOLDER,client_message);
        strcat(USERSFOLDER,"/");
         RES = mkdir(USERSFOLDER, 0777);  
        strcat(USERSFOLDER,FileName);
        strcpy(FileDIR,USERSFOLDER);  
        //Making the File
        //puts(FileDIR);
       // puts(FileName);
       UF = fopen(FileDIR , "w+");
        
        //END Condution 
        if(UF==NULL){
            
            fflush(stdout);
           // free(socket_desc);
            return R;
        }
        
        //writing File
//First we will take the long of the Text , then we will creat the size of the dynamic array .
        if( (read_size = recv( sock , &LongFileText , sizeof(LongFileText), 0)) < 0){
           printf("ERROR WITH RECIVING FILE");
           }
        FileText = (char *)malloc(LongFileText*sizeof(char));
       if( (read_size = recv( sock , FileText , LongFileText, 0)) < 0){
           printf("ERROR WITH RECIVING FILE");
           }
        //Printing the Text
        fprintf(UF,"%s",FileText);
        fclose(UF);
        free(FileText);
    R = 1 ;
    return R;
    }    
int ShowUserFiles (int sock){
    
    DIR *D;
    struct dirent *dir;
    char *AllFiles;
    int AllUsersNum=0,Filesnbr=0;
    int tall;
    char FDir[100];
    char UserFolderName[400];
    int read_size;
    int R=0;
    printf("working");

   if( (read_size = recv( sock , UserFolderName , 400, 0)) < 0){
           printf("ERROR WITH RECIVING Name");
           }
    
    
       // puts(UserFolderName);
        strcpy(FDir,"Users/");
        strcat(FDir,UserFolderName);
        D = opendir(FDir);
    
         if(D){
             while((dir = readdir(D)) != NULL){
                 Filesnbr ++;
                //printf("%d",Filesnbr);
             }closedir(D);
             
             
         }
      //  bzero(dir,sizeof(dir));
        AllFiles = (char * )malloc(Filesnbr * 30 * sizeof(char));
        tall = Filesnbr * 30 * sizeof(char);
        write( sock , &tall , sizeof(tall));
        
        D = opendir(FDir);
        
         if(D){
             //printf("test3");
             while((dir = readdir(D)) != NULL){
                 //printf("test4");
                 strcat(AllFiles , "\t");
                 strcat(AllFiles , dir->d_name);
             }closedir(D);
         }
      //  bzero(dir,sizeof(dir));
       // puts(AllFiles);
        write( sock , AllFiles , tall);
       R = 1;
    
    return R;
}
int NormalDownload(int sock){
   
    DIR *D;
    struct dirent *dir;
    char *AllFiles,*TextFile;
    int Filesnbr=0,FT = 0,k=0;
    int tall;
    char UserFolderName[40];
    char FDir[100];
    char FolderName[40];
    char FolderAddress[200];
    char rc;
    FILE *DF;
    int read_size;
    int R=0;
    
            
           if( (read_size = recv( sock , UserFolderName , 40, 0)) < 0){
           printf("ERROR WITH RECIVING Name");
           }
        strcpy(FDir,"Users/");
        strcat(FDir,UserFolderName);
         D = opendir(FDir);
       // puts(FDir);
        
         if(D){
             while((dir = readdir(D)) != NULL){
                 Filesnbr ++;
                // printf("%d",Filesnbr);
             }closedir(D);
             
             
         }
      //  bzero(dir,sizeof(dir));
        AllFiles = (char * )malloc(Filesnbr * 30 * sizeof(char));
        tall = Filesnbr * 30 * sizeof(char);
        write( sock , &tall , sizeof(tall));
        
        D = opendir(FDir);
        
         if(D){
             //printf("test3");
             while((dir = readdir(D)) != NULL){
                 //printf("test4");
                 strcat(AllFiles , "\t");
                 strcat(AllFiles , dir->d_name);
             }closedir(D);
         }
      //  bzero(dir,sizeof(dir));
       // puts(AllFiles);
        write( sock , AllFiles , tall);
        
         if( (read_size = recv( sock , FolderName , 40, 0)) < 0){
           printf("ERROR WITH RECIVING Name");
           }
        strcpy(FolderAddress,"Users/");
        strcat(FolderAddress,UserFolderName);
        strcat(FolderAddress,"/");
        strcat(FolderAddress,FolderName);
        DF = fopen(FolderAddress , "r");
       // puts(FolderAddress);
        if(DF == NULL){
            //free(socket_desc);
            return R;
        }
        
        while ((rc = getc(DF)) != EOF){
            FT++;
            
        }fclose(DF);
        
        TextFile = (char *)malloc(FT * sizeof(char));
        tall = FT * sizeof(char);
        
        write( sock , &tall , sizeof(tall));
        DF = fopen(FolderAddress , "r");
        
        while((rc = getc(DF)) != EOF){
            (*(TextFile + k)) = rc;
            k++;
        }
        write (sock , TextFile , FT);
        free(TextFile);
    R = 1;
    return R;
    
    
}
//------------------------------------------------------------------------------------------------------------


void afficheErrorSortie(char *nomFct) {
     printf("\n %s -> %s ", nomFct, strerror(errno));
     exit(1);
} 

//---------------------------------------------------------------------------------------------------------------
userList *GiveInput(userList *head,int id ){
++id;
//userList *head = NULL;
userList *temp = NULL;
userList *p    = NULL;
int c;
int r;
char UserName[30];
temp = ((userList *)malloc(sizeof(userList)));
printf("New user Name :");
    
/*Chacking the New User Name*/
while(1){
    scanf("%s",((UserName)));
    r = CheckspaceName(UserName,strlen(UserName));
    if(r==0){
        continue ; 
    }
    c = checkUsername(UserName);
    if(c==1){
      strcpy(temp->name,UserName);
        break;
    }
    printf("UserName Exist!\n");
}

//gets((temp ->name));
printf("New user Password :");
scanf("%s",((temp ->pass)));
printf("New user first name :");
scanf("%s",((temp ->firstname)));
printf("New user last name :");
scanf("%s",((temp ->lastname)));
printf("New user Premation(0-Block,1-Normal User,2-Supper User:");
scanf("%s",((temp->V)));
printf("New user ID :");
sprintf((temp->id),"%d",id);
temp -> next=NULL;

if(head == NULL){
    head = temp;
}else{
    p = head;
    while(p->next){
    p = p->next;
    }
    p->next = temp;
}
  return head;
}

//--------------------------------------------------------------------------------------------------------------
bool MakingFile(char n[]){
FILE *File;
if(File = fopen(n,"a")){
fclose(File);
    return true;
}
return false;
}
void ToStock(char tt[],char t[]){
FILE *F;
printf("opening.....");
F = fopen(tt,"a");
printf("writing.....");
fprintf(F,"%s",t);
fclose(F);
}
//--------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
void MakingNewUser(userList *HEAD,int r){
char text[150];
printf("Making New User\n");
HEAD = GiveInput(HEAD,r);
printf("Making New User File with name UsersData.dat....");
if(MakingFile("UsersData.dat")){
printf("Done\n");}else{
    printf("false");
}  
printf("Puting user Info....");
TAXTIG(HEAD,text);
ToStock("UsersData.dat",text);printf("Done\n");
}
//--------------------------------------------------------------------------------------------------------------
void TAXTIG(userList *HEAD,char text[]){
strcpy(text," NAME:");
strcat(text,HEAD->name);
strcat(text," PASS:");
strcat(text,HEAD->pass);
strcat(text," USERFIRSTNAME:");
strcat(text,HEAD->firstname);
strcat(text," USERLASTNAME:");
strcat(text,HEAD->lastname);
strcat(text," USERID:");
strcat(text,HEAD->id);
strcat(text," USERVARIFICTION:");
strcat(text,HEAD->V);
strcat(text," \n");
}
//--------------------------------------------------------------------------------------------------------------
int listeningMode(int *sServeur,int *sClient){
struct sockaddr_in addrServeur,addrSocket;
struct timeval tmp={0, 500000};
/* Pour gérer la liste des descripteurs à surveiller */
fd_set ensemble;
int flags;
int longAddr,ret_fct,longMessage=TAILLEMESSAGE;
char msg[TAILLEMESSAGE+1];
	ret_fct=listen(*sServeur,NBRECON);
	if(ret_fct==ERROR){ afficheErrorSortie("listen()");  exit(1);}

	longAddr=sizeof(struct sockaddr_in);
	*sClient=accept(*sServeur,(struct sockaddr *)&addrSocket,&longAddr);
	if(*sClient==ERROR){ afficheErrorSortie("accept()");  exit(1);}
	printf("\nConnexion ...");
	//aff_addr(addrSocket);

    /*Le clavier et non bloquant */
	flags = fcntl(STDIN_FILENO,F_GETFL,0);
    fcntl(STDIN_FILENO,F_SETFL,flags | O_NONBLOCK);
    return ret_fct;


}
//---------------------------------------------------------------------------------------------------------------
void CLOSE(int *sServeur,int *sClient){
close(*sServeur);
close(*sClient);

}
//---------------------------------------------------------------------------------------------------------------

int menu(){
int c;
printf("\n           Menu\n");
printf("1------------adding new user\n");
printf("2------------Show All Users\n");
printf("3------------Edit Premition\n");
printf("4------------Edit User\n");
printf("5------------Delete User\n");
printf("6------------Reset List from Data Base\n");
printf("7------------Show Data Base\n");
printf("8------------Refrich Data Base\n");
printf("9------------Devaloppers\n");
printf("0------------exit\n");
printf("Order:");
scanf("%d",&c);

return c;
}
//----------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
userList * Loading(char NameFile[],char indixn[],char indixp[],char indixfn[],char indixln[],char indixd[],char indixv[],int *R,userList *L){

char t[30];
int i,j,k,r,l,w;
long int m;
char *Word;
char C;
long int res;
    
userList *temp = NULL;
userList *p    = NULL;
    
i=0;j=0;k=1;r=0,m=0,l=0,w=0;
    
FILE * F;
F = fopen(NameFile, "r");
Word = (char*)malloc(30*sizeof(char));
temp = ((userList *)malloc(sizeof(userList)));

L=NULL;
fseek(F, 0L, SEEK_END); 
res= ftell(F);
printf("loading %ld bit....\n",res);
F = fopen(NameFile, "r");
    
while ((C = getc(F)) != EOF )
{//printf("%c",C);
//----------------------------LOADING 

    {
        
    
//----------------------------LOADING UserName
if(C == indixn[i]){
i++;//printf("%c",(C));
(*(Word+j))=C;
//printf("%d",i);
j++;
}
if(isspace(C)){
i=0;j=0;l=0;
}
if ((strncmp(Word,indixn,strlen(indixn))==0)){
  //printf("Scaning Name\n");
    if(0==isspace(C)&l!=0){
    ((temp ->name[w])) = C;//printf("%c",(temp ->name[j]));
    w++;
    }
    l++;
    if(isspace(C)){
    bzero(Word,sizeof(Word));
    w=0;l=0;
    }
}
//----------------------------LOADING UserPass
if(C == indixp[i]){
i++;
(*(Word+j))=C;
j++;
}
if(isspace(C)){
i=0;j=0;l=0;w=0;
}
if ((k = strncmp(Word,indixp,strlen(indixp)))==0){
  //printf("Scaning Pass\n");
    if(0==isspace(C)&l!=0){
    ((temp ->pass[w])) = C;
    w++;
    }
    l++;
    if(isspace(C)){
    bzero(Word,sizeof(Word));
    l=0;w=0;
    }
}

//----------------------------LOADING User First Name
if(C == indixfn[i]){
i++;//printf("%c",(C));
(*(Word+j))=C;
j++;
}
if(isspace(C)){
i=0;j=0;l=0;w=0;
}
if ((k = strncmp(Word,indixfn,strlen(indixfn)))==0){
  //printf("Scaning Name\n");
    if(0==isspace(C)&l!=0){
    ((temp ->firstname[w])) = C;//printf("%c",(temp ->firstname[w]));
    w++;
    }
    l++;
    if(isspace(C)){
    bzero(Word,sizeof(Word));
    w=0;l=0;
    }
}

//----------------------------LOADING User Last Name
if(C == indixln[i]){
i++;//printf("%c",(C));
(*(Word+j))=C;
j++;
}
if(isspace(C)){
i=0;j=0;l=0;w=0;
}
if ((k = strncmp(Word,indixln,strlen(indixln)))==0){
  //printf("Scaning Name\n");
    if(0==isspace(C)&l!=0){
    ((temp ->lastname[w])) = C;//printf("%c",(temp ->name[j]));
    w++;
    }
    l++;
    if(isspace(C)){
    bzero(Word,sizeof(Word));
    w=0;l=0;
    }
}

//----------------------------LOADING ID
if(C == indixd[i]){
i++;
(*(Word+j))=C;
j++;
}
if(isspace(C)){
i=0;j=0;l=0;w=0;
}
if ((k = strncmp(Word,indixd,strlen(indixd)))==0){

    if(0==isspace(C)&l!=0){
    
    ((temp ->id[w])) = C;
    w++;
    }
    l++;
    if(isspace(C)){
    bzero(Word,sizeof(Word));
    w=0;l=0;
    }
}
//----------------------------LOADING UserValdition
if(C == indixv[i]){
i++;
(*(Word+j))=C;
j++;
}
if(isspace(C)){
i=0;j=0;l=0;
//printf("%c\n",(C));
}
if ((k = strncmp(Word,indixv,strlen(indixv)))==0){

    
    if(0==isspace(C)&l!=0){
     ((temp ->V[w])) = C;
    w++;
    }
    l++;
    if(isspace(C)|| C == '\n'){
    bzero(Word,sizeof(Word));
     w=0;l=0;
    }
}
    }
//----------------------------LOADING Next User
if(C=='\n'){
temp->next = NULL; 
r++;
//printf("adding new user \n");
if(L == NULL){
//printf("making nexst\n");
L = temp;
}
//ShowUsers(L);
else{

p = L;
while(p->next != NULL){
p = p->next;
}
p->next = temp;
}
temp = ((userList *)malloc(sizeof(userList)));
}
m++;
}
//----------------------------Saving LIST
printf("Number of users is %d \n",r);
*R = r;
free(Word);
free(temp);
fclose(F);
return L;
}
//----------------------------------------------------------------------------------------------------------------
void ShowUsers(userList *L){
userList *tmp=L;
while (tmp != NULL){
printf(" UserName :");printer(tmp->name,strlen(tmp->name));
printf(" UserPass :");printer(tmp->pass,strlen(tmp->pass));
printf(" User First Name :");printer(tmp->firstname,strlen(tmp->firstname));
printf(" User last Name :");printer(tmp->lastname,strlen(tmp->lastname));
printf(" UserID :");printer(tmp->id,strlen(tmp->id));
printf(" UserPremation :");printer(tmp->V,strlen(tmp->V));
printf("\n\t------------------------------------------------------------------------------------------\n");
tmp=tmp->next;

}
}
//------------------------------------------------------------------------------------------------------------
void changePR(userList *L){
char id[4];
char VV[4];
userList *tmp=L;
printf("UserID:");
scanf("%s",(id));
printf("Looking For User with ID:%s\n",id);
while (tmp != NULL){
    
if(strncmp(tmp->id,id,strlen(tmp->id))==0){
printf("new premation :");
scanf("%s",(VV));
strcpy(tmp->V,VV);
printf("\n");
break;
}
    
tmp=tmp->next;
}
}
//------------------------------------------------------------------------------------------------------------
void printer(char TP[],int n){
int i;
i=0;
while(i<=n){
printf("%c",TP[i]);
i++;
}
}
//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
int removeUser(userList ** head) {
    int i = 0;
    int retval = -1;
    char id[4];
    userList * current = *head;
    userList* temp_node = NULL;
    printf("UserID to remove :");
    scanf("%s",id);

    while(current != NULL){
        if(strncmp(current->id,id,strlen(current->id)) == 0){
                temp_node = current->next;
                current->next = temp_node->next;
                free(temp_node);
            retval = 1;
            break;
        }   
        current = current -> next;
    }
    return retval;

}

//------------------------------------------------------------------------------------------------------------

void showDataBase(char NameDB[]){
FILE *F;
char c;
F = fopen(NameDB,"r");
while ((c= getc(F)) != EOF){
printf("%c",c);
}
fclose(F);
}
//------------------------------------------------------------------------------------------------------------
void TheDEV(){

printf("1--Name: Nimr Sawafta     -The Developer\n");
printf("2--Name: Khalid ELSarbout -Reacher \n");
printf("3--Name: Abd ElRahman     -Sapport \n");
printf("4--Name: Youniss AlAfia   -Writter \n");

}
//-------------------------------------------------------------------------------------------------------------------
void RefrichDataBase(userList *L){
    
    char text [100];
    userList *tmp;
    FILE *F;
    //-----------------------------reset FILE
    printf("Resiting Data Base....... ");
    F = fopen("UsersData.dat","w");
    fclose(F);
    
    tmp = L;
    //----------------------------UP Date File
    printf("Up date Data ....... ");
    while(tmp != NULL){
       TAXTIG(tmp,text);
       ToStock("UsersData.dat",text);
        tmp = tmp->next;
    }


    printf("Done\n");
}
//------------------------------------------------------------------------------------------------------------
void EditUser(userList *L){
    
    char id[30],Edit[30];
    int c,X1=0;
    userList *tmp;
    
    printf("UserID:");
    scanf("%s",id);
    
    tmp = L;
    
    while(tmp!=NULL){
        
        if(0==(strncmp(tmp->id,id,strlen(tmp->id)))){
            printf("ID Accepted");
            X1=1;
        }
        
        while(X1==1){
            //----------------------------------------------EDIT MENU
            printf("               EDIT MENU:\n");
            printf("1--------------UserName\n");
            printf("2--------------Password\n");
            printf("3--------------First Name\n");
            printf("4--------------Last Name\n");
            printf("0--------------Exit\n");
            printf("Order:");
            scanf("%d",&c);
            
            switch(c){
                    
                case 1:{
                    printf("New Name:");
                    scanf("%s",Edit);
                    strcpy(tmp->name,Edit);
                    bzero(Edit,sizeof(Edit));
                    break;
                }
                case 2:{
                    printf("New Password:");
                    scanf("%s",Edit);
                    strcpy(tmp->pass,Edit);
                    bzero(Edit,sizeof(Edit));
                    break;
                }
                case 3:{
                    printf("New First Name:");
                    scanf("%s",Edit);
                    strcpy(tmp->firstname,Edit);
                    bzero(Edit,sizeof(Edit));
                    break;
                }    
                case 4:{
                    printf("New Last Name:");
                    scanf("%s",Edit);
                    strcpy(tmp->lastname,Edit);
                    bzero(Edit,sizeof(Edit));
                    break;
                }  
                case 0:{
                    printf("Exit!\n");
                    X1=2;
                    break;
                }
            }
            
            //------------------------------------------------EDIT CONTROL
            if(X1==2){
                break;
            }
            
        }
        tmp = tmp->next;
    }
    //---------------------------------------------Saving
    RefrichDataBase(L);

}
//-----------------------------------------------------------------------------------------------------
int Vtoi(char Text[],int n){
    int i;
    int r;
    for(i=0;i<=n;i++){
        if(Text[i]=='0'){
            r=0;
        }  
        if(Text[i]=='1'){
            r=1;
        }
        if(Text[i]=='2'){
            r=2;
        }
    }
}
//---------------------------------------------------------------------------------------------------
int checkUsername(char NewT[]){
    int r = 1;
    userList *tmp;
tmp = LoadingWithoutOutPut ("UsersData.dat","NAME:","PASS:","USERFIRSTNAME:","USERLASTNAME:","USERID:","USERVARIFICTION:",tmp);
    
    while (tmp!=NULL){
        if(0==strncmp(tmp->name,NewT,strlen(tmp->name))){
            r =0;
        }
        tmp = tmp->next;
    }
    free(tmp);
    return r;
}
//--------------------------------------------------------------------------------------------------
int CheckspaceName(char T[],int n){
    
    int r = 1;
    int i = 0;
    while ( i <=n){
        if((T[i])==' '){
            r = 0;
            printf("Must not contain a Space !");
            break;
        }
        i++;
    }
    return r;
}
//---------------------------------------------------------------------------------------------------
userList * LoadingWithoutOutPut(char NameFile[],char indixn[],char indixp[],char indixfn[],char indixln[],char indixd[],char indixv[],userList *L){

char t[30];
int i,j,k,r,l,w;
long int m;
char *Word;
char C;
    
userList *temp = NULL;
userList *p    = NULL;
    
i=0;j=0;k=1;r=0,m=0,l=0,w=0;
    
FILE * F2;
F2 = fopen(NameFile, "r");
Word = (char*)malloc(30*sizeof(char));
temp = ((userList *)malloc(sizeof(userList)));

L=NULL;
while ((C = getc(F2)) != EOF )
{//printf("%c",C);
//----------------------------LOADING 

    {
        
    
//----------------------------LOADING UserName
if(C == indixn[i]){
i++;//printf("%c",(C));
(*(Word+j))=C;
//printf("%d",i);
j++;
}
if(isspace(C)){
i=0;j=0;l=0;
}
if ((strncmp(Word,indixn,strlen(indixn))==0)){
  //printf("Scaning Name\n");
    if(0==isspace(C)&l!=0){
    ((temp ->name[w])) = C;//printf("%c",(temp ->name[j]));
    w++;
    }
    l++;
    if(isspace(C)){
    bzero(Word,sizeof(Word));
    w=0;l=0;
    }
}
//----------------------------LOADING UserPass
if(C == indixp[i]){
i++;
(*(Word+j))=C;
j++;
}
if(isspace(C)){
i=0;j=0;l=0;w=0;
}
if ((k = strncmp(Word,indixp,strlen(indixp)))==0){
  //printf("Scaning Pass\n");
    if(0==isspace(C)&l!=0){
    ((temp ->pass[w])) = C;
    w++;
    }
    l++;
    if(isspace(C)){
    bzero(Word,sizeof(Word));
    l=0;w=0;
    }
}

//----------------------------LOADING User First Name
if(C == indixfn[i]){
i++;//printf("%c",(C));
(*(Word+j))=C;
j++;
}
if(isspace(C)){
i=0;j=0;l=0;w=0;
}
if ((k = strncmp(Word,indixfn,strlen(indixfn)))==0){
  //printf("Scaning Name\n");
    if(0==isspace(C)&l!=0){
    ((temp ->firstname[w])) = C;//printf("%c",(temp ->firstname[w]));
    w++;
    }
    l++;
    if(isspace(C)){
    bzero(Word,sizeof(Word));
    w=0;l=0;
    }
}

//----------------------------LOADING User Last Name
if(C == indixln[i]){
i++;//printf("%c",(C));
(*(Word+j))=C;
j++;
}
if(isspace(C)){
i=0;j=0;l=0;w=0;
}
if ((k = strncmp(Word,indixln,strlen(indixln)))==0){
  //printf("Scaning Name\n");
    if(0==isspace(C)&l!=0){
    ((temp ->lastname[w])) = C;//printf("%c",(temp ->name[j]));
    w++;
    }
    l++;
    if(isspace(C)){
    bzero(Word,sizeof(Word));
    w=0;l=0;
    }
}

//----------------------------LOADING ID
if(C == indixd[i]){
i++;
(*(Word+j))=C;
j++;
}
if(isspace(C)){
i=0;j=0;l=0;w=0;
}
if ((k = strncmp(Word,indixd,strlen(indixd)))==0){

    if(0==isspace(C)&l!=0){
    
    ((temp ->id[w])) = C;
    w++;
    }
    l++;
    if(isspace(C)){
    bzero(Word,sizeof(Word));
    w=0;l=0;
    }
}
//----------------------------LOADING UserValdition
if(C == indixv[i]){
i++;
(*(Word+j))=C;
j++;
}
if(isspace(C)){
i=0;j=0;l=0;
//printf("%c\n",(C));
}
if ((k = strncmp(Word,indixv,strlen(indixv)))==0){

    
    if(0==isspace(C)&l!=0){
     ((temp ->V[w])) = C;
    w++;
    }
    l++;
    if(isspace(C)|| C == '\n'){
    bzero(Word,sizeof(Word));
     w=0;l=0;
    }
}
    }
//----------------------------LOADING Next User
if(C=='\n'){
temp->next = NULL; 
r++;
//printf("adding new user \n");
if(L == NULL){
//printf("making nexst\n");
L = temp;
}
//ShowUsers(L);
else{

p = L;
while(p->next != NULL){
p = p->next;
}
p->next = temp;
}
temp = ((userList *)malloc(sizeof(userList)));
}
m++;
}
//----------------------------Saving LIST
free(Word);
free(temp);
fclose(F2);
return L;
}