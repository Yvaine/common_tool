// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.


#include <Servo.h> 
#include <ros.h>
#include <std_msgs/Char.h>

int E1 = 5;     //定义M1使能端
int E2 = 6;     //定义M2使能端
int M1 = 4;    //定义M1控制端
int M2 = 7;    //定义M1控制端

int Servox_pin = 9;
int Servoy_pin = 10;

Servo servox;  // create servo object to control a servo 
Servo servoy;                // a maximum of eight servo objects can be created 
 
int posx = 90;    // variable to store the servo position 
int posy = 50;

ros::NodeHandle nh;
//command
std_msgs::Char cmd_servox;
std_msgs::Char cmd_servoy;
std_msgs::Char cmd_motor;


int ang_step = 7;

inline int mkp(char s) {
   switch(s) {
      case '+': return +1;
      case '-': return -1;
      case '0': return 0;
   } 
   return 0;
}


void servo_x(const std_msgs::Char &cmd_servox)
{
  char x[3] = {'0', '+', '-'}; //   left(+) right(-)
  int stepx = mkp(cmd_servox.data);
  posx += stepx;
  if(posx > 180) posx = 178;
  if(posx < 0) posx = 0;
  servox.write(posx);
}

void servo_y(const std_msgs::Char &cmd_servoy)
{
  char y[3] = {'0', '+', '-'}; //    up(-)  down(+)
  int stepy = mkp(cmd_servoy.data);
  posy += stepy;
  if(posy > 180) posy = 178;
  if(posy < 55) posy = 55;
  servoy.write(posy); 
}

void keep_stop(void){                 //停止
       digitalWrite(E1,LOW);   
       digitalWrite(E2,LOW);      
}  
 
void advance(char a,char b, int milesecs){           //前进
       analogWrite (E1,a);             //PWM调速
       digitalWrite(M1,HIGH);    
       analogWrite (E2,b);    
       digitalWrite(M2,HIGH);
       delay(milesecs);
       
}  
void back_off (char a,char b, int milesecs) {          //后退
       analogWrite (E1,a);
       digitalWrite(M1,LOW);   
       analogWrite (E2,b);    
       digitalWrite(M2,LOW);
       delay(milesecs);
}
void turn_R (char a,char b, int milesecs) {           //左转
       analogWrite (E1,a);
       digitalWrite(M1,LOW);    
       analogWrite (E2,b);    
       digitalWrite(M2,HIGH);
       delay(milesecs);
}
void turn_L (char a,char b, int milesecs) {           //右转
       analogWrite (E1,a);
       digitalWrite(M1,HIGH);    
       analogWrite (E2,b);    
       digitalWrite(M2,LOW);
       delay(milesecs);
}

void motor(const std_msgs::Char &cmd_motor)
{
  char val = cmd_motor.data;
  if(val!=-1){
          switch(val){
             case 'w'://前进
                     advance (255,255,100);   //PWM调速
                     break;
             case 's'://后退
                     back_off (255,255,100);
                     break;
             case 'a'://左转
                     turn_L (255,255,ang_step * 3); // 2
                     break;       
             case 'd'://右转
                     turn_R (255,255,ang_step * 3);
                     break;
             case 'q':
                     keep_stop();
                     break;          
            }     
         keep_stop(); 
       }
      else keep_stop(); 
}
#if 0
ros::Subscriber<std_msgs::Char>sub_motor("motor_chatter", motor);
ros::Subscriber<std_msgs::Char>sub_servox("servox_chatter", servo_x);
ros::Subscriber<std_msgs::Char>sub_servoy("servoy_chatter", servo_y);
#endif
void setup() 
{ 
  servox.attach(Servox_pin);  // attaches the servo on pin 9 to the servo object 
  servoy.attach(Servoy_pin);
  servox.write(posx);
  servoy.write(posy);

  int i;
  for(i=6;i<=9;i++)
    pinMode(i, OUTPUT);  
  keep_stop();

  nh.initNode();
  nh.subscribe(sub_motor);
  //nh.subscribe(sub_servox);
  //nh.subscribe(sub_servoy);
} 
 

void loop() 
{ 
  nh.spinOnce();
  delay(100);
}

