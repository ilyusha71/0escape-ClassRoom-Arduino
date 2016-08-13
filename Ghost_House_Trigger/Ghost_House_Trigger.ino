/* Catapult 2015/10/30 iLYuSha */
/* Input */
const int cabinet01 = 4;
const int cabinet02 = 5;
const int cabinet03 = 6;
const int cabinet04 = 7;
/* Test Output */
const int pass = 8;

int valueCabinet01=0;
int valueCabinet02=0;
int valueCabinet03=0;
int valueCabinet04=0;

void setup() {
  Serial.begin(9600);
  Serial.println("Catapult 2015/10/30 iLYuSha");
  pinMode(cabinet01,INPUT_PULLUP);
  pinMode(cabinet02,INPUT);
  pinMode(cabinet03,INPUT);
  pinMode(cabinet04,INPUT);
  pinMode(pass,OUTPUT);
  digitalWrite(pass,HIGH);
}

void loop() {

  valueCabinet01 = digitalRead(cabinet01);
  valueCabinet02 = digitalRead(cabinet02);
  valueCabinet03 = digitalRead(cabinet03);
  valueCabinet04 = digitalRead(cabinet04);

  if(valueCabinet01 == 1 && valueCabinet02 == 1 && valueCabinet03 == 1 && valueCabinet04 == 1)
  {
    digitalWrite(pass,LOW);
  }
}
