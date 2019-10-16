#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <VirtualWire.h>

float x = 0; //değişkenlere ilk değerleri atanır. 
float y = 0;

// ADXL345 sensörüne bir kimlik numarası atanır(12345) 
Adafruit_ADXL345_Unified ivmeolcer = Adafruit_ADXL345_Unified(12345);

void sensorbilgileri(void) //sensörle ilgili teknik bilgiler ekrana yazdırılır.
{
sensor_t sensorbilgi; //sensör hakkında bilgileri vermek için kullanılan ve Adafruit_Sensor //kütüphanesinde yer alan bir komuttur. 

ivmeolcer.getSensor(&sensorbilgi);  //sensorle ilgili bilgiler okunur. 

Serial.println("------------------------------------");
Serial.print  ("Sensor:       "); Serial.println(sensorbilgi.name);
Serial.print  ("Surucu versiyonu:   "); Serial.println(sensorbilgi.version);
Serial.print  ("Kimlik numarasi:    "); Serial.println(sensorbilgi.sensor_id);
Serial.print  ("En buyuk deger:    "); Serial.print(sensorbilgi.max_value); Serial.println(" m/s^2");
Serial.print  ("En kucuk deger:    "); Serial.print(sensorbilgi.min_value); Serial.println(" m/s^2");
Serial.print  ("Hassasiyet   "); Serial.print(sensorbilgi.resolution); Serial.println(" m/s^2");  
Serial.println("------------------------------------");
Serial.println("");
delay(500);
}

void veriokumaaraligi(void)
{
Serial.print  ("Veri okuma araligi:    ");  //Hangi Hz'de veri okunduğu ekrana yazdırılır
  
switch(ivmeolcer.getDataRate())
{
case ADXL345_DATARATE_3200_HZ:
Serial.print  ("3200 "); 
break;
case ADXL345_DATARATE_1600_HZ:
Serial.print  ("1600 "); 
break;
case ADXL345_DATARATE_800_HZ:
Serial.print  ("800 "); 
break;
case ADXL345_DATARATE_400_HZ:
Serial.print  ("400 "); 
break;
case ADXL345_DATARATE_200_HZ:
Serial.print  ("200 "); 
break;
case ADXL345_DATARATE_100_HZ:
Serial.print  ("100 "); 
break;
case ADXL345_DATARATE_50_HZ:
Serial.print  ("50 "); 
break;
case ADXL345_DATARATE_25_HZ:
Serial.print  ("25 "); 
break;
case ADXL345_DATARATE_12_5_HZ:
Serial.print  ("12.5 "); 
break;
case ADXL345_DATARATE_6_25HZ:
Serial.print  ("6.25 "); 
break;
case ADXL345_DATARATE_3_13_HZ:
Serial.print  ("3.13 "); 
break;
case ADXL345_DATARATE_1_56_HZ:
Serial.print  ("1.56 "); 
break;
case ADXL345_DATARATE_0_78_HZ:
Serial.print  ("0.78 "); 
break;
case ADXL345_DATARATE_0_39_HZ:
Serial.print  ("0.39 "); 
break;
case ADXL345_DATARATE_0_20_HZ:
Serial.print  ("0.20 "); 
break;
case ADXL345_DATARATE_0_10_HZ:
Serial.print  ("0.10 "); 
break;
default:
Serial.print  ("???? "); 
break;
}  
Serial.println(" Hz");  
}

void verihassasiyet(void)
{
Serial.print  ("Aralik:         +/- "); //hangi hassasiyette veri okunduğu ekrana yazdırılır. 
  
switch(ivmeolcer.getRange())
{
case ADXL345_RANGE_16_G:
Serial.print  ("16 "); 
break;
case ADXL345_RANGE_8_G:
Serial.print  ("8 "); 
break;
case ADXL345_RANGE_4_G:
Serial.print  ("4 "); 
break;
case ADXL345_RANGE_2_G:
Serial.print  ("2 "); 
break;
default:
Serial.print  ("?? "); 
break;
}  
Serial.println(" g");  
}

void setup(void) 
{
vw_setup(2000); // Kütüphane iletişim hızı belirlenir.
vw_set_tx_pin(3);  // veri yollama için kullanılacak pin tanımlanır. 
Serial.begin(9600);   //seri veri alışverişi başlatılır. 
Serial.println("Ivme olcer test"); Serial.println("");
  
//sensör başlatılır
if(!ivmeolcer.begin())
{
//eğer sensör bağlantıları yanlışsa bu uyarıyı verir. 
Serial.println("ADXL345 bulunamadi ... luften baglantinizi kontrol ediniz!");
while(1);
}

//uygulama için hangi hassasiyet aralığı seçileceği tanımlanır. Bu uygulamada 16g //kullanılmıştır. İstenirse 2,4,8 g de aktif hale getirilebilir.
ivmeolcer.setRange(ADXL345_RANGE_16_G);
/* ivmeolcer.SetRange(ADXL345_RANGE_8_G);
 ivmeolcer.SetRange(ADXL345_RANGE_4_G);
ivmeolcer.SetRange(ADXL345_RANGE_2_G);  hasasiyet aralığı değiştirilebilir*/
  
//Yukarda tanımlanan sensorbilgileri isimli fonksiyon çağrılarak sensörün teknik özellikleri //ekrana yazdırılır. Bu 1 defaya mahsustur. 
sensorbilgileri();
  
//veriokumaraligi ve verihassasiyet fonksiyonları çağrılarak seri port ekranına bu değerler //yazdırılır. Bu bilgiler 1 defa yazdırılır.
veriokumaaraligi();
verihassasiyet();

Serial.println("");
}

void loop(void) 
{

sensors_event_t olay; //Belirlenen bir anda sensörden veri çekmek için kullanılan ve //Adafruit_Sensor kütüphanesinde yer alan bir komuttur. 
ivmeolcer.getEvent(&olay); //sensörden veri okunur. 
 
x=olay.acceleration.x; //sensörden okunan x koordinat değeri x isimli değişkene atanır. 
y=olay.acceleration.y; //sensörden okunan y koordinat değeri y isimli değişkene atanır. 

Serial.print("x değeri= ");Serial.print(x); Serial.print("  ");//Okunan verilen aynı zamanda yanyana seri port ekranından da takip //edilebilir. 
Serial.print("y değeri=");Serial.println(y); 

if ((y>2 && y<10)) //y değeri eğer 2 ile 10 arasında ise alıcıya gönderilmek üzere send isimli fonksiyona 8 karakteri yollanır. 
{
send("8");
} 
else 
{ 
if ((y>-10 && y<-2)) // y değeri -10 ile -2 arasında ise send isimli fonksiyona 2 karakteri yollanır. 
{
send("2");
}
if ((x>2 && x<10)) //x değeri 2 ile 10 arasında ise send isimli fonksiyona 6 karakteri yollanır. 
{
send("6");
}
if ((x>-10 && x<-2)) //x değeri -10 ile -2 arasında ise send isimli fonksiyona 4 karakteri yollanır. 
{
send("4"); 
}
if ((x>=0 && x<=2) && (y>=0 && y<=2)) //x değeri 0 ile 2 ve y değeri de 0 ile 2 arasında ise 5 karakteri yollanır. 
{
send("5");
}
}
}

void send(char *veri) //ivme sensörüden gelen değere göre 8(ileri),2(geri),4(sola),6(sağa), ve 5(dur) rakamları alıcı devreye yollanır. 
{
vw_send((uint8_t *)veri, strlen(veri)); //veri alıcı devreye yollanır. 
vw_wait_tx(); // Karakter yollanana kadar beklenir. 
Serial.println(veri); //Yollanan karakter seriport ekranına yazdırılır. 
}

