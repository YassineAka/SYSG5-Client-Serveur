#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>


int main(int argc, char * argv[]){
	if(argc != 2){
		printf("Do not forget to enter the addres !\n");
		exit(0);
	}
	int sockfd, ret, newSocket;
	struct sockaddr_in serverAddr;
	struct sockaddr_in newAddr;
	socklen_t addr_size;
	char uip [100];
	pid_t childpid;
	


	system("sudo -S rcSuSEfirewall2 stop"); //Désactivation du firewall

	sockfd = socket(PF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Server Socket is created.\n");

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(5990);
	if (! inet_aton(argv[1],&serverAddr.sin_addr.s_addr)){
		perror("[-]Error in INET_ATON");
		exit(1);
	}
	ret = bind(sockfd, &serverAddr, sizeof(serverAddr));
	if(ret < 0){
		perror("[-]Error in binding.\n");
		exit(1);
	}
	printf("[+]Bind to port %d\n", 5990);

	if(listen(sockfd, 10) == 0){
		printf("[+]Listening....\n");
	}else{
		printf("[-]Error in binding.\n");
	}

	
	while(1){
		newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);
		if(newSocket < 0){
			perror("Error on accepting");
			exit(1);
		}
		printf("Connection accepted from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));

		if((childpid = fork()) == 0){
			close(sockfd);

			while(1){
				int fd;
				int i, count_r, count_w;
				char* bufptr;
				char buffer[1024];
				char buf[1024];
				char filename[1024];
				recv(newSocket, buffer, 1024,0);
				if(strcmp(buffer, ":exit") == 0){
					printf("Disconnected from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
					break;
				}else if(strcmp(buffer,":history") == 0){
					memset(buffer, 0, sizeof(buffer));
					sscanf(inet_ntoa(newAddr.sin_addr),"%s",uip);
					strcat(uip,".txt");
					//FILE* f = fopen(uip,"w+");
					//if(f == NULL){ 	// Créer le fichier local avec le nom indiqué en mode écriture
					//	perror("Open");		 			
					//}	
					fd = open(uip, O_CREAT |O_WRONLY | O_TRUNC); 
					if (fd == -1)
					{
						perror("File open error");
						exit(1);
					}
					while((count_r = read(newSocket, buf, 1024))>0)
					{
						count_w = 0;
						bufptr = buf;
						while (count_w < count_r)
						{
							count_r -= count_w;
							bufptr += count_w;
							count_w = write(fd, bufptr, count_r);
							if (count_w == -1) 
							{
								perror("Socket read error");
								exit(1);
							}
						}
						if(strcmp(bufptr,"#")){
							break;
						   }
					}
					close(fd);
					send(newSocket, "Historique enregistré", strlen("Historique enregistrée"), 0);
				}else{
					if(strlen(buffer) < 20){					
						printf("%s: %s\n",inet_ntoa(newAddr.sin_addr),buffer);
					}
					send(newSocket, buffer, strlen(buffer), 0);
					bzero(buffer, sizeof(buffer));
				}

			}
		}

	}

	close(newSocket);


	return 0;
}
