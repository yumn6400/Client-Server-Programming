#include<windows.h>
#include<stdio.h>
#include<string.h>
int main()
{
WORD ver;
int successCode;
WSADATA wsaData;
int len;
int clientSocketDescriptor;
int serverSocketDescriptor;
struct sockaddr_in serverSocketInformation;
char response[5000];
char request[5000];
ver=MAKEWORD(1,1);


WSAStartup(ver,&wsaData);
clientSocketDescriptor=socket(AF_INET,SOCK_STREAM,0);
if(clientSocketDescriptor<0)
{
printf("Unable to create socket\n");
return 0;
}
serverSocketInformation.sin_family=AF_INET;
serverSocketInformation.sin_port=htons(5050);
serverSocketInformation.sin_addr.s_addr=inet_addr("127.0.0.1");
successCode=connect(clientSocketDescriptor,(struct sockaddr *)&serverSocketInformation,sizeof(serverSocketInformation));
if(successCode<0)
{
printf("Unable to connect to port 5050\n");
WSACleanup();
return 0;
}
strcpy(request,"Hello thinking machine");
successCode=send(clientSocketDescriptor,request,strlen(request)+1,0);
if(successCode>0)
{
printf("Request sent");
}
else
{
printf("Unable to sent request\n");
}
successCode=recv(clientSocketDescriptor,response,sizeof(response),0);
printf("%d\n",successCode);
printf("Response received\n");
printf("%s\n",response);
closesocket(clientSocketDescriptor);
WSACleanup();
return 0;
}