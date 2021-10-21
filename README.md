# Lidando com o multiprocessamento  

O Esp32 conta com dois núcleos físicos XRENSA LS6 (dual-core) e o IDF oferece suporte para o multiprocessamento ao usuário.

Multiprocessamento, é a capacidade de rodar um determinado programa na CPU, que possui mais de um núcleo físico. No caso do ESP32, existem dois processadores, podendo assim balancear suas tarefas, dessa forma podemos controlar em qual núcleo físico determinado processo irá rodar.

O multiprocessamento se divide em dois grupos:

* Assimétrico – Tendo por exemplo dois núcleos, cada um deles irá acessar uma área específica da memória fisicamente separadas, podendo assim receber instruções de localidades diferentes e trocam informações em uma área de memória compartilhada. A vantagem é que podemos ter dois núcleos funcionando sem relação um com o outro, podendo executar comados distintos. 

* Simétrico – O ESP32, opera nessa categoria, possuindo assim dois núcleos idênticos, compartilhando tudo, desde memória, periféricos e consumindo a mesma instância de firmware. Dessa forma, embora cada núcleo esteja executando um pedaço diferente do código, esses pedaços pertencem ao mesmo binário do firmware.
