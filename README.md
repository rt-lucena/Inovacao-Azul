# Detecção de Lixo Marinho com Display LCD e Módulo RTC
## Desafio de “Inovação Azul” 2024

Este projeto visa contribuir para a conscientização sobre a poluição dos oceanos, detectando lixo flutuante na superfície da água e exibindo informações em tempo real em um display LCD. Utilizaremos o Arduino Uno (ou similar), um sensor ultrassônico e um módulo RTC (Real-Time Clock) para manter a data e a hora atual.

### Funcionamento
O sistema mede a distância entre o sensor ultrassônico e a superfície da água. Com base nessa distância, exibe informações relevantes no display LCD. Além disso, mostra a data e a hora atual obtidas do módulo RTC.

### Requisitos
- Instalação das bibliotecas (LiquidCrystal I2C, RTClib)
- Arduino Uno ou similar
- Sensor ultrassônico
- Display LCD (16x2 ou 20x4) com módulo I2C
- Módulo RTC DS1307
- Cabos Jumper

### Montagem Física
1. Conecte o sensor ultrassônico ao Arduino conforme as especificações do fabricante.
2. Conecte o display LCD com módulo I2C aos pinos do Arduino (consulte o datasheet do display para os detalhes dos pinos).
3. Certifique-se de usar resistores adequados para o display, se necessário.
4. Conecte o módulo RTC ao Arduino via I2C.

### Programação
1. Inicialize o display LCD, o sensor ultrassônico e o módulo RTC no código.
2. No loop principal:
   - É medido a distância com o sensor ultrassônico.
   - A data e a hora são obtidas do módulo RTC.
   - É exibida a distância e a mensagem de detecção de lixo ou “Água Limpa” no display LCD.
   - É alternado entre exibir a data/hora e a distância em intervalos regulares.

### Exibição no Display
- Quando a distância for menor que um limite pré-definido (indicando a presença de lixo), o display exibe “Lixo Detectado!”.
- Caso contrário, o display exibe “Água Limpa”.
- Em intervalos regulares, o texto é alterado para exibir a data e a hora.

### Considerações Adicionais
- Utilize uma fonte de energia adequada para manter o dispositivo funcionando.
- Proteja os componentes contra água salgada e intempéries.
- Realize testes para verificar a precisão da detecção e a exibição correta no display.

### Impacto
Esperamos que essa solução conscientize as populações costeiras e incentive práticas sustentáveis para a preservação dos ecossistemas marinhos.

### Simulação Online
https://wokwi.com/projects/399567167559773185
