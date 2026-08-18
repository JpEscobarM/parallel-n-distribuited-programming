import xmlrpc.server
import datetime  
import sys


def daytime():
    return datetime.datetime.today()

if len(sys.argv) != 2:
    printf("sys.argv[0] <porta>")
    sys.exit(0)

porta = int(sys.argv[1])
server = xmlrpc.server.SimpleXMLRPCServer(('',porta))
server.register_function(daytime, 'daytime')
server.serve_forever()