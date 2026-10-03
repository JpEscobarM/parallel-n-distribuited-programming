# OPEN-MP

- API para programação paralela, (APPLICATION PROGRAM INTERFACE), utilizado em sistemas que fazem uso de memória compartilhada, segue o mesmo modelo das threads.

- Não possui mecanismos para troca de mensagens

- Modelo de execução fork-join, ou seja, uma thread mestre inicia o paralelismo e ao finalizar as threads sao sincronizadas novamente na thread mestre

THREAD-MESTRE
|
|-THREAD[0]-THREAD[1]-THREAD[2]...
|
|--ponto de uniao das threads
|
|finaliza.

## COMPARTILHAMENTO DE VARIAVIES

- variaveis são compartilhadas por padrão, ou seja, todas as threads podem ler e modificar as variaveis.

- para tornar uma variavel privada, é preciso declarar ela como *private* dessa forma cada thread, **antes do inicio da execução** , faz uma cópia dessa variável, logo, cada cópia possuirá um endereço de memória diferente, como uma variável declarada localmente para cada thread.


## PARALELIZAÇÃO

Para criar a paralelização no programa, o OpenMP utiliza de duas abordagens. 

- Paralelização de laços(loop level)
- Criação de regiões paralelas (parallel region);

### LOOP LEVEL

- precisa informar o **inicio** e o **fim** do código (laços), que vao ser paralelizados, e o número de threads que vão executar o laço
- o código paralelo é gerado pelo próprio compilador

para o loop level se usa:

```
#pragma omp parallel for;
```

- o indice do for mais externo ficará sempre privado por *default*

- é colocada uma **barreira** implícita no final do laço, dessa forma conforme as threads vão finalizando, elas obrigatóriamente preciisam esperar as demais executarem


### PARALLEL REGION

- usado para execução concorrente de um trecho mais genérico de código

- paralelizaçao explicita, o programador deve cuidar race conditions e regioes criticas

- todas as threads executam o mesmo trecho, assim como no loop-level

- o trabalho de cada thread é dividido com um identificador de thread, em conjunto com a estrutura `if`
