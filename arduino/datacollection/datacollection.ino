#include<SD.h>
#include<SPI.h>

#define wind_speed_1_pin 2

File myFile ;

volatile long pulsecount ;
volatile long initialcount ;
volatile long finalcount ;
volatile long netcount ;
int interval = 5000 ;
volatile long timespent ;
int wind_speed_1 ;
float wind_dir_1 ;

static String inittime="24-03-23-11-18-00";
int days=11,month=3,year=2023,hours=14,mins=30,secs=0;
void getTime(String t){
  int cnt=0;
  String str = "" ;
  for (int i = 0; i < t.length(); i++)
  {
    char c = t.charAt(i);
    if (c != '-')
    {
      str += String(c);

    }
    else
    {
    Serial.println(str);
      cnt++;
      if (cnt == 1)
      {
        days = str.toInt();
      }
      else if (cnt == 2)
      {
        month = str.toInt();
      }
      else if (cnt == 3)
      {
        year = str.toInt();
      }
      else if (cnt == 4)
      {
        hours = str.toInt();
      }
      else if (cnt == 4)
      {
        mins = str.toInt();
      }
      else if (cnt == 5)
      {
        secs = str.toInt();
      }
            str="";

    }
  }

}

void advanceTime(){
   secs+=(interval/1000);
   if(secs>60){
    mins++;
    secs=secs%60;
   }
   if(mins>60){
    hours++;
    mins=0;
   }
   if(hours>24)
   {
    hours=0;
    days++;
   }
   if(days>30)
   {
    days=1;
    month++;
   }
   if(month>12)
   {
    month=1;
    year++;
   }


}

void setup(){
  pinMode(wind_speed_1_pin , INPUT_PULLUP );
  attachInterrupt( 0,do_count, RISING);
  Serial.begin(9600);
  timespent = millis();
  initialcount = pulsecount;
 while(!Serial){
    
  };
 Serial.println("Let's initialize the SD module");
 if(!SD.begin(10)){
 Serial.println(" Sorry brroooooo!!!!Seems your SD card not working");
 while(1);
  }
 Serial.println(" Yooo! Its initialized now");
 myFile = SD.open("data.txt",FILE_WRITE);
getTime(inittime);
Serial.println(String(days)+":"+String(month)+":"+String(year)+":"+String(hours)+":"+String(mins)+":"+String(secs));
}

void do_count(){
  pulsecount++ ;
}


void loop(){
  
   //Serial.print(" Pulse Count =");
   //Serial.println(pulsecount);
   

   if( millis() - timespent >= interval){
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
    Serial.println(String(days)+":"+String(month)+":"+String(year)+":"+String(hours)+":"+String(mins)+":"+String(secs));
    myFile = SD.open("data.txt",FILE_WRITE);
    if(myFile){
    Serial.println("Seems, you are doing a good job");
    myFile.print(wind_speed_1);
    myFile.print("\t");
    myFile.println(wind_vel_2);
    myFile.print("\t");
    myFile.print(wind_dir_1);
    myFile.print("\t");
    myFile.print(wind_dir_2);
    myFile.print("\t");
    myFile.println(String(days)+":"+String(month)+":"+String(year)+":"+String(hours)+":"+String(mins)+":"+String(secs));
    advanceTime();
    myFile.close();
     }
    else {
    Serial.println(" Uuumm sorry !! Couldn't open your file");
    }
    pulsecount = 0 ;
    initialcount = pulsecount ;
     

   }
}



  
  
