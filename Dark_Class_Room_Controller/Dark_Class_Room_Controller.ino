/******************************************
  Title: Dark Class Room Controller
  Studio: Wakaka KocmocA & 0escape
  Author: By iLYuSha Wakaka KocmocA
  2016/08/13
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
const int y2 = 13; // Y訊號第二次觸發（機關門解鎖）

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

void setup() {
  Serial.begin(9600);
  pinMode(valueChairA1,INPUT);
  pinMode(valueChairA2,INPUT);
  pinMode(valueChairB1,INPUT);
  pinMode(valueChairB2,INPUT);
  pinMode(valueChairC1,INPUT);
  pinMode(valueChairC2,INPUT);
  pinMode(valueChairD1,INPUT);
  pinMode(valueChairD2,INPUT);
  pinMode(x1,OUTPUT);
  pinMode(x2,OUTPUT);
  pinMode(y1,OUTPUT);
  pinMode(y2,OUTPUT);
  digitalWrite(x1,HIGH);
  digitalWrite(x2,HIGH);
  digitalWrite(y1,HIGH);
  digitalWrite(y2,LOW);
  Serial.println("Dark Class Room Controller 2016/08/13 iLYuSha Wakaka KocmocA");
}

void loop() {

  valueChairA1 = digitalRead(chairA1);
  valueChairA2 = digitalRead(chairA2);
  valueChairB1 = digitalRead(chairB1);
  valueChairB2 = digitalRead(chairB2);
  valueChairC1 = digitalRead(chairC1);
  valueChairC2 = digitalRead(chairC2);
  valueChairD1 = digitalRead(chairD1);
  valueChairD2 = digitalRead(chairD2);

  if(valueChairA1 == 1 && valueChairB1 == 1 && valueChairC1 == 1 && valueChairD1 == 1)
  {
    if(turn == 0)
    {
        digitalWrite(x1,LOW);
        turn++;
    }
    else if(turn == 2)
    {
        digitalWrite(x2,LOW);
        turn++;
    }
  }

  if(valueChairA2 == 1 && valueChairB2 == 1 && valueChairC2 == 1 && valueChairD2 == 1)
  {
    if(turn == 1)
    {
        digitalWrite(y1,LOW);
        turn++;
    }
    else if(turn == 3)
    {
        digitalWrite(y2,HIGH);
        turn++;
    }
  }
}
