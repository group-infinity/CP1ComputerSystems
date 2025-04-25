
# 💡 Sistema de Monitoramento de Luminosidade - Vinheria Agnello

Este projeto foi desenvolvido para a Vinheria Agnello que deseja controlar a luminosidade do ambiente e assim preservar a qualidade dos seus vinhos. Utilizando um Arduino, o sistema monitora continuamente os níveis de luz e fornece alertas visuais e sonoros quando a iluminação atinge níveis críticos.
O sistema utiliza um sensor LDR (Light Dependent Resistor) para medir a intensidade da luz ambiente. Os dados são processados pelo Arduino e o resultado é exibido em um display LCD I2C 16x2. 

# Dependências ✅
Antes de executar o projeto, certifique-se de que as seguintes dependências estão instaladas:

    Wire.h
    LiquidCrystal_I2C.h

Estas bibliotecas estão disponíveis através do Gerenciador de Bibliotecas da IDE do Arduino.

# Reprodução 💻
Passo a passo para a execução do projeto:

 1. Instale a IDE do Arduino (https://www.arduino.cc/en/software)
 2. Vá em Sketch > Include Library > Manage Libraries... Pesquise e
    instale as bibliotecas mencionadas acima.
 3. Monte o circuito:
    
		Conecte os seguintes componentes ao Arduino: 
	    	Sensor LDR (entrada analógica A0)
    		Botão na porta 2
	    	LEDs nas portas digitais 13 (verde), 12 (amarelo) e 11 (vermelho) 
	    	Buzzer na porta digital 7
	    	Display LCD I2C 16x2
  
    
5. Abra o arquivo .ino com a IDE do Arduino e carregue-o na placa.
    
6. Execute o sistema

# Execução 🧑‍💻
Enquanto inicia, o display LCD também mostra uma sequência de boas-vindas com o nome "INFINITY" e um símbolo personalizado de infinito, reforçando a identidade visual do grupo.

Após a inicialização, o sistema irá realizar 10 leituras dentro de 10 segundos para calcular a luminosidade média do ambiente, apresentando um dos seguintes resultados abaixo:

**Ideal (luminosidade ≤ 30%):** LED verde será aceso e a mensagem "Ambiente OK" será exibida.

**Alerta (luminosidade entre 30% e 50%):** LED amarelo será aceso e a mensagem "Alerta! Luz alta" será exibida.

**Crítico (luminosidade > 50%):** LED vermelho será aceso, a mensagem "CRITICO!" será exibida e o buzzer irá apitar por 3 segundos, voltando a apitar enquanto a luminosidade estiver em estado crítico.

### Diferencial 🧠
O sistema conta com uma funcionalidade diferencial, que funciona por meio de um botão na protoboard, que ao ser segurado, irá exibir no display LCD o tempo que o sistema passou em estado crítico e em estado de alerta. Para voltar ao monitoramento normal, segure o botão novamente até que o display LCD atualize.

# Membros do Grupo 
[Diogo Pelinson](https://github.com/diogopelinson), RM563321

[Jessica Tavares](https://github.com/jessicavitoriatavares), RM566220

[Luara Soares](https://github.com/luafs1405), RM561266

[Miguel Amaro](https://github.com/Maldak123), RM566200

[Pedro Henrique Caires](https://github.com/Pedro-Caires), RM562344
