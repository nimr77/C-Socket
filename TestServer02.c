#include "StartServer.h"

int main(int argc,char *argv[]){
int flags;
        int r;
        int R=0;
        int c,i,nbrcon=0;
        int A;
        int pid =fork();
        int socket_desc , client_sock , C , *new_sock;
        struct sockaddr_in server , client;
        userList *L;
        userList *L2=NULL;
    ///Here we are loading the data from a simple database file, its better to make it JSON, or CSV 
L = Loading("UsersData.dat","NAME:","PASS:","USERFIRSTNAME:","USERLASTNAME:","USERID:","USERVARIFICTION:",&R,L);
/*******************************1PID*******************************/
    if(pid == 0){
	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}
	puts("Socket created");
	
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( 9988 );
	
	//Bind
	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		//print the error message
		perror("bind failed. Error");
		return 1;
	}
	puts("bind done");
	
	//Listen
	listen(socket_desc , 3);
	
	//Accept and incoming connection
	//puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);
	
	
	//Accept and incoming connection
	//puts("Waiting for incoming connections...");
//	c = sizeof(struct sockaddr_in);
	while( (client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&C)) )
	{
		//puts("Connection accepted");
		
		pthread_t sniffer_thread;
		new_sock = malloc(1);
		*new_sock = client_sock;
		nbrcon++;
	//	printf("\n User Number %d \n Order:",nbrcon);
		if(pthread_create( &sniffer_thread , NULL ,  connection_handler , (void*) new_sock) < 0)
		{
			perror("could not create thread");
			return 1;
		}
		
		//Now join the thread , so that we dont terminate before the thread
		pthread_join( sniffer_thread , NULL);
		//puts("Handler assigned");
	}
	
	if (client_sock < 0)
	{
		perror("accept failed");
		return 1;
	}
	}//if(pid != 0){
	
/*******************************2PID*******************************/
while(pid != 0){
c = menu();

switch (c){

case 1:{
MakingNewUser(L2,R);
L = Loading("UsersData.dat","NAME:","PASS:","USERFIRSTNAME:","USERLASTNAME:","USERID:","USERVARIFICTION:",&R,L);

break;
}
case 2:{
ShowUsers(L);
break;
}
case 3:{
changePR(L);
break;
}
case 4:{
EditUser(L);
break;
}
case 5:{
//r = startServer(&sClient,&sServer,PORT);
removeUser(&L);
//r=Login(&sClient,&sServer);
break;
}
case 6:{
L = Loading("UsersData.dat","NAME:","PASS:","USERFIRSTNAME:","USERLASTNAME:","USERID:","USERVARIFICTION:",&R,L);
break;
}
case 7:{
showDataBase("UsersData.dat");
break;
}
case 8:{
RefrichDataBase(L);
break;
}
case 9:{
TheDEV();
break;
}
case 0:{
CLOSE(&socket_desc,&client_sock);
kill(pid,SIGKILL);
return 0;
} 
       flags = fcntl(client_sock,F_GETFL,0);
    fcntl(client_sock,F_SETFL,flags | O_NONBLOCK);
    
    
	flags = fcntl(STDIN_FILENO,F_GETFL,0);
    fcntl(STDIN_FILENO,F_SETFL,flags | O_NONBLOCK);
}
}
//}
//if(PC != 0){

//}
kill(pid,SIGKILL);
CLOSE(&socket_desc,&client_sock);
return 0;
}
//}
