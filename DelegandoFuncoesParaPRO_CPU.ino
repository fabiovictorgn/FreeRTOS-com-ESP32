#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_ipc.h>

void setup(){
 Serial.begin(115200);
}

void LoopOnProCpu(void *arg) {
 (void)arg;
 Serial.print("Este loop é executado em PRO_CPU, o id é:");
 Serial.println(xPortGetCoreID()); //retorna o número do núcleo onde aquela função está executando
}

void loop(){
 //Loop padrão é executado em APP_CPU
 Serial.print("Este loop é executado em APP_CPU, o id é:");
 Serial.println(xPortGetCoreID());

 //Executa o LoopOnAppCpu no PRO_CPU
 esp_ipc_call(PRO_CPU_NUM, LoopOnProCpu, NULL);
 //Essa função recebe três parâmetros, o id do núcleo, a função que desejamos executar e um argumento
 //caso desejemos passar uma informação para essa função.
}
