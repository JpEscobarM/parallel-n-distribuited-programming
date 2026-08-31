import xmlrpc.server
import sys


#-------------------------------------------
def funcao(mensagem):
    print(f'Recebi: {mensagem}')
    return f'Martinotto: {mensagem}'

#-------------------------------------------

if len(sys.argv) != 2:
    print(f"{sys.argv[0]} <porta>")
    sys.exit(0)

porta = int(sys.argv[1])

servidor = xmlrpc.server.SimpleXMLRPCServer(('',porta))
servidor.register_function(funcao,'funcao')

servidor.register_multicall_functions()

servidor.serve_forever()