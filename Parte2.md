# O ESP32 é multitarefa e dual-core, o que podemos fazer com isso  

Um grande benefício no uso de RTOS nos sistemas embarcados está no isolamento de certos pedaços de uma aplicação, ou seja, eu posso dividir um projeto em duas partes e fazer separadamente sem que, diretamente, os domínios de suas tarefas impactem entre si.

Ao falar sobre RTOS é bom lembrarmos da expressão:"...de ter múltiplas mains na aplicação", e o ESP32 deixa isso significativamente melhor, já que agora o RTOS não entrega fatias de um núcleo por task, mas dois deles de forma que as políticas de execução ganham ainda mais flexibilidade. Obtendo um núcleo extra podemos separar melhor as tarefas, podendo controlar a prioridade e qual núcleo deve lidar mais intensamente com o que. 

Um exemplo é o caso do drone, temos dois domínios de comunicação a base e a do algoritmo de controle. Utilizando o RTOS, escolheríamos as prioridades das tarefas, para que assim a cominação tenha uma resposta arável com os comandos da base e ao mesmo tempo precisamos garantir o ideal funcionamento do algoritmo de estabilidade, de uma forma que não ocorra atrasos. 

## Introduzindo o conceito de afinidade por núcleo

Afinidade de tarefa por núcleo, é basicamente determinar uma tarefa para apenas um determinado núcleo, mesmo se houver outra CPU disponível. De forma similar, uma tesk pode não ter nenhuma afinidade, então, o RTOS lidara com a Tesk entregando-a para um núcleo disponível, essa forma é um protocolo para balancear o processamento dos núcleos. 

O RTOS, utiliza o protocolo de priorizar as tesks com afinidade primeiro, caso o núcleo disponível não encontre nenhuma com afinidade, ele pegara a tesk sem afinidade que terá maior prioridade, caso a prioridade seja a mesma, será por ordem de chegada.  Isso quem faz é o próprio RTOS, o usuário ira se preocupar em determinar se a tesk tem afinidade ou não durante a criação.  

## Exemplo de uso:

Você pode visualizar o código explicado em “AfinidadePorNucleo.ino”, em seguida está um print de seu funcionamento.

![dddd](https://user-images.githubusercontent.com/77392769/138618630-07fd8d76-c9e2-4221-9724-056778751066.png)

As tasks criadas rodam a cada 100ms, e a loop() a cada 500ms, por isso iremos ver a loop executando com menos frequência porém a relação sempre se mantém, para cada 5 execuções das tasks. O mais legal é que se travássemos um dos núcleos, o outro continua executando normalmente. 
