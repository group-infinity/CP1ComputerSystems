#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int ledVerde = 13;
int ledAmarelo = 12;
int ledVermelho = 11;
int buzzer = 7;
int ldrPin = A0;
int leituraLuz = 0;

// Caracteres personalizados para um ∞ mais bonito (2x2)
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

void setup() {
  lcd.init();
  lcd.backlight();

  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(buzzer, OUTPUT);

  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("BEM-VINDO A");
  delay(1500);

  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("INFINITY");
  delay(1500);

  // Criar caracteres personalizados
  lcd.createChar(0, name1x5);
  lcd.createChar(1, name0x6);
  lcd.createChar(2, name0x7);
  lcd.createChar(3, name0x8);

  // Desenhar o símbolo do infinito (∞) logo após "INFINITY"
  lcd.clear();
  lcd.setCursor(5, 1);
  lcd.write(byte(0));
  lcd.setCursor(6, 0);
  lcd.write(byte(1));
  lcd.setCursor(7, 0);
  lcd.write(byte(2));
  lcd.setCursor(8, 0);
  lcd.write(byte(3));
  delay(2000); // deixar visível por 2 segundos

  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("MONITORAMENTO");
  delay(1500);

  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("SISTEMA ATIVO");
  delay(2000);

  lcd.clear();
}

void loop() {
  leituraLuz = analogRead(ldrPin);
  int luzPercent = constrain(map(leituraLuz, 0, 1023, 100, 0), 0, 100);

  lcd.setCursor(0, 0);
  lcd.print("Luz: ");
  lcd.print(luzPercent);
  lcd.print("% ");

  if (luzPercent > 50) {
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, HIGH);
    digitalWrite(buzzer, HIGH);

    lcd.setCursor(0, 1);
    lcd.print("CRITICO!       ");
    delay(3000);
    digitalWrite(buzzer, LOW);

  } else if (luzPercent >= 30 && luzPercent <= 50) {
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, HIGH);
    digitalWrite(ledVermelho, LOW);
    digitalWrite(buzzer, LOW);

    lcd.setCursor(0, 1);
    lcd.print("Alerta! Luz alta.");
    
  } else {
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, LOW);
    digitalWrite(buzzer, LOW);

    lcd.setCursor(0, 1);
    lcd.print("Ambiente OK     ");
  }

  delay(1000);
}

