# Primeira Implementação
------------------------
### Introdução
Essa é uma solução do problema Modus Hall para a disciplina de Sistemas
Operacionais do segundo semestre de 2020.

### Explicação
#### Variáveis globais
Cria-se dois contadores, a saber heathens e prudes como variáveis de controle,
de tal modo que sempre que uma rotina de um desses tipos for executada
o seu respectivo contador será incrementado.

Cria-se também uma variável de nome mutex que é inicializada com a constante
simbólica PTHREAD\_MUTEX\_INITIALIZER.

Também são definidos dois semáforos indicadores de turno tanto para heathens
como para prudes.

#### run
A main é bem direta ao ponto, são declaradas uma variável contadora
genérica(i) para ser utilizada nos loops subsequentes. Juntamente com o número
de heathens e prudes, o valor inicial do semáforo(start) e ponteiros para os
vetores dinâmicos de threads de cada entidade: tid\_prudes,
tid\_heathens.

Em seguida inicia-se o número de heathens e prudes para um número aleatório
gerado por um gerador linear congruente(lcg) limitado de 0 a 81.

Então é definido o valor inicial da variável start. Se o número de heathens
for extritamente maior que prudes então start recebe 1, caso contrário
recebe 0.

Então os vetores de threads são alocados dinâmicamente:
```
tid_heathens = malloc(num_heathens * sizeof(pthread_t));
tid_prudes = malloc(num_prudes * sizeof(pthread_t));
```

Logo os semáforos de cada uma das entidades: prudes e heathens são
iniciados, referentes ao valor da variável start. Sendo que um recebe o valor
inicial oposto ao outro, como visto em:
```
sem_init(&heathens_turn, 0, start)

sem_init(&prudes_turn, 0, !start)
```

Assim, basta criar as threads e colocar as funções respectivas a heathens
e prudes para rodar nelas.

Um bom observador vai perceber que a criação e união de threads foram separadas
em dois casos, se num\_heathens >= num\_prudes e caso contrário. Isso eu fiz
ocorre para evitar casos limites de deadlock.

#### Funções de entidade
Há duas funções com objetivo de resolver o problema pra uma entidade: heathens
e prudes. Mas como elas são espelhadas explicarei apenas uma delas, a saber a
função heathens.

Ao início da função ocorre um incremento do contador de heathens, a partir da
aquisição e liberação do mutex. Algo que eu gosto de pensar nessa parte é
que o programa está se comportando como uma fila, então nesse caso ele está
sinalizando sua chegada na fila de processamento.

Então ocorre a aquisição do semáforo de heathens e novamente a aquisição
do mutex. Isso deve ocorrer nessa exata ordem, pois caso contrário a thread
poderia solicitar o mutex sem que seja a vez da sua entidade.

Assim o contador de heathens é decrementado com o fim de sinalizar a sua saída
de nossa fila fictícia.

Dessa maneira ocorrem uma sequência de testes de sanidade para que o programa
rode de maneira adequada. Ou seja se não houver mais heathens e ainda houver
prudes, libere a execução da fila para os prudes. Se houver mais prudes
que heathens libere a execução para os prudes caso contrário libere para os
heathens, ou seja a entidade que tiver o maior número de elementos na fila
recebe a prioridade, com o fim de evitar starvation.

Assim libera-se o mutex.

