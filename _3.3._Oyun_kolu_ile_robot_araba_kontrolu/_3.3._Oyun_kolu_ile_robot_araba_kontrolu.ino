#define motor1hizpin 10 //motor1 hız pini atanır. 
#define motor1ileri 2 //motor1 ileri hareket pini atanır. 
#define motor1geri 3 //motor1 geri hareket pini atanır. 
#define motor2hizpin 11 //motor2 hız pini atanır. 
#define motor2ileri 4 //motor2 ileri hareket pini atanır. 
#define motor2geri 5 //motor2 geri hareket pini atanır. 

int motor1hiz = 0; //motor1 ve motor2 ilk hızları 0 atanır. 
int motor2hiz = 0;
    
void setup() {
Serial.begin(9600); //seri veri iletişimi başlatılır. 
pinMode(motor1hizpin, OUTPUT); //motorların hız ve ileri-geri pinleri çıkış olarak atanır. 
pinMode(motor2hizpin, OUTPUT);
pinMode(motor1ileri, OUTPUT);
pinMode(motor1geri, OUTPUT);
pinMode(motor2ileri, OUTPUT);
pinMode(motor2geri, OUTPUT);
}
    
void loop() {
int xekseni = analogRead(A1); // X ekseni değerleri A1 girişinden okunur. 
int yekseni = analogRead(A0); // Y ekseni değerleri A0 girişinden okunur. 
Serial.print("X ekseni:");
Serial.print(xekseni);
Serial.print("Y ekseni:");
Serial.println(yekseni);
// Y ekseni geri ve ileri kontrol
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
