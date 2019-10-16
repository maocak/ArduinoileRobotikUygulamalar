#include <Servo.h> //Servomotor kütüphanesi koda eklenir. 

#define START_CMD_CHAR '>' //gelen verinin ayrıştırılması için kullanılan karakter atanır. 
#define DEBUG 1 // Sensör verilerinin seri çıktısı istenmiyorsa 0 ayarlanır. 

// servo motor nesneleri oluşturulur. 
Servo yatayservo;
Servo dikeyservo;

// Servo motorların başlangıç açıları 90 derece olarak belirlenir. 
int dikeydeger = 90; 
int yataydeger =90; 

// yatay ve dikey değerler için kullanılacak değişkenler tanımlanır. 
float xdegeri, ydegeri;

void setup() {
Serial.begin(38400); // HC-05  bluetooth modülünün hızı belirlenir. 
// Servomotorların takılacağı dijital pinler belirlenir. 
dikeyservo.attach(10);
yatayservo.attach(11); 
}

void loop()
{
Serial.flush(); //Giden seri veri iletiminin tamamlanmasını bekler
int sensortur = 0; //sensortur isimli bir değişkene ilk değer 0 atanır. 
unsigned long logsayim = 0; //logsayim isimli bir değişkene ilk değer 0 atanır. 

char gelenveri = ' ';  //gelenveri değişkenine ilk değer boş karakter atanır. 

// Mobil programdan veri girişi beklenir. 
if (Serial.available() < 1) return; // Eğer veri girişi olmazsa program loop fonksiyonuna geri döner. 

gelenveri = Serial.read(); // Okunan veri, gelenveri isminde bir değişkene atanır. 
if (gelenveri != START_CMD_CHAR) return; // Eğer gelen veri ayrıştırılmazsa, program loop fonksiyonuna geri döner. 

// Mobil uygulamadan yollanan sensör türü numarası ve sensör değerleri ayrıştırılır.  
sensortur = Serial.parseInt(); // Sensör türü okunur. 
logsayim = Serial.parseInt();  // Toplam loglanmış sensör okumaları hesaplanır.  
xdegeri = Serial.parseFloat();  // İvme ölçerden ilk değer okunur. 
ydegeri = Serial.parseFloat();  // İvme ölçerden 2. değer okunur. 

// Mobil program tarafından okunan değerler seri port ekranına yollanır. 
if (DEBUG) {
Serial.print("X değeri: ");
Serial.println(xdegeri);
Serial.print("Y değeri: ");
Serial.println(ydegeri);
Serial.println("------");
delay(10);
}
// Sensör türü kontrol edilir. Eğer, ivme ölçer yoksa, okunan değerler göz ardı edilir. 
// Mobil programda sensor türü 1= ivme ölçer sensör 
if (sensortur !=1) return;  //Mobil programda, eğer ivme ölçer sensörü(1) dışında başka bir sensör kullanılırsa program devam etmez, döner.  

yataydeger = xdegeri; // Sensörden okunan xdegeri, yataydeger isimli değişkene atanır. 
dikeydeger = ydegeri;  // Sensörden okunan ydegeri, dikeydeger isimli değişkene atanır.  

dikeydeger = map(dikeydeger, 10, -10, 0, 179);   // Map komutu yardımıyla -10 ile 10 arası okunan dikey değerler, 0-180 arası açısal değere dönüştürülür.
dikeyservo.write(dikeydeger); //Servo motorun, dönüştürülen açısal değere gitmesi sağlanır. 
delay(10); //10msn beklenir. 

yataydeger = map(yataydeger, -10, 10, 0, 179);  // Map komutu yardımıyla -10 ile 10 arası okunan dikey değerler, 0-180 arası açısal değere dönüştürülür.
yatayservo.write(yataydeger); //Servo motorun, dönüştürülen açısal değere gitmesi sağlanır.    
delay(10); //10msn beklenir.
}
