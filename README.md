# C Socket File Sending and Simple Auth model 

Download and send data with c languge 
`` `gcc -pthread StartServer02.c TestServer02.c ` ``for the server 
`` `gcc CONNECTTO.C TestClient02.c ` `` client

Note that its a mini Project for students 

This project is for sending text files and doing auth, with multi users 

And it is by using SOckets and TCP Modele

### About Lib

In StartServer02.c, it contains all the functions that we are using to handle the connection and threads in the server
beside the Auth, here we didn't use database or JSON file, we used a simple text file to store our data, 
this is part of C learning practise that I did.

In CONNECTTO. C, It contains all the functions for the client side, like giveing the right messages and downloading or uploading....

### About Loading from File

In StartServer02.c, there is a function called `` `loading(...)` `` This function is for loading the data from the database
```c 
userList * Loading(char NameFile[], char indixn[], char indixp[], char indixfn[], char indixln[], char indixd[], char indixv[], int *R, userList *L){

char t[30]; 
int i, j, k, r, l, w; 
long int m; 
char *Word; 
char C; 
long int res; 

    

userList *temp = NULL; 
userList *p    = NULL; 

    

i=0; j=0; k=1; r=0, m=0, l=0, w=0; 

    

FILE * F; 
F = fopen(NameFile, "r"); 
Word = (char*)malloc(30*sizeof(char)); 
temp = ((userList *)malloc(sizeof(userList))); 

L=NULL; 
fseek(F, 0L, SEEK_END); 
res= ftell(F); 
printf("loading %ld bit....\n", res); 
F = fopen(NameFile, "r"); 

    

while ((C = getc(F)) != EOF )
{//printf("%c", C); 
//----------------------------LOADING 

    {
        

    

//----------------------------LOADING UserName
if(C == indixn[i]){
i++; //printf("%c", (C)); 
(*(Word+j))=C; 
//printf("%d", i); 
j++; 
}
if(isspace(C)){
i=0; j=0; l=0; 
}
if ((strncmp(Word, indixn, strlen(indixn))==0)){
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
i=0; j=0; l=0; w=0; 
}
if ((k = strncmp(Word, indixp, strlen(indixp)))==0){
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
i++; //printf("%c", (C)); 
(*(Word+j))=C; 
j++; 
}
if(isspace(C)){
i=0; j=0; l=0; w=0; 
}
if ((k = strncmp(Word, indixfn, strlen(indixfn)))==0){
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
i++; //printf("%c", (C)); 
(*(Word+j))=C; 
j++; 
}
if(isspace(C)){
i=0; j=0; l=0; w=0; 
}
if ((k = strncmp(Word, indixln, strlen(indixln)))==0){
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
i=0; j=0; l=0; w=0; 
}
if ((k = strncmp(Word, indixd, strlen(indixd)))==0){

    if(0==isspace(C)&l!=0){

    

    ((temp ->id[w])) = C; 
    w++; 

    }

    l++; 
    if(isspace(C)){
    bzero(Word, sizeof(Word)); 
    w=0; l=0; 

    }

}
//----------------------------LOADING UserValdition
if(C == indixv[i]){
i++; 
(*(Word+j))=C; 
j++; 
}
if(isspace(C)){
i=0; j=0; l=0; 
//printf("%c\n", (C)); 
}
if ((k = strncmp(Word, indixv, strlen(indixv)))==0){

    

    if(0==isspace(C)&l!=0){
     ((temp ->V[w])) = C; 
    w++; 

    }

    l++; 
    if(isspace(C)|| C == '\n'){
    bzero(Word, sizeof(Word)); 
     w=0; l=0; 

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
printf("Number of users is %d \n", r); 
*R = r; 
free(Word); 
free(temp); 
fclose(F); 
return L; 
}

```
This is the hardest function to understand, it reads the data from the file, in line per line char per char, 
then it checks if it loaded the user, to pass to the next user, while doing that it will store the data into a List so we wont handle the file reading too much, this will require the admin of the server to save the data into the file each period of time, or after closing the server everything will be lost.

### About Uploading or Downlaoding a File

This is easy function it reads the data from the file and then send them, after that will read the file name and send it too.

```c 
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
```

Note that it require the socket only so it will know the socket that will recive the data or taking the data from, in the read and write.

### Other functions
The other function are C functions to handle the stracts and the threads in the server or the client. 