import socket
import sys


if len(sys.argv) != 3:
    print(f'{sys.argv[0]} <ip> <porta>')
    sys.exit(0)

ip = sys.argv[1]
porta = int(sys.argv[2])

soquete = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

soquete.sendto('eita bixo sabido'.encode(),(ip,porta))
msg, end = soquete.recvfrom(1024)
print(f'Recebi: {msg.decode()}')

soquete.close