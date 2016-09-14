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
	int sin_size;
	char buf[5000];
	int bytes_sent;
	int len;
	int bytes_received;
	sockfd = socket(PF_INET, SOCK_STREAM, 0); // do some error checking!
	my_addr.sin_family = AF_INET;         // host byte order
	my_addr.sin_port = htons(MYPORT);     // short, network byte order
	my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(&(my_addr.sin_zero), '\0', 8); // zero the rest of the struct
	
	// don’t forget your error checking for bind():
	bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr));
	listen(sockfd, 10);
	sin_size = sizeof(struct sockaddr_in);
	newfd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
	char *msg = "Hi Client!";
	len = strlen(msg);
	bytes_sent = send(newfd, msg, len, 0);
	bytes_received = recv(newfd, buf, sizeof buf, 0);
	for(int i = 0; i < bytes_received; i++){
		printf("%c", buf[i]);
	}
        printf("\nrecv()'d %d bytes of data in buf\n", bytes_received);
	
	close(newfd);
	return 0;
}
