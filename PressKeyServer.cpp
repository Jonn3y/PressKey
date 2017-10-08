
/* 
 *  Copyroight: github.com/Jonn3y
 *  Version: 1.0 - 08.10.2017 (dd/mm/yyyy)
 *  KeyPressServer.cpp
 */


#include "stdafx.h"
#include <iostream>
#include <winsock2.h>
#define WINVER 0x0500
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

void PressKey(char c) {

	int latin1 = (int)c;
	/*
	Keys that do not work at the moment:
	(SentID . KeyValue)


	switch (latin1) {
	case'-128': c = '€';
		break;
	case'-89': c = '\'';
		break;
	case'-78': c = '²';
		break;
	case'-77': c = '³';
		break;
	case'-76': c = '´';
		break;
	case'-75': c = 'µ';
		break;
	case'-60': c = 'Ä';
		break;
	case'-42': c = 'Ö';
		break;
	case'-36': c = 'Ü';
		break;
	case'-33': c = 'ß';
		break;
	case'-28': c = 'ä';
		break;
	case'-10': c = 'ö';
		break;
	case'-4': c = 'ü';
		break;
	default: break;
		break;
	}
	*/



	INPUT Event = { 0 };

	const SHORT key = VkKeyScan(c);
	const UINT mappedKey = MapVirtualKey(LOBYTE(key), 0);

	Event.type = INPUT_KEYBOARD;
	Event.ki.dwFlags = KEYEVENTF_SCANCODE;

	if ( (latin1 >= 58 && latin1 <= 63 && latin1) || ( latin1>= 65 && latin1 <= 90 && latin1)|| (latin1 >= 36 && latin1 <= 42) || (latin1 == 33 || latin1 == 95 || latin1 == 96)) {
		// Press shift key
		Event.ki.wScan = MapVirtualKey(VK_LSHIFT, 0);
		SendInput(1, &Event, sizeof(Event));
	}

	if (latin1 == 64 || latin1 == 91 || latin1 == 92 || latin1 == 93 || latin1 == 123 || latin1 == 124 || latin1 == 125 || latin1 == 126) {
		// Press alt+ctrl = altgr key
		Event.ki.wScan = MapVirtualKey(VK_RMENU, 0);
		SendInput(1, &Event, sizeof(Event));
		
		Event.ki.wScan = MapVirtualKey(VK_CONTROL, 0);
		SendInput(1, &Event, sizeof(Event));	
	}

	// Press (upper case) 'A'

	Event.ki.dwFlags = KEYEVENTF_SCANCODE;
	Event.ki.wScan = mappedKey;
	SendInput(1, &Event, sizeof(Event));

	// Release any Key 
	Event.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;

	// release (upper case) 'a-Z' ...
	Event.ki.wScan = mappedKey;
	SendInput(1, &Event, sizeof(Event));

	if (latin1 == 64 || latin1 == 91 || latin1 == 92 || latin1 == 93 || latin1 == 123 || latin1 == 124 || latin1 == 125 || latin1 == 126) {
		// Release alt+ctrl = altgr key
		Event.ki.wScan = MapVirtualKey(VK_RMENU, 0);
		SendInput(1, &Event, sizeof(Event));

		Event.ki.wScan = MapVirtualKey(VK_CONTROL, 0);
		SendInput(1, &Event, sizeof(Event)); 
	}

	if ((latin1 >= 58 && latin1 <= 63 && latin1) || (latin1 >= 65 && latin1 <= 90 && latin1) || (latin1 >= 36 && latin1 <= 42) || (latin1 == 33 || latin1 == 95 || latin1 == 96)) {
		// Release shift key
		Event.ki.wScan = MapVirtualKey(VK_LSHIFT, 0);
		SendInput(1, &Event, sizeof(Event));
	}
	

}

void Stealth()
{
	HWND Stealth;
	AllocConsole();
	Stealth = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(Stealth, 0);
}


int main()
{
	Stealth(); // Hide Windows always
	WSADATA WSAData;

	SOCKET server, client;

	SOCKADDR_IN serverAddr, clientAddr;

	WSAStartup(MAKEWORD(2, 0), &WSAData);
	server = socket(AF_INET, SOCK_STREAM, 0);

	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(5555);

	bind(server, (SOCKADDR *)&serverAddr, sizeof(serverAddr));
	listen(server, 0);

	while (true) {
	cout << "Listening for incoming connections..." << endl;
		char buffer[1024] = "";
		int clientAddrSize = sizeof(clientAddr);
		if ((client = accept(server, (SOCKADDR *)&clientAddr, &clientAddrSize)) != INVALID_SOCKET)
		{
			cout << "Client connected!" << endl;
			recv(client, buffer, sizeof(buffer), 0);
			cout << "Client says: " << buffer << endl;
			
			for (int i = 0; buffer[i] != '\0'; i++) {
				cout << (int)buffer[i] << ' '; 
				Sleep(15);
				PressKey(buffer[i]);
			}
			memset(buffer, 0, sizeof(buffer));
			closesocket(client);
			cout << "Client disconnected." << endl;
		}
	}

}
