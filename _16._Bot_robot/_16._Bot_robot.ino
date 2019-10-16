char veri = 0; //veri isminde bir değişkene ilk değer 0 atanır. 
int solmotorhiz = 9; // sol motor in hızını kontrol eden pin(PWM özelliği olan pin olmalıdır)
int sagmotorhiz = 10; // sag motor in hızını kontrol eden pin(PWM özelliği olan pin olmalıdır)
const int sagmotorileri=7; //Sağ motor ileri kontrol eden pin
const int sagmotorgeri=6; //Sağ motor geri kontrol eden pin
const int solmotorileri=5; //Sol motor ileri kontrol eden pin
const int solmotorgeri=4; //Sol motor geri kontrol eden pin
void setup()
{
Serial.begin(38400);   //HC-05  modülü kullanıldığı için bu bant genişliği seçilmelidir.                               
pinMode(solmotorhiz,OUTPUT); //Motor pinlerin tümü çıkış olarak atanır. 
pinMode(sagmotorhiz,OUTPUT);
pinMode(solmotorileri,OUTPUT);
pinMode(solmotorgeri,OUTPUT);
pinMode(sagmotorileri,OUTPUT);
pinMode(sagmotorgeri,OUTPUT);
}
void loop()
{
if(Serial.available() > 0)  // Veri girişi yapıldığında...
{
veri = Serial.read();  //Okunan veri, veri isimli değişkene atanır. 
Serial.print(veri);   //Okunan veri, seri port ekranına yazdırılır. 
Serial.print("\n");  
if(veri=='F'){  //Eğer gelen veri F ise, ileri() fonksiyonu çağrılır. 
ileri();   
}else if(veri=='B'){ //Eğer gelen veri B ise, geri() fonksiyonu çağrılır.
geri();
}else if(veri=='L'){ //Eğer gelen veri L ise, sola() fonksiyonu çağrılır.
sola();
}else if(veri=='R'){ //Eğer gelen veri R ise, saga() fonksiyonu çağrılır.
saga();
}else if(veri=='S'){ //Eğer gelen veri S ise, dur() fonksiyonu çağrılır.
dur();
}
}
}
void ileri(){ //Deniz botu ileri doğru hareket eder. 
Serial.println("İleri hareket");
analogWrite(solmotorhiz, 150);
analogWrite(sagmotorhiz, 150);
digitalWrite(sagmotorileri,HIGH);
digitalWrite(solmotorileri,HIGH);
digitalWrite(solmotorgeri,LOW);
digitalWrite(sagmotorgeri,LOW);
}
void geri(){ //Deniz botu geriye doğru hareket eder.
Serial.println("Geri hareket");
analogWrite(solmotorhiz, 150);
analogWrite(sagmotorhiz, 150);
digitalWrite(sagmotorgeri,HIGH);
digitalWrite(solmotorgeri,HIGH);
digitalWrite(solmotorileri,LOW);
digitalWrite(sagmotorileri,LOW);
}
void sola(){ //Deniz botu sola doğru hareket eder.
Serial.println("Sola hareket");
analogWrite(solmotorhiz, 150);
analogWrite(sagmotorhiz, 150);
digitalWrite(sagmotorileri,LOW);
digitalWrite(sagmotorgeri,HIGH);
digitalWrite(solmotorileri,HIGH);
digitalWrite(solmotorgeri,LOW);
}
void saga(){ //Deniz botu sağa doğru hareket eder.
Serial.println("Sağa hareket");
analogWrite(solmotorhiz, 150);
analogWrite(sagmotorhiz, 150);
digitalWrite(sagmotorileri,HIGH);
digitalWrite(sagmotorgeri,LOW);
digitalWrite(solmotorileri,LOW);
digitalWrite(solmotorgeri,HIGH);
}
void dur(){ //Deniz botu durur.
Serial.println("Dur");
analogWrite(solmotorhiz, 0);
analogWrite(sagmotorhiz, 0);
digitalWrite(solmotorileri,LOW);
digitalWrite(solmotorgeri,LOW);
digitalWrite(sagmotorileri,LOW);
digitalWrite(sagmotorgeri,LOW);
}

