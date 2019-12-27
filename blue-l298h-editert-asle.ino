#include <SoftwareSerial.h>

SoftwareSerial mySerial(12, 13); // RX, TX 
#define m1 3 
#define m2 5 
#define m3 9 
#define m4 10
//Denne virker 2019-06-22 Asle

int data=0,kec=0;
boolean forward=true;


int fast[11]={0,80,100,120,140,160,180,200,220,240,255};

void setup()
{
  pinMode(m1,OUTPUT);
  pinMode(m2,OUTPUT);
  pinMode(m3,OUTPUT);
  pinMode(m4,OUTPUT);

  mySerial.begin(9600);
 }

void motorOut(unsigned char lpwm, unsigned char rpwm, boolean arrow){
   if(arrow==false){
      digitalWrite(m3,HIGH);
      digitalWrite(m1,LOW);
      analogWrite(m4,255-lpwm);
      analogWrite(m2,rpwm);
   }
   else{
     digitalWrite(m3,LOW);
     digitalWrite(m1,HIGH);
     analogWrite(m4,lpwm);
     analogWrite(m2,255-rpwm);
  }
}

void loop(){
  if(mySerial.available()>0){
    data=mySerial.read();
    if (data =='0') { kec=0;}
      else if (data =='1') { kec=1;}
        else if (data =='2') { kec=2;}
          else if (data =='3') { kec=3;}
            else if (data =='4') { kec=4;}
              else if (data =='5') { kec=5;}
                else if (data =='6') { kec=6;}
                  else if (data =='7') { kec=7;}
                    else if (data =='8') { kec=8;}
                      else if (data =='9') { kec=9;}
                        else if (data =='q') {kec=10;}

//S= Stop
if (data == 'S')
{ motorOut(0,0,false); }

//F=Forward
if (data=='F')
{ motorOut(fast[kec],fast[kec],true); }

//I=turn right forward
if (data=='I')
{ motorOut(fast[kec],((fast[kec])/2),true);}

//G=turn left forward
if (data=='G')
{ motorOut(((fast[kec])/2),fast[kec],true); }

//R=turn right
if(data=='R')
{ motorOut(fast[kec],0,true); }

//L=turn left
if(data=='L')
{ motorOut(0,fast[kec],true); }

//B=back
if(data=='B')
{ motorOut(fast[kec],fast[kec],false); }

//H=turn left back
if (data=='H')
{ motorOut(((fast[kec])/2),fast[kec],false); }

//turn right back
if (data=='J')
{ motorOut(fast[kec],((fast[kec])/2),false); }
  }
}