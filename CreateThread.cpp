#include <iostream>
#include <stdio.h>
#include <windows.h>

int list[2];

//The actual thread function, which takes the convention of DWORD WINAPI function_name(param)
//This function, or thread, is the program running IN the process. 
DWORD WINAPI ThreadFun(LPVOID lpParam) {
    int x = list[0];
    int y = list[1];
    std::cout << x + y << std::endl;
    return 0;
}

int main()
{
    HANDLE hThread;
    DWORD ThreadId;
    std::cin >> list[0];
    std::cin >> list[1];

    hThread = CreateThread(NULL,0,ThreadFun,(void*)&list,0,&ThreadId); //notice the cast to void pointer to the address of list (global variable) - (void*)&list

    if (hThread == NULL) {
        std::cout <<"Error: "<< GetLastError() << std::endl;
    }
    std::cout << "SUCCESS" << std::endl;
    std::cout << ThreadId << std::endl;

    CloseHandle(hThread);

}
