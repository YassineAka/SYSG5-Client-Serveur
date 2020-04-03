#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define PORT 5990

int NbLinesInHistory(){
	FILE *fp; 
	int count = 0;  // Line counter (result) 
	char c;
	fp = fopen("history.txt", "r"); 
  
	// Check if file exists 
	if (fp == NULL) 
	{ 
	perror("Open of history"); 
	return 0; 
	} 

	// Extract characters from file and store in character c 
	for (c = getc(fp); c != EOF; c = getc(fp)) 
	if (c == '\n') // Increment count if this character is newline 
	count = count + 1; 

	// Close the file 
	fclose(fp); 
	return count;
}

int getLastLinesInHistory(){
	char tmp[1024];
	FILE * fp;
	fp = fopen("history.txt", "r");

	while(!feof(fp))
	    fgets(tmp, 1024, fp);

	printf("Fyn A fDP C'EST LAAAAAAAAAAAAAAAAAAAAAAAA DERNIÈRE LIGNE\n%s", tmp);
	char * strToken = strtok (tmp," ");
	int * x;
	sscanf(strToken, "%d", &x);
	return x;

    	
}


int main(int argc, char * argv[]){
	if(argc != 2){
		printf("Do not forget to enter the addres !\n");
		exit(0);
	}
	int clientSocket, ret,t,b;
	struct sockaddr_in serverAddr;
	struct in_addr adresse;
	char buffer[1024];
	clientSocket = socket(PF_INET, SOCK_STREAM, 0);
	if(clientSocket < 0){
		perror("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Client Socket is created.\n");
	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	if(!inet_aton(argv[1],&adresse)){
		perror("[-]Error in INET_ATON");
		exit(1);
	}
	serverAddr.sin_addr = adresse;

	ret = connect(clientSocket, &serverAddr, sizeof(serverAddr));
	if(ret == -1){
		perror("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Connected to Server.\n");

	while(1){
		printf("\nQue voulez-vous faire?\n");
		printf("\t:history\t pour upload votre historique\n");
		printf("\t:exit\t \t pour se déconnecter \n");
		printf("Client: \t");
		scanf("%s", &buffer);
		send(clientSocket, buffer, strlen(buffer), 0);
		if (strcmp(buffer,":history") == 0){
			//send(clientSocket, buffer, strlen(buffer), 0);
			FILE* f= fopen("history.txt","r+"); 				// Ouvrir le fichier local en mode lecture	
			char v; 							// Variable d'envoi
		 	
			do
			{	
			v=fgetc(f);
			t=send(clientSocket,(const char*)&v,sizeof(v),0);		// Envoyer le caractère
			}while(v!=EOF); 						// Reboucler si on n'atteint toujours pas la fin du fichier
			close(f);							// Fermer le fichier
			printf("(Historique envoyé)\n");
			
			////////////////////////////////////////////////////////////////////////////////////////////////////////////
			
		}
		if(strcmp(buffer, ":exit") == 0){
			close(clientSocket);
			printf("[-]Disconnected from server.\n");
			exit(1);
		}

		if(recv(clientSocket, buffer, 1024, 0) < 0){
			perror("[-]Error in receiving data.\n");
		}else{
			if(strlen(buffer) < 100){					
				printf("Server: \t%s\n", buffer);
			}
			
		}
		memset(buffer, 0, sizeof(buffer));
	}

	return 0;
}
