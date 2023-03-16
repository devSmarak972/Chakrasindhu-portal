#include<SD.h>
#include<SPI.h>



#define wind_speed_1_pin 2

File myFile ;

volatile long pulsecount ;
volatile long initialcount ;
volatile long finalcount ;
volatile long netcount ;
int delayTime = 1000 ;
volatile long timespent ;
int wind_speed_1 ;
float wind_dir_1 ;

void setup(){
  pinMode(wind_speed_1_pin , INPUT_PULLUP );
  attachInterrupt( 0,do_count, RISING);
  Serial.begin(9600);
  timespent = millis();
  initialcount = pulsecount;
 while(!Serial){
    ;
  }
 Serial.println("Let's initialize the SD module");
 if(!SD.begin(10)){
 Serial.println(" Sorry brroooooo!!!!Seems your SD card not working");
 while(1);
  }
 Serial.println(" Yooo! Its initialized now");
 myFile = SD.open("data.txt",FILE_WRITE);


}

void do_count(){
  pulsecount++ ;
}


void loop(){
  
   //Serial.print(" Pulse Count =");
   //Serial.println(pulsecount);
   

   if( millis() - timespent >= delayTime){
    timespent = millis();
    finalcount = pulsecount ;
    netcount = finalcount - initialcount ;
    wind_speed_1 = netcount*2.25*0.44704 ;
    wind_dir_1 = analogRead(A0)* 0.3515 ; // 0.3515 = 360/1024

    //ADC Code Start

    float wind_vel_2 = analogRead(A2);
    wind_vel_2 = wind_vel_2*50/1024;
//  Serial.println(wind_vel_2);
  //delay(200);
  
  float wind_dir_2 = analogRead(A1);
  wind_dir_2 = wind_dir_2*360/1024;
//  Serial.println(wind_dir_2);
 // delay(200);
  // ADC End
    
    Serial.print( " Wind Speed 1 = ");
    Serial.print( wind_speed_1);  
    Serial.print( " Wind Direction 1 = ");
    Serial.println(wind_dir_1);
    Serial.print( " Wind Speed 2 = ");
    Serial.print( wind_vel_2);  
    Serial.print( " Wind Direction 2 = ");
    Serial.println(wind_dir_2);
    myFile = SD.open("data.txt",FILE_WRITE);
    if(myFile){
    Serial.println("Seems, you are doing a good job");
    myFile.print(wind_speed_1);
    myFile.print("\t");
    myFile.println(wind_vel_2);
    myFile.print("\t");
    myFile.print(wind_dir_1);
    myFile.print("\t");
    myFile.println(wind_dir_2);
      
    
    myFile.close();
     }
    else {
    Serial.println(" Uuumm sorry !! Couldn't open your file");
    }
    pulsecount = 0 ;
    initialcount = pulsecount ;
     

   }
}



  
  
