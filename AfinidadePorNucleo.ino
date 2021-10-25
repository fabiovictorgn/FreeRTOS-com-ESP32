#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

// As funções de task basicamente irão imprimir o uptime, ou seja, quantos ticks do RTOS já se passaram desde
// que ele começou a rodar juntamente com o ID do núcleo em que essa task está executando.

void TaskRunningOnAppCore(void *arg){
  while(1) {
    Serial.print(__func__);
    Serial.print(" : ");
    Serial.print(xTaskGetTickCount());
    Serial.print(" : ");
    Serial.print("This loop runs on APP_CPU which id is:");
    Serial.println(xPortGetCoreID());
    Serial.println();
    vTaskDelay(100);
   }
}


void TaskRunningOnProtocolCore(void *arg) {
  while(1) {
    Serial.print(__func__);
    Serial.print(" : ");
    Serial.print(xTaskGetTickCount());
    Serial.print(" : ");
    Serial.print("This loop runs on PRO_CPU which id is:");
    Serial.println(xPortGetCoreID());
    Serial.println();
    vTaskDelay(100);
   }
}


// Temos uma função da API do RTOS do ESP32, que é uma versão modificada do FreeRTOS.
// Essa nova função para criação de tasks é igualzinha a do FreeRTOS, exceto pelo parâmetro extra.
void setup(){
    Serial.begin(115200);

    // xTaskCreatePinnedToCore é utilizada para criar tasks (as "multiplas mains" da sua aplicação) 
    // e adicionalmente assinalar ou não uma afinidade por núcleo 
   
    xTaskCreatePinnedToCore(TaskRunningOnAppCore, "TaskOnApp", 2048, NULL, 4, NULL, APP_CPU_NUM);   
    xTaskCreatePinnedToCore(TaskRunningOnProtocolCore, "TaskOnPro", 2048, NULL, 8, NULL, PRO_CPU_NUM);
    
    // - 1° parâmetro: Função principal da sua task.
    // - 2° parâmetro: Nome para essa task.
    // - 3° parâmetro: Tamanho de pilha para essa task, ou seja, espaço em bytes que essa função irá utilizar. 
    // - 4° parâmetro: Argumento para ser passado a task.
    // - 5° parâmetro: Prioridade dessa task,quanto maior o número, maior a prioridade, o RTOS do ESP oferece 25 níveis.
    // - 6° parâmetro: Local para guardar o Identificador único para essa task.
    // - 7° parâmetro: Afinidade dessa task, podendo ter afinidade com PRO_CPU, APP_CPU ou "tskNO_AFFINITY", caso queira
    //      que o RTOS decida em quais núcleos essa task vai rodar.
}


// loop() por si só já é uma task que roda no núcleo APP_CPU
// Ela fica continuamente mostrando no console em qual núcleo ele está executando
void loop(){
    Serial.print(__func__);
    Serial.print(" : ");
    Serial.print(xTaskGetTickCount());
    Serial.print(" : ");
    Serial.print("Arduino loop is running on core:");
    Serial.println(xPortGetCoreID());
    Serial.println();
    delay(500);
}

    
