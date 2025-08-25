// Converte Temperatura Analógica

float lerTemperaturaAnalogica(int pino, int numLeituras) {
  long somaLeituras = 0;

  for (int i = 0; i < numLeituras; i++) {
    somaLeituras += analogRead(pino);
    delay(5);
  }

  float leituraMedia = somaLeituras / (float)numLeituras;
  float volt = leituraMedia * (vcc / 4095.0);
  float rNTC = rFixo * ((vcc / volt) - 1.0);
  float tempK = 1.0 / ((1.0 / T0Kelvin) + (1.0 / beta) * log(rNTC / R0));

  return tempK - 273.15;
}

void publicarTemperatura(){
  
  tempAtual = lerTemperaturaAnalogica(pinoTemperatura, 10);

  // Verificando Alteração na Temperatura

  if (tempAtual == tempAnterior) {
    return;
  }

  Serial.print(F("Temperatura Enviada: "));
  Serial.print(tempAtual, 2);
  Serial.println(F("°C"));

  // Envio / Registro no Feed "sensorTemperatura"

  temperatura->save(tempAtual);
  tempAnterior = tempAtual;

  // Serial.print("Temperatura Analógica: ");
  // Serial.println(analogRead(pinoTemperatura));
}