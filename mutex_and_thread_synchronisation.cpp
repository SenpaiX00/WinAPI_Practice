// CreateMutex.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <stdio.h>
#include <iostream>
#include <windows.h>

HANDLE hMutex;
int gcount = 1;

DWORD WINAPI ThreadEvenCount(LPVOID lpParam) {
    std::cout << "Thread running Even\n" << std::endl;
    while (gcount < 1)
    {
        WaitForSingleObject(hMutex,INFINITE);
        if (gcount%2==0)
        {
            std::cout << "Even " << std::endl;
           
        }
        ReleaseMutex(hMutex);
        
    }
    
    //std::cout << "t1 gcount = " << gcount++ << std::endl;
    return 0;
}

DWORD WINAPI ThreadOddCount(LPVOID lpParam) {
    std::cout << "Thread running Odd \n" << std::endl;
    while (gcount < 10)
    {
        WaitForSingleObject(hMutex, INFINITE);
        if (gcount % 2 == 1)
        {
            std::cout << "Odd " << gcount << std::endl;
           
        }
        ReleaseMutex(hMutex);
    }
    
    //std::cout << "t2 gcount = " << gcount << std::endl;
    return 0;
}

int main()
{
    HANDLE hThread1, hThread2;
    hMutex = CreateMutex(NULL,FALSE,NULL);//Named Mutex, otherwise use NULL for unnamed

    hThread1 = CreateThread(NULL, 0, ThreadEvenCount, NULL, 0, NULL);
    hThread2 = CreateThread(NULL, 0, ThreadOddCount, NULL, 0, NULL);
      


    CloseHandle(hThread1);
    CloseHandle(hThread2);
    //CloseHandle(hMutex);

    return 0;
}


