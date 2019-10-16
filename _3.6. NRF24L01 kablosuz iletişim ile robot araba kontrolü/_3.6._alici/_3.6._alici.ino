#include <SPI.h> //kütüphaneler koda eklenir.
#include <nRF24L01.h>
#include <RF24.h>

#define motor1hizpin 2 //motor1 hız pini atanır. 
#define motor1ileri 4 //motor1 ileri hareket pini atanır. 
#define motor1geri 5 //motor1 geri hareket pini atanır. 
#define motor2hizpin 3 //motor2 hız pini atanır. 
#define motor2ileri 6 //motor2 ileri hareket pini atanır. 
#define motor2geri 7 //motor2 geri hareket pini atanır. 

int motor1hiz = 0; //motor1 ve motor2 ilk hızları 0 atanır. 
int motor2hiz = 0;

RF24 radio(9, 10); // CE, CSN pinleri atanır. 
const uint64_t veriadresi = 0xE8E8F0F0E1LL; //veri alışverişi yapılacak adres yolu atanır. verici ve alıcı kodda bu aynı olmalıdır.

int  xekseni, yekseni;
int motorSpeedA = 0;
int motorSpeedB = 0;
float deger[2]; //2 elemanlı değer isimli bir dizi tanımlanır.    
   
void setup() {
Serial.begin(9600); //seri veri iletişimi başlatılır. 
radio.begin(); //NRF24L01 başlatılır. 
radio.openReadingPipe(1, veriadresi); //veri okuma için veriadresi yolu açılır.
radio.startListening(); //Açılan veri yolundan veri dinleme işlemi başlatılır.
     
pinMode(motor1hizpin, OUTPUT); //motorların hız ve ileri-geri pinleri çıkış olarak atanır. 
pinMode(motor2hizpin, OUTPUT);
pinMode(motor1ileri, OUTPUT);
pinMode(motor1geri, OUTPUT);
pinMode(motor2ileri, OUTPUT);
pinMode(motor2geri, OUTPUT);
}

void loop() {
if (radio.available()) {   // If the NRF240L01 module received data
bool degisken = false; //degisken ilk değer false atanır.
while (!degisken) //eğer veri girişi yapılırsa değişken true değeri alır ve program devam eder. 
{
degisken = radio.read(&deger, sizeof(deger)); //vericiden okunan değer degiskene atanır. 

Serial.print(deger[0]); //okunan veri seri port ekrana yazdırılır. 
Serial.print(" "); 
Serial.println(deger[1]); //okunan veri seri port ekrana yazdırılır.
}
}
xekseni=deger[1]; //X eksenine deger[1] den okunan değerler atanır. 
yekseni=deger[0]; //Y eksenine dege[0] dan okunan değerler atanır. 
 if (yekseni < 470) {
//  Motor 1 geri
digitalWrite(motor1ileri, LOW);
digitalWrite(motor1geri, HIGH);
//  Motor 2 geri
digitalWrite(motor2ileri, LOW);
digitalWrite(motor2geri, HIGH);
// Motor hızını artırmak için  geriye doğru 470'dan 0'a azalan Y ekseni değerlerini, PWM sinyali için 0'dan 255'e dönüştürür.
motor1hiz = map(yekseni, 470, 0, 0, 255); //her iki motorda aynı hızda geri hareket eder. 
motor2hiz = map(yekseni, 470, 0, 0, 255);
}
else if (yekseni > 550) {
//  Motor 1 ileri
digitalWrite(motor1ileri, HIGH);
digitalWrite(motor1geri, LOW);
// Motor 2 ileri
digitalWrite(motor2ileri, HIGH);
digitalWrite(motor2geri, LOW);
// Motorların hızını arttırmak için  550'den 1023'e  artan Y ekseni değerlerini PWM sinyali için 0'dan 255'e dönüştür
motor1hiz = map(yekseni, 550, 1023, 0, 255); //her iki motorda aynı hızda ileri hareket eder.
motor2hiz = map(yekseni, 550, 1023, 0, 255);
}
// Joystick ortada ise motorlar hareket etmez
else {
motor1hiz = 0;
motor2hiz = 0;
}
// Sol ve sağ kontrol için kullanılan X ekseni
if (xekseni < 470) {
// x değerleri 470den küçükse sağdaki motor(motor1) ileri doğru hareket eder. 
//  Motor 1 ileri
digitalWrite(motor1ileri, HIGH);
digitalWrite(motor1geri, LOW);    
int donusturulendeger = map(xekseni, 470, 0, 0, 255); //Azalan 470'dan 0'a X ekseni değerleri, 0'dan 255'e artan bir değere dönüştürülür.
// Sola dön - sol motor hızını düşürür, sağ motor hızını arttır
motor2hiz = motor2hiz - donusturulendeger;
motor1hiz = motor1hiz + donusturulendeger;
}
if (xekseni > 550) { // x değerleri 550den büyükse soldaki motor(motor2) ileri doğru hareket eder.
// Motor 2 ileri
digitalWrite(motor2ileri, HIGH);
digitalWrite(motor2geri, LOW);
int donusturulendeger = map(xekseni, 550, 1023, 0, 255); // Artan 550'den 1023'e X ekseni değerleri  0'dan 255'e dönüştür
// Sağa dön - sağ motor hızını düşür, sol motor hızını arttır
motor1hiz = motor1hiz - donusturulendeger;
motor2hiz = motor2hiz + donusturulendeger;
}
analogWrite(motor1hizpin, motor1hiz); // Motor 1'e PWM sinyali gönderilir.
analogWrite(motor2hizpin, motor2hiz); // Motor 2'e PWM sinyali gönderilir. 
}
