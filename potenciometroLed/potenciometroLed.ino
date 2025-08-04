// Pinos usados
// GPIO34 = entrada analógica (ADC1_CH6), sem função digital (somente leitura ADC)
#define pinoPotenciometro 34

// GPIO14 = saída digital (PWM disponível)
#define pinoLed 14            

void setup() {
  Serial.begin(115200);          // Inicia o monitor serial
  pinMode(pinoLed, OUTPUT);      // Define LED como saída
  
  delay(1000); // Pausa Estratégica
}

void loop() {
  int valorAnalogico = analogRead(pinoPotenciometro);  // Lê valor do potenciômetro (0-4095)
  int brilhoLed = map(valorAnalogico, 0, 4095, 0, 255); // Mapeia para PWM (0-255)

  analogWrite(pinoLed, brilhoLed); // Define brilho do LED

  // Exibe valores no Monitor Serial
  Serial.print("Potenciômetro: ");
  Serial.print(valorAnalogico);
  Serial.print(" -> PWM: ");
  Serial.println(brilhoLed);

  delay(200); // Pausa Estratégica
}