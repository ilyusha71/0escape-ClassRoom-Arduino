/******************************************
  Title: Dark Class Room Controller
  Studio: Wakaka KocmocA & 0escape
  Author: By iLYuSha Wakaka KocmocA
  2016/08/21
*******************************************/
/* Input */
const int chairA1 = 4; // A桌X訊號
const int chairA2 = 5; // A位Y訊號

const int chairB1 = 6; // B位置X訊號
const int chairB2 = 7; // B位置Y訊號

const int chairC1 = 8; // C位置X訊號
const int chairC2 = 9; // C位置Y訊號

const int chairD1 = 10; // D位置X訊號
const int chairD2 = 11; // D位置Y訊號
/* Output */
const int x1 = 2; // X訊號第一次語音（第一輪語音）
const int x2 = 3; // X訊號第二次語音（第三輪語音）
const int y1 = 12; // Y訊號第一次語音（第二輪語音）
const int y2 = 13; // Y訊號第二次觸發（解鎖音效 + 機關門解鎖）

/* Variable */
int valueChairA1 = 0;
int valueChairA2 = 0;
int valueChairB1 = 0;
int valueChairB2 = 0;
int valueChairC1 = 0;
int valueChairC2 = 0;
int valueChairD1 = 0;
int valueChairD2 = 0;
int turn = 0; // 已完成輪數
int durationTurn = 30000;
unsigned long timerOut; // 延遲結束時間

void setup() {
  Serial.begin(9600);
  pinMode(chairA1,INPUT);
  pinMode(chairA2,INPUT);
  pinMode(chairB1,INPUT);
  pinMode(chairB2,INPUT);
  pinMode(chairC1,INPUT);
  pinMode(chairC2,INPUT);
  pinMode(chairD1,INPUT);
  pinMode(chairD2,INPUT);
  pinMode(x1,OUTPUT);
  pinMode(x2,OUTPUT);
  pinMode(y1,OUTPUT);
  pinMode(y2,OUTPUT);
  digitalWrite(x1,HIGH);
  digitalWrite(x2,HIGH);
  digitalWrite(y1,HIGH);
  digitalWrite(y2,HIGH);
  Serial.println("Dark Class Room Controller 2016/08/21 iLYuSha Wakaka KocmocA");
}
void Replay()
{
  if(millis() > timerOut && turn > 0 && turn < 4)
    Play();
}
void Play()
{
  timerOut = millis() + 20000;
  Serial.println(timerOut);
  if(turn == 1)
  {
    digitalWrite(x1,HIGH);
    delay(300);
    digitalWrite(x1,LOW);
    Serial.println("0001: ");
  }
  else if(turn == 2)
  {
    digitalWrite(y1,HIGH);
    delay(300);
    digitalWrite(y1,LOW);
    Serial.println("0002: ");
  }
  else if(turn == 3)
  {
    digitalWrite(x2,HIGH);
    delay(300);
    digitalWrite(x2,LOW);
    Serial.println("0003: ");
  }
}
void loop() {
  char tt = Serial.read();
  if(tt == 'c')
  {
    turn++;
    Serial.println("is ");
    Serial.println(turn);
    Play();
  }
  else   if(tt == 'd')
  {
    Serial.println("is ");
    Serial.println(turn);
    Play();
  }

  valueChairA1 = digitalRead(chairA1);
  valueChairA2 = digitalRead(chairA2);
  valueChairB1 = digitalRead(chairB1);
  valueChairB2 = digitalRead(chairB2);
  valueChairC1 = digitalRead(chairC1);
  valueChairC2 = digitalRead(chairC2);
  valueChairD1 = digitalRead(chairD1);
  valueChairD2 = digitalRead(chairD2);
//  Serial.print("A1: ");
//  Serial.print(valueChairA1);
//  Serial.print("   ");
//  Serial.print("B1: ");
//  Serial.print(valueChairB1);
//  Serial.print("   ");
//  Serial.print("C1: ");
//  Serial.print(valueChairC1);
//  Serial.print("   ");
//  Serial.print("D1: ");
//  Serial.print(valueChairD1);
//  Serial.print("   ");
//  Serial.print("A2: ");
//  Serial.print(valueChairA2);
//  Serial.print("   ");
//  Serial.print("B2: ");
//  Serial.print(valueChairB2);
//  Serial.print("   ");
//  Serial.print("C2: ");
//  Serial.print(valueChairC2);
//  Serial.print("   ");
//  Serial.print("D2: ");
//  Serial.print(valueChairD2);
//  Serial.println("   ");
  if(turn == 0 || turn == 2)
  {
    if(valueChairA1 == 1 && valueChairB1 == 1 && valueChairC1 == 1 && valueChairD1 == 1)
    {
      turn++;
      Play();
    }
  }
  else if(turn == 1)
  {
    if(valueChairA2 == 1 && valueChairB2 == 1 && valueChairC2 == 1 && valueChairD2 == 1)
    {
      turn++;
      Play();
    }
  }
  else if(turn == 3)
  {
    if(valueChairA2 == 1 && valueChairB2 == 1 && valueChairC2 == 1 && valueChairD2 == 1)
    {
      turn++;
      digitalWrite(y2,LOW);
      Serial.println("0004: ");
    }
  }
  Replay();
}
