#include <Wire.h>                // Biblioteca para comunicação I2C
#include <LiquidCrystal_I2C.h>   // Biblioteca para controle do LCD via I2C

// Inicializa o LCD com endereço I2C 0x27, 16 colunas e 2 linhas
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Definição dos pinos
int ledVerde = 13;      // LED verde conectado ao pino 13
int ledAmarelo = 12;    // LED amarelo conectado ao pino 12
int ledVermelho = 11;   // LED vermelho conectado ao pino 11
int buzzer = 7;         // Buzzer conectado ao pino 7
int ldrPin = A0;        // LDR (sensor de luz) conectado ao pino analógico A0
int botaoPin = 2;       // Botão conectado ao pino 2

// Variáveis para controle de tempo
unsigned long tempoAlertaInicio = 0;   // Marca quando o estado de alerta começou
unsigned long tempoCriticoInicio = 0;  // Marca quando o estado crítico começou
unsigned long tempoAlertaTotal = 0;    // Tempo total em estado de alerta (ms)
unsigned long tempoCriticoTotal = 0;   // Tempo total em estado crítico (ms)

// Flags de estado
bool emAlerta = false;           // Indica se o sistema está em estado de alerta
bool emCritico = false;          // Indica se o sistema está em estado crítico
bool mostrandoTempos = false;    // Indica se está mostrando os tempos no LCD
bool botaoPressionado = false;   // Indica se o botão está pressionado
unsigned long ultimoBotaoPress = 0;  // Última vez que o botão foi pressionado

// Caracteres personalizados para o símbolo do infinito (∞)
byte name1x5[] = { B00000, B00000, B00000, B00000, B00000, B00000, B00000, B00000 };
byte name0x6[] = { B00000, B00111, B01000, B10000, B10000, B10000, B01000, B00111 };
byte name0x7[] = { B00000, B00000, B10001, B01010, B00100, B01010, B10001, B00000 };
byte name0x8[] = { B00000, B11100, B00010, B00001, B00001, B00001, B00010, B11100 };

void setup() {
  lcd.init();          // Inicializa o LCD
  lcd.backlight();     // Liga a luz de fundo

  // Configura os pinos como saída ou entrada
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(botaoPin, INPUT_PULLUP); 

  // Sequência de inicialização no LCD
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("BEM-VINDO A");
  delay(1500);
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("INFINITY");
  delay(1500);

  // Cria os caracteres personalizados para o símbolo do infinito
  lcd.createChar(0, name1x5);
  lcd.createChar(1, name0x6);
  lcd.createChar(2, name0x7);
  lcd.createChar(3, name0x8);

  // Desenha o símbolo do infinito (∞) no LCD
  lcd.clear();
  lcd.setCursor(5, 1);
  lcd.write(byte(0));
  lcd.setCursor(6, 0);
  lcd.write(byte(1));
  lcd.setCursor(7, 0);
  lcd.write(byte(2));
  lcd.setCursor(8, 0);
  lcd.write(byte(3));
  delay(2000);

  // Continuação da sequência de inicialização
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

// Função para mostrar os tempos acumulados de alerta e crítico
void mostrarTempos() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Alerta: ");
  lcd.print(tempoAlertaTotal / 1000);  // Converte ms para segundos
  lcd.print("s");

  lcd.setCursor(0, 1);
  lcd.print("Critico: ");
  lcd.print(tempoCriticoTotal / 1000); // Converte ms para segundos
  lcd.print("s");
}

// Função para verificar o botão
void verificarBotao() {
  int leituraBotao = digitalRead(botaoPin);

  if (leituraBotao == LOW) {  // Botão pressionado
    if (!botaoPressionado && (millis() - ultimoBotaoPress) > 50) {  // Verifica se o botão foi acionado a mais de 50ms
      botaoPressionado = true;
      ultimoBotaoPress = millis();
      mostrandoTempos = !mostrandoTempos;  // Alterna entre mostrar e não mostrar tempos

      if (mostrandoTempos) {
        mostrarTempos();  // Atualiza o display com os tempos
      } else {
        lcd.clear();  // Volta para a tela normal
      }
    }
  } else {
    botaoPressionado = false;
  }
}

void loop() {
  verificarBotao();  // Verifica o botão a cada loop

  if (!mostrandoTempos) {  // Se não estiver mostrando tempos, faz o monitoramento normal
    // Faz a média de 10 leituras do LDR para suavizar variações
    int soma = 0;
    for (int i = 0; i < 10; i++) {
      soma += analogRead(ldrPin);
      delay(600);  // Pequeno delay entre leituras
    }
    int media = soma / 10;

    // Converte a leitura analógica para porcentagem (0-100%)
    // Valores 1002 (escuro) e 250 (claro)
    int luzPercent = constrain(map(media, 1002, 250, 0, 100), 0, 100);

    // Mostra a porcentagem de luz no LCD
    lcd.setCursor(0, 0);
    lcd.print("Luz: ");
    lcd.print(luzPercent);
    lcd.print("%    ");

    // Atualiza os tempos acumulados antes de mudar de estado
    unsigned long agora = millis();
    if (emAlerta) {
      tempoAlertaTotal += agora - tempoAlertaInicio;
      tempoAlertaInicio = agora;
    }
    if (emCritico) {
      tempoCriticoTotal += agora - tempoCriticoInicio;
      tempoCriticoInicio = agora;
    }

    // Estados
    if (luzPercent > 50) {  // Estado CRÍTICO (luz muito alta)
      if (!emCritico) {     // Verifica se acabou de entrar no estado crítico
        tempoCriticoInicio = millis();
        emCritico = true;
      }
      // Aciona o LED vermelho e buzzer
      digitalWrite(ledVerde, LOW);
      digitalWrite(ledAmarelo, LOW);
      digitalWrite(ledVermelho, HIGH);
      tone(buzzer, 1000);  // Buzzer ligado
      delay(3000);
      noTone(buzzer);      // Desliga o buzzer após 3 segundos
      lcd.setCursor(0, 1);
      lcd.print("CRITICO!       ");
    } 
    else if (luzPercent >= 30 && luzPercent <= 50) {  // Estado de ALERTA
      if (!emAlerta) {  // Verifica se acabou de entrar no estado de alerta
        tempoAlertaInicio = millis();
        emAlerta = true;
      }
      // Aciona apenas o LED amarelo
      digitalWrite(ledVerde, LOW);
      digitalWrite(ledAmarelo, HIGH);
      digitalWrite(ledVermelho, LOW);
      noTone(buzzer);
      lcd.setCursor(0, 1);
      lcd.print("Alerta! Luz alta.");
    } 
    else {  // Estado NORMAL (luz adequada)
      // Atualiza os tempos totais ao sair dos estados
      if (emCritico) {
        tempoCriticoTotal += agora - tempoCriticoInicio;
        emCritico = false;
      }
      if (emAlerta) {
        tempoAlertaTotal += agora - tempoAlertaInicio;
        emAlerta = false;
      }
      // Aciona apenas o LED verde
      digitalWrite(ledVerde, HIGH);
      digitalWrite(ledAmarelo, LOW);
      digitalWrite(ledVermelho, LOW);
      noTone(buzzer);
      lcd.setCursor(0, 1);
      lcd.print("Ambiente OK    ");
    }
  }

  delay(1000); 
}
