#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main() {
char c=' ';
int s, s2;
s = socket (AF_INET, SOCK_STREAM, 0);

struct sockaddr_in server;
server.sin_family = AF_INET;
server.sin_port   = 50789;
server.sin_addr.s_addr = INADDR_ANY;
struct sockaddr_in client;
int clen = sizeof(client);

char aux = 'n';
int rc;

rc = bind (s,(struct sockaddr*)&server, sizeof(server));
if (rc < 0) {
	perror("bind");
	exit (1);
}

rc = listen ( s, 5 );
if (rc < 0) {
	perror("listen");
	exit (1);
}

s2 = accept ( s,(struct sockaddr*)&client, &clen);
if (s2 < 0) {
	perror("accept");
	exit (1);
}
	
while(1){

	int l, flag=0;
	char buff[100];
		
	l = read ( s2, buff, 100);
	if (l == 0) break;
	if(l < 0){
		perror("read");
		exit(1);
	}	
	printf("Message: %s\nfrom: %s\n",buff,inet_ntoa(client.sin_addr));
	printf("port: %d\n",ntohs(client.sin_port));
	strcpy(buff, "pong");
	write (s2, buff, strlen(buff)+1);
}

close(s2);
printf("Komunnikation beendet\n");
close(s);

return 0;
}
