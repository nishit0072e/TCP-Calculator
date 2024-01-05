/*
 * client.c
 *
 *  Created on: 05-Jan-2024
 *      Author: nishit
 *
 *
 *      filename server_ipaddress portno
 *
 *		argv[0] filename
 *	    argv[1] server_ipaddress
 *		argv[2] portno
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>

void error(const char *msg)
{
	perror(msg);
	exit(0);
}

int main(int argc, char *argv[])
{
	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;

	char buffer[255];
	if(argc<3)
	{
		fprintf(stderr,"usage %s hostname port\n",argv[0]);
		exit(1);
	}
	portno = atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_STREAM,0);
	if(sockfd< 0)
		error("Error opening socket.");

	server = gethostbyname(argv[1]);
	if(server == NULL)
	{
		fprintf(stderr,"Error, no such host.");
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family =AF_INET;
	bcopy((char *) server-> h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portno);
	if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr))<0)
		error("Connection Failed");
	int num1, num2, choice, answer;

	S: bzero(buffer, 255);
	n = read(sockfd,buffer,255);
	if(n<0)
		error("Error reading from socket");
	printf("Server - %s\n",buffer);
	scanf("%d", &num1);
	write(sockfd, &num1,sizeof(int));

	bzero(buffer, 255);
	n = read(sockfd,buffer,255);
	if(n<0)
		error("Error reading from socket");
	printf("Server - %s\n",buffer);
	scanf("%d", &num2);
	write(sockfd, &num2,sizeof(int));


	bzero(buffer, 255);
	n = read(sockfd,buffer,255);
	if(n<0)
		error("Error reading from socket");
	printf("Server - %s\n",buffer);
	scanf("%d", &choice);
	write(sockfd, &choice,sizeof(int));

	if(choice == 5)
		goto Q;
	read(sockfd, &answer,sizeof(int));
	printf("Server - the answer is %d\n",answer);

	if(choice != 5)
		goto S;
	Q:
	printf("You have selected to exit. Exit Success");
	close(sockfd);
	return 0;
}
