#include "Ultrasonic.h"
Ultrasonic ultrasonic(9,8); //trig,echo

int solileri = 2; // Arduino kartın 2 nolu pini sol motor ileri hareketi için atanır 
int solgeri = 3; // Arduino kartın 3 nolu pini sol motor geri hareketi için atanır 

int sagileri = 6; // Arduino kartın 6 nolu pini sağ motor ileri hareketi için atanır 
int saggeri = 7; // Arduino kartın 7 nolu pini sağ motor geri hareketi için atanır 

int enable1=10; //Motor 1 hızını kontrol eden pin tanımlanır. 
int enable2=11; //Motor 2 hızını kontrol eden pin tanımlanır. 

#define IR_sensor_on A0 // Ön taraf IR sensör
#define IR_sensor_arka A1 // Arka taraf IR sensör 
int uzaklik ; //uzaklık isminde değişken tanımlanır. 

void setup()
{
Serial.begin(9600); //Seri veri iletişimi başlatılır. 

pinMode(solileri, OUTPUT);  // pin çıkış olarak tanımlanır
pinMode(sagileri, OUTPUT);  // pin çıkış olarak tanımlanır
pinMode(solgeri, OUTPUT);  // pin çıkış olarak tanımlanır
pinMode(saggeri, OUTPUT);  // pin çıkış olarak tanımlanır
pinMode(enable1, OUTPUT);  //enable1 çıkış olarak tanımlanır.
pinMode(enable2, OUTPUT);  //enable2 çıkış olarak tanımlanır. 
}

void loop()
{
  
int IR_on = analogRead(IR_sensor_on); //Ön sensörden okunan değer, IR_on isimli değişkene atanır. 
int IR_arka = analogRead(IR_sensor_arka); //Arka sensörden okunan değer, IR_arka isimli değişkene atanır.
uzaklik = ultrasonic.Ranging(CM) ; //Okunan mesafe, uzaklik isimli değişkene atanır. 

don(180); // Robot araba ekseni etrafında dönmeye başlar. 

if (uzaklik < 20){ //Eğer uzaklık 20cm'den aşağıya düşerse...
dur(0); //Sumo robot durur. 
delay(250); //Yarım saniye bekler. 
while (uzaklik < 20 ) { //Eğer mesafe 20cm'den aşağıya düşerse, motor durduktan sonra...
ilerigit(255);  //Sumo robot ileri hareket eder. 
uzaklik = ultrasonic.Ranging(CM); //Mesafe sensöründen tekrar uzaklık ölçülür. 
IR_on = analogRead(IR_sensor_on); //Ön sensörden değer ölçülür. 
IR_arka = analogRead(IR_sensor_arka); //Arka sensörden değer ölçülür. 
if ( IR_on > 680 || IR_arka > 100 ) { break;} //Eğer ön sensör değeri 650 den fazla ve arka sensör değeri 100 den fazla ise/yani renk beyaz değil ise koşul devam eder. 
delay(10); }
}
if (IR_on < 680 )  // < Eğer ön sensör eşik değeri 650 den küçükse/beyaz renk ise
{
dur(0); //Sumo robot durur. 
delay (50); //50 msn beklenir. 
gerigit(255); //gerigit fonksiyonu çağrılır. 
delay (500); //500 msn beklenir. 
} 

if (IR_arka < 100 )  //Eğer arka sensör eşik değeri 100 den küçükse/beyaz renk ise
{
dur(0); //Sumo robot durur. 
delay (50); //50 msn beklenir. 
ilerigit(255); //İlerigit fonksiyonu çağrılır. 
delay (500); //500 msn beklenir. 
}

Serial.print(ultrasonic.Ranging(CM));
Serial.println("cm");
Serial.print("IR ön taraf :");
Serial.println(IR_on); 
Serial.print("IR arka taraf :");
Serial.println(IR_arka);  
delay (1000);
}
// Robot araba ileri gider
void ilerigit(int hiz)
{  
analogWrite(enable1, hiz);  //sağ motor hızı 200 ayarlanır. 
analogWrite(enable2, hiz);  //sol motor hızı 200 ayarlanır.   
digitalWrite(sagileri, HIGH);   // Sağ ileri motor döner
digitalWrite(solileri, HIGH);   // sol ileri motor döner
digitalWrite(saggeri,LOW);   // Sağ geri motor durur
digitalWrite(solgeri, LOW);   // Sol geri motor durur
}

// Robot bulunduğu yerde ekseni etrafında döner
void don (int hiz){
analogWrite(enable1, hiz);  //sağ motor hızı 180 ayarlanır. 
analogWrite(enable2, hiz);  //sol motor hızı 180 ayarlanır. 
digitalWrite(sagileri, HIGH);   // Sağ ileri motor döner.
digitalWrite(solileri, LOW);   // sol ileri motor durur.
digitalWrite(saggeri,LOW);   // Sağ geri motor durur.
digitalWrite(solgeri, HIGH);   // sol geri motor döner.
}
// Robot bulunduğu yerden geriye hareket eder.
void gerigit(int hiz)
{  
analogWrite(enable1, hiz);  //sağ motor hızı 255 ayarlanır. 
analogWrite(enable2, hiz);  //sol motor hızı 255 ayarlanır.   
digitalWrite(saggeri, HIGH);   // Sağ motor döner
digitalWrite(solgeri, HIGH);   //sol motor döner
digitalWrite(sagileri, LOW);   // Sağ motor durur
digitalWrite(solileri, LOW);   // sol motor durur
}
void dur(int hiz) //Robot araba durur. 
{  
analogWrite(enable1, hiz);  //sağ motor hızı 0 ayarlanır. 
analogWrite(enable2, hiz);  //sol motor hızı 0 ayarlanır.   
digitalWrite(sagileri, LOW);   // Sağ ileri motor durur.
digitalWrite(solileri, LOW);   // sol ileri motor durur. 
digitalWrite(saggeri, LOW);   // Sağ geri motor durur.
digitalWrite(solgeri, LOW);   // sol geri motor durur.

}

