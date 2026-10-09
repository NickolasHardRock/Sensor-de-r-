/*
  Projeto: Assistente de estacionamento
  Placa: RoboCore compatível com Arduino Uno (Kit IniciantA V8)

  Componentes:
  - Sensor ultrassônico HC-SR04: TRIG no D9, ECHO no D10
  - LED RGB de cátodo comum: R no D3, G no D5, B no D6
  - Buzzer piezo passivo: sinal no D8
  - GND comum e resistores de 220 ohms nos três canais do LED

  Faixas padrão (podem ser ajustadas no código):
  - Verde: acima de 100 cm
  - Amarelo: de 41 a 100 cm
  - Vermelho: até 40 cm
  Quanto menor a distância, mais rápido o buzzer apita.
*/

const byte PINO_TRIG = 9;
const byte PINO_ECHO = 10;
const byte PINO_LED_R = 3;
const byte PINO_LED_G = 5;
const byte PINO_LED_B = 6;
const byte PINO_BUZZER = 8;

const float DISTANCIA_AMARELA_CM = 100.0;
const float DISTANCIA_VERMELHA_CM = 40.0;
const unsigned long INTERVALO_MEDICAO_MS = 60;
const unsigned int DURACAO_BIP_MS = 55;

unsigned long instanteMedicao = 0;
unsigned long instanteBip = 0;
unsigned long inicioBip = 0;
bool bipAtivo = false;
float distanciaCm = -1.0;

void definirCor(bool vermelho, bool verde, bool azul) {
  // Este código considera LED RGB de cátodo comum (HIGH acende).
  digitalWrite(PINO_LED_R, vermelho ? HIGH : LOW);
  digitalWrite(PINO_LED_G, verde ? HIGH : LOW);
  digitalWrite(PINO_LED_B, azul ? HIGH : LOW);
}

float medirDistanciaCm() {
  digitalWrite(PINO_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PINO_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PINO_TRIG, LOW);

  // Timeout de 25 ms evita travar o programa se não houver eco.
  unsigned long duracao = pulseIn(PINO_ECHO, HIGH, 25000UL);
  if (duracao == 0) return -1.0;

  // Velocidade do som: distância de ida e volta / 2.
  return duracao * 0.0343 / 2.0;
}

void atualizarIndicacao() {
  if (distanciaCm < 0) {
    // Sem leitura válida: amarelo indica que a situação é desconhecida.
    definirCor(true, true, false);
    bipAtivo = false;
    noTone(PINO_BUZZER);
    return;
  }

  if (distanciaCm > DISTANCIA_AMARELA_CM) {
    definirCor(false, true, false);  // Verde: distância segura
  } else if (distanciaCm > DISTANCIA_VERMELHA_CM) {
    definirCor(true, true, false);   // Vermelho + verde: amarelo
  } else {
    definirCor(true, false, false);  // Vermelho: muito perto
  }

  if (distanciaCm > DISTANCIA_AMARELA_CM) {
    bipAtivo = false;
    noTone(PINO_BUZZER);
    return;
  }

  // Mapeia 100 cm -> bip lento (700 ms) e 5 cm -> bip rápido (80 ms).
  float distanciaLimitada = constrain(distanciaCm, 5.0, DISTANCIA_AMARELA_CM);
  unsigned long intervaloBip = (unsigned long) map((long)(distanciaLimitada * 10), 50, 1000, 80, 700);
  unsigned long agora = millis();

  if (!bipAtivo && agora - instanteBip >= intervaloBip) {
    tone(PINO_BUZZER, 2200);
    inicioBip = agora;
    instanteBip = agora;
    bipAtivo = true;
  }

  if (bipAtivo && agora - inicioBip >= DURACAO_BIP_MS) {
    noTone(PINO_BUZZER);
    bipAtivo = false;
  }
}

void setup() {
  pinMode(PINO_TRIG, OUTPUT);
  pinMode(PINO_ECHO, INPUT);
  pinMode(PINO_LED_R, OUTPUT);
  pinMode(PINO_LED_G, OUTPUT);
  pinMode(PINO_LED_B, OUTPUT);
  pinMode(PINO_BUZZER, OUTPUT);
  Serial.begin(9600);
  definirCor(false, true, false);
}

void loop() {
  unsigned long agora = millis();
  if (agora - instanteMedicao >= INTERVALO_MEDICAO_MS) {
    instanteMedicao = agora;
    distanciaCm = medirDistanciaCm();
    if (distanciaCm >= 0) {
      Serial.print("Distancia: ");
      Serial.print(distanciaCm, 1);
      Serial.println(" cm");
    } else {
      Serial.println("Sem leitura valida do sensor.");
    }
    atualizarIndicacao();
  } else if (distanciaCm >= 0) {
    // Continua desligando o som no tempo correto entre as medições.
    if (bipAtivo && agora - inicioBip >= DURACAO_BIP_MS) {
      noTone(PINO_BUZZER);
      bipAtivo = false;
    }
  }
}
