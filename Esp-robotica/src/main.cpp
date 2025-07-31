// Entradas (nomes e GPIOs)
#define ENTRADA_VP 36  // ED0 -    SENSOR DE INICIO
#define ENTRADA_VN 39  // ED1 -    SENSOR METALICO
#define ENTRADA_D34 34 // ED2 -    SENSOR FINAL
#define ENTRADA_D32 32 // ED3 -    SENSOR OPTICO2
#define ENTRADA_D33 33 // ED4 -    SENSOR MEDIDOR MEIO
#define ENTRADA_D25 25 // ED5 -    SENSOR MEDIDOR FINAL
#define ENTRADA_D26 26 // ED6 -    SENSOR MAGAZINE AVANÇADO
#define ENTRADA_D27 27 // ED7 -

// Saídas correspondentes
#define SAIDA_D23 23 // SD0 -     TRAVA/PINO
#define SAIDA_D22 22 // SD1 -     ESTEIRA
#define SAIDA_D21 21 // SD2 -     SEPARADOR
#define SAIDA_D19 19 // SD3 -     MAGAZINE
#define SAIDA_D18 18 // SD4 -     MEDIDOR
#define SAIDA_TX2 17 // SD5 -
#define SAIDA_RX2 16 // SD6 -
#define SAIDA_D4 4   // SD7 -

// Definição dos estados
enum Estado
{
  ESTADO_1,
  ESTADO_2,
  ESTADO_3,
  ESTADO_4,
  ESTADO_5,
  ESTADO_6,
  ESTADO_7,
  ESTADO_8,
  ESTADO_9,
  ESTADO_10,
};

Estado estadoAtual = ESTADO_1;

void setup()
{
  Serial.begin(9600);
  // Configurar entradas
  pinMode(ENTRADA_VP, INPUT);
  pinMode(ENTRADA_VN, INPUT);
  pinMode(ENTRADA_D34, INPUT);
  pinMode(ENTRADA_D32, INPUT);
  pinMode(ENTRADA_D33, INPUT);
  pinMode(ENTRADA_D25, INPUT);
  pinMode(ENTRADA_D26, INPUT);
  pinMode(ENTRADA_D27, INPUT);

  // Configurar saídas
  pinMode(SAIDA_D23, OUTPUT);
  pinMode(SAIDA_D22, OUTPUT);
  pinMode(SAIDA_D21, OUTPUT); // separador
  pinMode(SAIDA_D19, OUTPUT);
  pinMode(SAIDA_D18, OUTPUT);
  pinMode(SAIDA_TX2, OUTPUT);
  pinMode(SAIDA_RX2, OUTPUT);
  pinMode(SAIDA_D4, OUTPUT);

  // Pull-Down das entradas digitais
  digitalWrite(ENTRADA_VP, LOW);
  digitalWrite(ENTRADA_VN, LOW);
  digitalWrite(ENTRADA_D34, LOW);
  digitalWrite(ENTRADA_D32, LOW);
  digitalWrite(ENTRADA_D33, LOW);
  digitalWrite(ENTRADA_D25, LOW);
  digitalWrite(ENTRADA_D26, LOW);
  digitalWrite(ENTRADA_D27, LOW);

  // Reset das Saídas
  digitalWrite(SAIDA_D23, LOW); // trava
  digitalWrite(SAIDA_D22, LOW);
  digitalWrite(SAIDA_D21, LOW);
  digitalWrite(SAIDA_D19, LOW);
  digitalWrite(SAIDA_D18, LOW);
  digitalWrite(SAIDA_TX2, LOW);
  digitalWrite(SAIDA_RX2, LOW);
  digitalWrite(SAIDA_D4, LOW);
}

void loop()
{

  Serial.println(digitalRead(ENTRADA_D34));
  switch (estadoAtual)
  {
  case ESTADO_1:
    if (digitalRead(ENTRADA_VP) == HIGH) // aciona a esteira, como o sensor inicial
    {
      digitalWrite(SAIDA_D22, HIGH);
      estadoAtual = ESTADO_2;
    }
    break;
  case ESTADO_2:
    if (digitalRead(ENTRADA_VN) == HIGH) // aciona o sensor metalico, ativando o separador
    {
      digitalWrite(SAIDA_D21, HIGH);
      estadoAtual = ESTADO_3;
    }

  case ESTADO_3:
    if (digitalRead(ENTRADA_D32) == HIGH) // aciona o sensor optico
    {
      digitalWrite(SAIDA_D19, HIGH); // liga o magazine
      delay(2000);
      estadoAtual = ESTADO_4;
    }
    break;

  case ESTADO_4:
    if (digitalRead(ENTRADA_D26) == LOW) // aciona o sensor optico
    {
      digitalWrite(SAIDA_D19, LOW); // liga o magazine
      delay(1500);
      digitalWrite(SAIDA_D23, HIGH);
      digitalWrite(SAIDA_D19, HIGH); // liga o magazine
      delay(1000);
      digitalWrite(SAIDA_D19, LOW); // liga o magazine
      estadoAtual = ESTADO_5;
    }
  case ESTADO_5:
    if (digitalRead(ENTRADA_D34) == LOW)
    {
      digitalWrite(SAIDA_D21, LOW);
      digitalWrite(SAIDA_D23, LOW); // trava
      delay(1500);
      digitalWrite(SAIDA_D22, LOW);
      estadoAtual = ESTADO_1;
    }
    break;
  }
}
