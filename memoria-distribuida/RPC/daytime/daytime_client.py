import xmlrpc.client
import datetime  
import sys


if len(sys.argv) != 3:
    printf("sys.argv[0] <ip> <porta>")
    sys.exit(0)

ip = sys.argv[1]
porta = int(sys.argv[2])

server = xmlrpc.client.ServerProxy(f"http://{ip}:{porta}")

print(f'{server.daytime()}')