/*Klavyeden kontrollü Robot Araba Uygulaması
Klavye yerleşimine de uygun olarak yönler aşağıdaki şekilde tanımlanmıştır.
Klavye 7 Tuşu Sol İleri
Klavye 8 Tuşu Direkt İleri
Klavye 9 Tuşu İleri Sağ
Klavye 1 Tuşu Sol Geri
Klavye 2 Tuşu Direkt Geri
Klavye 3 Tuşu Sağ Geri */

// Motor 1
int motor1ileri = 2; //motor1 ileri hareketi kontrol eden pin
int motor1geri = 3;  //motor1 geri hareketi kontrol eden pin
int motor1hiz = 9; // motor1 in hızını kontrol eden pin(PWM özelliği olan pin olmalıdır)

// Motor 2
int motor2ileri = 4; //motor2 ileri hareketi kontrol eden pin
int motor2geri = 5;  //motor2 geri hareketi kontrol eden pin
int motor2hiz = 10; // motor2 in hızını kontrol eden pin(PWM özelliği olan pin olmalıdır)

void setup() { 
// seri veri iletişimi başlatılır.
Serial.begin(9600);

//motor1 ve motor2 ileri, geri ve hız pinleri çıkış olarak atanır.

pinMode(motor1ileri,OUTPUT);
pinMode(motor1geri,OUTPUT);
pinMode(motor1hiz,OUTPUT);

pinMode(motor2ileri,OUTPUT);
pinMode(motor2geri,OUTPUT);
pinMode(motor2hiz,OUTPUT);

}

void loop() {

if (Serial.available() > 0) { //seri porttan veri girişi yapıldığında...
int gelenveri = Serial.read(); //gelenveri isimli değişkene atanır.

switch (gelenveri) {

case '7': // Motor 1 sol ileri
analogWrite(motor1hiz, 100); // PWM değeri 100 olarak ayarlanır. 
analogWrite(motor2hiz, 0);
digitalWrite(motor1ileri, HIGH);
digitalWrite(motor1geri, LOW);
Serial.println("Motor 1 sol ileri"); // Seri port ekranında "Motor 1 sol ileri" yazar
break;

case '1': // Motor 1 sol geri
analogWrite(motor1hiz, 100);
analogWrite(motor2hiz, 0);
digitalWrite(motor1ileri, LOW);
digitalWrite(motor1geri, HIGH);
Serial.println("Motor 1 sol geri");
break;

case '9': // Motor 2 sağ ileri
analogWrite(motor1hiz, 0);
analogWrite(motor2hiz, 100);
digitalWrite(motor2ileri, HIGH);
digitalWrite(motor2geri, LOW);
Serial.println("Motor 2 sağ ileri");
break;

case '5': // Tamamen dur
analogWrite(motor1hiz, 0);
analogWrite(motor2hiz, 0);

digitalWrite(motor1ileri, HIGH);
digitalWrite(motor1geri, LOW);
digitalWrite(motor2ileri, HIGH);
digitalWrite(motor2geri, LOW);
Serial.println("Tamamen dur");
break;

case '3': // Motor 2 sağ geri
analogWrite(motor1hiz, 0);
analogWrite(motor2hiz, 100);
digitalWrite(motor2ileri, LOW);
digitalWrite(motor2geri, HIGH);
Serial.println("Motor 2 sağ geri");
break;

case '8': // Motor 1 ve 2 ileri
analogWrite(motor1hiz, 100);
analogWrite(motor2hiz, 100);

digitalWrite(motor1ileri, HIGH);
digitalWrite(motor1geri, LOW);
digitalWrite(motor2ileri, HIGH);
digitalWrite(motor2geri, LOW);
Serial.println("Motor 1 ve 2 ileri");
break;


case '2': // Motor 1 ve 2 geri
analogWrite(motor1hiz, 100);
analogWrite(motor2hiz, 100);

digitalWrite(motor1ileri, LOW);
digitalWrite(motor1geri, HIGH);
digitalWrite(motor2ileri, LOW);
digitalWrite(motor2geri, HIGH);
Serial.println("Motor 1 ve 2 geri");
break;

}
}
}
