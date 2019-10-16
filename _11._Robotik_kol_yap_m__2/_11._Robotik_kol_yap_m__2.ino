#include <Servo.h> //servo kütüphanesi koda eklenir. 
Servo servo1; //4 adet servo motor nesneleri oluşturulur. 
Servo servo2;
Servo servo3;
Servo servo4;
int pot1deger; //pot1deger isimli değişken tanımlanır. 
int pot2deger; //pot2deger isimli değişken tanımlanır. 
int pot3deger; //pot3deger isimli değişken tanımlanır. 
int pot4deger; //pot4deger isimli değişken tanımlanır. 

void setup()
{
pinMode(A0,INPUT); //A0 analog pin giriş olarak tanımlanır. 
pinMode(3,OUTPUT); //3 nolu dijital pin çıkış olarak tanımlanır. 
servo1.attach(3); //1.servo motor 3 nolu dijital pine bağlanır. 
  
pinMode(A1,INPUT); //A1 analog pin giriş olarak tanımlanır. 
pinMode(5,OUTPUT); //5 nolu dijital pin çıkış olarak tanımlanır.
servo2.attach(5);  //2.servo motor 5 nolu dijital pine bağlanır. 
  
pinMode(A2,INPUT); //A2 analog pin giriş olarak tanımlanır. 
pinMode(6,OUTPUT); //6 nolu dijital pin çıkış olarak tanımlanır.
servo3.attach(6);  //3.servo motor 6 nolu dijital pine bağlanır. 
  
pinMode(A3,INPUT); //A3 analog pin giriş olarak tanımlanır.
pinMode(9,OUTPUT); //9 nolu dijital pin çıkış olarak tanımlanır.
servo4.attach(9);  //4.servo motor 9 nolu dijital pine bağlanır. 
}

void loop()
{
pot1deger = analogRead(A0); //A0 pininden okunan analog değer pot1deger isimli değişkene atanır. 
pot1deger = map(pot1deger, 0, 1023, 10, 170); //0-1023 arası okunan analog değer 0-180 arası açısal değere dönüştürülür. 
servo1.write(pot1deger); //servo1 motor dönüştürülen açısal değere gider. 
pot2deger = analogRead(A1); //A1 pininden okunan analog değer pot2deger isimli değişkene atanır.
pot2deger = map(pot2deger, 0, 1023, 0, 180); //0-1023 arası okunan analog değer 0-180 arası açısal değere dönüştürülür.
servo2.write(pot2deger); //servo2 motor dönüştürülen açısal değere gider. 
pot3deger = analogRead(A2); //A2 pininden okunan analog değer pot3deger isimli değişkene atanır.
pot3deger = map(pot3deger, 0, 1023, 0, 180); //0-1023 arası okunan analog değer 0-180 arası açısal değere dönüştürülür.
servo3.write(pot3deger); //servo3 motor dönüştürülen açısal değere gider. 
pot4deger = analogRead(A3); //A3 pininden okunan analog değer pot4deger isimli değişkene atanır.
pot4deger = map(pot4deger, 0, 1023, 0, 180); //0-1023 arası okunan analog değer 0-180 arası açısal değere dönüştürülür.
servo4.write(pot4deger); //servo4 motor dönüştürülen açısal değere gider. 
}

