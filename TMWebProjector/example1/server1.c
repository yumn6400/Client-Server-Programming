#include<windows.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
WORD ver;
char request[5000];
char response[5000];
int successCode;
int serverSocketDescriptor;
int clientSocketDescriptor;
struct sockaddr_in serverSocketInformation;
struct sockaddr_in clientSocketInformation;
int len;
WSADATA wsaData;
ver=MAKEWORD(1,1);
WSAStartup(ver,&wsaData);
serverSocketDescriptor=socket(AF_INET,SOCK_STREAM,0);
if(serverSocketDescriptor<0)
{
printf("Unable to create socket\n");
return 0;
}
serverSocketInformation.sin_family=AF_INET;
serverSocketInformation.sin_port=htons(5050);
serverSocketInformation.sin_addr.s_addr=htonl(INADDR_ANY);
successCode=bind(serverSocketDescriptor,(struct sockaddr *)&serverSocketInformation,sizeof(serverSocketInformation));
if(successCode<0)
{
printf("Unable to bind socket to port 5050");
WSACleanup();
return 0;
}
listen(serverSocketDescriptor,10);
printf("TMServer is ready to accept request on port 5050\n");
len=sizeof(clientSocketInformation);
clientSocketDescriptor=accept(serverSocketDescriptor,(struct sockaddr *)&clientSocketInformation,&len);
if(clientSocketDescriptor<0)
{
printf("Unable to accept client connection");
closesocket(serverSocketDescriptor);
WSACleanup();
return 0;
}
successCode=recv(clientSocketDescriptor,request,sizeof(request),0);
printf("%d\n",successCode);
if(successCode>0)
{
printf("Request arrived\n");
printf("%s\n",request);
}
strcpy(response,"Hello my name is Pradhyumn Patidar");
successCode=send(clientSocketDescriptor,response,strlen(response)+1,0);
if(successCode>0)
{
printf("Response sent\n");
}
else
{
printf("Unable to sent response\n");
}
closesocket(clientSocketDescriptor);
closesocket(serverSocketDescriptor);
return 0;
}