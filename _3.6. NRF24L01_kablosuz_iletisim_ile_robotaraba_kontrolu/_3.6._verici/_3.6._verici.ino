#include <SPI.h> //kütüphaneler koda eklenir. 
#include <nRF24L01.h>
#include <RF24.h>

RF24 verici(9, 10); // CE, CSN pinleri atanır. 
const uint64_t veriadresi = 0xE8E8F0F0E1LL; //veri alışverişi yapılacak adres yolu atanır. verici ve alıcı kodda bu aynı olmalıdır. 
float  deger[2]; //2 elemanlı deger isminde bir dizi tanımlanır. 
float xekseni, yekseni;
    
void setup() {
Serial.begin(9600); //seri veri iletişimi başlatılır. 
verici.begin(); //NRF24L01 başlatılır. 
verici.openWritingPipe(veriadresi); //verileri yazmak için veriadresi yolu açılır. 
verici.startListening(); //veri okuma için veriadresi yolu dinlenir. 
}
    
void loop() {
      
xekseni = analogRead(A4); // A4'den analog değer okunur ve xekseni'ne atanır. 
yekseni = analogRead(A5); // A5'den analog değer okunur ve yekseni'ne atanır. 
     
deger[0] = xekseni; //dizinin 1.elemanına x ekseni değeri atanır. 
deger[1] = yekseni;  //dizinin 2.elemanına y ekseni değeri atanır. 
     
Serial.print(deger[0]); //okunan x ekseni değeri seriport ekrana yazdırılır. 
Serial.print(" ");    
Serial.println(deger[1]); //okunan y ekseni değeri seriport ekrana yazdırılır. 
verici.write(deger, sizeof(deger)); //okunan değerler deger dizisinin elemanları olarak alıcıya yollanır. 
}
