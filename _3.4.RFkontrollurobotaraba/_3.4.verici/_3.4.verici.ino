#include <VirtualWire.h>

// Butonları kontrol edecek dijital pinlerin atamaları yapılır. 
int ileri = 8;
int geri = 9;
int soladon = 10;
int sagadon = 11;
int dur = 12;

int ledpin=7; //LED pini atanır. 

// buton pinleri dizi olarak tanımlanır. 
int butonpin [] = {8, 9, 10, 11, 12};

void setup () {
Serial.begin (9600);         // Seri veri iletişimi başlatılır. 
Serial.println ("YÖNLER");  //Ekrana "YÖNLER" yazısı yazar. 

vw_setup (2000);        // Virtual wire kütüphane iletişim hızı belirlenir. 
vw_set_tx_pin (3);          // veri yollamak için kullanılacak pin tanımlanır (3 nolu dijital pin).
digitalWrite(ledpin, OUTPUT);  //LED pini çıkış olarak tanımlanır. 
for (int i = 0; i < 6; i ++) {// Döngü yardımıyla 5 adet buton pini giriş(INPUT) olarak atanır ve butonların ilk durumları HIGH(sönük) belirlenir. 
pinMode (butonpin [i], INPUT);
digitalWrite(butonpin [i], HIGH);
}
}

void loop () {
char *veri; //veri isminde bir değişken tanımlanır. 
  
if (digitalRead (ileri) == LOW) { //ileri butonuna basılırsa...
char *veri = "1"; //veri değişkenine 1 atanır.
digitalWrite(ledpin, HIGH); //LED yanar. 
    
vw_send ((uint8_t *) veri, strlen (veri)); //1 değişkeni alıcıya yollanır. 
vw_wait_tx (); //yollama işleminin tamamlanması beklenir. 
digitalWrite (ledpin, LOW); //LED söner. 
Serial.println (*veri); //Yollanan veri seri port ekranına yazdırılır. 
}
  
if (digitalRead (geri) == LOW) { //geri butonuna basılıra...
char *veri = "2"; //veri değişkenine 2 atanır. 
digitalWrite (ledpin, HIGH);  //LED yanar. 
    
vw_send ((uint8_t *) veri, strlen (veri)); //2 değişkeni alıcıya yollanır. 
vw_wait_tx (); //yollama işleminin tamamlanması beklenir. 
digitalWrite (ledpin, LOW);  //LED söner. 
Serial.println (*veri);  //Yollanan veri seri port ekranına yazdırılır.
}
  
if (digitalRead (soladon) == LOW) { //soladon butonuna basılırsa...
char *veri = "3";  //veri değişkenine 3 atanır. 
digitalWrite (ledpin, HIGH); //LED yanar. 
    
vw_send ((uint8_t *) veri, strlen (veri)); //3 değişkeni alıcıya yollanır. 
vw_wait_tx (); //yollama işleminin tamamlanması beklenir. 
digitalWrite (ledpin, LOW); //LED söner.
Serial.println (*veri); //Yollanan veri seri port ekranına yazdırılır.
}
  
if (digitalRead (sagadon) == LOW) { //sagadon butonuna basılırsa...
char *veri = "4"; //veri değişkenine 4 atanır. 
digitalWrite (ledpin, HIGH); //LED yanar. 
    
vw_send ((uint8_t *) veri, strlen (veri)); //4 değişkeni alıcıya yollanır.
vw_wait_tx (); //Yollama işleminin tamamlanması beklenir.
digitalWrite (ledpin, LOW); //LED söner.
Serial.println (*veri); //Yollanan veri seri port ekranına yazdırılır.
}
  
if (digitalRead(dur)==LOW) { //dur butonuna basılırsa...
char *veri = "5";  //veri değişkenine 5 atanır.
digitalWrite (ledpin, HIGH);  //LED yanar.
    
vw_send ((uint8_t *) veri, strlen (veri)); //5 değişkeni alıcıya yollanır.
vw_wait_tx (); //Yollama işleminin tamamlanması beklenir.
digitalWrite (ledpin, LOW); //LED söner.
Serial.println (*veri); //Yollanan veri seri port ekranına yazdırılır.
} 
}
