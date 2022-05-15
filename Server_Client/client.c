#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <strings.h>

#define BUF_SIZE 100
#define SOCK_ADDR "./sock_addr"
int main(int argc, char* argv[])
{
	int sock,len;
	struct sockaddr_un sock_addr;
	char buf[BUF_SIZE] = {0,};

	sock_addr.sun_family = AF_UNIX;
	strcpy(sock_addr.sun_path, SOCK_ADDR);

	sock = socket(AF_UNIX, SOCK_STREAM, 0);
	if(sock==-1)
	{
		perror("Socket Error\n");
	}

	if(connect(sock, (struct sockaddr *)&sock_addr, sizeof(sock_addr))==-1)
	{
		perror("Connect Error\n");
		exit(1);
	}
	while(1)
	{
		printf("Message : ");
		gets(buf);

		if(send(sock, buf, BUF_SIZE+1, 0) >0)
		{
			memset(buf, 0 , BUF_SIZE);
		}
		if(strncmp(buf, "\quit",strlen("\quit"))==0)
		{
			break;
		}
	}
	close(sock);

	return 0;
}
