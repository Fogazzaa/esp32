
// Função chamada automaticamente quando o feed receber atualizações

void handleBotaoLed(AdafruitIO_Data *data) {

  bool estadoBotao = data->toBool();

  Serial.print(F("Estado Recebido do Feed: "));
  Serial.println(estadoBotao);

  // Lógica para Acender ou Não o LED

  if (estadoBotao == true) {
    digitalWrite(pinoLed, HIGH);
  }
  else{
    digitalWrite(pinoLed, LOW);
  }
}