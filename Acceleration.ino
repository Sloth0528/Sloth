#include <SoftwareSerial.h>
#include <Wire.h>

//輸出到L298N的腳位
#define MT_L 3  //ENA
#define IN1 4
#define IN2 5

#define IN3 7
#define IN4 8
#define MT_R 9  //ENB

SoftwareSerial BT(10,11);
String XYValue;
int dX,dY;
int RightSpeed;
int LeftSpeed;


void setup() {
  BT.begin(9600); 
  BT.setTimeout(50); 
  Serial.begin(9600); 
  pinMode(MT_L,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(MT_R,OUTPUT);

  
}

void loop() {
  while(BT.available()) {
    XYValue=BT.readString();
    ValueTransform();
    RightSpeed=(dX+dY)*2;
    LeftSpeed=(dX-dY)*2;
    char MR_DIR=Motor_R_DIR();   
    char ML_DIR=Motor_L_DIR();  
    analogWrite(MT_R,abs(RightSpeed));//輸出右馬達速度
    analogWrite(MT_L,abs(LeftSpeed)); //輸出左馬達速度
    Serial.print(LeftSpeed);
    Serial.print(',');
    Serial.print(ML_DIR);
    Serial.print(',');
    Serial.print(RightSpeed);
    Serial.print(',');
    Serial.println(MR_DIR);
    
  }
  
}


void ValueTransform(){
  String X, Y;
  for(int i=0; i<XYValue.length(); i++){
    if(i<XYValue.indexOf(',')){
      X=X+XYValue[i];
    }
    else if(i>XYValue.indexOf(',')){
      Y=Y+XYValue[i];
    }
  }
    dX=X.toInt();
    dY=Y.toInt();
}


char Motor_R_DIR()
{
  if(RightSpeed>0){
   digitalWrite(IN3,HIGH);
   digitalWrite(IN4,LOW);
   return 'B';
  }
  else if(RightSpeed<0){
   digitalWrite(IN3,LOW);
   digitalWrite(IN4,HIGH);
   return 'F';
  }
}

//正反轉
char Motor_L_DIR()
{
  if(LeftSpeed>0){
   digitalWrite(IN1,LOW);
   digitalWrite(IN2,HIGH);
   return 'B';
  }  
  else if(LeftSpeed<0){
   digitalWrite(IN1,HIGH);
   digitalWrite(IN2,LOW);
   return 'F';
  }   
}
