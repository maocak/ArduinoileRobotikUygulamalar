#include <PID_v1.h> //Kütüphaneler koda eklenir. 
#include <LMotorController.h>
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h" //Wire kütüphanesini koda eklenir. 
#endif

#define MIN_ABS_SPEED 20

MPU6050 mpu;

// MPU kontrol değişkenleri
bool dmpReady = false;  // DMP(dijital motion processor/dijital hareket işlemcisi) eğer başarılı olursa deper TRUE olur. 
uint8_t mpuIntStatus;   // MPU'dan gelen gerçek kesme durumu baytını tutar.
uint8_t devStatus;      // Her cihaz işleminden sonra geri dönüş durumu (0 = başarı,! 0 = hata)
uint16_t packetSize;    // Beklenen DMP paket boyutu (varsayılan değer 42 bayttır)
uint16_t fifoCount;     // FIFO(First in First Out)'da şu anda tüm baytların sayısı sayılır.
uint8_t fifoBuffer[64]; // FIFO depolama belleği(buffer) atanır. 

// Yönlendirme / hareket değişkenleri
Quaternion q;           // [w, x, y, z]         kuaternion konteyneri değişkeni tanımlanır. 
VectorFloat gravity;    // [x, y, z]            yerçekimi vektör değişkenleri tanımlanır. 
float ypr[3];           // [yaw, pitch, roll]   yaw / pitch / roll konteyner ve yerçekimi vektör değişkenleri tanımlanır. 

//PID (proportional integral derivative)- oransal integral türev ayarları
double originalSetpoint = 176; 
double setpoint = originalSetpoint;
double movingAngleOffset = 0.1;
double input, output;
int moveState=0; //0 = denge; 1 = geriye; 2 = ileri
//Kp ve Kd ve Ki ayarları robotun dengesini ayarlamak için değiştirilebilir. 
double Kp = 50; 
double Kd = 1.4; 
double Ki = 60;
PID pid(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT); //PID kütüphane ayarları yapılarak PID nesnesi oluşturulur. 

double motorSpeedFactorLeft = 0.6;
double motorSpeedFactorRight = 0.5;
//motor kontrol pinleri
int ENA = 5;
int IN1 = 6;
int IN2 = 7;
int IN3 = 8;
int IN4 = 9;
int ENB = 10;
LMotorController motorController(ENA, IN1, IN2, ENB, IN3, IN4, motorSpeedFactorLeft, motorSpeedFactorRight);//motor kütüphane ayarları.

//zamanlama değişkenlerine ilk değişken 0 atanır. 
long time1Hz = 0;
long time5Hz = 0;

volatile bool mpuInterrupt = false;     // Mikroişlemci kesme pininin yüksek olup olmadığını gösterir. 
void dmpDataReady()
{
mpuInterrupt = true;
}


void setup()
{
// I2C veri yoluna katıl (I2Cdev kitaplığı bunu otomatik olarak yapamaz)
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
Wire.begin(); //Wire kütüphanesi başlatılır. 
TWBR = 24; // 400 kHz I2C saat (CPU 8MHz ise 200kHz)
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
Fastwire::setup(400, true);
#endif
// Seri veri iletişimi 115200 hızda başlatılır. 
// Ancak yapılan projeye bağlı olarak gerçekten size bağlıdır.
Serial.begin(115200);
while (!Serial); // Programın devam etmesi beklenir. 

// initialize device
Serial.println(F("I2C cihazı(MPU6050) başlatılır..."));
mpu.initialize();

// Bağlantı doğrulanır. 
Serial.println(F("Cihaz bağlantısı test edilmektedir."));
Serial.println(mpu.testConnection() ? F("MPU6050 bağlantısı başarılı.") : F("MPU6050 bağlantısı sağlanamadı."));

// DMP(dijital hareket işlemcisi) 
Serial.println(F("DMP(dijital hareket işlemcisi) başlatılıyor..."));
devStatus = mpu.dmpInitialize();

// Küçük hassasiyetler için ölçeklendirilmiş  gyro ofset ayarları burdan değişitirebilir. 
mpu.setXGyroOffset(220);
mpu.setYGyroOffset(76);
mpu.setZGyroOffset(-85);
mpu.setZAccelOffset(1788); // Kullanılan çip için varsayılan değer 1788'dir. 

// Gyro sensör başlatılır. Başlamazsa 0 döndürülür. 
if (devStatus == 0)
{
// DMP hazırdır ve çalışmaya başlar. 
Serial.println(F("DMP(dijital hareket işlemcisi) başlatılıyor..."));
mpu.setDMPEnabled(true);

// Arduino interrupt tespitini etkinleştirir. 
Serial.println(F("Kesme tespiti etkinleştirme (Arduino harici kesme 0'dır...)"));
attachInterrupt(0, dmpDataReady, RISING);
mpuIntStatus = mpu.getIntStatus();

// DMP hazır olduğu TRUE ile belirleni. Böylece ana loop() fonksiyonu kullanıma hazır olduğunu bilir. 
Serial.println(F("DMP hazır! İlk kesme işlemi için bekleniyor..."));
dmpReady = true;

// Daha sonra karşılaştırma için beklenen DMP paket boyutu belirlenir. 
packetSize = mpu.dmpGetFIFOPacketSize();
        
//PID(oransal integral türev ayarları) yapılır. 
pid.SetMode(AUTOMATIC);
pid.SetSampleTime(10);
pid.SetOutputLimits(-255, 255);  
}
else
{
// Eğer PID ayarları yapılamazsa hata verir. Hata kodları şu şekildedir:
// 1 = İlk bellek yükleme başarısız oldu. 
// 2 = DMP konfigürasyon güncelleme başarısız oldu. 
Serial.print(F("DMP başlatılma başarısız oldu (Kod: "));
Serial.print(devStatus);
Serial.println(F(")"));
}
}

void loop()
{
// Program başarısız olursa, başa döner. Bu durumda, yapılacak bir şey yoktur. 
if (!dmpReady) return;

// Mikroişlemci kesme ya da ekstra paket için bekleme yapılır. 
while (!mpuInterrupt && fifoCount < packetSize)
{
//Mikro işlemci verisi yoksa...PID hesaplamaları ve motorları giden değişkenler yollanır. 
pid.Compute();
motorController.move(output, MIN_ABS_SPEED);
}

// kesme işaretini sıfırla ve INT_STATUS baytını al
mpuInterrupt = false;
mpuIntStatus = mpu.getIntStatus();
// get current FIFO count
fifoCount = mpu.getFIFOCount();
// check for overflow (this should never happen unless our code is too inefficient)
if ((mpuIntStatus & 0x10) || fifoCount == 1024)
{
// Mikro işlemci sıfırlanarak FIFO'nun temiz şekilde devam edebilmesi sağlanır. 
mpu.resetFIFO();
Serial.println(F("FIFO taşması!"));
// DMP kesmeye hazır olduğu sıklıkla kontrol edilir. 
}
else if (mpuIntStatus & 0x02)
{
// Doğru veri uzunluğu için beklenir. Bu bekleme çok kısa sürer. 
while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();
// FIFO'dan bir paket okunur. 
mpu.getFIFOBytes(fifoBuffer, packetSize);
// 1'den büyük bir paket olursa FIFO hareketleri burdan takip edilebilir. 
// bu bize kesmeyi beklemeden hızlıca daha fazla okuma yapmamıza imkan verir. 
fifoCount -= packetSize;
mpu.dmpGetQuaternion(&q, fifoBuffer);
mpu.dmpGetGravity(&gravity, &q);
mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
#if LOG_INPUT
Serial.print("ypr\t");
Serial.print(ypr[0] * 180/M_PI);
Serial.print("\t");
Serial.print(ypr[1] * 180/M_PI);
Serial.print("\t");
Serial.println(ypr[2] * 180/M_PI);
#endif
input = ypr[1] * 180/M_PI + 180;
}
}



