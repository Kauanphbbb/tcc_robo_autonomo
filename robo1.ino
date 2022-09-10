#include <Servo.h>

int servoPorta = 7;

int motorEsquerdoTras = 8;
int motorEsquerdoFrente = 9;
int motorDireitoFrente = 10;
int motorDireitoTras = 11;

int pinoTrigger = 5;
int pinoEcho = 6;

int posicaoServo;
float duracao, cm;
float distanciaMinima = 10;

Servo servo;

float lerDistancia()
{
  digitalWrite(pinoTrigger, LOW);
  delayMicroseconds(5);
  digitalWrite(pinoTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinoTrigger, LOW);
  duracao = pulseIn(pinoEcho, HIGH);
  float calcDistancia = (duracao / 2) * 0.0343;
  if (calcDistancia >= 331)
  {
    calcDistancia = 0;
  }
  return calcDistancia;
}

void moveRoboParaFrente()
{
  digitalWrite(motorEsquerdoFrente, HIGH);
  digitalWrite(motorDireitoFrente, HIGH);
  delay(750);
  desligaMotor();
}

void moveRoboParaTras()
{
  digitalWrite(motorEsquerdoTras, HIGH);
  digitalWrite(motorDireitoTras, HIGH);
  delay(750);
  desligaMotor();
}

void viraRoboParaEsquerda()
{
  // digitalWrite(motorEsquerdoTras, HIGH);
  digitalWrite(motorDireitoFrente, HIGH);
  delay(750);
  desligaMotor();
}

void viraRoboParaDireita()
{
  digitalWrite(motorEsquerdoFrente, HIGH);
  // digitalWrite(motorDireitoTras, HIGH);
  delay(750);
  desligaMotor();
}

void desligaMotor()
{
  digitalWrite(motorEsquerdoFrente, LOW);
  digitalWrite(motorDireitoFrente, LOW);
  digitalWrite(motorEsquerdoTras, LOW);
  digitalWrite(motorDireitoTras, LOW);
}

void viraServoDireita()
{
  servo.write(0);
  delay(2000);
}

void viraServoEsquerda()
{
  servo.write(180);
  delay(2000);
}

void centralizaServo()
{
  servo.write(90);
  delay(2000);
}

void verificaEsquerda()
{
  viraServoEsquerda();
  if (lerDistancia() <= distanciaMinima)
  {
    verificaDireita();
  }
  else
  {
    viraRoboParaEsquerda();
    centralizaServo();
  }
}

void verificaDireita()
{
  viraServoDireita();
  if (lerDistancia() <= distanciaMinima)
  {
    centralizaServo();
    moveRoboParaTras();
  }
  else
  {
    viraRoboParaDireita();
    centralizaServo();
  }
}

void setup()
{
  // put your setup code here, to run once:
  pinMode(pinoEcho, INPUT);
  pinMode(pinoTrigger, OUTPUT);

  pinMode(motorEsquerdoTras, OUTPUT);
  pinMode(motorEsquerdoFrente, OUTPUT);
  pinMode(motorDireitoFrente, OUTPUT);
  pinMode(motorDireitoTras, OUTPUT);

  servo.attach(servoPorta);
  servo.write(90);
  Serial.begin(9600);
}

void loop()
{
  // put your main code here, to run repeatedly:
  if (lerDistancia() <= distanciaMinima)
  {
    verificaEsquerda();
  }
  else
  {
    moveRoboParaFrente();
  }
}
