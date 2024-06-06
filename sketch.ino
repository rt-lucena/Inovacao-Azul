#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>

// Define o endereço I2C do display 16x2 (pode variar)
const int lcdAddress = 0x27;

// Inicializa o display LCD
LiquidCrystal_I2C lcd(lcdAddress, 16, 2); // 16 colunas, 2 linhas

// Define os pinos do sensor ultrassônico
const int trigPin = 2;
const int echoPin = 3;

// Inicializa o módulo RTC
RTC_DS1307 rtc;

// Variáveis para alternar entre mensagens
unsigned long previousMillis = 0;
const long interval = 2000; // Intervalo de 2 segundos
bool showDateTime = false;

void setup() {
  // Inicializa o display LCD
  lcd.init();
  lcd.backlight();

  // Inicializa o sensor ultrassônico
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Inicializa o módulo RTC
  if (!rtc.begin()) {
    lcd.setCursor(0, 0);
    lcd.print("RTC nao encontrado");
    while (1);
  }

  if (!rtc.isrunning()) {
    // Se o RTC perdeu a energia, define a data e a hora para a compilação
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  // Configura a velocidade de transmissão serial (opcional)
  Serial.begin(9600);
}

void loop() {
  // Obtém a data e a hora atuais do RTC
  DateTime now = rtc.now();

  // Mede a distância com o sensor ultrassônico
  long duration, distanceCm;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * 0.034 / 2; // Calcula a distância em centímetros

  // Alterna entre mensagens com base no tempo
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    showDateTime = !showDateTime;
    lcd.clear(); // Limpa o LCD apenas quando mudar a mensagem
  }

  if (showDateTime) {
    // Exibe a data e a hora no display LCD
    lcd.setCursor(0, 0);
    lcd.print("DATA: ");
    char dateBuffer[11]; // Buffer para a data no formato DD/MM/YYYY
    snprintf(dateBuffer, sizeof(dateBuffer), "%02d/%02d/%04d", now.day(), now.month(), now.year());
    lcd.print(dateBuffer);

    lcd.setCursor(0, 1);
    lcd.print("HORA: ");
    char timeBuffer[9]; // Buffer para a hora no formato hh:mm:ss
    snprintf(timeBuffer, sizeof(timeBuffer), "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
    lcd.print(timeBuffer);
  } else {
    // Exibe a distância e a mensagem de detecção de lixo no display LCD
    lcd.setCursor(0, 0);
    lcd.print("Distancia: ");
    if (distanceCm > 100) {
      float distanceM = distanceCm / 100.0; // Converte para metros
      lcd.print(distanceM, 2); // Mostra 2 casas decimais
      lcd.print(" m");
    } else {
      lcd.print(distanceCm);
      lcd.print(" cm");
    }

    lcd.setCursor(0, 1);
    if (distanceCm < 30) {
      lcd.print("Lixo Detectado!");
    } else {
      lcd.print("Agua Limpa");
    }
  }

  // Aguarda um intervalo antes da próxima medição
  delay(100);
}
