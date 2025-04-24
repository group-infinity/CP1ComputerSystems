#💡 Sistema de Monitoramento de Luminosidade - Vinheria INFINITY

Este projeto foi desenvolvido para uma vinheria que deseja controlar a luminosidade do ambiente e assim preservar a qualidade dos seus vinhos. Utilizando um Arduino, o sistema monitora continuamente os níveis de luz e fornece alertas visuais e sonoros quando a iluminação atinge níveis críticos.
O sistema utiliza um sensor LDR (Light Dependent Resistor) para medir a intensidade da luz ambiente. Os dados são processados pelo Arduino e o resultado é exibido em um display LCD I2C 16x2. Dependendo da intensidade da luz, o sistema reage da seguinte forma:
Ideal (≤ 30%): LED verde aceso e mensagem "Ambiente OK".
Alerta (entre 30% e 50%): LED amarelo aceso e mensagem "Alerta! Luz alta".
Crítico (> 50%): LED vermelho aceso, buzzer ativado por 3 segundos e mensagem "CRITICO!".
O display também mostra uma sequência de boas-vindas com a marca "INFINITY" e um símbolo personalizado de infinito, reforçando a identidade visual do grupo que realizou o projeto.

Dependências
 bibliotecas do Arduino:
Wire.h
LiquidCrystal_I2C.h
Adafruit_RGBLCDShield.h
Adafruit_MCP23017.h (via utility/Adafruit_MCP23017.h)

Estas bibliotecas estão disponíveis através do Gerenciador de Bibliotecas da IDE do Arduino.

Como Reproduzir
Instale a IDE do Arduino
Baixe em: https://www.arduino.cc/en/software
Instale as bibliotecas necessárias
Vá em Sketch > Include Library > Manage Libraries...
Pesquise e instale as bibliotecas mencionadas acima.
Monte o circuito
Conecte os seguintes componentes ao Arduino:
Sensor LDR (entrada analógica A0)
LEDs nas portas digitais 13 (verde), 12 (amarelo) e 11 (vermelho)
Buzzer na porta digital 7
Display LCD I2C 16x2
Carregue o código
Abra o arquivo .ino com a IDE do Arduino e carregue-o na placa.
Execute o sistema
Após o upload, o sistema será iniciado automaticamente e começará a monitorar a luminosidade do ambiente.
