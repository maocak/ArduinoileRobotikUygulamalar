#include <Servo.h>   //servo motor kütüphanesi koda eklenir. 

Servo servo[4][3];//2 elemanlı bir dizi şeklinde 12 servo motor için servo motor nesnesi  oluşturulur. 

//12 adet servo motorun pin atamaları yapılır. 
const int servo_pin[4][3] = { {2, 3, 4}, {5, 6, 7}, {8, 9, 10}, {11, 12, 13} };

void setup()
{
//Tüm servo motorlar başlatılır. 
for (int i = 0; i < 4; i++)
{
for (int j = 0; j < 3; j++)
{
delay (500);
servo[i][j].attach(servo_pin[i][j]);
delay(1000);
}
}
while (1);
}

void loop(void)
{
  
}

