from threading import Thread, Semaphore
from random import randint
from time import sleep

FILA_SIZE = 1024

fila = [None] * FILA_SIZE

indexEscrita = 0
indexLeitura = 0

semaforoFila = Semaphore(1)
semaforoLeitores = Semaphore(20)

count = 0
mutexCount = Semaphore(1)

maxLido = 0
mutexLido = Semaphore(1)


def adicionarNaFila(valor):
    global indexEscrita, fila

    fila[indexEscrita] = valor
    indexEscrita = (indexEscrita + 1) % FILA_SIZE


def lerDaFila(quantidadeLeitura):
    global indexLeitura, fila

    for i in range(quantidadeLeitura):
        posicao = (indexLeitura + i) % FILA_SIZE

        print(
            f"Lendo {fila[posicao]} "
            f"na posição {posicao}"
        )

    return quantidadeLeitura


def produtor(threadId):
    global indexLeitura, maxLido

    while(True):
            
        semaforoFila.acquire()

        # Atualiza a posição de leitura
        # considerando o maior avanço dos leitores.
        mutexLido.acquire()

        indexLeitura = (indexLeitura + maxLido) % FILA_SIZE
        maxLido = 0

        mutexLido.release()

        print(f"Thread[{threadId}] produzindo")

        for i in range(40):
            adicionarNaFila(randint(0, 1234))

        semaforoFila.release()

        sleep(1)


def leitor(threadId):
    global count, maxLido

    while(True):

        semaforoLeitores.acquire()

        mutexCount.acquire()

        if count == 0:
            semaforoFila.acquire()

        count += 1

        mutexCount.release()

        quantidade = randint(0, 10)

        print(f"Leitor {threadId} iniciou leitura")

        lido = lerDaFila(quantidade)

        mutexLido.acquire()

        if lido > maxLido:
            maxLido = lido

        mutexLido.release()

        mutexCount.acquire()

        count -= 1

        if count == 0:
            semaforoFila.release()

        mutexCount.release()

        semaforoLeitores.release()
        sleep(2)

def main():

    threadProdutor = Thread(
        target=produtor,
        args=(0,)
    )

    threadProdutor.start()

    threadConsumidor = []

    for i in range(100):
        t = Thread(
            target=leitor,
            args=(i,)
        )

        threadConsumidor.append(t)

    for t in threadConsumidor:
        t.start()

    for t in threadConsumidor:
        t.join()


if __name__ == "__main__":
    main()