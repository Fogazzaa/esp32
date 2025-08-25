#define pinoTemperatura 34
#define pinoLed 14

#include <math.h>
#include "AdafruitIO_WiFi.h"

// Configuração do WiFi
#define WIFI_SSID "fogazzaaa"
#define WIFI_PASS "fogazzaaa"

// Autenticação AdafuritIO
#define IO_USERNAME "fogazza"
#define IO_KEY "aio_yuwn43VjTMw8ncn46128ivfdanA6"

// Autenticação AdafruitIO - do Dri
// #define IO_USERNAME "adrianosenai604"
// #define IO_KEY "aio_drCL54AkFANKA5SxTwvGUu8Y3cCJ"

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// AdafruitIO_Feed *temperatura = io.feed("sensorTemperatura");  // Variável / Ponteiro para Referenciar o Feed "sensorTemperatura"

AdafruitIO_Feed *temperatura = io.feed("sensorTemperatura");  // Variável / Ponteiro para Referenciar o Feed "sensorTemperatura"

// Controle de Envio de Dados
float tempAtual = 0;
float tempAnterior = -1;

const float rFixo = 10000.0;    // Resistor do Projeto (OHMS)
const float beta = 3950.0;      // Constante Beta do NTC (Fornecida pelo Fabricante)
const float R0 = 10000.0;       // Normal do Sensor de Temperatura (OHMS)
const float T0Kelvin = 298.15;  // 25° em Kelvin
const float vcc = 3.3;          // Tensão de Operação

void setup() {

  pinMode(pinoLed, OUTPUT);
  pinMode(pinoTemperatura, INPUT);
  Serial.begin(115200);

  while (!Serial)
    ;

  Serial.println("Conectando com AdafruitIO");
  io.connect();

  int numTentativas = 0;

  while (io.status() < AIO_CONNECTED) {
    Serial.print(numTentativas);
    Serial.println(" - Conexão Ainda Não Realizada");
    numTentativas = numTentativas + 1;
    delay(500);
  }

  // Mostra status da conexão

  Serial.println();
  Serial.println(io.statusText());

  // Configuração do Callback, quando o feed recebe(atualizar) um valor

  temperatura->onMessage(recebeTemperatura);  // Registra a função de Callback

  delay(1000);
}

void loop() {

  io.run();  // Manter a conexão com a AdrafuitIO Ativa

  // publicarTemperatura();   // Função de Publicar Temperatura

  delay(3000);
}
