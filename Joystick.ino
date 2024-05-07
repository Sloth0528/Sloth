#include <SoftwareSerial.h>
#include <Wire.h>

#define MT_L 9  //ENA
#define IN1 8
#define IN2 7

#define IN3 5
#define IN4 4
#define MT_R 3  //ENB

char Car_status;
int Speed_value=150;

SoftwareSerial BT(10,11);
//定義Arduino PIN10及PIN11分別為RX及TX腳

void setup() {
  pinMode(MT_L,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(MT_R,OUTPUT);

  BT.begin(9600); // 設定和 HC-06 通訊的速度 (預設 9600)
  Serial.begin(9600); 

}

void loop() {
//當Serial有資料傳輸時，會將讀取到的字元存到Car_status。
  if(Serial.available() == true){   
    Car_status = Serial.read();  
  }
  
//當藍芽有資料傳輸時，會將讀取到的字元存到Car_status。
  if (BT.available()){      
    Car_status =BT.read();  
    Serial.println(Car_status);  
  }
  
//車子方向控制
 switch(Car_status){   
  case 'F':
    Forward();
    Serial.println("Forward");
    Car_status='N';
    break;
  case 'B':
    Backward();
    Serial.println("Backward");
    Car_status='N';
    break;
  case 'R':
    TurnRight();
    Serial.println("TurnRight");
    Car_status='N';
    break;
  case 'L':
    TurnLeft();
    Serial.println("TurnLeft");
    Car_status='N';
    break;
  case 'S':
    Stop();
    Serial.println("Stop");
    Car_status='N';
    break;
  case 'v':
    Speed_value=0; 
    do{
      if (BT.available()){
        Car_status =BT.read();  //讀取藍芽傳送字元
        Serial.println(Car_status); 
        if( Car_status=='e'){        
          Serial.println(Speed_value);
          break;
        }         
        else
        //將傳送來的速度數值字元轉成整數。
        Speed_value=10*Speed_value+(Car_status-48); 
      }
    }while(true);      
  }
}

void Stop() 
{
  analogWrite(MT_L,0);
  analogWrite(MT_R,0);
}

void Forward()
{
   digitalWrite(IN1,HIGH);
   digitalWrite(IN2,LOW);
   digitalWrite(IN3,LOW);
   digitalWrite(IN4,HIGH);  
   analogWrite(MT_R,Speed_value);
   analogWrite(MT_L,Speed_value); 
}
void Backward()
{
   digitalWrite(IN1,LOW);
   digitalWrite(IN2,HIGH);
   digitalWrite(IN3,HIGH);
   digitalWrite(IN4,LOW);  
   analogWrite(MT_R,Speed_value);
   analogWrite(MT_L,Speed_value); 
}
void TurnRight()
{
   digitalWrite(IN1,HIGH);
   digitalWrite(IN2,LOW);
   digitalWrite(IN3,LOW);
   digitalWrite(IN4,HIGH);  
   analogWrite(MT_L,0);
   analogWrite(MT_R,Speed_value);   
}
void TurnLeft()
{
   digitalWrite(IN1,HIGH);
   digitalWrite(IN2,LOW);
   digitalWrite(IN3,LOW);
   digitalWrite(IN4,HIGH);  
   analogWrite(MT_L,Speed_value);
   analogWrite(MT_R,0);   
}