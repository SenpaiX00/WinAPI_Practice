/*Client side file that connects to the named pipe in NamedPipe_Server.cpp


1. CreateFile or CallNamedPipe
2. WriteFile / ReadFile / TransactNamedPipe
3. CLoseHandle */

#include <stdio.h>
#include <iostream>
#include <windows.h>

int main()
{
    std::cout<<"\t\t...NAMED PIPE CLIENT..."<<std::endl;
    //local variable definitions
    HANDLE hCreateFile;

    //ReadFile local variables
    BOOL bReadFile;
    char szReadFile[1023];
    DWORD dwReadBufferSize = sizeof(szReadFile);
    DWORD dwNoBytesWrite;
    //WriteFile local variables
    BOOL bWriteFile;
    char szWriteFileBuffer[] = "Hello from named pipe client!";
    DWORD dwWriteBufferSize = sizeof(szWriteFileBuffer);
    DWORD dwNoBytesRead;
    
    //CreateFile
    hCreateFile = CreateFile(L"\\\\.\\pipe\\MYNAMEDPIPE", GENERIC_READ|GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    
    if (INVALID_HANDLE_VALUE == hCreateFile) {
        std::cout << "FILE CREATION FASILED WITH " << GetLastError() << std::endl;
    }
    else { std::cout << "createfile success" << std::endl; }

    //ReadFile Operation
    bReadFile = ReadFile(hCreateFile,szReadFile,dwReadBufferSize,&dwNoBytesRead,NULL);
    
    if (bReadFile == FALSE)
    {
        std::cout << "ReadFile failed on client side with " << GetLastError() << std::endl;
    }
    else 
    { 
        std::cout << "ReadFile successful on client side" << std::endl; 
        std::cout << "data reading from server -> " << szReadFile << std::endl; 
    }

    //writefile operation
    bWriteFile = WriteFile(hCreateFile, szWriteFileBuffer,dwWriteBufferSize,&dwNoBytesWrite,NULL);
    
    if (bWriteFile == FALSE)
    {
        std::cout << "Writefile on client side failed with " << GetLastError() << std::endl;
    }
    else { std::cout << "WriteFile success on client side!" << std::endl; }

    CloseHandle(hCreateFile);

    return 0;
}

