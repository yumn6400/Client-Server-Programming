#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
int main()
{
char response[5000];
char request[5000];
WORD ver;
char header[11];
int i;
int success1,success2,len;
int clientSocketDescriptor;
int serverSocketDescriptor;
struct sockaddr_in serverSocketInformation;
ver=MAKEWORD(1,1);
WSADATA wsaData;
WSAStartup(ver,&wsaData);
clientSocketDescriptor=socket(AF_INET,SOCK_STREAM,0);
if(clientSocketDescriptor<0)
{
printf("Unable to create a socket\n");
return 0;
}
serverSocketInformation.sin_family=AF_INET;
serverSocketInformation.sin_port=htons(5050);
serverSocketInformation.sin_addr.s_addr=inet_addr("127.0.0.1");
success1=connect(clientSocketDescriptor,(struct sockaddr*)&serverSocketInformation,sizeof(serverSocketInformation));
if(success1<0)
{
printf("Unable to connect to port 5050\n");
WSACleanup();
return 0;
}
strcpy(request,"There are two types of democracy. First, the democracy of a small club with a voting membership of less than a thousand.  Here, the members can personally meet and know the candidates for office, and can have their voices heard within the club. Second is mass democracy, in which the number of voters is so large that very few can personally know the candidates.Obviously, the United States, and all other countries practice mass democracy. This comes in various forms, such as the US system of mass-voting for the chiefs (governors and the president) and for the representatives. There is the parliamentary system. such as in the United Kingdom, in which the political parties form coalitions that select a prime minister, the head of state being either a monarch or, like in Germany, a president as a symbolic chief.Many people in the US are now worried about the coming election in November, wondering whether the results will be rigged or fraudulent. Some Americans worry that people will be fooled by fase information, and whether emotion will triumph over reason. But, beneath the particular circumstances of the 2020 US election is the system, mass democracy – which is inherently dysfunctional even in the best of circumstances.When there are thousands or millions of voters choosing a candidate, the office seeker needs to reach them using mass media: television, Internet advertising, bulk mail, and those annoying telephone calls. Advertising is costly; candidates for US president spend many millions of dollars. (You can see the data on campaign spending in <https://www.opensecrets.org/>, compiled by the Center for Responsive Politics.) This inherent demand for campaign funds generates a supply of such funds by the big-money special interests. Yes, there are contributions from individuals, but it is well known that special interests such as corporations, lawyers, labor unions, and real estate firms obtain political clout – and subsidies – due to their campaign contributions and subsequent lobbying.Attempts to imit the role of the moneyed and landed interests have been unsuccessful. First, there is the clash between free speech and restrictions on campaign contributions. Second, since governmental representatives need campaign money, they will allow ways to overcome limitations, such as the use of political action committees, to indirectly support candidates. It is like building a dam to hold back a flood: gushing water will go over and around the dam.Some propose that government would and should pay for political campaigns. But the prohibition of a candidate using one’s own money for the campaign again clashes with free speech. Freedom of expression requires the freedom to use media to spread the message. Moreover, many taxpayers would object to being forced to finance negative and false advertising.There is really no effective way to reform an inherently dysfunctional system. The remedy is small-group democracy, in which voting takes place only in a small group. But, how can millions of people be represented in sall-group voting? By the method of multi-level, bottom-up voting.Small-group voting is implemented by dividing the political body into tiny neighborhood cells, like the human body and biological cells. Hence, small-group voting has also been referred to as “cellular democracy.” The cell is a geographical neighborhood of about 1000 persons. The residents elect a neighborhood council and an alternate. Suppose the neighborhoods are in a city of 100,000 persons. The 100 neighborhood councils each send a representative to the city council. A large city would be divided into districts of 100,000, whose councils then elect the city council. The city councils then elect a county council, which elects the state or provincial legislature, which then elects the national or federal congress or parliament. The national and state legislatures elect a president or governor.An advantage of cellular democracy – small group, bottom-up, multi-level voting – is that it would be much easier to remove a representative or chief exeutive who performs poorly. The demand for campaign funds would disappear. And, the desires of the people would be much better represented.Small-group voting would have a profound effect on government policy. For example, taxation would become decentralized. Income taxes, for example, enable the federal government to impose policies on the states in order for them to obtain federal funds. But, as political power would flow bottom-up, so too would revenues. Tax power would shift from the federal and state governments down to the counties that elect the higher-level governments.The federal and state income taxes would likely be replaced by county-level property taxes, ideally tapping only the land value and not the value of buildings and other improvements. As they send representatives to the states, so too would counties send some of their tax funds to the state governments, and the states would send funds to the federal governments. Taxing power would follow the voting power.This year, when so many Americans ae worried about the integrity of the election, let’s make this an opportunity to rethink our system of democracy. Back in 1789, when the Constitution was adopted, the population was much smaller, and most people were not allowed to vote. Now, with our much greater population and voting, mass democracy is ever more vulnerable to voter suppression, fraud, and postal manipulations.when voting for your ");
len=strlen(request);
sprintf(header,"%-10d",len);
for(i=len;i>=0;i--)request[i+10]=request[i];
for(i=0;i<10;i++)request[i]=header[i];
send(clientSocketDescriptor,request,strlen(request)+1,0);
success1=recv(clientSocketDescriptor,response,sizeof(response),0);
printf("%d\n",success1);
response[success1]='\0';
if(success1>0)
{
printf("Request arrived\n");
for(i=0;i<10;i++)header[i]=response[i];
header[i]='\0';
len=atoi(header);
printf("%s\n",response);
while(len>success1)
{
success2=recv(clientSocketDescriptor,response,sizeof(response),0);
response[success2]='\0';
success1=success1+success2;
printf("%s\n",response);
}
}
closesocket(serverSocketDescriptor);
closesocket(clientSocketDescriptor);
WSACleanup();
return 0;
}