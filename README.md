# Sistemas Distribuídos - Pipes

Este é um trabalho desenvolvido por alunos da
Universidade Federal do RIo de Janeiro - UFRJ
com o objetivo de realizar uma comunicação
interprocessos.

## Produtor
```c
void producer(int write_pipe, int count);
```

Um <em>Produtor</em> é responsável por gerar
números aleatórios até um parâmetro passado
pelo usuário crescentes e escrevê-los em um 
<b>pipe</b>.
Ao atingir o limite definido pelo usuário, a
função envia 0 para o pipe, par aindicar ao
consumidor que é possível parar a leitura.

## Consumidor
```c
void consumer(int read_pipe);
```

Um <em>Consumidor</em> é responsável por
receber um <b>pipe</b> e lê-lo. Após a
leitura, verifica se o número lido é primo, e
, finalmente, imprime uma mensagem na tela
mostrando o número recebido e se o mesmo é
primo. Como dito na função do <em>Produtor</em>
a leitura termina quando o número recebido é
zero.
Ao final, fecha o <b>pipe</b>.

## É primo?
```c
void is_prime(int number);
```

Apenas uma função auxiliar para ser executada
por um consumidor de números.

## Main
```c
void main(int argc, char *argv[]);
```

De fato a função a ser executada. O executável
recebe um número inteiro positivo e cria um
processo filho com a função <em>fork</em>.

Aqui, temos dois processos e o <em>pid</em> do
filho é sempre identificado com 0.

Executando dois processos, caso seja o filho, 
pid == 0, é fechada a escrita e o consumidor
realiza o seu trabalho de leitura e verificação
de se é primo.

Caso seja o processo pai, é fechada a extremidade
de leitura. O produtor inicia seu trabalho.
Como ele será o primeiro a terminar, utilizamos
a função <em>wait</em> para esperar o processo
filho terminar a sua execução.


## Executando o Trabalho
Esta pasta possui um Makefile. Para compilar, basta
fazer:
```
$ make
```

que o compilador irá gerar um executável com
nome padrão <b>pipe</b>. É possível realizar a execução
com:
```
$ make run
```

que o programa executará com uma valor de contador
padrão NUM=50. Caso queira modificar, pode fazer:
```
$ make run NUM=<seu_numero>
```

