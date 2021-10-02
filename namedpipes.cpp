//NOT COMPLETE!


// namedpipes.cpp : This file contains the 'main' function. Program execution begins and ends there.
/* Server side
  1. Create Named Pipe
  2. ConnectNamedPipe
  3. WriteFile or ReadFile
  4. FlushFileBuffers
  5. DisconnectNamedPipe
  6. CloseHandle
  
  
  Client side
  1. CreateFile or CallNamedPipe
  2. WriteFile/ReadFile/TransactNamedPipe
  3. CLoseHandle*/

#include <stdio.h>
#include <iostream>
#include <windows.h>



int main()
{
    //Create named pipe params
    HANDLE hCreateNamedPipe;
    char szInputBuffer[1023];
    char szOutputBuffer[1023];
    //Connect to named pipe params
    BOOL bConnectNamedPipe;
    //Write file params
    char szWriteFileBuffer[] = "WRITING TO FILE";
    DWORD dwWriteBufferSize = sizeof(szWriteFileBuffer);
    DWORD dwNoBytesRead;
    //FlushFileBuffers param
    BOOL bFlushFileBuffers;
    //ReadFile params
    BOOL bReadFile;
    char szReadFile[1023];
    DWORD dwReadBufferSize = sizeof(szReadFile);
    DWORD dwNoBytesRead;
    


    //CreateNamedPipe operation
    hCreateNamedPipe = CreateNamedPipe(L"\\\\.\\pipe\\MYNAMEDPIPE", PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE|PIPE_READMODE_MESSAGE|PIPE_WAIT, PIPE_UNLIMITED_INSTANCES, 1023, 1023, NMPWAIT_USE_DEFAULT_WAIT, NULL);
    if (hCreateNamedPipe == INVALID_HANDLE_VALUE) { std::cout << "NamedPipe Creation failed & error no. is " << GetLastError() << std::endl;}

    //ConnectNamedPipe operation
    bConnectNamedPipe = ConnectNamedPipe(hCreateNamedPipe, NULL);
    if (bConnectNamedPipe == 0)
    {
        std::cout << "Connect to named pipe failed with error " << GetLastError() << std::endl;
    }
    else { std::cout << "CONNECTION SUCCESS" << std::endl; }

    //WriteFile operation
    BOOL bWriteFile;
    bWriteFile = WriteFile(hCreateNamedPipe,szWriteFileBuffer, dwWriteBufferSize, &dwNoBytesRead, NULL);
    if (bWriteFile == FALSE)
    {
        std::cout << "WrtieFile failed with " << GetLastError() << std::endl;
    }
    else
    {
        std::cout << "WriteFile success" << std::endl;
    }

    //FlushFileBuffers operation
    bFlushFileBuffers = FlushFileBuffers(hCreateNamedPipe);
    if (bFlushFileBuffers == FALSE) { std::cout << "FlushFileBuffers failed with " << GetLastError() << std::endl; }
    else
    {
        std::cout << "FLushFileBuffers succeeded" << std::endl;
    }

    //ReadFile operation
    bReadFile = ReadFile(hCreateNamedPipe,szReadFile,dwReadBufferSize,&dwNoBytesRead, NULL);
    if (bReadFile == FALSE)
    {
        std::cout << "ReadFile failed with " << GetLastError() << std::endl;
    }
    else
    {
        std::cout << "ReadFile success" << std::endl;
    }

   DisconnectNamedPipe(hCreateNamedPipe);

   CloseHandle(hCreateNamedPipe);


}


