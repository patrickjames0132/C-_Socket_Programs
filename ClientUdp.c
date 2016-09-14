#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define DEST_IP   "127.0.0.1"
#define DEST_PORT 10001

int main(){
	int sockfd;
	int bytes_received;
	char buf[5000];
	struct sockaddr_in dest_addr;   // will hold the destination addr
	sockfd = socket(PF_INET, SOCK_DGRAM, 0); // do some error checking!
	dest_addr.sin_family = AF_INET;          // host byte order
	dest_addr.sin_port = htons(DEST_PORT);   // short, network byte order
	dest_addr.sin_addr.s_addr = inet_addr(DEST_IP);
	memset(&(dest_addr.sin_zero), '\0', 8);  // zero the rest of the struct
	char *msg = "Hello Server!";
	int len, bytes_sent;
	len = strlen(msg);
	bytes_sent = sendto(sockfd, msg, len, 0, (struct sockaddr *)&dest_addr, sizeof(struct sockaddr));
	close(sockfd);
	
	return 0;
}
