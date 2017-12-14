/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>

#define R 2  //right encoder interrupt num
#define L 3  //left  encoder interrupt num
#define EN1 6//pin for run the right motor 
#define IN1 7//pin for control right motor direction
#define EN2 5//pin for run the left motor 
#define IN2 12//pin for control left motor direction
float  time_step= 500; //delay time
volatile int r_val=0;  //store right wheel num
volatile int l_val=0;  //store left wheel num
float l_speed_reality; //reality right speed
float r_speed_reality;  //reality left speed

#define FORW 0
#define BACK 1

int RECV_PIN = 17;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  pinMode(5,OUTPUT);//init the motor driver pins
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(12,OUTPUT);
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
   
}
void Motor_Control(int M1_DIR,int M1_EN,int M2_DIR,int M2_EN)//control motor
{
  //////////M1////////////////////////
  if(M1_DIR==FORW)//M1 motor direction
    digitalWrite(IN1,FORW);//forward
  else
    digitalWrite(IN1,BACK);//back
  if(M1_EN==0)
    analogWrite(EN1,LOW);//stop
  else
    analogWrite(EN1,M1_EN);//set speed

  ///////////M2//////////////////////
  if(M2_DIR==FORW)
    digitalWrite(IN2,FORW);
  else
    digitalWrite(IN2,BACK);
  if(M2_EN==0)
    analogWrite(EN2,LOW);
  else
    analogWrite(EN2,M2_EN);
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    Serial.println("--------------------");
    
    Serial.println(results.value);
    
    irrecv.resume(); // Receive the next value
    static int a;
    static int b;

    if(results.value == 16582903){
       Motor_Control(FORW,60,BACK,60);
       a=1;
       b=1;
    }
    else if(results.value == 16615543){
       Motor_Control(FORW,120,BACK,45);
       a=2;
       b=1;
    }
    else if(results.value == 16599223){
      Motor_Control(FORW,240,BACK,30);
       a=3;
       b=1;
    }
    else if(results.value == 16605343 && a == 1){     //오른쪽 1번
      Motor_Control(BACK,60,FORW,60);
      a=1;
      b=0;
    }
    else if(results.value == 16605343 && a == 2){     //2번
      Motor_Control(BACK,120,FORW,45);
      a=2;
      b=0;
    }
    else if(results.value == 16605343 && a == 3){     //3번
      Motor_Control(BACK,240,FORW,30);
      a=3;
      b=0;
    }
    else if(results.value == 16589023 && a == 1){               //왼쪽 1번
      Motor_Control(FORW,60,BACK,60);
      b=1;
    }
    else if(results.value == 16589023 && a == 2){               //왼쪽 2번
      Motor_Control(FORW,120,BACK,45);
      b=1;
    }
    else if(results.value == 16589023 && a == 3){               //왼쪽 3번
      Motor_Control(FORW,240,BACK,30);
      b=1;
    }
    else if(results.value == 16613503 && a == 1 && b==1){               //속도+
      Motor_Control(FORW,60,BACK,60);
      Serial.println("+++");
    }
    else if(results.value == 16613503 && a == 2 && b==1){               //속도+
      Motor_Control(FORW,120,BACK,45);
      Serial.println("+++++");
    }
    else if(results.value == 16613503 && a == 3 && b==1){               //속도+
      Motor_Control(FORW,240,BACK,30);
      Serial.println("+++++++");
    }
     else if(results.value == 16617583 && a == 1 && b==1){               //속도-
      Motor_Control(FORW,30,BACK,30);
      Serial.println("---");
    }
    else if(results.value == 16617583 && a == 2 && b==1){               //속도-
      Motor_Control(FORW,60,BACK,23);
      Serial.println("-----");
    }
    else if(results.value == 16617583 && a == 3 && b==1){               //속도-
      Motor_Control(FORW,120,BACK,15);
      Serial.println("-------");
    }

    
    else if(results.value == 16613503 && a == 1 && b==0){               //속도+
      Motor_Control(BACK,60,FORW,60);
      Serial.println("+++");
    }
    else if(results.value == 16613503 && a == 2 && b==0){               //속도+
      Motor_Control(BACK,120,FORW,45);
      Serial.println("+++++");
    }
    else if(results.value == 16613503 && a == 3 && b==0){               //속도+
      Motor_Control(BACK,240,FORW,30);
      Serial.println("+++++++");
    }
     else if(results.value == 16617583 && a == 1 && b==0){               //속도-
      Motor_Control(BACK,30,FORW,30);
      Serial.println("---");
    }
    else if(results.value == 16617583 && a == 2 && b==0){               //속도-
      Motor_Control(BACK,60,FORW,23);
      Serial.println("-----");
    }
    else if(results.value == 16617583 && a == 3 && b==0){               //속도-
      Motor_Control(BACK,120,FORW,15);
      Serial.println("-------");
    }
    
  }
}
