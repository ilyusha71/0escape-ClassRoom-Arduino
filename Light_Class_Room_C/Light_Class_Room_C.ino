/******************************************
  Title: Light Class Room C
  Studio: Wakaka KocmocA & 0escape
  Author: By iLYuSha Wakaka KocmocA
  2016/08/26
*******************************************/
/******************************************
  PURPOSE:  Learn to use the MF522-AN RFID card reader
  Created by      Rudy Schlaf for www.makecourse.com
  DATE:   2/2014
*******************************************/

/*
   This sketch uses the MFRC522 Library to use ARDUINO RFID MODULE KIT 13.56 MHZ WITH TAGS SPI W AND R BY COOQROBOT.
   The library file MFRC522.h has a wealth of useful info. Please read it.
   The functions are documented in MFRC522.cpp.

   Based on code Dr.Leong   ( WWW.B2CQSHOP.COM )
   Created by Miguel Balboa (circuitito.com), Jan, 2012.
   Rewritten by Søren Thing Andersen (access.thing.dk), fall of 2013 (Translation to English, refactored, comments, anti collision, cascade levels.)

   This library has been released into the public domain.
*/

#include <SPI.h>//include the SPI bus library
#include <MFRC522.h>//include the RFID reader library

#define SS_PIN 10  //slave select pin
#define RST_PIN 5  //reset pin
MFRC522 mfrc522(SS_PIN, RST_PIN);        // instatiate a MFRC522 reader object.
MFRC522::MIFARE_Key key;//create a MIFARE_Key struct named 'key', which will hold the card information
/* Constant for Chair Tag ID */
#define SHOW_TAG_ID
const int RFID_A[4] = {60, 73, 49, 0}; // A椅腳 RFID Tag 李嬅 3C49310
const int RFID_B[4] = {68, 151, 230, 233}; // B椅腳 RFID Tag 佳倫 4497E6E9
const int RFID_C[4] = {112, 186, 28, 51}; // C椅腳 RFID Tag 王廷 70BA1C33
const int RFID_D[4] = {64, 70, 44, 51}; // D椅腳 RFID Tag 廖毛 40462C33
const int RFID_W[4] = {79, 179, 52, 0}; // 萬用W椅腳 RFID Tag 4FB3340
const int RFID_X[4] = {27, 79, 50, 0}; // 萬用X椅腳 RFID Tag 1B4F320
const int RFID_Y[4] = {160, 59, 44, 51}; // 萬用Y椅腳 RFID Tag A03B2C33
const int RFID_Z[4] = {235, 12, 49, 0}; // 萬用Z椅腳 RFID Tag EBC310
/* Output */
const int teacherDoor = 2; // 教職員門
const int secretDoor = 3; // 暗門
/* Variable */
unsigned long timerStart; // 計時器開始時間
unsigned long timerOut; // 延遲結束時間
int msgDelay = 10000; // 語音延遲時間 10 秒
boolean play = false;
char tt; // 測試用
int escape = 0;

void setup() {
  Serial.begin(9600);        // Initialize serial communications with the PC
  SPI.begin();               // Init SPI bus
  mfrc522.PCD_Init();        // Init MFRC522 card (in case you wonder what PCD means: proximity coupling device)
  Serial.println("Scan a MIFARE Classic card");

  // Prepare the security key for the read and write functions - all six key bytes are set to 0xFF at chip delivery from the factory.
  // Since the cards in the kit are new and the keys were never defined, they are 0xFF
  // if we had a card that was programmed by someone else, we would need to know the key to be able to access it. This key would then need to be stored in 'key' instead.

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;//keyByte is defined in the "MIFARE_Key" 'struct' definition in the .h file of the library
  }

  pinMode(teacherDoor, OUTPUT);
  pinMode(secretDoor, OUTPUT);
  digitalWrite(teacherDoor, LOW);
  digitalWrite(secretDoor, LOW);
  Serial.println("Light Class Room C 2016/08/26 iLYuSha Wakaka KocmocA");
}

int block = 2; //this is the block number we will write into and then read. Do not write into 'sector trailer' block, since this can make the block unusable.

byte blockcontent[16] = {"makecourse_____"};//an array with 16 bytes to be written into one of the 64 card blocks is defined
//byte blockcontent[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};//all zeros. This can be used to delete a block.
byte readbackblock[18];//This array is used for reading out a block. The MIFARE_Read method requires a buffer that is at least 18 bytes to hold the 16 bytes of a block.

// 語音延遲方法
void Play()
{
  // 注意! 延時不得在延遲期間重複觸發
  if(!play)
  {
    play = true;
    timerStart = millis();
    timerOut = timerStart + msgDelay;
  }
}
void ShowTagID()
{
  #ifdef SHOW_TAG_ID
  Serial.print("Tag ID: ");
  Serial.print(mfrc522.uid.uidByte[0]);
  Serial.print(" , ");
  Serial.print(mfrc522.uid.uidByte[1]);
  Serial.print(" , ");
  Serial.print(mfrc522.uid.uidByte[2]);
  Serial.print(" , ");
  Serial.println(mfrc522.uid.uidByte[3]);
  #endif
}
void loop()
{
  ///////////////////////////////////////
  /* 測試用程式碼 */
//  tt= Serial.read();  
//  if(tt=='a')
//  {
//    digitalWrite(msgB2A, LOW);
//    Play();
//  }
  ///////////////////////////////////////

  // 語音播放後10秒才能再播放語音
  // 語音播放延遲不會影響機關觸發，兩者獨立運作
  if(play && millis() > timerOut)
  {
     play = false;
  }
  
  if(escape == -1)
  {
    ShowTagID();

    // A椅子 放 C位置 觸發 -> 中控機關 -> 判斷暗門開啟
    if (mfrc522.uid.uidByte[0] == RFID_A[0] && mfrc522.uid.uidByte[1] == RFID_A[1] && mfrc522.uid.uidByte[2] == RFID_A[2] && mfrc522.uid.uidByte[3] == RFID_A[3])
    {
      digitalWrite(secretDoor, HIGH); // 發送暗門開啟訊號
      Serial.print("A Bingo ");
      ShowTagID();
    }
    
    // C椅子 放 C位置 觸發 -> 中控機關 -> 判斷教職員門開啟
    else if (mfrc522.uid.uidByte[0] == RFID_C[0] && mfrc522.uid.uidByte[1] == RFID_C[1] && mfrc522.uid.uidByte[2] == RFID_C[2] && mfrc522.uid.uidByte[3] == RFID_C[3])
    {
      digitalWrite(teacherDoor, HIGH); // 發送教職員門開啟訊號
      Serial.print("C Bingo ");
      ShowTagID();
    }
    
    // 萬用椅子作弊
    else if (mfrc522.uid.uidByte[0] == RFID_W[0] && mfrc522.uid.uidByte[1] == RFID_W[1] && mfrc522.uid.uidByte[2] == RFID_W[2] && mfrc522.uid.uidByte[3] == RFID_W[3])
    {
      digitalWrite(teacherDoor, HIGH);
      digitalWrite(secretDoor, HIGH);
      Serial.print("Cheat W Bingo ");
      ShowTagID();
    }
    else if (mfrc522.uid.uidByte[0] == RFID_X[0] && mfrc522.uid.uidByte[1] == RFID_X[1] && mfrc522.uid.uidByte[2] == RFID_X[2] && mfrc522.uid.uidByte[3] == RFID_X[3])
    {
      digitalWrite(teacherDoor, HIGH);
      digitalWrite(secretDoor, HIGH);
      Serial.print("Cheat X Bingo ");
      ShowTagID();
    }
    else if (mfrc522.uid.uidByte[0] == RFID_Y[0] && mfrc522.uid.uidByte[1] == RFID_Y[1] && mfrc522.uid.uidByte[2] == RFID_Y[2] && mfrc522.uid.uidByte[3] == RFID_Y[3])
    {
      digitalWrite(teacherDoor, HIGH);
      digitalWrite(secretDoor, HIGH);
      Serial.print("Cheat Y Bingo ");
      ShowTagID();
    }
    else if (mfrc522.uid.uidByte[0] == RFID_Z[0] && mfrc522.uid.uidByte[1] == RFID_Z[1] && mfrc522.uid.uidByte[2] == RFID_Z[2] && mfrc522.uid.uidByte[3] == RFID_Z[3])
    {
      digitalWrite(teacherDoor, HIGH);
      digitalWrite(secretDoor, HIGH);
      Serial.print("Cheat Z Bingo ");
      ShowTagID();
    }
  }

  /********************************************* 
   *  Important!!! escape每次迴圈都會+1
   *  Arduino RFID 第一次進入迴圈會確認Tag並讀取(escape = -1)
   *  Arduino RFID 第二次進入迴圈【一定】會return跳出(escape = 0)
   *  故判斷Tag離開會在第三次進入迴圈
   *  此時如果Tag仍留著，escape = -1
   *  反之，escape = 1
   *  所以第四次迴圈判斷條件如下
  **********************************************/
  // 椅子拿起來 -> 恢復訊號
  else if(escape > 0)
  {
    digitalWrite(teacherDoor, LOW);
    digitalWrite(secretDoor, LOW);
  }
  /*****************************************establishing contact with a tag/card**********************************************************************/

  // Look for new cards (in case you wonder what PICC means: proximity integrated circuit card)
  if ( ! mfrc522.PICC_IsNewCardPresent()) {//if PICC_IsNewCardPresent returns 1, a new card has been found and we continue
    escape++;
    return;//if it did not find a new card is returns a '0' and we return to the start of the loop
  }
  escape = -1;

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {//if PICC_ReadCardSerial returns 1, the "uid" struct (see MFRC522.h lines 238-45)) contains the ID of the read card.
    return;//if it returns a '0' something went wrong and we return to the start of the loop
  }

  // Among other things, the PICC_ReadCardSerial() method reads the UID and the SAK (Select acknowledge) into the mfrc522.uid struct, which is also instantiated
  // during this process.
  // The UID is needed during the authentication process
  //The Uid struct:
  //typedef struct {
  //byte    size;     // Number of bytes in the UID. 4, 7 or 10.
  //byte    uidByte[10];            //the user ID in 10 bytes.
  //byte    sak;      // The SAK (Select acknowledge) byte returned from the PICC after successful selection.
  //} Uid;

  //Serial.println("card selected");

  /*****************************************writing and reading a block on the card**********************************************************************/

  //writeBlock(block, blockcontent);//the blockcontent array is written into the card block
  //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));

  //The 'PICC_DumpToSerial' method 'dumps' the entire MIFARE data block into the serial monitor. Very useful while programming a sketch with the RFID reader...
  //Notes:
  //(1) MIFARE cards conceal key A in all trailer blocks, and shows 0x00 instead of 0xFF. This is a secutiry feature. Key B appears to be public by default.
  //(2) The card needs to be on the reader for the entire duration of the dump. If it is removed prematurely, the dump interrupts and an error message will appear.
  //(3) The dump takes longer than the time alloted for interaction per pairing between reader and card, i.e. the readBlock function below will produce a timeout if
  //    the dump is used.

  //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));//uncomment this if you want to see the entire 1k memory with the block written into it.
  /*
    readBlock(block, readbackblock);//read the block back
    Serial.print("read block: ");
    for (int j=0 ; j<16 ; j++)//print the block contents
    {
    Serial.write (readbackblock[j]);//Serial.write() transmits the ASCII numbers as human readable characters to serial monitor
    }
    Serial.println("");
  */

  int i;
  Serial.print("uid:");
  for (i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  }
  Serial.println();
}
