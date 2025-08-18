#define pinoTemperatura 34

#include <math.h>
#include "AdafruitIO_WiFi.h"

// Configuração do WiFi
#define WIFI_SSID "fogazzaa"
#define WIFI_PASS "fogazzaa"

// Autenticação AdafuritIO
#define IO_USERNAME "fogazza"
#define IO_KEY "aio_yuwn43VjTMw8ncn46128ivfdanA6"

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// Variável / Ponteiro para Referenciar o Feed "sensorTemperatura"
AdafruitIO_Feed *temperatura = io.feed("sensorTemperatura");

// Controle de Envio de Dados
float tempAtual = 0;
float tempAnterior = -1;

const float rFixo = 10000.0; // Resistor do Projeto (OHMS)
const float beta = 3950.0; // Constante Beta do NTC (Fornecida pelo Fabricante)
const float R0 = 10000.0; // Normal do Sensor de Temperatura (OHMS)
const float T0Kelvin = 298.15; // 25° em Kelvin
const float vcc = 3.3; // Tensão de Operação

float lerTemperaturaAnalogica(int pino, int numLeituras){
  long somaLeituras = 0;
  
  for(int i = 0; i < numLeituras; i++){
      somaLeituras += analogRead(pino);
      delay(5);
  }

  float leituraMedia = somaLeituras / (float)numLeituras;
  float volt = leituraMedia * (vcc / 4095.0);
  float rNTC = rFixo * ((vcc / volt) - 1.0);
  float tempK = 1.0 / ((1.0 / T0Kelvin) + (1.0 / beta) * log(rNTC / R0));

  return tempK - 273.15;

}

void setup() {
  
  pinMode(pinoTemperatura, INPUT);
  Serial.begin(115200);

  while(!Serial);

  Serial.println("Conectando com AdafruitIO");
  io.connect();

  int numTentativas = 0;

  while(io.status() < AIO_CONNECTED){
    Serial.print(numTentativas);
    Serial.println(" - Conexão Ainda Não Realizada");
    numTentativas = numTentativas + 1;
    delay(500);
  }

  Serial.println();
  Serial.println(io.statusText());

  delay(1000);

}

void loop() {
  
  // Manter a conexão com a AdrafuitIO Ativa

  io.run();

  tempAtual = lerTemperaturaAnalogica(pinoTemperatura, 10);

  // Verificando Alteração na Temperatura

  if(tempAtual == tempAnterior){
    return;
  }

  Serial.print(F("Temperatura Enviada: "));
  Serial.print(tempAtual, 2);
  Serial.println(F("°C"));

  // Envio / Registro no Feed "sensorTemperatura"

  temperatura -> save(tempAtual);
  tempAnterior = tempAtual;

  // Serial.print("Temperatura Analógica: ");
  // Serial.println(analogRead(pinoTemperatura));

  delay(3000);

}
