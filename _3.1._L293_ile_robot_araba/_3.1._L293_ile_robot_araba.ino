// L293D Entegresi ile Robot araba ileri saga sola geri hareketi ve durma uygulaması

int solileri = 2; // Arduino kartın 2 nolu pini sol motor ileri hareketi için atanır 
int solgeri = 3; // Arduino kartın 3 nolu pini sol motor geri hareketi için atanır 

int sagileri = 6; // Arduino kartın 6 nolu pini sağ motor ileri hareketi için atanır 
int saggeri = 7; // Arduino kartın 7 nolu pini sağ motor geri hareketi için atanır 

void setup()
{
pinMode(solileri, OUTPUT);  // pin çıkış olarak tanımlanır
pinMode(sagileri, OUTPUT);  // pin çıkış olarak tanımlanır
pinMode(solgeri, OUTPUT);  // pin çıkış olarak tanımlanır
pinMode(saggeri, OUTPUT);  // pin çıkış olarak tanımlanır
}

void loop()
{
// Üç saniye boyunca robot araba ileri gider
void ilerigit();
  
digitalWrite(sagileri, HIGH);   // Sağ motor döner
digitalWrite(solileri, HIGH);   // sol motor döner
delay(3000);               // her iki motor ileri yönde 3 saniye döner
 
digitalWrite(sagileri,LOW);   // Sağ motor durur
digitalWrite(solileri, LOW);   // Sol motor durur
delay(1000);               // her iki motor da 1 saniye durur

// Üç saniye boyunca robot bulunduğu yerde sağa döner
void sagadon();
  
digitalWrite(sagileri, LOW);   // Sağ motor durur
digitalWrite(solileri, HIGH);   //Sol motor döner
delay(3000);               // 3 saniye boyunca hareket eder
 
digitalWrite(sagileri,LOW);   // Sağ motor durur
digitalWrite(solileri, LOW);   // Sol motor döner
delay(1000);               // her iki motor da 1 saniye durur

// Üç saniye boyunca robot bulunduğu yerde sola döner
void soladon();
  
digitalWrite(sagileri, HIGH);   // Sağ motor döner
digitalWrite(solileri, LOW);   // sol motor durur
delay(3000);               // 3 saniye boyunca hareket eder
 
digitalWrite(sagileri,LOW);   // Sağ motor durur
digitalWrite(solileri, LOW);   // sol motor durur
delay(1000);   // her iki motor da 1 saniye durur

// Üç saniye boyunca robot bulunduğu yerden geriye hareket eder
void gerigit();
  
digitalWrite(saggeri, HIGH);   // Sağ motor döner
digitalWrite(solgeri, HIGH);   //sol motor döner
delay(3000);               // 3 saniye boyunca hareket eder
    
digitalWrite(saggeri, LOW);   // Sağ motor durur
digitalWrite(solgeri, LOW);   // sol motor durur
delay(1000);               // her iki motor da 1 saniye durur

void dur();
  
digitalWrite(saggeri, LOW);   // Sağ motor durur
digitalWrite(solgeri, LOW);   // sol motor durur
delay(2000);               // her iki motor da 1 saniye durur

}

