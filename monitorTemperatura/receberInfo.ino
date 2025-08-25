
// Função chamada automaticamente quando o feed receber atualizações

void recebeTemperatura(AdafruitIO_Data *data) {

  Serial.print("Teste");

  float tempRecebida = data->toFloat();

  Serial.print(F("Temperatura Recebida do Feed: "));
  Serial.print(tempRecebida, 2);
  Serial.println(F("°C"));

  // Lógica para Acender ou Não o LED

  if (tempRecebida <= 36) {
    digitalWrite(pinoLed, HIGH);
  }
  else{
    digitalWrite(pinoLed, LOW);
  }
}