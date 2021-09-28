#include <iostream>
#include <Windows.h>
#include <stdio.h>


int main() {
    char chBuffer[] = "this is a test";
    char lpBuf[252];

    BOOL bDIR;
    bDIR = CreateDirectory(
        L"C:\\Users\\X00Ge\\TEST",
        NULL
    );
    if (bDIR == FALSE) { std::cout << "creatdirectory failed with " << GetLastError() << std::endl; }
    printf("createDir success!");

    BOOL vFile;
    vFile = CopyFile(L"C:\\Users\\X00Ge\\TEST\\oldfile.txt", L"C:\\Users\\X00Ge\\TEST\\newfile.txt", TRUE);
    
    BOOL mFile;
    mFile = MoveFile(L"C:\\Users\\X00Ge\\TEST\\oldfile.txt", L"C:\\Users\\X00Ge\\Desktop\\OLDFILE.TXT");


    HANDLE h;
    h = CreateFile(
        L"C:\\Users\\X00Ge\\Desktop\\HUGE_FILE.txt",GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ,NULL,CREATE_NEW,FILE_ATTRIBUTE_NORMAL,NULL
    );

    DWORD dw = sizeof(chBuffer);

    BOOL bFile;
    bFile = WriteFile(
        h,&chBuffer,dw,0,NULL
    );

    ReadFile(h, &lpBuf, dw, 0, NULL);
    std::cout << lpBuf << std::endl;

    CloseHandle(h);
    
    BOOL bCreateHardLink;
    bCreateHardLink = CreateHardLink(
        L"C:\\Users\\X00Ge\\Desktop\\NEW_FILE.txt",
        L"C:\\Users\\X00Ge\\Desktop\\HUGE_FILE.txt",
        NULL
    );
    if (bCreateHardLink == FALSE) {
        std::cout << "CreateHardLink Failed with " << GetLastError << std::endl;
    }

    BOOL bSymbolicLink;
    bSymbolicLink = CreateSymbolicLink(
        L"C:\\Users\\X00Ge\\Desktop\\FILE.txt",
        L"C:\\Users\\X00Ge\\Desktop\\sample.txt",
        0
    );
    if (bSymbolicLink == FALSE) { std::cout << "Symbolic linking failed with " << GetLastError << std::endl; }

    LONG lstat;
    HKEY hKey;

    lstat = RegCreateKeyEx(
            HKEY_LOCAL_MACHINE,
            L"Software\\Test\\Product\\SmartID",
            0,
            NULL,
            REG_OPTION_NON_VOLATILE,
            KEY_ALL_ACCESS|KEY_WOW64_64KEY,
            NULL,
            &hKey,
            NULL
        );

    if (lstat != ERROR_SUCCESS) { std::cout << "RegCreateKeyEx failed with " << GetLastError << std::endl; }
    std::cout << "REGCREATE SUCCESSFUL" << std::endl;
    
    RegCloseKey(hKey);


    //ANSI
    BOOL bCompName;
    char a[256]; //for LPWSTR use wchar_t!!!
    DWORD d = sizeof(a);
    bCompName = GetComputerNameA(
        a, &d
    );
    if (bCompName == FALSE) { std::cout << "FAILED WITH " << GetLastError << std::endl; }
    printf("comp name = %s\n", a);


    //wide string version
    wchar_t wBuffer[256];
    DWORD wdw = sizeof(wBuffer);
    BOOL wBCompName;
    wBCompName = GetComputerNameW(wBuffer, &wdw);
    std::wcout << "Wide computer name = " << wBuffer << std::endl;


    return 0;


}


