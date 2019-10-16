#include <Servo.h>
int servo_pin = 2; // Servo motor pin numarası atanır. 
int kalem_asagi = 90; // kalem aşağıya indiğinde servo açısı
int kalem_yukari = 175;   // kalem yükseldiğinde servo açısı
Servo servomotor; //Servo motor nesnesi oluşturulur. 

float tekerlik_capi=65; //    Kullanılan tekerlek çapı
float tekerlik_tabani=95; //    İki tekerlek arası uzaklık 
int donme_adimi=512; //        Dişli kutusu 64x olan motorlar için 512, 16x olan motorlar için 128 girilmelidir. 
int bekleme_zamani=6; //    Motor adımları arasında geçen süre(ms)

// Adım motoru kablo sırası: turuncu, pembe, mavi, yeşil. 
int solmotorpinleri[] = {12, 10, 9, 11}; //Sol adım motor pin atamaları. 
int sagmotorpinleri[] = {4, 6, 7, 5}; //Sağ adım motor pin atamaları. 

int ilerimotorsurme[][4] =  {{1, 0, 1, 0},//2 fazlı motor sürme
                      {0, 1, 1, 0},
                      {0, 1, 0, 1},
                      {1, 0, 0, 1}};

int gerimotorsurme[][4] =  {{1, 0, 0, 1}, //2 fazlı motor sürme
                      {0, 1, 0, 1},
                      {0, 1, 1, 0},
                      {1, 0, 1, 0}};
void setup() {
Serial.begin(9600); //seri veri iletişimi başlatılır. 
for(int pin=0; pin<4; pin++){
pinMode(solmotorpinleri[pin], OUTPUT); //sol adım motor pinleri çıkış olarak atanır. 
digitalWrite(solmotorpinleri[pin], LOW); //sol adım motor pinleri ilk durum LOW atanır. 
pinMode(sagmotorpinleri[pin], OUTPUT); //sağ adım motor pinleri çıkış olarak atanır. 
digitalWrite(sagmotorpinleri[pin], LOW); //sağ adım motor pinleri ilk durum LOW atanır.
}
servomotor.attach(servo_pin); //Servo motor 2 nolu dijital pinde başlatılır. 
Serial.println("Çizgi çizen robot"); //Ekrana "Çizgi çizen robot" yazar. 
kalemyukari(); //program ilk çalıştırıldığına kalem yukarı çekilir. 
delay(1000); //1sn beklenir. 
}

void loop(){ // 4 defa kutu çizimi yapılır. 
kalemasagi(); //Kalem aşağıya indirilerek çizime hazır hale getirilir. 
for(int x=0; x<12; x++){ //döngü yardımıyla ilerigit ve soladön fonksiyonları çağrılır. 
ilerigit(100); //ilerigit fonksiyonuna 100 değeri yollanır. 
soladon(90);   //soladon fonksiyonuna 90 değeri yollanır.
}
kalemyukari(); //Çizme işlemi bittikten sonra kalemyukarı fonksiyonu çağrılır. 
bitti();      // bitti fonksiyonuna gider. Adım motoru durur. 
while(1);    // Program resetlenene kadar durur. 
}
// Kullanılan parametre değerleri buradan takip edilebilir. 
int step(float uzaklik){
int adim_sayisi = uzaklik * donme_adimi / (tekerlik_capi * 3.1412); //24.61
 
Serial.print("Uzaklık:");
Serial.print(uzaklik);
Serial.print(" ");
Serial.print("Dönme adımı:");
Serial.print(donme_adimi);
Serial.print(" ");  
Serial.print("Tekerlik çapı:");
Serial.print(tekerlik_capi);
Serial.print(" ");  
Serial.print("Alınan adım:");
Serial.println(adim_sayisi);
delay(1000);
return adim_sayisi;  
}

void ilerigit(float uzaklik){ //Robot araba ileri hareket eder. 
int adim_sayisi = step(uzaklik);
Serial.println(adim_sayisi);
for(int step=0; step<adim_sayisi; step++){
for(int mask=0; mask<4; mask++){
for(int pin=0; pin<4; pin++){
digitalWrite(solmotorpinleri[pin], gerimotorsurme[mask][pin]);
digitalWrite(sagmotorpinleri[pin], ilerimotorsurme[mask][pin]);
}
delay(bekleme_zamani);
} 
}
}

void soladon(float degrees){ //Robot araba sola döner. 
float rotasyon = degrees / 360.0;
float uzaklik = tekerlik_tabani * 3.1412 * rotasyon;
int adim_sayisi = step(uzaklik);
for(int step=0; step<adim_sayisi; step++){
for(int mask=0; mask<4; mask++){
for(int pin=0; pin<4; pin++){
digitalWrite(sagmotorpinleri[pin], ilerimotorsurme[mask][pin]);
digitalWrite(solmotorpinleri[pin], ilerimotorsurme[mask][pin]);
}
delay(bekleme_zamani);
} 
}   
}
void bitti(){ //Motorlar durur.  
for(int mask=0; mask<4; mask++){
for(int pin=0; pin<4; pin++){
digitalWrite(sagmotorpinleri[pin], LOW);
digitalWrite(solmotorpinleri[pin], LOW);
}
delay(bekleme_zamani);
}
}
void kalemyukari(){
delay(250);
Serial.println("Kalem yukari gider ve çizim biter.");
servomotor.write(kalem_yukari);
delay(250);
}
void kalemasagi(){
delay(250);  
Serial.println("Kalem asagi gider ve çizim başlar.");
servomotor.write(kalem_asagi);
delay(250);
}
/*
void gerigit(float uzaklik){
  int adim_sayisi = step(uzaklik);
  for(int step=0; step<adim_sayisi; step++){
    for(int mask=0; mask<4; mask++){
      for(int pin=0; pin<4; pin++){
        digitalWrite(solmotorpinleri[pin], ilerimotorsurme[mask][pin]);
        digitalWrite(sagmotorpinleri[pin], gerimotorsurme[mask][pin]);
      }
      delay(bekleme_zamani);
    } 
  }
}
void sagadon(float degrees){
  float rotasyon = degrees / 360.0;
  float uzaklik = tekerlik_tabani * 3.1412 * rotasyon;
  int adim_sayisi = step(uzaklik);
  for(int step=0; step<adim_sayisi; step++){
    for(int mask=0; mask<4; mask++){
      for(int pin=0; pin<4; pin++){
        digitalWrite(sagmotorpinleri[pin], gerimotorsurme[mask][pin]);
        digitalWrite(solmotorpinleri[pin], gerimotorsurme[mask][pin]);
      }
      delay(bekleme_zamani);
    } 
  }   
}
*/
