#define pinoLed 14

#include <math.h>
#include "AdafruitIO_WiFi.h"

// Configuração do WiFi
#define WIFI_SSID "fogazzaaaa"
#define WIFI_PASS "fogazzaaaa"

// Autenticação AdafuritIO
#define IO_USERNAME ""
#define IO_KEY ""

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

AdafruitIO_Feed *botaoled = io.feed("botaoled");

void setup() {

  pinMode(pinoLed, OUTPUT);
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

  botaoled->onMessage(handleBotaoLed);  // Registra a função de Callback

  delay(1000);
}

void loop() {

  io.run();  // Manter a conexão com a AdrafuitIO Ativa

  //delay(3000);
}
