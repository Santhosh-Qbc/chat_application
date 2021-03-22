#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#define SER_PORT 1200
int main()
{
	int a,clisock;
	char str[50],str2[50];
	struct sockaddr_in serv_addr;
	serv_addr.sin_port=htons(SER_PORT);
	serv_addr.sin_family=AF_INET;
	printf("---------------Client---------------\n");
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
	{ 
		printf("\nInvalid address/ Address not supported \n"); 
		return -1; 
	} 
	clisock=socket(AF_INET,SOCK_STREAM,0);
	if(clisock<0)
	{
		perror("\n SOCKET");
		exit(0);
	}
	if(connect(clisock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0)
	{
		perror("\n CONNECT");
		exit(0);
	}
	printf("\nClient msg:");
	scanf("%s",str);
	if(write(clisock,str,sizeof(str))<0)
	{
		printf("\n data could not be sent");
	}
	do
	{
		listen(clisock,1);
		read(clisock,str2,sizeof(str2));
		printf("\nserver msg:%s",str2);
		printf("\nclient msg:");
		scanf("%s",str);
		a=strcmp(str2,"BYE");
		write(clisock,str,sizeof(str));
	}
	while(a!=0);
	close(clisock);
	return 0;
}
