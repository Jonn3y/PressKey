
/* 
 *  Copyroight: github.com/Jonn3y
 *  Version: 1.0 - 08.10.2017 (dd/mm/yyyy)
 *
 */
 
 #include "stdafx.h"
#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#include <windows.h>
#include <atlbase.h>


using namespace std;


//int main(int argc, char* argv[])
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{	
	USES_CONVERSION;
	
	LPWSTR *szArglist;
	int nArgs;
	int i;
	char str[502] = ""; //"@";

	szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
	if (NULL == szArglist)
	{
		wprintf(L"CommandLineToArgvW failed\n");
		return 0;
	} 

		for (i = 1; i < nArgs; i++) {
			strcat(str, W2A(szArglist[i]));
			strcat(str, " ");
		}


	WSADATA WSAData;
	SOCKET server;
	SOCKADDR_IN addr;
	
	WSAStartup(MAKEWORD(2, 0), &WSAData);
	server = socket(AF_INET, SOCK_STREAM, 0);

	addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // replace the ip with your futur server ip address. If server AND client are running on the same computer, you can use the local ip 127.0.0.1
	addr.sin_family = AF_INET;
	addr.sin_port = htons(5555);
		connect(server, (SOCKADDR *)&addr, sizeof(addr));
		char buffer[1024];
		strcpy(buffer, str);
		send(server, buffer, sizeof(buffer), 0);
		closesocket(server);
		Sleep(25);
	WSACleanup();
	LocalFree(szArglist);
	return 0; 
}

