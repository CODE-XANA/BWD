import sys
import string
import os

# Fonction pour lire le contenu du fichier source C++
def read_source():
    source = open("poc.cpp", "rt")
    data = source.read()
    source.close()
    return data

# Fonction pour lire le contenu du fichier binaire contenant le shellcode
def read_shellcode():
    payload = open("payload.bin", "rb")
    data = payload.read()
    payload.close()
    return data

def main():
    # Lecture du contenu du fichier source C++
    source = read_source()

    # Lecture du contenu du fichier binaire contenant le shellcode
    payload = read_shellcode()

    # Formatage du shellcode en une chaîne hexadécimale utilisable dans le code C++
    format_payload = '"\\x' + '\\x'.join(hex(x)[2:] for x in payload) + '";'

    # Remplacement de la déclaration du tableau shellcode dans le code source avec le shellcode formaté
    new_code = source.replace('unsigned char shellcode[] = "";', 'unsigned char shellcode[] = ' + format_payload)

    # Écriture du nouveau code dans un nouveau fichier
    pwn = open("new-poc.cpp", "w+")
    pwn.write(new_code)
    pwn.close()

    # Compilation du nouveau fichier C++ en un exécutable Windows
    os.system("x86_64-w64-mingw32-g++ --static new-poc.cpp -o poc.exe")

if __name__ == "__main__":
    main()
