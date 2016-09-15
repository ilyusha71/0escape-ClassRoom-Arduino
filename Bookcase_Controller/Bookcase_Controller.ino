/******************************************
  Title: Bookcase Controller
  Studio: Wakaka KocmocA & 0escape
  Author: By iLYuSha Wakaka KocmocA
  2016/09/15
*******************************************/
/* Input */
const int cabinetA = 4;
const int cabinetB = 5;
const int cabinetC = 6;
const int cabinetD = 7;
/* Test Output */
const int pass = 8;

int valueCabinetA;
int valueCabinetB;
int valueCabinetC;
int valueCabinetD;

void setup() {
  Serial.begin(9600);
  pinMode(cabinetA,INPUT);
  pinMode(cabinetB,INPUT);
  pinMode(cabinetC,INPUT);
  pinMode(cabinetD,INPUT);
  pinMode(pass,OUTPUT);
  digitalWrite(pass,HIGH);
  Serial.println("Bookcase Controller 2016/09/15 iLYuSha Wakaka KocmocA");
}

void loop() 
{
  valueCabinetA = digitalRead(cabinetA);
  valueCabinetB = digitalRead(cabinetB);
  valueCabinetC = digitalRead(cabinetC);
  valueCabinetD = digitalRead(cabinetD);

  if(valueCabinetA == 1 && valueCabinetB == 1 && valueCabinetC == 1 && valueCabinetD == 1)
  {
    digitalWrite(pass,LOW);
  }
}
