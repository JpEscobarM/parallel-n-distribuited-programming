import socket
import sys


if len(sys.argv) != 2:
    print(f'{sys.argv}<porta>')
    sys.exit(0)

ip = 'localhost'
porta = int(sys.argv[1])

soquete = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

soquete.bind((ip,porta))

soquete.listen(50)

while True:
    s,cliente = soquete.accept() #novo socket para cada cliente
    msg = s.recv(1024).decode()
    print(f'Recebi: {msg} ORIGEM: {cliente}')
    s.send('TESTE MENSAGEM'.encode())
    s.close()

soquete.close()
