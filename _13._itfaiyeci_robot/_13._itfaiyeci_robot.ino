#include <Servo.h> //servo motor kütüphanesi koda eklenir. 
Servo servomotor; //servo motor nesnesi oluşturulur. 
int aci=0;  //aci değişkeni ilk değer 0 atanır. 
boolean ates = false; //ates ilk değer false atanır. 
 
#define sagsensor 8 //sağ sensör pin numarası tanımlanır. 
#define solsensor 9   // sol sensor pin numarası atanır. 
#define ilerisensor 10  // ileri  sensor pin numarası atanır. 

int solileri = 2; // Arduino kartın 2 nolu pini sol motor ileri hareketi için atanır 
int solgeri = 3; // Arduino kartın 3 nolu pini sol motor geri hareketi için atanır 

int sagileri = 6; // Arduino kartın 6 nolu pini sağ motor ileri hareketi için atanır 
int saggeri = 7; // Arduino kartın 7 nolu pini sağ motor geri hareketi için atanır 

int pompa= 11; //su pompası pin numarası dijital 11 atanır. 

void setup()
{
servomotor.attach(4); //Servo motor 4 nolu dijital pine bağlanır. 

pinMode(solsensor, INPUT); //Sol, sağ ve ileri ateş sensörleri pinleri giriş  olarak atanır. 
pinMode(sagsensor, INPUT);
pinMode(ilerisensor, INPUT);

pinMode(solileri, OUTPUT);  // Sol ileri motor pin çıkış olarak tanımlanır.
pinMode(sagileri, OUTPUT);  // Sağ ileri motor pin çıkış olarak tanımlanır.
pinMode(solgeri, OUTPUT);  // Sol geri motor pin çıkış olarak tanımlanır.
pinMode(saggeri, OUTPUT);  // Sağ geri motor pin çıkış olarak tanımlanır.
pinMode(pompa, OUTPUT);  //Su pompası pini çıkış olarak tanımlanır. 
digitalWrite(pompa, LOW); //Su pompasının ilk değeri LOW yapılarak çalışmaz durumda başlar. 
}

void atessondur() //atessondur isimli bir fonksiyon oluşturulur. 
{
digitalWrite(solileri, LOW); //motor pinleri LOW yapılır.(Robot araba durur)
digitalWrite(sagileri, LOW);
digitalWrite(solgeri, LOW);
digitalWrite(saggeri, LOW);

digitalWrite(pompa, HIGH);  //Robot araba durduktan sonra su pompası çalışır.
delay (500); //Yarım saniye beklenir. 
  
for (aci = 40; aci <= 120; aci += 1) { //Servo motor 40 dereceden 120 dereceye döner. 
servomotor.write(aci); // 
delay(15);  
}

for (aci = 120; aci >= 40; aci -= 1) { //Servo motor 120 dereceden 40 dereceye döner. 
servomotor.write(aci); 
delay(15);
}

digitalWrite(pompa,LOW); //Pompa durur. 
delay (10);
servomotor.write(90); //Servo motor 90 dereceye girer. 
 
ates=false;
}
void loop()
{
if (digitalRead(solsensor) ==1 && digitalRead(sagsensor)==1 && digitalRead(ilerisensor) ==1)//sensörler ateş algılamazsa...
{

digitalWrite(sagileri, LOW);   // Sağ ileri motor durur.
digitalWrite(solileri, LOW);   // sol ileri motor durur. 
digitalWrite(saggeri, LOW);   // Sağ geri motor durur.
digitalWrite(solgeri, LOW);   // sol geri motor durur.
 
}  
else if (digitalRead(solsensor) ==0) //Eğer soldaki sensör ateş algılarsa...
{
  
digitalWrite(sagileri, HIGH);   // Sağ ileri motor döner.
digitalWrite(solileri, LOW);   // sol ileri motor durur.
digitalWrite(saggeri,LOW);   // Sağ geri motor durur.
digitalWrite(solgeri, LOW);   // sol geri motor durur.
 
}
else if (digitalRead(sagsensor) ==0) //Eğer sağdaki sensör ateş algılarsa...  
{
digitalWrite(sagileri, LOW);   // Sağ ileri motor durur.
digitalWrite(solileri, HIGH);   //Sol ileri motor döner.
digitalWrite(saggeri,LOW);   // Sağ geri motor durur.
digitalWrite(solgeri, LOW);   // Sol geri motor döner.

}
else if (digitalRead(ilerisensor) ==0) //Eğer ileri sensör ateş algılarsa...  
{
digitalWrite(sagileri, HIGH);   // Sağ ileri motor döner
digitalWrite(solileri, HIGH);   // sol ileri motor döner
digitalWrite(saggeri,LOW);   // Sağ geri motor durur
digitalWrite(solgeri, LOW);   // Sol geri motor durur
ates = true;
}
delay(300);
while (ates == true) //Eğer ileri sensör tarafından ateş algılanırsa atessondur fonksiyonu çağrılır.. 
{
atessondur();
}
}

