#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main() {
	int s, s2;
	char c=' ';
	s = socket (AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port   = 50789;
	server.sin_addr.s_addr = inet_addr ("141.57.9.14");

	int rc;
	rc = connect(s,(struct sockaddr*)&server,sizeof(server));
	if (rc < 0) {
		perror("connect");
		exit (2);
	}

	//Data transfer
	int l, flag=0;
	char buff[100];
	char aux = 'n';
	strcpy(buff, "ping");

	//Senden
	while(c != EOF){
		l = write ( s, buff, strlen(buff)+1);
		if(l < 0){
			perror("send");
			exit(1);
		}
		l = read (s, buff, sizeof(buff));
		printf ("Empfang: %d Bytes, %s\n", l, buff);
		c = getchar();
		if (c != EOF)
		while (getchar() != '\n');
	}
	close(s);
	printf("Kommunikation beendet\n");
return 0;
}
