int sensor1=2; //sensör pinleri tanımlanır. 
int sensor2=3;

int motor1ileri = 4; //motor1 ileri pin
int motor1geri = 5;  //motor1 geri pin
int motor2ileri= 6;  //motor2 ileri pin
int motor2geri =7;  //motor2 geri pin

int motor1hiz = 9; // motor1 in hızını kontrol eden pin(PWM özelliği olan pin olmalıdır)
int motor2hiz = 10; // motor2 in hızını kontrol eden pin(PWM özelliği olan pin olmalıdır) 

void setup() {
Serial.begin(9600);
pinMode(motor1ileri,OUTPUT); //motor1 ileri pin çıkış olarak atanır. 
pinMode(motor1geri,OUTPUT); //motor1 geri pin çıkış olarak atanır. 
pinMode(motor2ileri,OUTPUT); //motor2 ileri pin çıkış olarak atanır. 
pinMode(motor2geri,OUTPUT); //motor2 geri pin çıkış olarak atanır. 

pinMode(sensor1,INPUT); //sensör1 pini giriş olarak atanır. 
pinMode(sensor2,INPUT); //sensör2 pini giriş olarak atanır. 

pinMode(motor1hiz,OUTPUT); //Motor1 hiz pini çıkış olarak atanır. 
pinMode(motor2hiz,OUTPUT); //Motor2 hiz pini çıkış olarak atanır. 

}

void loop() {
// put your main code here, to run repeatedly:
int s1=digitalRead(2); //2 nolu dijital pinden sensör değeri okunur. 
int s2=digitalRead(3); //3 nolu dijital pinden sensör değeri okunur. 
Serial.print(s1); //okunan s1 değeri seri port ekrana yazdırılır.
Serial.println(s2); //okunan s2 değeri seri port ekrana yazdırılır. 

if(s1==LOW && s2==LOW) //Eğer s1 ve s2 değeri 0 ise(beyaz renk)...
{
analogWrite(motor1hiz, 90); //Motor1 hız pini motor1geri 90 olur. 
analogWrite(motor2hiz, 90); //Motor1 hız pini motor1geri 90 olur. 

digitalWrite(motor1ileri,HIGH); //motor1 ve motor2 ileri pinleri HIGH olur. Robot araba ileri gider. 
digitalWrite(motor1geri,LOW);
digitalWrite(motor2ileri,HIGH);
digitalWrite(motor2geri,LOW);
delay(10);
}
else if(s1==LOW&&s2==HIGH) //Eğer s1 değeri 0(beyaz), s2 değeri 1(siyah) ise...
{
analogWrite(motor1hiz, 90); //Motor1 hız pini motor1geri 90 olur. 
analogWrite(motor2hiz, 90); //Motor1 hız pini motor1geri 90 olur. 

digitalWrite(motor1ileri,LOW);
digitalWrite(motor1geri,LOW);
digitalWrite(motor2ileri,HIGH); //motor2 ileri pin HIGH olur. Robot araba sağa döner. 
digitalWrite(motor2geri,LOW);
delay(10);
}
else if(s1==HIGH&&s2==LOW) //Eğer s1 değeri 1(siyah), s2 değeri 0(beyaz) ise...
{
analogWrite(motor1hiz, 90); //Motor1 hız pini motor1geri 90 olur. 
analogWrite(motor2hiz, 90); //Motor1 hız pini motor1geri 90 olur. 

digitalWrite(motor1ileri,HIGH); //motor1 ileri pin HIGH olur. Robot araba sola döner. 
digitalWrite(motor1geri,LOW);
digitalWrite(motor2ileri,LOW);
digitalWrite(motor2geri,LOW);
delay(10);
}
else //Eğer s1 ve s2 değerleri 1 olursa(ikisi de siyah) motorlar LOW değeri alır. Robot araba durur. 
{
analogWrite(motor1hiz, 90); //Motor1 hız pini motor1geri 90 olur. 
analogWrite(motor2hiz, 90); //Motor1 hız pini motor1geri 90  olur. 

digitalWrite(motor1ileri,LOW);
digitalWrite(motor1geri,LOW);
digitalWrite(motor2ileri,LOW);
digitalWrite(motor2geri,LOW);
delay(10);
}
}
