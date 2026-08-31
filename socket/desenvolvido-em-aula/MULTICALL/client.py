import xmlrpc.server
import sys


#-------------------------------------------
def funcao(mensagem):
    print(f'Recebi: {mensagem}')
    return f'Martinotto: {mensagem}'

#-------------------------------------------

if len(sys.argv) != 3:
    print(f"sys.argv[0] <ip> <porta>")
    sys.exit(0)

ip = sys.argv[1]
porta = int(sys.argv[2])


url = f'http://{ip}:{porta}'


client = xmlrpc.client.ServerProxy(url)
mult = xmlrpc.client.MultiCall(client)
mult.funcao('Teste1')
mult.funcao('Teste2')
mult.funcao('Teste3')

resultados = mult()
for r in resultados:
    print(r)

