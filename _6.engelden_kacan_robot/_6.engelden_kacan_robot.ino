#include <NewPing.h>
#include <Servo.h> 

#define trig_pin A4 //mesafe sensörünün trig pini tanımlanır. 
#define echo_pin A5 //mesafe sensörünün echo pini tanımlanır. 
#define maksimum_uzaklik 200 //mesafe sensörü için maksimum uzaklık cm cinsinden belirlenir. 
NewPing sonar(trig_pin, echo_pin, maksimum_uzaklik); //kütüphane yardımıyla mesafe sensör nesnesi oluşturulur. 
Servo servo;  servo motor nesnesi oluşturulur. 
int ledileri=2; //LED ileri pin tanımlanır. 
int ledgeri=3; //LED geri pin tanımlanır. 

int uzaklik=100; //uzaklık ilk değeri 100 olarak atanır. 

int solileri = 5; //Sol motor ileri pin tanımlanır.
int solgeri = 6; //Sol motor geri pin tanımlanır. 

int sagileri = 10; //Sağ motor ileri pin tanımlanır. 
int saggeri = 11; //Sağ motor geri  pin tanımlanır. 

void setup(){

servo.attach(9);  //Servomotor 9 nolu dijial pine bağlanır. 
servo.write(115); //Servomotor 115 derecede okuma yapar. 
delay(2000); //2 saniye beklenir. 
uzaklik = uzaklikoku(); //Uzaklık oku sensöründen okunan değer uzaklık isimli değişkene atanır. 
delay(100);

pinMode(ledileri, OUTPUT); //LED pinleri çıkış olarak atanır. 
pinMode(ledgeri, OUTPUT);

pinMode(solileri, OUTPUT); //Sol motor ileri ve geri pinleri çıkış olarak atanır. 
pinMode(solgeri, OUTPUT);

pinMode(sagileri, OUTPUT); //Sağ motor ileri ve geri pinleri çıkış olarak atanır. 
pinMode(saggeri, OUTPUT);

}

void loop() {
int saguzaklik = 0; //sağ uzaklık ilk değeri 0 atanır. 
int soluzaklik =  0; //sol uzaklık ilk değeri 0 atanır. 
Serial.begin(9600); //Seri veri iletişimi başlatılır. 
Serial.println(uzaklik); //Okunan uzaklık değeri aynı zamanda seri port ekranda takip edilebilir. 
 
if(uzaklik<35) //Eğer okunan değer 35 cm'den küçükse...
{
digitalWrite(ledileri, LOW); //Yeşil LED söner.
digitalWrite(ledgeri, HIGH); //Kırmızı LED yanar. 
dur(); //dur fonksiyonu çağrılır. 
delay(100); 100 msn beklenir. 
gerigit(); //gerigit fonksiyonu çağrılır. 
delay(300); //300 msn beklenir. 
dur(); //dur fonksiyonu çağrılır. 
delay(200); //200 msn beklenir. 
saguzaklik = sagabak(); //sagabak fonksiyonundan okunan değer saguzaklik değişkenine atanır. 
delay(200); //200 msn beklenir. 
soluzaklik = solabak(); //solabak fonksiyonundan okunan değer soluzaklik değişkenine atanır. 
delay(200); //200 msn beklenir. 
Serial.print("sağ mesafe");Serial.println(saguzaklik); //sağ taraftan okunan değer seri port ekrana yazdırılır. 
Serial.print("sol mesafe");Serial.println(soluzaklik); //sol taraftan okunan değer seri port ekrana yazdırılır. 
if(saguzaklik>=soluzaklik) //Eğer sağ taraftaki boşluk, sol taraftakinden fazla ise...
{
sagadon(); //sağa dön fonksiyonu çağrılır.
dur(); //dur fonksiyonu çağrılır. 
} else //Eğer sol taraftaki boşluk, sağ taraftakinden fazla ise...
{
soladon(); //sola dön fonksiyonu çağrılır. 
dur(); //dur fonksiyonu çağrılır. 
}
}
else //Her iki durumda karşılanmazsa...
{
digitalWrite(ledileri, HIGH); //yeşil LED yanar. 
digitalWrite(ledgeri, LOW); //Kırmızı LED söner. 
ileri(); //İleri fonksiyonu çağrılır. 
delay(10); //10msn beklenir. 
}
uzaklik = uzaklikoku(); //uzaklikoku fonksiyonundan okunan değer tekrar uzaklik isimli değişkene atanır. 
} 

int sagabak() //Sağa bak fonkisyonu
{
servo.write(50); //Servomotor 50 dereceye(sağa doğru) döner...
delay(500); //500 msn beklenir. 
int uzaklik = uzaklikoku(); //uzaklikoku fonksiyonu çağrılır. 
delay(100); //100msn beklenir. 
servo.write(115); //Servomotor 115 dereyece(ileri) döner. 
return uzaklik; //okunan uzaklık değeri döndürülür. 
}

int solabak() //Sola bak fonkisyonu
{
servo.write(170); //Servomotor 170 dereceye(sola doğru) döner...
delay(500); //500 msn beklenir. 
int uzaklik = uzaklikoku();  //uzaklikoku fonksiyonu çağrılır.
delay(100); //100msn beklenir. 
servo.write(115); //Servomotor 115 dereyece(ileri) döner.
return uzaklik; //okunan uzaklık değeri döndürülür.
delay(100); //100msn beklenir. 
}

int uzaklikoku() { //Uzaklık oku fonksiyonu
delay(10);
int cm = sonar.ping_cm(); //Newping kütüphanesi yardımıyla uzaklık cm cinsinden ölçülür ve cm isilmli değişkene atanır. 
if(cm==0) //Eğer okunan değer 0 ise cm değişkeninen 250cm atanır.
{
cm = 250;
}
return cm; //Değer 0 değilse ölçülen uzaklık cm cinsinden döndürülür. 
}

void dur(){ //dur fonksiyonu. Tüm motor pinleri LOW konumunda. Robot araba durur. 
  
digitalWrite(solileri, LOW);
digitalWrite(solgeri, LOW);

digitalWrite(sagileri, LOW);
digitalWrite(saggeri, LOW);
}

void ileri(){ //ileri fonksiyonu. //Sol ve sağ motor pinleri HIGH konumda. Robot araba ileri hareket eder. 

digitalWrite(solileri, HIGH);
digitalWrite(solgeri, LOW);

digitalWrite(sagileri, HIGH);
digitalWrite(saggeri, LOW); 
}

void gerigit(){ //gerigit fonksiyonu. Sol ve sağ geri  pinleri HIGH durumda. Robot araba geri gider. 

digitalWrite(solileri, LOW);
digitalWrite(solgeri, HIGH);

digitalWrite(sagileri, LOW);
digitalWrite(saggeri, HIGH);
  
}

void sagadon(){ //sagadon fonksiyonu. Sol motor ileri pin HIGH diğerleri LOW durumda. Robot araba sağa döner. 

digitalWrite(solileri, HIGH);
digitalWrite(solgeri, LOW);

digitalWrite(sagileri, LOW);
digitalWrite(saggeri, LOW);

delay(300);  //300msn beklenir. 
ileri(); //Dönme işlemi yaptıktan sonra ileri fonksiyonu tekrar çağrılır ve ileri hareket gerçekleştirilir. Yoksa, robot araba devamlı sağa döner. 

}

void soladon(){ //soladon fonksiyonu. Sağ motor ileri pin HIGH diğerleri LOW durumda. Robot araba sola döner.

digitalWrite(solileri, LOW);
digitalWrite(solgeri, LOW);

digitalWrite(sagileri, HIGH);
digitalWrite(saggeri, LOW);  
delay(300); //300msn beklenir. 
ileri(); //Dönme işlemi yaptıktan sonra ileri fonksiyonu tekrar çağrılır ve ileri hareket gerçekleştirilir. Yoksa, robot araba devamlı sola döner. 
}

