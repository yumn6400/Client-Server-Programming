#include<stdio.h>
#include<string.h>
#include<windows.h>
int main()
{
char response[5000];
char request[5000];
char header[11];
WORD ver;
int success1,success2,len,i;
int clientSocketDescriptor;
int serverSocketDescriptor;
struct sockaddr_in serverSocketInformation;
struct sockaddr_in clientSocketInformation;
ver=MAKEWORD(1,1);
WSADATA wsaData;
WSAStartup(ver,&wsaData);
serverSocketDescriptor=socket(AF_INET,SOCK_STREAM,0);
if(serverSocketDescriptor<0)
{
printf("Unable to create a socket\n");
return 0;
}
serverSocketInformation.sin_family=AF_INET;
serverSocketInformation.sin_port=htons(5050);
serverSocketInformation.sin_addr.s_addr=htonl(INADDR_ANY);
success1=bind(serverSocketDescriptor,(struct sockaddr*)&serverSocketInformation,sizeof(serverSocketInformation));
if(success1<0)
{
printf("Unable to bind to port 5050\n");
WSACleanup();
return 0;
}
listen(serverSocketDescriptor,10);
len=sizeof(clientSocketInformation);
clientSocketDescriptor=accept(serverSocketDescriptor,(struct sockaddr*)&clientSocketInformation,&len);
if(clientSocketDescriptor<0)
{
printf("Unable to accept request to port 5050\n");
closesocket(serverSocketDescriptor);
WSACleanup();
return 0;
}
success1=recv(clientSocketDescriptor,request,sizeof(request),0);
request[success1]='\0';
printf("%d\n",success1);
if(success1>0)
{
printf("Request arrived\n");
for(i=0;i<10;i++)header[i]=request[i];
header[i]='\0';
len=atoi(header);
printf("%s\n",request);
while(len>success1)
{
printf("------------------\n");
success2=recv(clientSocketDescriptor,request,sizeof(request),0);
request[success1]='\0';
success1=success1+success2;
printf("%s\n",request);
}
}
strcpy(response,"Welcome to home");
len=strlen(response);
sprintf(header,"%-10d",len);
for(i=len;i>=0;i--)response[i+10]=response[i];
for(i=0;i<10;i++)response[i]=header[i];
printf("%s\n",response);
send(clientSocketDescriptor,response,strlen(response)+1,0);
printf("Response sent");
closesocket(serverSocketDescriptor);
closesocket(clientSocketDescriptor);
WSACleanup();
return 0;
}