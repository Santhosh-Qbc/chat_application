#include<sys/socket.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#define SER_PORT 1200
int main()
{
	int a,sersock,newsock,n;
	char str[50],str2[50];
	struct sockaddr_in seraddr;
	struct sockaddr_in cliinfo;
	socklen_t csize=sizeof(cliinfo);
	seraddr.sin_family=AF_INET;
	seraddr.sin_port=htons(SER_PORT);
	seraddr.sin_addr.s_addr=htonl(INADDR_ANY);
	printf("-----------------Server---------------\n");
	if((sersock=socket(AF_INET,SOCK_STREAM,0))<0)
	{
		perror("\n socket");
		exit(0);
	}
	printf("Socket created\n");
	if(bind(sersock,(struct sockaddr *)&seraddr,sizeof(seraddr))<0)
	{
		perror("\nBIND");
		exit(0);
	}
	if(listen(sersock,1)<0)
	{
		perror("\n LISTEN");
	}
	if((newsock=accept(sersock,(struct sockaddr *)&cliinfo,&csize))<0)
	{
		perror("\n ACCEPT");
		exit(0);
	}
	else
		printf("\n now connected to %s\n",inet_ntoa(cliinfo.sin_addr));
	do
	{
		listen(newsock,1);
		read(newsock,str,sizeof(str));
		printf("\n client msg:%s",str);
		printf("\n server msg:");
		scanf("%s",str2);
		write(newsock,str2,sizeof(str2));
		n=strcmp(str,"BYE");
		a=strcmp(str2,"BYE");
	}
	while(n!=0||a!=0);
	close(newsock);
	close(sersock);
	return 0;
}
