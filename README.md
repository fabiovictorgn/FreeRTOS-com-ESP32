# Lidando com o multiprocessamento  

O Esp32 conta com dois núcleos físicos XRENSA LS6 (dual-core) e o IDF oferece suporte para o multiprocessamento ao usuário.

Multiprocessamento, é a capacidade de rodar um determinado programa na CPU, que possui mais de um núcleo físico. No caso do ESP32, existem dois processadores, podendo assim balancear suas tarefas, dessa forma podemos controlar em qual núcleo físico determinado processo irá rodar.

O multiprocessamento se divide em dois grupos:

* Assimétrico – Tendo por exemplo dois núcleos, cada um deles irá acessar uma área específica da memória fisicamente separadas, podendo assim receber instruções de localidades diferentes e trocam informações em uma área de memória compartilhada. A vantagem é que podemos ter dois núcleos funcionando sem relação um com o outro, podendo executar comados distintos. 

* Simétrico – O ESP32, opera nessa categoria, possuindo assim dois núcleos idênticos, compartilhando tudo, desde memória, periféricos e consumindo a mesma instância de firmware. Dessa forma, embora cada núcleo esteja executando um pedaço diferente do código, esses pedaços pertencem ao mesmo binário do firmware.

## Suporte ao multiprocessamento simétrico no ESP32

![Sem título](https://user-images.githubusercontent.com/77392769/138317163-c3b5eebb-8e1d-4ae1-9afc-0a8af7c2c282.png)

Possuindo dois núcleos:

* PRO_CPU – É o núcleo padrão, que quando o ESP32 é inicializado apenas esse núcleo recebe instruções da memória. 
* APP_CPU – É o núcleo secundário, inicia desativado, mas quando ativado começa a receber instruções a partir do valor inicial colocado no contador de programa. 

Quando utilizamos o IDF, ambos os núcleos são inicializados, já estando a disposição para rodar quando o programa alcança a função main(), setup() ou loop(). 
Por padrão a função loop() roda na APP_CPU, nesse caso, podemos mover funções da aplicação para executarmos somente na PRO_CPU, tendo assim, mais processamento livre. 

## Delegando funções para a PRO_CPU

Veja os códigos colocados em “DelegandoFuncoesParaPRO_CPU.io”, lá é explicado o processo. 

* esp_ipc_call(): Vale ressaltar o seu funcionamento. Essa função será executada em paralelo com a que à chamou, ou seja, as duas extarão em execução sem sabermos qual terminará primeiro. 
* esp_ipc_call_blocking(): Visto isso, temos essa função que funciona de forma semelhante, a diferença é que a função que a chama aguarda sua execução.  É interessante quando     queremos sincronizar o processamento dos cores.  

# Continua...
