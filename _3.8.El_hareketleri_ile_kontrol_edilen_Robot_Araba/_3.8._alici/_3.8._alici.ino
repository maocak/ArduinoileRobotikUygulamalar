#include <VirtualWire.h>

#define motor1ileri 3 //motor1 ileri hareket pini atanır. 
#define motor1geri 4 //motor1 geri hareket pini atanır.  

#define motor2ileri 5 //motor2 ileri hareket pini atanır. 
#define motor2geri 6 //motor2 geri hareket pini atanır.  

void setup (void) {
Serial.begin (9600);     // Seri veri iletişimi başlatılır. 
vw_setup (2000);      // Kütüphane iletişim hızı belirlenir.  
vw_set_rx_pin (2);    // Veri alma işlemi için kullanılacak pin atanır. 
vw_rx_start ();       // Veri alma işlemi başlatılır. 
 
// Motor1 ve Motor2 yön kontrol pinleri çıkış olarak tanımlanır. 
pinMode(motor1ileri, OUTPUT); //Birinci motor ileri pin.
pinMode(motor1geri, OUTPUT); //Birinci motor geri pin.
pinMode(motor2ileri, OUTPUT); // İkinci motor ileri pin.
pinMode(motor2geri, OUTPUT); // İkinci motor geri pin.

}

void loop (void) {
uint8_t veri [VW_MAX_MESSAGE_LEN]; // Gelen veriyi arabellekte tutacak veri isimli //değişken tanımlanır.
uint8_t veriuzunluk = VW_MAX_MESSAGE_LEN; // Gelen verinin uzunluğunu tutan //değişken tanımlanır.

if (vw_get_message (veri, &veriuzunluk)) { // Eğer veri alımı gerçekleşirse...
int i;
for (i = 0; i < veriuzunluk; i ++) { // Verinin uzunluk karakteri kadar gelen veri okunur.
Serial.print("Gelen değer= "); Serial.println (char(veri[i])); //Okunan karakter sei port ekranına yazdırılır. 
 
if ((veri[i]=='8'))   { //Gelen karakter 8 ise motor1 ve motor2 ileri pinleri HIGH olur. Araba ileri hareket eder. 
digitalWrite(motor1ileri, HIGH);
digitalWrite(motor1geri, LOW);
digitalWrite(motor2ileri, HIGH);
digitalWrite(motor2geri, LOW);
}
      
if ((veri[i]=='2')) { //Gelen karakter 2 ise motor1 ve motor2 geri pinleri HIGH olur. Araba geri hareket eder. 
 
digitalWrite(motor1ileri, LOW);
digitalWrite(motor1geri, HIGH);
digitalWrite(motor2ileri, LOW);
digitalWrite(motor2geri, HIGH);
}

if ((veri[i]=='4'))  { // Gelen karakter 4 ise motor1 ileri pin HIGH olur. Araba sola döner. 

digitalWrite(motor1ileri, HIGH); 
digitalWrite(motor1geri, LOW);
digitalWrite(motor2ileri, LOW);
digitalWrite(motor2geri, LOW);
}
      
if ((veri[i]=='6'))  { //Gelen karakter 6 ise motor2 ileri pin HIGH olur. Araba sağa döner. 

digitalWrite(motor1ileri, LOW);
digitalWrite(motor1geri, LOW);
digitalWrite(motor2ileri, HIGH);
digitalWrite(motor2geri, LOW);
}
      
if ((veri[i]=='5'))  { //Gelen karakter 5 ise tüm pinler LOW olur. Araba hareket etmez. 
  
digitalWrite(motor1ileri, LOW);
digitalWrite(motor1geri, LOW);
digitalWrite(motor2ileri, LOW);
digitalWrite(motor2geri, LOW); 
}
}
}
}






