#include <Wire.h> // Biblioteca para comunicação I2C
#include <LiquidCrystal_I2C.h> // Biblioteca para controlar displays LCD com I2C
#include <Adafruit_RGBLCDShield.h> // Biblioteca para o LCD com fundo RGB
#include <utility/Adafruit_MCP23017.h> // Biblioteca para o controle de I/O expandidos (se necessário)

// Inicializa o display LCD com endereço 0x27, 16 colunas e 2 linhas
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Definindo os pinos para os LEDs e o buzzer
int ledVerde = 13;
int ledAmarelo = 12;
int ledVermelho = 11;
int buzzer = 7;
int ldrPin = A0; // Pino do LDR (sensor de luz)
int leituraLuz = 0; // Variável para armazenar a leitura do LDR

// Caracteres personalizados para criar o símbolo ∞ (infinito)
byte name1x5[] = {
  B00000, B00000, B00000, B00000,
  B00000, B00000, B00000, B00000
};

byte name0x6[] = {
  B00000, B00111, B01000, B10000,
  B10000, B10000, B01000, B00111
};

byte name0x7[] = {
  B00000, B00000, B10001, B01010,
  B00100, B01010, B10001, B00000
};

byte name0x8[] = {
  B00000, B11100, B00010, B00001,
  B00001, B00001, B00010, B11100
};

// Função de inicialização do sistema
void setup() {
  lcd.init(); // Inicializa o LCD
  lcd.backlight(); // Ativa a luz de fundo do LCD

  // Define os pinos como saída para os LEDs e o buzzer
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(buzzer, OUTPUT);

  // Exibe mensagem de boas-vindas no LCD
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("BEM-VINDO A");
  delay(1500); // Pausa de 1.5 segundos

  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("INFINITY");
  delay(1500); // Pausa de 1.5 segundos

  // Cria os caracteres personalizados para o símbolo ∞
  lcd.createChar(0, name1x5);
  lcd.createChar(1, name0x6);
  lcd.createChar(2, name0x7);
  lcd.createChar(3, name0x8);

  // Exibe o símbolo do infinito (∞) após a palavra "INFINITY"
  lcd.clear();
  lcd.setCursor(5, 1);
  lcd.write(byte(0));
  lcd.setCursor(6, 0);
  lcd.write(byte(1));
  lcd.setCursor(7, 0);
  lcd.write(byte(2));
  lcd.setCursor(8, 0);
  lcd.write(byte(3));
  delay(2000); // Deixa o símbolo visível por 2 segundos

  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("MONITORAMENTO");
  delay(1500); // Pausa de 1.5 segundos

  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("SISTEMA ATIVO");
  delay(2000); // Pausa de 2 segundos

  lcd.clear();
}

// Função principal (loop)
void loop() {
  leituraLuz = analogRead(ldrPin); // Lê o valor do LDR (sensor de luz)
  // Mapeia a leitura do LDR de 0-1023 para 100-0 e limita entre 0 e 100
  int luzPercent = constrain(map(leituraLuz, 0, 1023, 100, 0), 0, 100);

  // Exibe a porcentagem de luz no LCD
  lcd.setCursor(0, 0);
  lcd.print("Luz: ");
  lcd.print(luzPercent);
  lcd.print("% ");

  // Verifica o nível de luz e aciona os LEDs e buzzer
  if (luzPercent > 50) {
    // Se a luz for crítica (acima de 50%), acende o LED vermelho e ativa o buzzer
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, HIGH);
    digitalWrite(buzzer, HIGH);

    lcd.setCursor(0, 1);
    lcd.print("CRITICO!       ");
    delay(3000); // Exibe por 3 segundos
    digitalWrite(buzzer, LOW); // Desativa o buzzer

  } else if (luzPercent >= 30 && luzPercent <= 50) {
    // Se a luz estiver em um nível de alerta (30% a 50%), acende o LED amarelo
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, HIGH);
    digitalWrite(ledVermelho, LOW);
    digitalWrite(buzzer, LOW);

    lcd.setCursor(0, 1);
    lcd.print("Alerta! Luz alta.");
    
  } else {
    // Se a luz estiver ok (abaixo de 30%), acende o LED verde
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, LOW);
    digitalWrite(buzzer, LOW);

    lcd.setCursor(0, 1);
    lcd.print("Ambiente OK     ");
  }

  delay(1000); // Espera 1 segundo antes de fazer uma nova leitura
}
