#include<iostream>
#include<Winsock2.h>
#include<conio.h>
#include<unistd.h>
#include<cmath>
#include<cstdio> 
using namespace std;
int len=100,sum=0;
bool ifconnect[10001];
char recvBuf[101],nickname[101][51];
WSADATA wsa;
SOCKET server,client[101];
HANDLE thread[101],rec;
SOCKADDR_IN addrSrv,addrClien;
void order(char a[])
{
	if(a[1]=='u'&&a[2]=='s'&&a[3]=='e'&&a[4]=='r')
	{
		for(int i=1;i<=sum;i++)
			if(ifconnect[i]==1)
				cout<<nickname[i]<<endl;
	}
	if(a[1]=='k'&&a[2]=='i'&&a[3]=='c'&&a[4]=='k')
	{
		for(int i=1;i<=sum;i++)
		{
			int flag=0;
			for(int j=5;j<strlen(a);j++)
				if(a[j]!=nickname[i][j-5])
				{
					flag=1;
					break;
				}
			if(flag==0)
			{
				cout<<"�ɹ�"<<endl;
				ifconnect[i]=0;
			}
		}
	}
}
void sendtoall(char Buf[],char x)
{
	char sb[1001];
	sprintf(sb,"%c%s",x,Buf);
	for(int i=1;i<=sum;i++)
	{
		if(ifconnect[i]==1)
		{
			send(client[i],sb,strlen(sb)+1,0);//������Ϣ�ͻ���
		}
	}
}
DWORD WINAPI Recv(LPVOID lp)
{
	int cl=*(int *)lp;
	char Buf[1001];
	char Buf2[1001],num;
	num=cl+1;
	recv(client[cl],nickname[cl],100,0);
	Sleep(100);
	sprintf(Buf,"%s%s",nickname[cl],"������");
	sendtoall(Buf,'G');
	ifconnect[cl]=1;
	while(1)
	{
		if(recv(client[cl],Buf,100,0)==-1||ifconnect[cl]==0)
			break;//���տͻ�������
		sprintf(Buf2,"%s:%s",nickname[cl],Buf);
		cout<<Buf2<<endl;
		sendtoall(Buf2,num);
	}
	ifconnect[cl]=0;
}
DWORD WINAPI recconnect(LPVOID n)
{
	while(1)
	{
		client[sum+1]=accept(server,(SOCKADDR*)&addrClien,&len);
		sum++;
		thread[sum]=CreateThread(NULL,0,Recv,&sum,NULL,NULL);
	}
}
int main()
{
	char a[101];
	WSAStartup(MAKEWORD(2,2),&wsa);
	server=socket(AF_INET,SOCK_STREAM,0);                    //����socket
	addrSrv.sin_addr.S_un.S_addr=htonl(INADDR_ANY);            //���õ�ַ
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_port=htons(80);                            //���ö˿ں�
	bind(server,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));//��
	listen(server,10);//�������������
	rec=CreateThread(NULL,0,recconnect,NULL,NULL,NULL);
	char num;
	num=71;
	while(1)
	{
		cin>>a;
		if(a[0]=='-')
		{
			order(a);
			continue;
		}
		sendtoall(a,num);
	}
	return 0;
}
