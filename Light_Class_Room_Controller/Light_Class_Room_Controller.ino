/******************************************
  Title: Light Class Room Controller
  Studio: Wakaka KocmocA & 0escape
  Author: By iLYuSha Wakaka KocmocA
  2016/09/26
*******************************************/
/* Input */
const int tableA1 = 4; // A位置觸發教職員門輸入訊號
const int tableA2 = 5; // A位置觸發暗門輸入訊號
const int tableB1 = 6; // B位置觸發教職員門輸入訊號
const int tableB2 = 7; // B位置觸發暗門輸入訊號
const int tableC1 = 8; // C位置觸發教職員門輸入訊號
const int tableC2 = 9; // C位置觸發暗門輸入訊號
const int tableD1 = 10; // D位置觸發教職員門輸入訊號
const int tableD2 = 11; // D位置觸發暗門輸入訊號 = 根據邏輯 10, 11 會同時觸發
/* Output */
const int teacherDoor = 2; // 教職員門輸出訊號
const int secretDoor = 3; // 暗門輸出訊號
const int lightBG = 12; // 光教室背景音樂（包含燈光輸出訊號）
const int darkBG = 13; // 暗教室背景音樂
/* Input Variable */
int digitalTableA1 = 0;
int digitalTableA2 = 0;
int digitalTableB1 = 0;
int digitalTableB2 = 0;
int digitalTableC1 = 0;
int digitalTableC2 = 0;
int digitalTableD1 = 0;
int digitalTableD2 = 0;
/* Retained Variable */
int valueTableA1 = 0;
int valueTableA2 = 0;
int valueTableB1 = 0;
int valueTableB2 = 0;
int valueTableC1 = 0;
int valueTableC2 = 0;
int valueTableD1 = 0;
int valueTableD2 = 0;
/* Boolean */
boolean teacherPass = false;
/* Variable */
int passTime = 1000;
void setup() 
{
  Serial.begin(9600);
  pinMode(valueTableA1,INPUT);
  pinMode(valueTableA2,INPUT);
  pinMode(valueTableB1,INPUT);
  pinMode(valueTableB2,INPUT);
  pinMode(valueTableC1,INPUT);
  pinMode(valueTableC2,INPUT);
  pinMode(valueTableD1,INPUT);
  pinMode(valueTableD2,INPUT);
  pinMode(teacherDoor,OUTPUT);
  pinMode(secretDoor,OUTPUT);
  pinMode(lightBG,OUTPUT);
  pinMode(darkBG,OUTPUT);
  digitalWrite(teacherDoor,LOW);
  digitalWrite(secretDoor,LOW); // 暗門電磁鐵NC（開啟狀態），紫光燈與初始背景音樂訊號直接接出去（不經過繼電器）
  //digitalWrite(lightBG,HIGH);
  digitalWrite(lightBG,LOW);
  digitalWrite(darkBG,HIGH);
  Serial.println(" Light Class Room Controller 2016/09/26 iLYuSha Wakaka KocmocA");
  //delay(3000);
  //digitalWrite(lightBG,LOW);
}
int Digital2Value(int value, int digital)
{
  digital == 1 ? value++ : value = 0;
  return value;
}
void loop() 
{
  valueTableA1 = Digital2Value(valueTableA1, digitalRead(tableA1));
  valueTableA2 = Digital2Value(valueTableA2, digitalRead(tableA2));
  valueTableB1 = Digital2Value(valueTableB1, digitalRead(tableB1));
  valueTableB2 = Digital2Value(valueTableB2, digitalRead(tableB2));
  valueTableC1 = Digital2Value(valueTableC1, digitalRead(tableC1));
  valueTableC2 = Digital2Value(valueTableC2, digitalRead(tableC2));
  valueTableD1 = Digital2Value(valueTableD1, digitalRead(tableD1));
  valueTableD2 = Digital2Value(valueTableD2, digitalRead(tableD2));

  if(valueTableA1 > passTime && valueTableB1 > passTime && valueTableC1 > passTime && valueTableD1 > passTime)
  {
    digitalWrite(teacherDoor,HIGH); // 教職員門解鎖
    teacherPass = true; // 教職員門解鎖判斷
  }

  if(teacherPass) // 教職員門解鎖之後才會觸發
  {
    if(valueTableA2 > passTime && valueTableB2 > passTime && valueTableC2 > passTime && valueTableD2 > passTime)
    {
      digitalWrite(secretDoor,HIGH); // 暗門電磁鐵NC（關閉狀態、）
      digitalWrite(lightBG,HIGH); // 切換紫光燈
      digitalWrite(darkBG,LOW); // 切換暗教室背景音樂
    }
  }
}
