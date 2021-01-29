#include<SoftwareSerial.h>
#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include<DHT.h>
DHT dht(8 , DHT11);
#define R 9
#define G 10
#define B 11
SoftwareSerial btSerial(2, 3);

void setup(){
  lcd.init();
  lcd.clear();
  lcd.backlight();
  dht.begin();
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  btSerial.begin(9600);
  Serial.begin(9600);
}

void loop(){
  unsigned char t=dht.readTemperature();
  unsigned char h=dht.readHumidity();
  char str[16];
  sprintf(str, "temp:%02d, hum:%03d", t, h);
  lcd.setCursor(0,0);
  lcd.print(str);
  if(btSerial.available()){
    char c = btSerial.read();
    Serial.println(c);
    switch(c){
      case 'o':
        digitalWrite(R, HIGH);
        digitalWrite(G, HIGH);
        digitalWrite(B, HIGH); 
        break; 
      case 'f':
        digitalWrite(R, LOW);
        digitalWrite(G, LOW);
        digitalWrite(B, LOW);
        break;                
      case 'r':
        digitalWrite(R, HIGH);
        digitalWrite(G, LOW);
        digitalWrite(B, LOW);
        break;
      case 'g':
        digitalWrite(R, LOW);
        digitalWrite(G, HIGH);
        digitalWrite(B, LOW);
        break;  
      case 'b':
        digitalWrite(R, LOW);
        digitalWrite(G, LOW);
        digitalWrite(B, HIGH);
        break;
    }
  }
}
