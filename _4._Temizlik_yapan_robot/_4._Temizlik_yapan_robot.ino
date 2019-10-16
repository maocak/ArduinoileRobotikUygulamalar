int sagmotorileri = 6; //sağ motor ileri
int sagmotorgeri = 9; //sağ motor geri
int solmotorileri = 10; //sol motor ileri
int solmotorgeri = 11; //sol motor geri
int supompa = 4;
int mop_pin = 5;
int hiz = 255; //hız ilk değer 255 PWM atanır. 
int gelenveri = 0; // gelen veri ilk değer 0 atanır. 

void setup()
{ 
Serial.begin(38400);  //HC-05 modülü kullanıldığından iletişim hızı 38400 olmalıdır.
pinMode(sagmotorgeri, OUTPUT); //Sağ ve sol motor ileri ve geri pinleri çıkış olarak atanır. 
pinMode(sagmotorileri, OUTPUT);
pinMode(solmotorileri, OUTPUT); 
pinMode(solmotorgeri, OUTPUT);
pinMode(supompa, OUTPUT);
pinMode(mop_pin, OUTPUT);
digitalWrite(sagmotorileri, LOW); //Motor pinleri ilk değer LOW atanır ve program çalıştırıldığında çalışması önlenir. 
digitalWrite(sagmotorgeri, LOW);
digitalWrite(solmotorileri, LOW); 
digitalWrite(solmotorgeri, LOW);
digitalWrite(supompa, LOW);
digitalWrite(mop_pin, LOW);
}

void loop()
{
if (Serial.available() > 0) //Android programdan veri girişi yapılırsa....
{
gelenveri = Serial.read(); //Gelen veri gelenveri değişkenine atanır. 
}
switch(gelenveri)
{
case 'S': // Gelen veri S karakteri ise motorlar durur. 
digitalWrite(sagmotorileri, LOW);
digitalWrite(sagmotorgeri, LOW);
digitalWrite(solmotorileri, LOW); 
digitalWrite(solmotorgeri, LOW);
gelenveri='*'; //Gelen veri * değiştirilerek case yapısının tekrar çalışması önlenir. Bu şekilde butona her basışta robot hareket eder.
break;

case 'R': //Gelen veri R karakteri ise robot araba sağa hareket eder. 
analogWrite(solmotorileri, hiz); 
digitalWrite(solmotorgeri, LOW);
analogWrite(sagmotorileri, LOW);
digitalWrite(sagmotorgeri, LOW);
gelenveri='*';
break;

case 'L': //Gelen veri L karakteri ise robot araba sola hareket eder. 
analogWrite(solmotorileri, LOW); 
digitalWrite(solmotorgeri, LOW);
analogWrite(sagmotorileri, hiz);
digitalWrite(sagmotorgeri, LOW);
gelenveri='*';
break;

case 'F': //Gelen veri F ise robot araba ileri hareket eder. 
analogWrite(solmotorileri, hiz); 
digitalWrite(solmotorgeri, LOW);
analogWrite(sagmotorileri, hiz);
digitalWrite(sagmotorgeri, LOW);
gelenveri='*';
break;


case 'B': //Gelen veri B ise robot araba geri hareket eder. 
digitalWrite(solmotorileri, LOW); 
analogWrite(solmotorgeri, hiz);
digitalWrite(sagmotorileri, LOW);
analogWrite(sagmotorgeri, hiz);
gelenveri='*';
break;


case 'P': // Gelen veri P karakteri ise su dalgıç pompası çalışır. 
digitalWrite(supompa, HIGH);
gelenveri='*';
break;  

case 'p': // Gelen veri p karakteri ise su pompası durur. 
digitalWrite(supompa, LOW); 
gelenveri='*';
break;

case 'M':
digitalWrite(mop_pin, HIGH); // Gelen veri M karakteri ise temizlik yapan öndeki motorlar çalışır. 
gelenveri='*';
break;

case 'm':
digitalWrite(mop_pin, LOW); // Gelen veri m karakteri ise temizlik yapan öndeki motorlar durur. 
gelenveri='*';
break;

case '1': //Gelen veri ise 1 ise motor hızları 100 ayarlanır. 
hiz = 100;
gelenveri='*';
break;

case '2': //Gelen veri  2 ise motor hızları 150 ayarlanır. 
hiz = 150;
gelenveri='*';
break;

case '3':  //Gelen veri 3 ise motor hızları 200 ayarlanır. 
hiz = 200;
gelenveri='*';
break;

case '4':  //Gelen veri 4 ise motor hızları 255 ayarlanır. 
hiz = 255;
gelenveri='*';
break;

delay(500);
}
}
