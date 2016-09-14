#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define DEST_IP   "199.244.212.93"
#define DEST_PORT 80

int main(){
	int sockfd;
	int bytes_received;
	char buf[50000];
	struct sockaddr_in dest_addr;   // will hold the destination addr
	sockfd = socket(PF_INET, SOCK_STREAM, 0); // do some error checking!
	dest_addr.sin_family = AF_INET;          // host byte order
	dest_addr.sin_port = htons(DEST_PORT);   // short, network byte order
	dest_addr.sin_addr.s_addr = inet_addr(DEST_IP);
	memset(&(dest_addr.sin_zero), '\0', 8);  // zero the rest of the struct
	// don’t forget to error check the connect()!
	connect(sockfd, (struct sockaddr *)&dest_addr, sizeof(struct sockaddr));
	
	char *msg = "GET / HTTP/1.1\r\n\r\n";
	int len, bytes_sent;
	len = strlen(msg);
	bytes_sent = send(sockfd, msg, len, 0);	
	bytes_received = recv(sockfd, buf, sizeof buf, 0);

	for (int i = 0; i < bytes_received; i++){
		printf("%c", buf[i]);
	}
	printf("\nrecv()'d %d bytes of data in buf\n", bytes_sent);
	close(sockfd);
	
	return 0;
}
