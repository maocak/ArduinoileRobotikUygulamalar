#include <IRremote.h> //IR kütüphanesini koda eklenir. 
#include <Servo.h> //servo motor kütüphanesi koda eklenir. 

int IRpin = 11; //IR okuyucu pin atanır.

IRrecv iralici(IRpin);  //IR alıcı nesnesi oluşturulur. 
decode_results sonuclar;  //decode_results sınıfından sonuclar isimli bir nesne oluşturulur. 
//Bu nesne iralici tarafından kullanılacak olup, bilgileri decode etmeye yarar.

Servo servo;  //servo motorlar için nesne oluşturulur. 
Servo servodon;
 
int aci = 0;   // servo motorların ilk derecesi 0 olarak atanır.  
int acidon = 0; 

void setup()
{
Serial.begin(9600); //seri veri iletişimi başlatılır.
iralici.enableIRIn(); // IR okuyucu başlatılır. 
servo.attach(4); //1. servo motor 4 nolu dijital pine bağlanır. 
servo.write(90); //program çalıştırıldığında 1.servo motor 90 derece açıya gider. 
servodon.attach(7); //2.servo motor 7 nolu dijital pine bağlanır. 
servodon.write(90); //program çalıştırıldığında 2.servo motor 90 derece açıya gider. 
}
void loop()
{
if (iralici.decode(&sonuclar)) //Eğer okuyucu tuşa basıldığını algılarsa...
{
Serial.println(sonuclar.value, HEX); //işlenen kod seri port ekrana yazdırılır. 
cevirIR(); //Alınan kod oluşturulan fonksiyona yollanır. 
iralici.resume(); // bir sonraki değer gelene kadar beklenir. 
}
}
void cevirIR() // tuşa basılınca alınan kod koşul yardımıyla ilgili servo motorun açısal değere gitmesi sağlanır. . 
{
switch(sonuclar.value) //alınan değer...
{
case 0XFF6897:  //0 ise, 10 dereceye git. 
aci = 10;
break;

case 0xFF9867:  //100+ ise, 170 dereceye git. 
aci = 170;
break;

case 0xFFE21D:  //CH++ ise, dereceyi artır. 
aci++;
Serial.println(aci); //seri port ekrandan açısal değer takip edilebilir. 
break;

case 0xFFA25D:  //CH-- ise, dereceyi azalt. 
aci--;
Serial.println(aci); //seri port ekrandan açısal değer takip edilebilir.
break;

case 0xFF02FD: //>> ise, 160 dereceye git. 
acidon = 160;
break;

case 0xFF22DD: //<< ise, 10 dereceye git. 
acidon= 10;
break;

case 0xFFA857: //+ ise, dereceyi artır. 
acidon++;
Serial.println(acidon); //seri port ekrandan açısal değer takip edilebilir.
break;

case 0xF076C13B: //- ise, dereceyi azalt. 
acidon --; 
Serial.println(acidon); //seri port ekrandan açısal değer takip edilebilir.
break;

default: //başka bir tuşa basıldığında "diğer tuşlara basıldı!" uyarısını verir. 
Serial.println("diğer tuşlara basıldı!");
}
servodon.write(acidon); //case koşullarından gelen değere göre 2.servomotor hareket eder. 
delay(15);
servo.write(aci); //case koşullarından gelen değere göre 1.servomotor hareket eder.
delay(15);

}


   
