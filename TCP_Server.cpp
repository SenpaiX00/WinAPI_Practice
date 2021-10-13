// tcpSocket.cpp : This file contains the 'main' function. Program execution begins and ends there.
/* Serverside:
    WSAStartUp
    Fill ClientORServer Struct
    Socket
    Bind
    Listen
    Accept
    recvfrm or sendto
    closesocket
    WSACleanUp
    SEE THE ACCOMPANYING CLIENT SIDE C++ FILE FOR A CLIENT THAT CONNECTS TO THIS SERVER OR ALTERNATIVELY USE: ncat.exe -nv 127.0.0.1 8000*/



#include <iostream>
#include <WinSock2.h>
#include <Ws2tcpip.h>
#include <Tchar.h>
#pragma warning(suppress : 4996)
using namespace std;


int main()
{
    cout << "TCP SERVER" << endl;
    //LOCAL VARIABLES
    WSADATA Winsockdata;
    int iWsaStartUp;
    int iWsaCleanUp;

    SOCKET TCPServerSocket;
    int iCloseSocket;

    struct sockaddr_in TCPServerAdd; //This is the structure
    struct sockaddr_in TCPClientAdd;
    int iTCPClientAdd = sizeof(TCPClientAdd);

    int iBind;

    int iListen;

    SOCKET sAcceptSocket;

    int iSend;
    char SenderBuffer[512] = "Hello from server!";
    int iSenderBuffer = strlen(SenderBuffer);

    int iRecv;
    char RecvBuffer[512];
    int iRecvBuffer = strlen(RecvBuffer) + 1;


    //STEP 1: WSAStasrtup Function - initiates use of the Winsock DLL by a process
    iWsaStartUp = WSAStartup(MAKEWORD(2,2),&Winsockdata); //more info-https://stackoverflow.com/questions/24131843/what-is-makeword-used-for 
    if (iWsaStartUp != 0) {
        cout << "WSAStartup FAILED" << endl;
    }
    else {
        cout << "WSAStartup Success" << endl;
    }
    //STEP 2 - FILL THE STRUCTURE
    TCPServerAdd.sin_family = AF_INET;
    InetPton(AF_INET, _T("127.0.0.1"), &TCPServerAdd.sin_addr.s_addr);
    //TCPServerAdd.sin_addr.s_addr = inet_addr("127.0.0.1"); <------- this is now depreciated, so see the above line of code
    TCPServerAdd.sin_port = htons(8000);


    //STEP 3: Create socket
    TCPServerSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if (TCPServerSocket == INVALID_SOCKET) {
        cout << "TCP Server socket gailed " << WSAGetLastError() << endl;
    }
    else {
        cout << "TCP Server socket creation success" << endl;
    }

    //STEP 4: Bind
    iBind = bind(TCPServerSocket, (SOCKADDR*)&TCPServerAdd, sizeof(TCPServerAdd));
    if (iBind == SOCKET_ERROR) {
        cout << "bind failed with " << WSAGetLastError() << endl;
    }
    else {
        cout << "bind success" << endl;
    }
    //STEP 5: listen
    iListen=listen(TCPServerSocket, SOMAXCONN);
    if (iListen == SOCKET_ERROR) {
        cout << "Listen function failed with " << WSAGetLastError() << endl;
    }
    else
    {
        cout << "Listen fucntiuon success" << endl;
    }
    //STEP 6: Accept
    sAcceptSocket = accept(TCPServerSocket, (SOCKADDR*)&TCPClientAdd, &iTCPClientAdd);
    if (sAcceptSocket == INVALID_SOCKET)
    {
        cout << "accept failed with " << WSAGetLastError() << endl;
    }
    else
    {
        cout << "Accept success" << endl;
    }
    //STEP 7: send
    iSend = send(sAcceptSocket,SenderBuffer,iSenderBuffer,0);
    if (iSend == SOCKET_ERROR)
    {
        cout << "sned failed with " << WSAGetLastError() << endl;
    }
    else
    {
        cout << "send success" << endl;
    }
    //STEP 8: recv
    iRecv = recv(sAcceptSocket, RecvBuffer, iRecvBuffer, 0);
    if (iRecv == SOCKET_ERROR)
    {
        cout << "receive failed with " << WSAGetLastError() << endl;
    }
    else
    {
        cout << "Receive success" << endl;
    }
    //STEP 9: Close socket
    iCloseSocket = closesocket(TCPServerSocket);

    //STEP 10: clean up dll
    iWsaCleanUp = WSACleanup();

}


