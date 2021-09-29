#include <iostream>
#include <stdio.h>
#include <Windows.h>

int main()
{
    HANDLE hProcess = NULL;
    HANDLE hThread = NULL;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    DWORD dwProcessId = 0;
    DWORD dwThreadId = 0;
    ZeroMemory( &si, sizeof(si) );
    ZeroMemory( &pi, sizeof(pi) );

    BOOL bCreateProcess = NULL;
    bCreateProcess = CreateProcess(
        L"C:\\Program Files\\Notepad++\\notepad++.exe",
        NULL,
        NULL,
        NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &si,
        &pi
    );

    if (bCreateProcess == FALSE) {
        std::cout << "Process failed with " << GetLastError() << std::endl;
    }
    std::cout << "Create process succeeded" << std::endl;

    WaitForSingleObject(pi.hProcess,INFINITE);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);

}
