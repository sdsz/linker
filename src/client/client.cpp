#include <winsock2.h>
#include<cstdio> 
#pragma comment(lib,"WS2_32.lib")
#include<iostream>
#include<conio.h>
#include<unistd.h>
#include<cmath>
#include<windows.h>
using namespace std;
SOCKET sockClient;                                      //�ͻ���socket
HANDLE thread;
HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
DWORD WINAPI Recv(LPVOID lp)
{
	char Buf[1001];
	while (1)
	{
		if (recv(sockClient, Buf, 100, 0) == -1)
			break;									//���տͻ�������
		int a = Buf[0];
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY|a);
		cout << Buf + 1 << endl;
		SetConsoleTextAttribute(handle, 7);
	}
}
int main()
{
	SOCKADDR_IN addrSrv;
	WSADATA wsd;
	char recvBuf[100];
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		printf("�Ҳ�������\n");
		return 0;
	}
	addrSrv.sin_addr.S_un.S_addr = *(u_long *) gethostbyname("beijingsunsiyu.oicp.net") -> h_addr_list[0];//inet_addr("103.44.145.243");
	printf("%s\n", inet_ntoa(addrSrv.sin_addr)); // ת��Ϊ�ַ������
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(12493);
	sockClient = socket(AF_INET,SOCK_STREAM,0);//����socket
	cout << "Loading..." << endl;
	while (1)
	{
		if (connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR)) != -1)
			break;
	}
	Sleep(3000);
	system("cls");
	cout << "�����ǳ�" << endl; 
	char nickname[51];
	cin >> nickname;
	send(sockClient, nickname, strlen(nickname) + 1, 0);
	system("cls");
	thread = CreateThread(NULL, 0, Recv, NULL, NULL, NULL);
	char a[1001];
	while (1)
	{
		cin >> a;
		send(sockClient, a, strlen(a) + 1, 0);
	}
	closesocket(sockClient);//�ر�����
	WSACleanup();
}
