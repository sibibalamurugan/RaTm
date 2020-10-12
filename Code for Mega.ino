#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>
#include <MemoryFree.h>
#include <EEPROM.h>
#define PIN_LED 13
String inString;
#define SS_PIN 53
#define RST_PIN 49
MFRC522 mfrc522(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;
String inputString = "";
boolean stringComplete = false;
String commandString = "";
boolean isConnected = false;
Servo servo;
Servo servo1;
int Contrast=80;
LiquidCrystal lcd(10,11, 5, 4, 3, 2);char ted[16]={"
Welcome"},bed[16]={"Auto-Ration Shop"};
const byte rows = 4;
const byte cols = 4;
char keyMap [rows] [cols] = {
 {'1', '2', '3', 'A'},
 {'4', '5', '6', 'B'},
 {'7', '8', '9', 'C'},
 {'*', '0', '#', 'D'}
 };
byte rowPins [rows] = {22,24,26,28};
byte colPins [cols] = {30,32,34,36};
Keypad myKeypad = Keypad( makeKeymap(keyMap), rowPins, colPins, rows,
cols);
void setup()
{ Serial.begin(115200);
Serial3.begin(115200);
SPI.begin();
 mfrc522.PCD_Init();
 Serial.println("Scan a MIFARE Classic card");
 for (byte i = 0; i < 6; i++) {
 key.keyByte[i] = 0xFF;
 }
 analogWrite(6,Contrast);
 lcd.begin(16, 2);
 servo.attach(8);
 servo.write(0);
 servo1.attach(9);
 servo1.write(0);
 }
int block=2;
byte blockcontent[16] = {"S______________"};
byte readbackblock[18];
 void loop()
{ lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print(ted);
 delay(1000);
 lcd.clear();
 char whichKey;
 int t;
 int c=0,pos=0;
 int volume=0,dgt=1;
 lcd.setCursor(0, 0);
 lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print(bed);
 delay(1000);
 lcd.setCursor(0, 1);
 lcd.print("Press OK to Buy");
 int option;
 while(c==0)
 {whichKey = myKeypad.getKey();
 if(whichKey == 'D')
 c=1;
 }
 c=0;
delay(1000);
lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print("Select Commodity");
 lcd.setCursor(0, 1);
 lcd.print("1.Rice 2.Dal");
delay(1000);
 while(c==0)
 {
 whichKey = myKeypad.getKey();
 if(whichKey == '1' || whichKey == '2')
 {
 option=whichKey-'0';
 c=1;
 }
 if(whichKey == '4' || whichKey == 'A' || whichKey == 'B' || whichKey == '3' ||
whichKey == '5' || whichKey == '6'|| whichKey == '0' || whichKey == '7' ||
whichKey == '8' || whichKey == '9'|| whichKey == 'C' || whichKey == '#' ||
whichKey == '*')
 {lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print("Invalid Entry");
 delay(1000);
 lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print("Select Commodity");
 lcd.setCursor(0, 1);
 lcd.print("1.Rice 2.Dal")
 }
 }

c=0;
lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print("Volume (Grams)");

 while(c==0)
 {whichKey = myKeypad.getKey();
 if(whichKey == '4' || whichKey == '1' || whichKey == '2' || whichKey == '3' ||
whichKey == '5' || whichKey == '6'|| whichKey == '0' || whichKey == '7' ||
whichKey == '8' || whichKey == '9')
 {lcd.setCursor(1, 1);
 t=whichKey-'0';
 Serial.print(t);
 Serial.println();
 volume*=10;
 volume+=t;
 Serial.print(volume);
 Serial.println();

 delay(500);
 itoa(volume,ted,10);
 Serial.print(ted);
 Serial.println();
 lcd.print(ted);
 pos++;
 delay(300);
 }
 if(whichKey == 'D')
 {c=1;}
 }
int price;
if(option==1)
{
 price = (volume/20);
}
if(option==2)
{
 price = (volume/10);
}
 Serial.print(price);
lcd.clear();
lcd.setCursor(0, 0);
 lcd.print("TOTAL AMOUNT");
 delay(1000);
 lcd.setCursor(1, 1);
 lcd.print("Rs. ");
 lcd.print(price);
delay(2000);
lcd.clear();
 //Evaluate or Send CArd
Serial.print("reddy");
lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print("PLACE SMART CARD");
 lcd.setCursor(0, 1);
 lcd.print("ON THE READER");
 int lop=0;
 while(lop==0)
{
if ( mfrc522.PICC_IsNewCardPresent())
 if ( mfrc522.PICC_ReadCardSerial()) {
 lop=1;//if it returns a '0' something went wrong and we return to the start of the
loop
 }
}
char x='_';
 byte a;
 a=(byte)x;
 char na[16],aa[16],naa[16],aaa[16],bb[16],bbb[16];
readBlock(2, readbackblock);
for (int j=0 ; j<16 ; j++)//print the block contents
 {if(readbackblock[j]!=a)
 Serial.write (readbackblock[j]);
 na[j]=readbackblock[j];
 }
for (int i=0 ; i<16 ; i++)//print the block contents
 {if(na[i]!=a)
 aa[i]=na[i];
 }
int nn=strlen(aa);
for (int i=0 ; i<nn-1 ; i++)//print the block contents
 {
 bb[i]=aa[i];
 }
Serial.print("superr");
lcd.clear();
 lcd.setCursor(0, 1);
 lcd.print("Processing");
 char porul[5];
 if(option==1)
 strcpy(porul,"Rice");
 if(option==2)
 strcpy(porul,"Dal");
char fina[15];
for (int i=0 ; i<14 ; i++)//print the block contents
 { fina[i]=bb[i];
 }
char str[40];char vols[5];
itoa (volume,vols,10);
strcpy (str,"[");
 strcat (str,fina);
 strcat (str," has bought ");
 strcat (str,vols);
 strcat (str,"g ");
 strcat (str,porul);
 strcat (str,"]");
 Serial.println("");
 Serial.println(str);
delay(300);
Serial3.println(str);
delay(200);
delay(1000);
float c1=1,c2=29.8;
float podu1,podu2;
podu1=volume*c1;
podu2=volume*c2;
 lcd.clear();
 lcd.setCursor(0, 1);
 lcd.print("Processed");
 delay(1000);
Serial.print("reddy3");
 //VENDING

 delay(500);
 lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print("Vending");
 if(option==1)
 {lcd.setCursor(0, 1);
 lcd.print(" Rice");
 delay(500);
 servo.write(90);
 delay(podu2);
 servo.write(0);
 }
 if(option==2)
 {lcd.setCursor(0, 1);
 lcd.print(" Dal");
 delay(500);
 servo1.write(90);
 delay(podu2);
 servo1.write(0);}
 delay(10000);
}
int writeBlock(int blockNumber, byte arrayAddress[])
{
 int largestModulo4Number=blockNumber/4*4;
 int trailerBlock=largestModulo4Number+3;
 if (blockNumber > 2 && (blockNumber+1)%4 ==
0){Serial.print(blockNumber);Serial.println(" is a trailer block:");return 2;}
 Serial.print(blockNumber);
 Serial.println(" is a data block:");

 Byte status =
mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A,
trailerBlock, &key, &(mfrc522.uid));
 if (status != MFRC522::STATUS_OK) {
 Serial.print("PCD_Authenticate() failed: ");
 Serial.println(mfrc522.GetStatusCodeName(status));
 return 3;
 }
 status = mfrc522.MIFARE_Write(blockNumber, arrayAddress, 16);
 if (status != MFRC522::STATUS_OK) {
 Serial.print("MIFARE_Write() failed: ");
 Serial.println(mfrc522.GetStatusCodeName(status));
 return 4;
 }
 Serial.println("block was written");
}
int readBlock(int blockNumber, byte arrayAddress[])
{
 int largestModulo4Number=blockNumber/4*4;
 int trailerBlock=largestModulo4Number+3;
 byte status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A,trailerBlock, &key, &(mfrc522.uid));
 if (status != MFRC522::STATUS_OK) {
 Serial.print("PCD_Authenticate() failed (read): ");
 Serial.println(mfrc522.GetStatusCodeName(status));
 return 3;
 }
 byte buffersize = 18;
 status = mfrc522.MIFARE_Read(blockNumber, arrayAddress, &buffersize);
 if (status != MFRC522::STATUS_OK) {
 Serial.print("MIFARE_read() failed: ");
 Serial.println(mfrc522.GetStatusCodeName(status));
 return 4;
 }
