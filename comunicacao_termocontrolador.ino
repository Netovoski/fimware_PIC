#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <queue.h>
#include <Wire.h>

#define Aumenta__temperatura 01
#define Diminue_temperatura 02
#define Sem_comunicacao_arduino 03
#define Sem_comunicacao_computador 04
#define esperando_comunicacao 05
#define reseta_dados 06
#define mantem_temperatura 07

int statusA = mantem_temperatura;
int conta=0;
QueueHandle_t Dados;
SemaphoreHandle_t semaforoInterrupcao;

void setup() {
  Wire.begin(0x0A);//defini o inicio de uma comunicacao i2c como slave, com endereço 0x0A
  Wire.onReceive(getDados);//define a funcao de interrupção quando houver mensagem a receber
  Wire.onRequest(sendDados);//define a funcao de interrupção quando houver solicitacao de dados do master
  // digitalWrite(SCL, LOW); //define a saida digital para o scl como low. deve ser ligado no pino A5
  // digitalWrite(SDA, LOW);//define a saida digital para o SDA como low. deve ser ligado no pino A4
  Dados = xQueueCreate(10, sizeof(char)); //fila para enviar dados entre as task
  semaforoInterrupcao = xSemaphoreCreateBinary(); //contrucao do semáforo para controlar o recebimento de dados pelo i2c
  xTaskCreate(TaskRecebimento, "recebimento", 128, 1000, 1, NULL); //criacao de task para controlar o recebimento de dados do i2c
  xTaskCreate(Taskcomunicacao, "comunicacao", 128, 1000, 1, NULL); //criacao de task para controlar a comunicacao com o computador
  Serial.begin(9600);
}

void loop() {}
//funcao de interrupcao  quando há dados a serem recebidos no i2c
void getDados(int numBytes) {
  xSemaphoreGiveFromISR(semaforoInterrupcao, NULL);
}
//funcao de interrupcao  quando há solicitacao de dados pelo master no i2c
void sendDados() {
  Wire.write((char)statusA);
  if(conta<1){
  statusA = mantem_temperatura;
  }else{
    conta--;
  }
}

//task que controla o recebimento de dados no i2c
void TaskRecebimento(void *pvParameters) {
  char dado = 0;
  while (true) {
    if (xSemaphoreTake(semaforoInterrupcao, portMAX_DELAY) == pdPASS) { /*semáforo de interruçã*/
      while (0 < Wire.available())/*verifica se há dados recebidos no i2c*/
      {
        dado = Wire.read();/*le os dados recebidos no i2c*/
        vTaskDelay(1 / portTICK_PERIOD_MS);
        Serial.println((int)dado);
      }
    }
    vTaskDelay(30 / portTICK_PERIOD_MS);
  }
}

//task que controla a comunicacao com o computador, enviando dados lidos da temperatura no sensor para o computador
void Taskcomunicacao(void *pvParameters) {
  int recebido = mantem_temperatura;
  while (true) {
    if (Serial.available()) {
      recebido = Serial.parseInt();
      if (recebido > 0 && recebido < 8) {
        statusA = recebido;
      }else if(recebido==160){
        statusA=Sem_comunicacao_arduino;
        conta=200;
      }
    } 
    vTaskDelay(30 / portTICK_PERIOD_MS);
  }
}
