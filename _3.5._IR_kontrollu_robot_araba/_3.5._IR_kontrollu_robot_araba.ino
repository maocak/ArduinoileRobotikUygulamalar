#include <IRremote.h> //IR kütüphanesi eklenir. 
 
int kizilotesiIR_pin = 11;  //IR okuyucu pin atanır. 
int kirmiziLEDpin = 12; //LED pini atanır. 
// Motor 1
int motor1ileri = 2; //motor1 ileri hareketi kontrol eden pin
int motor1geri = 3;  //motor1 geri hareketi kontrol eden pin
int motor1hiz = 9; // motor1 in hızını kontrol eden pin(PWM özelliği olan pin olmalıdır)

// Motor 2
int motor2ileri = 4; //motor2 ileri hareketi kontrol eden pin
int motor2geri = 5;  //motor2 geri hareketi kontrol eden pin
int motor2hiz = 10; // motor2 in hızını kontrol eden pin(PWM özelliği olan pin olmalıdır)
 
IRrecv iralici(kizilotesiIR_pin); //IR alıcı nesnesi oluşturulur. 
decode_results sonuclar;  //decode_results sınıfından sonuclar isimli bir nesne oluşturulur. 
//Bu nesne iralici tarafından kullanılacak olup, bilgileri decode etmeye yarar.
 
void setup()
{
Serial.begin(9600); //seri veri iletişimi başlatılır. 
iralici.enableIRIn(); // IR okuyucu başlatılır. 

pinMode(kirmiziLEDpin,OUTPUT); //LED pini çıkış olarak tanımlanır. 

pinMode(motor1ileri,OUTPUT); //motor 1 ileri, geri ve hız pinleri tanımlanır. 
pinMode(motor1geri,OUTPUT);
pinMode(motor1hiz,OUTPUT);

pinMode(motor2ileri,OUTPUT); //motor 2 ileri, geri ve hız pinleri tanımlanır.
pinMode(motor2geri,OUTPUT);
pinMode(motor2hiz,OUTPUT);


}
void loop()
{
if (iralici.decode(&sonuclar)) //Eğer okuyucu tuşa basıldığını algılarsa...
{
cevirIR(); //Alınan kod oluşturulan fonksiyona yollanır. 
iralici.resume(); // bir sonraki tuşa basma için IR okuyucu hazır hale getirilir. 
}
}
 
void cevirIR() // tuşa basılınca alından kod koşu yardımıyla ilgili LEDi yakar. 
{
switch(sonuclar.value) //alınan kod eğer...
{
case 0xFF18E7:  //2 ise(FF18E7), ileri gider.
 
digitalWrite(kirmiziLEDpin,HIGH); //kırmızı LED yanar.

analogWrite(motor1hiz, 100); //motor1 ve motor2  hız pinleri PWM değeri 100 atanır. 
analogWrite(motor2hiz, 100);

digitalWrite(motor1ileri, HIGH); //motor1 ve motor2 ileri  pinleri HIGH durumda olduğundan araba ileri gider. 
digitalWrite(motor1geri, LOW);
digitalWrite(motor2ileri, HIGH);
digitalWrite(motor2geri, LOW);
delay(100);
digitalWrite(kirmiziLEDpin,LOW); //Kırmızı LED söner. 
break;

case 0xFF4AB5:  //8 ise(FF4AB5), geri gider. 
digitalWrite(kirmiziLEDpin,HIGH); //kırmızı LED yanar.

analogWrite(motor1hiz, 100); //motor1 ve motor2  hız pinleri PWM değeri 100 atanır. 
analogWrite(motor2hiz, 100);

digitalWrite(motor1ileri, LOW); //motor1 ve motor2 geri  pinleri HIGH durumda olduğundan araba geri gider.
digitalWrite(motor1geri, HIGH);
digitalWrite(motor2ileri, LOW);
digitalWrite(motor2geri, HIGH);

delay(100);
digitalWrite(kirmiziLEDpin,LOW); //Kırmızı LED söner.
break;

case 0xFF10EF:  //4 ise(FF10EF), sola döner. 
digitalWrite(kirmiziLEDpin,HIGH); //kırmızı LED yanar.

analogWrite(motor1hiz, 100); //motor1 hız pini için 100 ve motor2  hız pini için PWM değeri 0 atanır. 
analogWrite(motor2hiz, 0);
digitalWrite(motor1ileri, HIGH); //motor1ileri pin HIGH olduğu için motor sola döner.
digitalWrite(motor1geri, LOW);
digitalWrite(motor2ileri, LOW);
digitalWrite(motor2geri, LOW);

delay(100);
digitalWrite(kirmiziLEDpin,LOW); //Kırmızı LED söner.

break;
case 0xFF5AA5:  //6 ise(FF5AA5), sağa döner. 
digitalWrite(kirmiziLEDpin,HIGH); //kırmızı LED yanar.

analogWrite(motor1hiz, 0); //motor1 hız pini için 0 ve motor2  hız pini için PWM değeri 100 atanır.
analogWrite(motor2hiz, 100);
digitalWrite(motor1ileri, LOW);
digitalWrite(motor1geri, LOW);
digitalWrite(motor2ileri, HIGH); //motor2ileri pin HIGH olduğu için motor sola döner.
digitalWrite(motor2geri, LOW);

delay(100);
digitalWrite(kirmiziLEDpin,LOW); //Kırmızı LED söner.
break;
case 0xFF38C7: //5 ise(FF38C7), araba durur. 
digitalWrite(kirmiziLEDpin,HIGH); //kırmızı LED yanar.

analogWrite(motor1hiz, 0); //motor1 ve motor2  hız pini için PWM değeri 0 atanır.
analogWrite(motor2hiz, 0);

digitalWrite(motor1ileri, LOW); //Tüm pinler LOW durumunda olduğundan araba durur. 
digitalWrite(motor1geri, LOW);
digitalWrite(motor2ileri, LOW);
digitalWrite(motor2geri, LOW);
delay(100);
digitalWrite(kirmiziLEDpin,LOW); //Kırmızı LED söner.
break;

default: // başka bir tuşa basıldığında LED yanıp sönerek uyarı verir. 
digitalWrite(kirmiziLEDpin,HIGH); //kırmızı LED yanar.
delay(50);
digitalWrite(kirmiziLEDpin,LOW); //kırmızı LED söner.
delay(50);
digitalWrite(kirmiziLEDpin,HIGH); //kırmızı LED yanar.
delay(50);
digitalWrite(kirmiziLEDpin,LOW); //kırmızı LED söner.
}
}

