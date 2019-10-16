#include <Servo.h> //servo motor kütüphanesini koda eklenir. 
Servo sagayak; //sağ ayak için kullanılacak servo motor nesnesi oluşturulur. 
Servo sagust;  //sağ üst için kullanılacak servo motor nesnesi oluşturulur. 
Servo solayak; //sol ayak için kullanılacak servo motor nesnesi oluşturulur. 
Servo solust;  //sol üst için kullanılacak servo motor nesnesi oluşturulur. 
int deger; //deger isimli bir değişken tanımlanır. 
void setup() 
{ 
sagayak.attach(3); //sağ ayak için kullanılacak motor 3 nolu dijital pine bağlanır. 
sagust.attach(5); //sağ üst için kullanılacak motor 5 nolu dijital pine bağlanır. 
solayak.attach(9); //sol ayak için kullanılacak motor 9 nolu dijital pine bağlanır. 
solust.attach(6); //sol üst için kullanılacak motor 6 nolu dijital pine bağlanır. 
} 
 
void loop() 
{  
int deger=120; //deger isimli değişkene ilk değer 120 atanır. 
sagayak.write(90); //sağ ayak servo motor 90 dereceye gider. 
sagust.write(90); //sağ üst servo motor 90 dereceye gider. 
solayak.write(90); //sol ayak servo motor 90 dereceye gider. 
solust.write(90); //sol üst servo motor 90 dereceye gider. 
delay(500); //500msn beklenir. 
solayak.write(55); //sol ayak servo motor 55 derecey gider. 
delay(400); //400 msn beklenir. 
for(int i=90;i<=115;i++) //sağ ayak servo motor 90 dereceden 115 dereceye gider. 
{
sagayak.write(i);
delay(12); //her geçişte 12msn beklenir. 
}
solayak.write(120); //sol ayak servo motor 120 dereceye gider. 
delay(100); //100msn beklenir. 
solust.write(120); //sol üst servo motor 120 derecey gider. 
delay(600); //600 msn beklenir. 
for(int i=90;i<=120;i++) //sağ üst ve sol üst servo motorlar 90 dereceden 120 dereceye gider.
{
sagust.write(i);
delay(12); //Her geçişte 12msn beklenir. 
solust.write(i); 
delay(12); //Her geçişte 12msn beklenir. 
}
solayak.write(90); //Sol ayak servo motor 90 derecey gider. 
delay(300); //300 msn beklenir. 
for(int i=115;i>=90;i--) //sağ ayak servo motor 115 dereceden 90 dereceye gider. 
{
sagayak.write(i);
delay(12); //Her geçişte 12 msn beklenir. 
}
delay(500); //500msn beklenir. 
sagayak.write(120); //sağ ayak servo motor 120 dereceye gider. 
delay(300); //300 msn beklenir. 
solayak.write(65); //Sol ayak servo motor 65 dereceye gider. 
sagust.write(60); //Sağ üst servo motor 60 dereceye gider. 
for(deger=120;deger>=60;deger--) //Sol üst servo motor 120 dereceden 60 dereceye gider. 
{
solust.write(deger);
delay(7); //7 msn beklenir. 
}
sagayak.write(60); //Sağ ayak servo motor 60 dereceye gider. 
delay(500); //500 msn beklenir. 
sagayak.write(90); //Sağ ayak servo motor 90 dereceye gider. 
delay(300); //300msn beklenir. 
solayak.write(90); //Sol ayak servo motor 90 dereceye gider. 
delay(300); //300msn beklenir. 
solust.write(60); //Sol üst servo motor 60 dereceye gider. 
delay(300); //300 msn beklenir. 
sagust.write(60); //Sağ üst servo motor 60 dereceye gider. 
delay(800);
} 
