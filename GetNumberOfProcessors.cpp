//Using Native API, NOT WinAPI
//
#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <sysinfoapi.h>
#include <winternl.h>


int main()
{

	SYSTEM_BASIC_INFORMATION sbi;
	NtQuerySystemInformation(SystemBasicInformation, &sbi, sizeof(sbi), nullptr);
	std::cout << "ntdll says no. of processors = " << sbi.NumberOfProcessors << std::endl;
	if (sbi.NumberOfProcessors == 1) { ExitProcess(0); }
}

