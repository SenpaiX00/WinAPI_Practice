int main() {
   

    BOOL bDIR;
    bDIR = CreateDirectory(
        L"C:\\Users\\X00Ge\\TEST",
        NULL
    );
    if (bDIR == FALSE) { std::cout << "creatdirectory failed with "<<GetLastError()<<std::endl; }
    printf("createDir success!");

    return 0;



}
