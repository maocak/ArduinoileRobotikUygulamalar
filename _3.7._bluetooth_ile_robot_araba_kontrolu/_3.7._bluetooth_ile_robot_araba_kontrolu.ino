// Motor 1
int motor1ileri = 3; //motor1 ileri hareketi kontrol eden pin
int motor1geri = 4;  //motor1 geri hareketi kontrol eden pin
int motor1hiz = 9; // motor1 in hızını kontrol eden pin(PWM özelliği olan pin olmalıdır)

// Motor 2
int motor2ileri = 5; //motor2 ileri hareketi kontrol eden pin
int motor2geri = 6;  //motor2 geri hareketi kontrol eden pin
int motor2hiz = 10; // motor2 in hızını kontrol eden pin(PWM özelliği olan pin olmalıdır) 

const int BTdurum = 2; //Bluetooth (HC-05) modülünün pini tanımlanır. 
int durum; //durum isimli değişken atanır. 
int hiz=200;     // Hız ilk değeri 200 PWM atanır. 

void setup() {
// Seri veri iletişim hızı HC-05 kullanıldığı için 38400 olmalıdır. Yoksa iletişim sağlanmaz.
Serial.begin(38400);
     
pinMode(motor1ileri,OUTPUT);
pinMode(motor1geri,OUTPUT);
pinMode(motor1hiz,OUTPUT);

pinMode(motor2ileri,OUTPUT);
pinMode(motor2geri,OUTPUT);
pinMode(motor2hiz,OUTPUT);

pinMode(BTdurum, INPUT);     
}
 
void loop() {

if(digitalRead(BTdurum)==LOW) { 
durum='S'; 
} //Bağlantı koptuğunda ya da Hc-05 modül bağlantısı kesildiğinde araba durur. 

//Hızı değiştirecek veri okunarak durum adlı değişkene atanır. 
if(Serial.available() > 0){     
durum = Serial.read();   
}
//0 ile 4 arası girilen değere göre arabanın hızı değişir. Bu hız, Android programda kaydırma çubuğu ile belirlenir. 
//Değerler 0-255 arası PWM olması gerekir. 
if (durum == '0'){ //Android programdan gelen değer 0 ise hız 50 PWM olur. 
hiz=50;} 
else if (durum == '1'){ //Android programdan gelen değer 1 ise hız 100 PWM olur.
hiz=100;}
else if (durum == '2'){ //Android programdan gelen değer 2 ise hız 150 PWM olur.
hiz=150;}
else if (durum == '3'){ //Android programdan gelen değer 3 ise hız 200 PWM olur.
hiz=200;}
else if (durum == '4'){ //Android programdan gelen değer 4 ise hız 255 PWM olur.
hiz=255;}
 	  
//Eğer arabellekten gelen değer 'F' ise, araba İLERİ hareket eder. 
if (durum == 'F') {
    	
analogWrite(motor1hiz, hiz); //Motorların hız değerleri kaydırma çubuğundan gelen değere göre atanır. 
analogWrite(motor2hiz, hiz);

digitalWrite(motor1ileri, HIGH); //motor1 ve motor2 ileri pinleri HIGH olur. 
digitalWrite(motor1geri, LOW);  //motor1 ve motor2 geri pinleri LOW olur. 
digitalWrite(motor2ileri, HIGH); //Böylecek motorlar ileri doğru hareketi sağlar. 
digitalWrite(motor2geri, LOW);  //Ve araba ileri gider. 
    	
}
//Eğer arabellekten gelen değer(durum) 'B' ise, araba GERİ hareket eder. 
else if (durum == 'B') {
analogWrite(motor1hiz, hiz); //motor1'in hiz değeri atanır. 
analogWrite(motor2hiz, hiz); //motor2'in hız değeri atanır. 

digitalWrite(motor1ileri, LOW); //Motor1 ileri pin LOW değeri atanır. 
digitalWrite(motor1geri, HIGH); //Motor1 geri pin HIGH değeri atanır. 
digitalWrite(motor2ileri, LOW); //Motor2 ileri pin LOW değeri atanır. 
digitalWrite(motor2geri, HIGH); //Motor2 geri pin HIGH değeri atanır. 

}
//Eğer arabellekten gelen değer(durum) 'L' ise, araba SOLA hareket eder.
else if (durum == 'L') {
analogWrite(motor1hiz, hiz); //Motor1 hız değeri atanır. 
analogWrite(motor2hiz, 0); //Motor2 hız değeri 0 atanır.

digitalWrite(motor1ileri, HIGH); //Motor1 ileri pin değeri HIGH atanır.
digitalWrite(motor1geri, LOW); //Motor1 geri pin değeri LOW atanır. Böylece araba sola doğru döner. 
}
//If durum 'R' ye eşitse, araba SAĞA hareket eder. 
else if (durum == 'R') {
analogWrite(motor1hiz, 0); //Motor1 hız pini 0 atanır. 
analogWrite(motor2hiz, hiz); //Motor2 hız pini için değer atanır. 

digitalWrite(motor2ileri, HIGH); //Motor2 ileri pin HIGH atanır. 
digitalWrite(motor2geri, LOW); //Motor2 geri pin LOW atanır. Böylece araba sağa doğru döner. 

}
//If durum 'S' ye eşitse, araba DURur. 
else if (durum == 'S'){
analogWrite(motor1hiz, 0); //Motor1 hız pini 0 olur. 
analogWrite(motor2hiz, 0); //Motor1 hız pini 0 olur. 

digitalWrite(motor1ileri, LOW); //Motor pinleri LOW atandığından araba hareket etmez. 
digitalWrite(motor1geri, LOW);
digitalWrite(motor2ileri, LOW);
digitalWrite(motor2geri, LOW);

}
} 



