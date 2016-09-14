#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define MYPORT 10001
int main()
{
	int sockfd;
	int newfd;
	struct sockaddr_in my_addr;
	struct sockaddr_in their_addr; // connector’s address information
	int theirlen;
	int sin_size;
	char buf[5000];
	int bytes_sent;
	int len;
	int bytes_received;
	sockfd = socket(PF_INET, SOCK_DGRAM, 0); // do some error checking!
	my_addr.sin_family = AF_INET;         // host byte order
	my_addr.sin_port = htons(MYPORT);     // short, network byte order
	my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(&(my_addr.sin_zero), '\0', 8); // zero the rest of the struct
	
	// don’t forget your error checking for bind():
	bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr));
	bytes_received = recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&their_addr, theirlen);
	for(int i = 0; i < bytes_received; i++){
		printf("%c", buf[i]);
	}
        printf("\nrecv()'d %d bytes of data in buf\n", bytes_received);
	
	close(newfd);
	return 0;
}
