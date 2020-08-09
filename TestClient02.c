
#include "CONNECTINGTO.h"
//Here we start the main client connection with the server 
/*
first thing it will connect to the server via the port and the Ip address of the machine itself 
then it will ask for a user name and a password 
then it will load user's prevlage
if its allow to do stuff it will show the menu
*/
int main(){
    char ip[16],UserName[30];
    int Port;
    int ret_fct;
    int r=0;
    int l;
    int c;
    int OP , KeepMeIn = 1;
    IPADDRESS(ip);
    Port = GivePort(9988);
    
    int sock;
	struct sockaddr_in server;
	char message[1000] , server_reply[2000];
    int NP=0,CV;
	
	//Create socket
	sock = socket(AF_INET , SOCK_STREAM , 0);
	if (sock == -1)
	{
		printf("Could not create socket");
	}
	puts("Socket created");
	///Binding the server 
	server.sin_addr.s_addr = inet_addr(ip);
	server.sin_family = AF_INET;
	server.sin_port = htons( Port );

	//Connect to remote server
	if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		perror("connect failed. Error");
		return 1;
	}
    
	puts("Connected\n");
	//keep communicating with server 
    
	/*if( recv(sock , server_reply , 2000 , 0) < 0)
		{
			puts("recv failed");
		}*/
    
    /****************************************LOgin**************************/
		printf("UserName : ");
		scanf("%s" , message);
		
		//Send some data
		if( send(sock , message , strlen(message) , 0) < 0)
		{
			puts("Send failed");
			return 1;
		}
		
		//Receive a reply from the server
		if( recv(sock , &NP, sizeof(NP), 0) < 0)
		{
			puts("recv failed");
			return 0;
		}
        
        if(NP==1){
            printf("User Accepted\n");
            strcpy(UserName,message);
            printf("User Password:");
            bzero(message,strlen(message));
            
            scanf("%s", message);
              if( send(sock , message , strlen(message) , 0) < 0)
		          {
			puts("Send failed");
			return 0;
		     }
              
        //---------------------------------------Chacking Password    
    	if( recv(sock , &NP, sizeof(NP), 0) < 0)
		{
			puts("recv failed");
			return 0;
		}
        
        if(NP==1){
            printf("Password Correct\n");
            printf("Chacking Validation....");
            NP=0;
        
        //-----------------------------------------Chacking Validation  
    	if( recv(sock , &CV, sizeof(CV), 0) < 0)
		{
			puts("recv failed");
			return 0;
		}
        if(CV !=0){
            printf("Login Complated!");
            r = CV;
           // return 0;
            
        }else{
            close(sock);
            printf("User BLOCKED!!\n");
            return 0;
        }
        }
        }
		//printf("%d",NP);
   while (write ( sock , &KeepMeIn , sizeof(KeepMeIn))){
    if(r!=0){
    ///The menu, please note its better to take it from the server, and not using the functions as I made
    c = menu();
    switch (c){
    
    case 1:{
    write( sock , &c , sizeof(c));
    OP = upload( sock , UserName , strlen(UserName));
    break;
    }
    case 2:{
    if(r==1){
        printf("Unable to Download check the Admin\n");
        break;
    }
    write( sock , &c , sizeof(c));
    OP = Download( sock );
    break;
    }
    case 3:{
        write( sock , &c , sizeof(c));
        NormalDownload(sock , UserName , strlen(UserName));
        break;
    }
    case 4:{
        write( sock , &c , sizeof(c));
        ShowUserFiles(sock , UserName , strlen(UserName));
        break;
    }
    case 0:{
    close(sock);
    return 0;
    break;
    }
    
    }
    
    }
  }
    //Chat(sClient,ret_fct);
    //r=choise();
    //printf("%d \n",sClient);
    close(sock);
    return 0;
          }
