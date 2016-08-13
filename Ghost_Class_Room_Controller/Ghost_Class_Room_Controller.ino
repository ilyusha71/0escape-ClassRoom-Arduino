/******************************************
  Title: Ghost Class Room Controller
  Studio: Wakaka KocmocA & 0escape
  Author: By iLYuSha Wakaka KocmocA
  2016/08/07
*******************************************/
/* Input */
const int chairA1 = 4; // A位置觸發教職員門輸入訊號
const int chairA2 = 5; // A位置觸發暗門輸入訊號

const int chairB1 = 6; // B位置觸發教職員門輸入訊號
const int chairB2 = 7; // B位置觸發暗門輸入訊號

const int chairC1 = 8; // C位置觸發教職員門輸入訊號
const int chairC2 = 9; // C位置觸發暗門輸入訊號

const int chairD1 = 10; // D位置觸發教職員門輸入訊號
const int chairD2 = 11; // D位置觸發暗門輸入訊號 = 根據邏輯 10, 11 會同時觸發
/* Output */
const int teacherDoor = 2; // 教職員門輸出訊號
const int secretDoor = 3; // 暗門輸出訊號
const int lightBG = 12; // 光教室背景音樂（包含燈光輸出訊號）
const int darkBG = 13; // 暗教室背景音樂

/* Variable */
int valueChairA1 = 0;
int valueChairA2 = 0;
int valueChairB1 = 0;
int valueChairB2 = 0;
int valueChairC1 = 0;
int valueChairC2 = 0;
int valueChairD1 = 0;
int valueChairD2 = 0;
boolean teacherPass = false;

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
  pinMode(teacherDoor,OUTPUT);
  pinMode(secretDoor,OUTPUT);
  pinMode(lightBG,OUTPUT);
  pinMode(darkBG,OUTPUT);
  digitalWrite(teacherDoor,LOW);
  digitalWrite(secretDoor,LOW); // 暗門電磁鐵NC（開啟狀態），紫光燈與初始背景音樂訊號直接接出去（不經過繼電器）
  digitalWrite(lightBG,HIGH);
  digitalWrite(darkBG,HIGH);
  Serial.println("Ghost Class Room Controller 2016/08/04 iLYuSha Wakaka KocmocA");
  delay(3000);
  digitalWrite(lightBG,LOW);
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
    digitalWrite(teacherDoor,HIGH); // 教職員門解鎖
    teacherPass = true; // 教職員門解鎖判斷
  }

  if(teacherPass) // 教職員門解鎖之後才會觸發
  {
    if(valueChairA2 == 1 && valueChairB2 == 1 && valueChairC2 == 1 && valueChairD2 == 1)
    {
      digitalWrite(secretDoor,HIGH); // 暗門電磁鐵NC（關閉狀態、）
      digitalWrite(lightBG,HIGH); // 切換紫光燈
      digitalWrite(darkBG,LOW); // 切換暗教室背景音樂
    }
  }
}
