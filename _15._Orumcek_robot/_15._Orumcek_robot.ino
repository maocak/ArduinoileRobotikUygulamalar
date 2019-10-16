#include <Servo.h>    //Servo motor kütüphanesi koda eklenir. 
#include <FlexiTimer2.h> //Servo motorları yönetmek için kullanılan ve zamanlayıcı ayarlayan kütüphanedir. 
Servo servo[4][3]; //12 adet servo motor nesnesi 2 elemanlı dizi şeklinde oluşturulur. 
const int servo_pin[4][3] = { {2, 3, 4}, {5, 6, 7}, {8, 9, 10}, {11, 12, 13} }; //Servo motor pin numaraları atanır. 
//Robotun boyutu için kullanılan sabitler atanır. 
const float length_a = 55;
const float length_b = 77.5;
const float length_c = 27.5;
const float length_side = 71;
const float z_absolute = -28;
//Hareket için kullanılan sabitler atanır. 
const float z_default = -50, z_up = -30, z_boot = z_absolute;
const float x_default = 62, x_offset = 0;
const float y_start = 0, y_step = 40;
//Hareket için kullanılan değişkenler atanır. 
volatile float site_now[4][3];    //her bacağın ucunun gerçek zamanlı koordinatları
volatile float site_expect[4][3]; //her bacağın sonu için beklenen koordinatlar
float temp_speed[4][3];   //her bir eksenin hızı, her hareketden önce yeniden hesaplanması gerekir
float move_speed;     //Hareket hızı
float speed_multiple = 1; //Hareket hızı çoklu
const float spot_turn_speed = 4;
const float leg_move_speed = 8;
const float body_move_speed = 3;
const float stand_seat_speed = 1;
volatile int rest_counter;      //+1/0.02s, Otomatik dinlenme için
const float KEEP = 255; //Fonksiyonların parametresi
const float pi = 3.1415926; //Pi değeri
// Dönüş için kullanılan sabitler 
//Geçici uzunluk
const float temp_a = sqrt(pow(2 * x_default + length_side, 2) + pow(y_step, 2));
const float temp_b = 2 * (y_start + y_step) + length_side;
const float temp_c = sqrt(pow(2 * x_default + length_side, 2) + pow(2 * y_start + y_step + length_side, 2));
const float temp_alpha = acos((pow(temp_a, 2) + pow(temp_b, 2) - pow(temp_c, 2)) / 2 / temp_a / temp_b);
//Dönüş için kullanılan x0,y0,x1 ve y1 değerleri
const float turn_x1 = (temp_a - length_side) / 2;
const float turn_y1 = y_start + y_step / 2;
const float turn_x0 = turn_x1 - temp_b * cos(temp_alpha);
const float turn_y0 = temp_b * sin(temp_alpha) - turn_y1 - length_side;

void setup()
{
Serial.begin(115200); //Seri veri iletişimi 115200 bant aralığında başlatılır. 
Serial.println("Robot başlatmaya hazırlanıyor");
//Varsayılan parametreler başlatılır. 
set_site(0, x_default - x_offset, y_start + y_step, z_boot);
set_site(1, x_default - x_offset, y_start + y_step, z_boot);
set_site(2, x_default + x_offset, y_start, z_boot);
set_site(3, x_default + x_offset, y_start, z_boot);
for (int i = 0; i < 4; i++)
{
for (int j = 0; j < 3; j++)
{
site_now[i][j] = site_expect[i][j];
}
}
//Servo motorlar çalışmaya hazırlanır. 
FlexiTimer2::set(20, servo_service);
FlexiTimer2::start();
Serial.println("Servo motorlar çalışmaya hazırlanıyor.");
//Servo motorların çalışması başlatılır. 
servo_attach();
Serial.println("Servo motorlar çalışmaya başladı");
Serial.println("Robot başlatma bitirildi.");
}


void servo_attach(void) //Servo motorlar başlatılır. 
{
for (int i = 0; i < 4; i++)
{
for (int j = 0; j < 3; j++)
{
delay(500);
servo[i][j].attach(servo_pin[i][j]);
delay(10);
}
}
}

void servo_detach(void) //Servo motorlar durdurulur. 
{
for (int i = 0; i < 4; i++)
{
for (int j = 0; j < 3; j++)
{
servo[i][j].detach();
delay(100);
}
}
}

void loop()
{
Serial.println("Ayağa kalk");
stand(); //Ayağa kalk fonksiyona çağrılır. 
delay(2000); //2 sn beklenir. 
Serial.println("İleri git");
step_forward(10); //İleri git fonksiyonu çağrılır (10 adım ileri gider)
delay(2000); //2 sn beklenir. 
Serial.println("Geri gel"); 
step_back(5); //Geri gel fonksiyonu çağrılır (5 adım geri gelir).
delay(2000); //2 sn beklenir. 
Serial.println("Sola dön");
turn_left(5); //Sola dön fonksiyonu çağrılır ( 5 adım sola döner)
delay(2000); //2 sn beklenir. 
Serial.println("Sağa dön");
turn_right(5); //Sağa döne fonkisyonu çağrılır (5 adım sağa döner)
delay(2000); //2 sn beklenir. 
Serial.println("El salla");
hand_wave(5); //El salla fonksiyonu çağrılır ( 5 kez devam eder)
delay(5000); //5 sn beklenir. 
Serial.println("El sık");
hand_shake(3); //El sık fonksiyonu çağrılır (3 kez devam eder)
delay(2000);  //2 sn beklenir. 
Serial.println("Otur");
sit(); //otur fonksiyonu çağrılır. 
delay(5000); //5 sn beklenir. 
while(true){}

}

void sit(void) //Otur fonksiyonu
{
move_speed = stand_seat_speed;
for (int leg = 0; leg < 4; leg++)
{
set_site(leg, KEEP, KEEP, z_boot);
}
wait_all_reach();
}

void stand(void) //Ayağa kalk fonksiyonu
{
move_speed = stand_seat_speed;
for (int leg = 0; leg < 4; leg++)
{
set_site(leg, KEEP, KEEP, z_default);
}
wait_all_reach();
}


void turn_left(unsigned int step) //Sola dön fonksiyonu
{
move_speed = spot_turn_speed;
while (step-- > 0)
{
if (site_now[3][1] == y_start)
{
//1. ve 3. ayak hareket eder. 
set_site(3, x_default + x_offset, y_start, z_up);
wait_all_reach();

set_site(0, turn_x1 - x_offset, turn_y1, z_default);
set_site(1, turn_x0 - x_offset, turn_y0, z_default);
set_site(2, turn_x1 + x_offset, turn_y1, z_default);
set_site(3, turn_x0 + x_offset, turn_y0, z_up);
wait_all_reach();

set_site(3, turn_x0 + x_offset, turn_y0, z_default);
wait_all_reach();

set_site(0, turn_x1 + x_offset, turn_y1, z_default);
set_site(1, turn_x0 + x_offset, turn_y0, z_default);
set_site(2, turn_x1 - x_offset, turn_y1, z_default);
set_site(3, turn_x0 - x_offset, turn_y0, z_default);
wait_all_reach();

set_site(1, turn_x0 + x_offset, turn_y0, z_up);
wait_all_reach();

set_site(0, x_default + x_offset, y_start, z_default);
set_site(1, x_default + x_offset, y_start, z_up);
set_site(2, x_default - x_offset, y_start + y_step, z_default);
set_site(3, x_default - x_offset, y_start + y_step, z_default);
wait_all_reach();

set_site(1, x_default + x_offset, y_start, z_default);
wait_all_reach();
}
else
{
//0. ve 2. ayak hareket eder. 
set_site(0, x_default + x_offset, y_start, z_up);
wait_all_reach();

set_site(0, turn_x0 + x_offset, turn_y0, z_up);
set_site(1, turn_x1 + x_offset, turn_y1, z_default);
set_site(2, turn_x0 - x_offset, turn_y0, z_default);
set_site(3, turn_x1 - x_offset, turn_y1, z_default);
wait_all_reach();

set_site(0, turn_x0 + x_offset, turn_y0, z_default);
wait_all_reach();

set_site(0, turn_x0 - x_offset, turn_y0, z_default);
set_site(1, turn_x1 - x_offset, turn_y1, z_default);
set_site(2, turn_x0 + x_offset, turn_y0, z_default);
set_site(3, turn_x1 + x_offset, turn_y1, z_default);
wait_all_reach();

set_site(2, turn_x0 + x_offset, turn_y0, z_up);
wait_all_reach();

set_site(0, x_default - x_offset, y_start + y_step, z_default);
set_site(1, x_default - x_offset, y_start + y_step, z_default);
set_site(2, x_default + x_offset, y_start, z_up);
set_site(3, x_default + x_offset, y_start, z_default);
wait_all_reach();

set_site(2, x_default + x_offset, y_start, z_default);
wait_all_reach();
}
}
}

void turn_right(unsigned int step) //Sağa dön fonksiyonu
{
move_speed = spot_turn_speed;
while (step-- > 0)
{
if (site_now[2][1] == y_start)
{
//0. ve 2. bacak hareket eder. 
set_site(2, x_default + x_offset, y_start, z_up);
wait_all_reach();

set_site(0, turn_x0 - x_offset, turn_y0, z_default);
set_site(1, turn_x1 - x_offset, turn_y1, z_default);
set_site(2, turn_x0 + x_offset, turn_y0, z_up);
set_site(3, turn_x1 + x_offset, turn_y1, z_default);
wait_all_reach();

set_site(2, turn_x0 + x_offset, turn_y0, z_default);
wait_all_reach();

set_site(0, turn_x0 + x_offset, turn_y0, z_default);
set_site(1, turn_x1 + x_offset, turn_y1, z_default);
set_site(2, turn_x0 - x_offset, turn_y0, z_default);
set_site(3, turn_x1 - x_offset, turn_y1, z_default);
wait_all_reach();

set_site(0, turn_x0 + x_offset, turn_y0, z_up);
wait_all_reach();

set_site(0, x_default + x_offset, y_start, z_up);
set_site(1, x_default + x_offset, y_start, z_default);
set_site(2, x_default - x_offset, y_start + y_step, z_default);
set_site(3, x_default - x_offset, y_start + y_step, z_default);
wait_all_reach();

set_site(0, x_default + x_offset, y_start, z_default);
wait_all_reach();
}
else
{
//1. ve 3. bacak hareket eder. 
set_site(1, x_default + x_offset, y_start, z_up);
wait_all_reach();

set_site(0, turn_x1 + x_offset, turn_y1, z_default);
set_site(1, turn_x0 + x_offset, turn_y0, z_up);
set_site(2, turn_x1 - x_offset, turn_y1, z_default);
set_site(3, turn_x0 - x_offset, turn_y0, z_default);
wait_all_reach();

set_site(1, turn_x0 + x_offset, turn_y0, z_default);
wait_all_reach();

set_site(0, turn_x1 - x_offset, turn_y1, z_default);
set_site(1, turn_x0 - x_offset, turn_y0, z_default);
set_site(2, turn_x1 + x_offset, turn_y1, z_default);
set_site(3, turn_x0 + x_offset, turn_y0, z_default);
wait_all_reach();

set_site(3, turn_x0 + x_offset, turn_y0, z_up);
wait_all_reach();

set_site(0, x_default - x_offset, y_start + y_step, z_default);
set_site(1, x_default - x_offset, y_start + y_step, z_default);
set_site(2, x_default + x_offset, y_start, z_default);
set_site(3, x_default + x_offset, y_start, z_up);
wait_all_reach();

set_site(3, x_default + x_offset, y_start, z_default);
wait_all_reach();
}
}
}

void step_forward(unsigned int step)//ileri git fonksiyonu
{
move_speed = leg_move_speed;
while (step-- > 0)
{
if (site_now[2][1] == y_start)
{
//1. ve 2. bacak hareket eder. 
set_site(2, x_default + x_offset, y_start, z_up);
wait_all_reach();
set_site(2, x_default + x_offset, y_start + 2 * y_step, z_up);
wait_all_reach();
set_site(2, x_default + x_offset, y_start + 2 * y_step, z_default);
wait_all_reach();

move_speed = body_move_speed;

set_site(0, x_default + x_offset, y_start, z_default);
set_site(1, x_default + x_offset, y_start + 2 * y_step, z_default);
set_site(2, x_default - x_offset, y_start + y_step, z_default);
set_site(3, x_default - x_offset, y_start + y_step, z_default);
wait_all_reach();

move_speed = leg_move_speed;

set_site(1, x_default + x_offset, y_start + 2 * y_step, z_up);
wait_all_reach();
set_site(1, x_default + x_offset, y_start, z_up);
wait_all_reach();
set_site(1, x_default + x_offset, y_start, z_default);
wait_all_reach();
}
else
{
//0. ve 3. bacak hareket eder. 
set_site(0, x_default + x_offset, y_start, z_up);
wait_all_reach();
set_site(0, x_default + x_offset, y_start + 2 * y_step, z_up);
wait_all_reach();
set_site(0, x_default + x_offset, y_start + 2 * y_step, z_default);
wait_all_reach();

move_speed = body_move_speed;

set_site(0, x_default - x_offset, y_start + y_step, z_default);
set_site(1, x_default - x_offset, y_start + y_step, z_default);
set_site(2, x_default + x_offset, y_start, z_default);
set_site(3, x_default + x_offset, y_start + 2 * y_step, z_default);
wait_all_reach();

move_speed = leg_move_speed;

set_site(3, x_default + x_offset, y_start + 2 * y_step, z_up);
wait_all_reach();
set_site(3, x_default + x_offset, y_start, z_up);
wait_all_reach();
set_site(3, x_default + x_offset, y_start, z_default);
wait_all_reach();
}
}
}

void step_back(unsigned int step) //Geri git fonksiyonu
{
move_speed = leg_move_speed;
while (step-- > 0)
{
if (site_now[3][1] == y_start)
{
//0. ve 3. bacak hareket eder. 
set_site(3, x_default + x_offset, y_start, z_up);
wait_all_reach();
set_site(3, x_default + x_offset, y_start + 2 * y_step, z_up);
wait_all_reach();
set_site(3, x_default + x_offset, y_start + 2 * y_step, z_default);
wait_all_reach();

move_speed = body_move_speed;

set_site(0, x_default + x_offset, y_start + 2 * y_step, z_default);
set_site(1, x_default + x_offset, y_start, z_default);
set_site(2, x_default - x_offset, y_start + y_step, z_default);
set_site(3, x_default - x_offset, y_start + y_step, z_default);
wait_all_reach();

move_speed = leg_move_speed;

set_site(0, x_default + x_offset, y_start + 2 * y_step, z_up);
wait_all_reach();
set_site(0, x_default + x_offset, y_start, z_up);
wait_all_reach();
set_site(0, x_default + x_offset, y_start, z_default);
wait_all_reach();
}
else
{
//1. ve 2. bacanak hareket eder. 
set_site(1, x_default + x_offset, y_start, z_up);
wait_all_reach();
set_site(1, x_default + x_offset, y_start + 2 * y_step, z_up);
wait_all_reach();
set_site(1, x_default + x_offset, y_start + 2 * y_step, z_default);
wait_all_reach();

move_speed = body_move_speed;

set_site(0, x_default - x_offset, y_start + y_step, z_default);
set_site(1, x_default - x_offset, y_start + y_step, z_default);
set_site(2, x_default + x_offset, y_start + 2 * y_step, z_default);
set_site(3, x_default + x_offset, y_start, z_default);
wait_all_reach();

move_speed = leg_move_speed;

set_site(2, x_default + x_offset, y_start + 2 * y_step, z_up);
wait_all_reach();
set_site(2, x_default + x_offset, y_start, z_up);
wait_all_reach();
set_site(2, x_default + x_offset, y_start, z_default);
wait_all_reach();
}
}
}

void body_left(int i)//Robot şasisi sola döner. 
{
  set_site(0, site_now[0][0] + i, KEEP, KEEP);
  set_site(1, site_now[1][0] + i, KEEP, KEEP);
  set_site(2, site_now[2][0] - i, KEEP, KEEP);
  set_site(3, site_now[3][0] - i, KEEP, KEEP);
  wait_all_reach();
}

void body_right(int i) //Robot şasisi sağa döner. 
{
  set_site(0, site_now[0][0] - i, KEEP, KEEP);
  set_site(1, site_now[1][0] - i, KEEP, KEEP);
  set_site(2, site_now[2][0] + i, KEEP, KEEP);
  set_site(3, site_now[3][0] + i, KEEP, KEEP);
  wait_all_reach();
}

void hand_wave(int i) //El salla fonksiyonu
{
float x_tmp;
float y_tmp;
float z_tmp;
move_speed = 1;
if (site_now[3][1] == y_start)
{
body_right(15);
x_tmp = site_now[2][0];
y_tmp = site_now[2][1];
z_tmp = site_now[2][2];
move_speed = body_move_speed;
for (int j = 0; j < i; j++)
{
set_site(2, turn_x1, turn_y1, 50);
wait_all_reach();
set_site(2, turn_x0, turn_y0, 50);
wait_all_reach();
}
set_site(2, x_tmp, y_tmp, z_tmp);
wait_all_reach();
move_speed = 1;
body_left(15);
}
else
{
body_left(15);
x_tmp = site_now[0][0];
y_tmp = site_now[0][1];
z_tmp = site_now[0][2];
move_speed = body_move_speed;
for (int j = 0; j < i; j++)
{
set_site(0, turn_x1, turn_y1, 50);
wait_all_reach();
set_site(0, turn_x0, turn_y0, 50);
wait_all_reach();
}
set_site(0, x_tmp, y_tmp, z_tmp);
wait_all_reach();
move_speed = 1;
body_right(15);
}
}

void hand_shake(int i)//El sıkma fonksiyonu
{
float x_tmp;
float y_tmp;
float z_tmp;
move_speed = 1;
if (site_now[3][1] == y_start)
{
body_right(15);
x_tmp = site_now[2][0];
y_tmp = site_now[2][1];
z_tmp = site_now[2][2];
move_speed = body_move_speed;
for (int j = 0; j < i; j++)
{
set_site(2, x_default - 30, y_start + 2 * y_step, 55);
wait_all_reach();
set_site(2, x_default - 30, y_start + 2 * y_step, 10);
wait_all_reach();
}
set_site(2, x_tmp, y_tmp, z_tmp);
wait_all_reach();
move_speed = 1;
body_left(15);
}
else
{
body_left(15);
x_tmp = site_now[0][0];
y_tmp = site_now[0][1];
z_tmp = site_now[0][2];
move_speed = body_move_speed;
for (int j = 0; j < i; j++)
{
set_site(0, x_default - 30, y_start + 2 * y_step, 55);
wait_all_reach();
set_site(0, x_default - 30, y_start + 2 * y_step, 10);
wait_all_reach();
}
set_site(0, x_tmp, y_tmp, z_tmp);
wait_all_reach();
move_speed = 1;
body_right(15);
}
}

void servo_service(void)
{
sei();
static float alpha, beta, gamma;

for (int i = 0; i < 4; i++)
{
for (int j = 0; j < 3; j++)
{
if (abs(site_now[i][j] - site_expect[i][j]) >= abs(temp_speed[i][j]))
site_now[i][j] += temp_speed[i][j];
else
site_now[i][j] = site_expect[i][j];
}

cartesian_to_polar(alpha, beta, gamma, site_now[i][0], site_now[i][1], site_now[i][2]);
polar_to_servo(i, alpha, beta, gamma);
}

rest_counter++;
}

void set_site(int leg, float x, float y, float z)
{
float length_x = 0, length_y = 0, length_z = 0;

if (x != KEEP)
length_x = x - site_now[leg][0];
if (y != KEEP)
length_y = y - site_now[leg][1];
if (z != KEEP)
length_z = z - site_now[leg][2];

float length = sqrt(pow(length_x, 2) + pow(length_y, 2) + pow(length_z, 2));

temp_speed[leg][0] = length_x / length * move_speed * speed_multiple;
temp_speed[leg][1] = length_y / length * move_speed * speed_multiple;
temp_speed[leg][2] = length_z / length * move_speed * speed_multiple;

if (x != KEEP)
site_expect[leg][0] = x;
if (y != KEEP)
site_expect[leg][1] = y;
if (z != KEEP)
site_expect[leg][2] = z;
}

void wait_reach(int leg)
{
while (1)
if (site_now[leg][0] == site_expect[leg][0])
if (site_now[leg][1] == site_expect[leg][1])
if (site_now[leg][2] == site_expect[leg][2])
break;
}

void wait_all_reach(void)
{
for (int i = 0; i < 4; i++)
wait_reach(i);
}

void cartesian_to_polar(volatile float &alpha, volatile float &beta, volatile float &gamma, volatile float x, volatile float y, volatile float z)
{
float v, w;
w = (x >= 0 ? 1 : -1) * (sqrt(pow(x, 2) + pow(y, 2)));
v = w - length_c;
alpha = atan2(z, v) + acos((pow(length_a, 2) - pow(length_b, 2) + pow(v, 2) + pow(z, 2)) / 2 / length_a / sqrt(pow(v, 2) + pow(z, 2)));
beta = acos((pow(length_a, 2) + pow(length_b, 2) - pow(v, 2) - pow(z, 2)) / 2 / length_a / length_b);
gamma = (w >= 0) ? atan2(y, x) : atan2(-y, -x);
alpha = alpha / pi * 180;
beta = beta / pi * 180;
gamma = gamma / pi * 180;
}

void polar_to_servo(int leg, float alpha, float beta, float gamma)
{
if (leg == 0)
{
alpha = 90 - alpha;
beta = beta;
gamma += 90;
}
else if (leg == 1)
{
alpha += 90;
beta = 180 - beta;
gamma = 90 - gamma;
}
else if (leg == 2)
{
alpha += 90;
beta = 180 - beta;
gamma = 90 - gamma;
}
else if (leg == 3)
{
alpha = 90 - alpha;
beta = beta;
gamma += 90;
}

servo[leg][0].write(alpha);
servo[leg][1].write(beta);
servo[leg][2].write(gamma);
}

