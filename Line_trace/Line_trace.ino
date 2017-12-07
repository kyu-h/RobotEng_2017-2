#define EN1 5//pin for run the left motor 
#define IN1 12//pin for control left motor direction
#define EN2 6//pin for run the right motor 
#define IN2 7//pin for control right motor direction


#define Forward 0      // value for forward
#define Back 1         //value for go back

int data[5]={};

void Motor(int M1_DIR,int M1_EN,int M2_DIR,int M2_EN)//control the motor
{
  //////////M1-->left motor////////////////////////
  if(M1_DIR==Forward)//distinguish the command
    digitalWrite(IN1,Forward);
  else
    digitalWrite(IN1,Back);
  if(M1_EN==0)
    analogWrite(EN1,LOW);
 else
    analogWrite(EN1,M1_EN);

  ///////////M2-->right motor//////////////////////
  if(M2_DIR==Forward)
    digitalWrite(IN2,Forward);
  else
    digitalWrite(IN2,Back);
  if(M2_EN==0)
    analogWrite(EN2,LOW);
  else
    analogWrite(EN2,M2_EN);
}

void Read_Value(void)//read the five sensors
{  
  int i;
  for(i=0;i<5;i++)
  {
    data[i]=analogRead(i);//store the value read from the sensors
    
    Serial.print("time ");
    Serial.print(i);
    Serial.print(" = ");
    Serial.println(data[i]);
    //delay(100);
  }
}

void huntline_deal( )//function for line-hunt, white and black line, the value is less than 700 when detect line and for paper is bigger than 800
{
  if(data[0]<300 || data[1] <300) //left detect black line
  { 
    Motor(Forward,15,Forward,45);//turn right
    
    delay(10);
  }
  else  if(data[3]<300 || data[4] <300)//black line in the right
  {
    Motor(Forward,45,Forward,15);//turn left
    delay(10);
  }
  else if(data[2]>300)//line in middle
  {
    Motor(Forward,30,Forward,30);//go forward
    delay(20);
  }
  
 /* else if(data[2]<300)
  {
    Motor(Back,60,Back,110);
    delay(450);
    Motor(Forward,110,Forward,30);//undefine state just go slowly
    delay(100);
  }
  else if(data[3]<300 || data[4] <300){
    Motor(Back,110,Back,30);//undefine state just go slowly
    delay(250);
  }
  else if(data[1]<300 || data[0]<300) {
    Motor(Back,30,Back,110);//undefine state just go slowly
    delay(250);
  }*/
}


void setup()
{
  pinMode(5,OUTPUT);//init the pins for motor
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(12,OUTPUT); 
  Motor(Forward,0,Forward,0);//电机停转
  Serial.begin(9600);
}

void loop()
{
  Read_Value();//read the value of sensors
  huntline_deal();//function for line hunt
}


