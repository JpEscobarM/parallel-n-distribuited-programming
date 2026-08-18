import socket
import sys


if len(sys.argv) != 3:
    print(f'{sys.argv[0]} <ip> <porta>')
    sys.exit(0)

ip = sys.argv[1]
porta = int( sys.argv[2])

soquete = socket.socket(socket.AF_INET,socket.SOCK_STREAM)

soquete.connect((ip,porta))

soquete.send('absolute cinema'.encode())


msg = soquete.recv(1024).decode()
print(f'RECEBI {msg}')

soquete.close();