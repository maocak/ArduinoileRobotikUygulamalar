#include <VirtualWire.h>
int ledpin=12;

#define motor1ileri 3 //motor1 ileri hareket pini atanır. 
#define motor1geri 4 //motor1 geri hareket pini atanır.  

#define motor2ileri 6 //motor2 ileri hareket pini atanır. 
#define motor2geri 7 //motor2 geri hareket pini atanır.  

void setup () {
Serial.begin (9600);            // Seri veri iletişimi başlatılır. 
Serial.println ("YÖNLER"); //Seri port ekrana "YÖNLER" yazar. 

// Initialise the IO and ISR
vw_setup (2000);      // Kütüphane iletişim hızı belirlenir.  
vw_set_rx_pin (2);    // Veri alma işlemi için kullanılacak pin atanır. 
vw_rx_start ();       // Veri alma işlemi başlatılır. 
  
pinMode(motor1ileri, OUTPUT); //2 tane motor ileri-geri pinleri çıkış olarak tanımlanır. 
pinMode(motor1geri, OUTPUT);
pinMode(motor2ileri, OUTPUT);
pinMode(motor2geri, OUTPUT);

pinMode(ledpin, OUTPUT); //LED pini çıkış olarak tanımlanır. 
}

void loop () {
uint8_t veri [VW_MAX_MESSAGE_LEN]; // Gelen veriyi arabellekte tutacak veri isimli değişken tanımlanır.
uint8_t veriuzunluk = VW_MAX_MESSAGE_LEN; // Gelen verinin uzunluğunu tutan değişken tanımlanır.

if (vw_get_message (veri, &veriuzunluk)) { // Eğer veri alımı gerçekleşirse...
int i;
    
digitalWrite(ledpin, HIGH); //LED yanar. 
    
// Verinin uzunluk karakteri kadar gelen veri okunur...
for (i = 0; i < veriuzunluk; i ++) {
Serial.print (char(veri [i])); //seri port ekrana yazdırılır. Burada, char kullanılmasının nedeni, gelen sayının ASCII kodunun gözükmemesi içindir. 
      
if((veri [i]) == '1') { //Eğer gelen veri 1 ise...
ileri (); //tanımlanan ileri fonksiyonuna gidilir ve  motor ileri pinleri HIGH yapılır. 
Serial.println (" = ileri"); //ekranda ileri yazar. 
}
      
if(veri [i] == '2') { //Eğer gelen veri 2 ise...
geri (); //tanımlanan geri fonksiyonuna gidilir ve motor geri pinleri HIGH yapılır.
Serial.println (" = geri"); //ekranda geri yazar.
}

if(veri [i] == '3') { //Eğer gelen veri 3 ise...
sol (); //tanımlanan sol fonksiyonuna gidilir ve  motor1 ileri pini HIGH yapılır.
Serial.println (" = sol"); //ekranda sol yazar.
}
      
if(veri [i] == '4') { //Eğer gelen veri 4 ise...
sag (); //tanımlanan sag fonksiyonuna gidilir ve  motor2 ileri pini HIGH yapılır.
Serial.println (" = sağ"); //ekranda sol yazar.
}
      
if (veri [i] == '5') { //Eğer gelen veri 5 ise...
dur (); //tanımlanan dur fonksiyonuna gidilir ve  motor1 ve motor2 pinleri LOW yapılır.
Serial.println (" = dur");
}
Serial.print(" ");
}
digitalWrite(ledpin, LOW); //LED söner. 
}
}

void ileri () { //motor1ileri ve motor2ileri pinleri HIGH yapılarak robotun ileri hareketi sağlanır. 
digitalWrite(motor1ileri, HIGH);
digitalWrite(motor1geri, LOW);
digitalWrite(motor2ileri, HIGH);
digitalWrite(motor2geri, LOW);
}

void geri () { //motor1geri ve motor2geri pinleri HIGH yapılarak robotun geri hareketi sağlanır. 
digitalWrite(motor1ileri, LOW);
digitalWrite(motor1geri, HIGH);
digitalWrite(motor2ileri, LOW);
digitalWrite(motor2geri, HIGH);
} 
void sol () { //motor1ileri pini HIGH yapılarak robotun sola dönüş hareketi sağlanır. 
digitalWrite(motor1ileri, HIGH); 
digitalWrite(motor1geri, LOW);
digitalWrite(motor2ileri, LOW);
digitalWrite(motor2geri, LOW);
}
void sag () { //motor2ileri pini HIGH yapılarak robotun sağa dönüş hareketi sağlanır. 
digitalWrite(motor1ileri, LOW);
digitalWrite(motor1geri, LOW);
digitalWrite(motor2ileri, HIGH);
digitalWrite(motor2geri, LOW);
}
void dur () { //Tüm pinler LOW yapılarak robotun durması sağlanır. 
digitalWrite(motor1ileri, LOW);
digitalWrite(motor1geri, LOW);
digitalWrite(motor2ileri, LOW);
digitalWrite(motor2geri, LOW);
}

