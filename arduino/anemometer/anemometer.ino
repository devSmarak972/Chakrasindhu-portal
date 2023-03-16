int VaneValue;// raw analog value from wind vane
int Direction;// translated 0 - 360 direction
int CalDirection1;// converted value with offset applied
int LastValue;
int VaneValue2;// raw analog value from wind vane
int Direction2;// translated 0 - 360 direction
int CalDirection2;// converted value with offset applied
int LastValue2;
char timestamp[20];
#include "SD.h"
#include"SPI.h"
#include <math.h>

#define WindSensorPin1 (2) // The pin location of the anemometer sensor

volatile unsigned long Rotations1; // cup rotation counter used in interrupt routine
volatile unsigned long ContactBounceTime1; // Timer to avoid contact bounce in interrupt routine

float WindSpeed1; // speed miles per hour

#define Offset 0;
//the hardware CS pin (10 on most Arduino boards,
// 53 on the Mega) must be left as an output or the SD
// library functions will not work.
const int CSpin = 10;
String dataString =""; // holds the data to be written to the SD card
float sensorReading1 = 0.00; // value read from your first sensor
float sensorReading2 = 0.00; // value read from your second sensor
float sensorReading3 = 0.00; // value read from your third sensor
File sensorData;
void setup() {
LastValue = 1;
Serial.begin(9600);
Serial.print("Initializing SD card...");
pinMode(CSpin, OUTPUT);
//
pinMode(WindSensorPin1, INPUT);
attachInterrupt(digitalPinToInterrupt(WindSensorPin1), isr_rotation1, FALLING);
// pinMode(WindSensorPin2, INPUT);
// attachInterrupt(digitalPinToInterrupt(WindSensorPin2), isr_rotation2, FALLING);

// see if the card is present and can be initialized:
if (!SD.begin(CSpin)) {
Serial.println("Card failed, or not present");
// don't do anything more:
return;
}
Serial.println("card initialized.");
Serial.println("Vane Value\tDirection\tHeading");

}
void isr_rotation1 () {

if ((millis() - ContactBounceTime1) > 15 ) { // debounce the switch contact.
Rotations1++;
ContactBounceTime1 = millis();
}

}
// void isr_rotation2 () {

// if ((millis() - ContactBounceTime2) > 15 ) { // debounce the switch contact.
// Rotations2++;
// ContactBounceTime2 = millis();
// }

// }
void loop() {
VaneValue = analogRead(A0);
VaneValue2 = analogRead(A1);
Direction = map(VaneValue, 0, 1023, 0, 360);
Direction2 = map(VaneValue2, 0, 1023, 0, 360);
CalDirection1 = Direction + Offset;
CalDirection1 = Direction2 + Offset;

if(CalDirection1 > 360)
CalDirection1 = CalDirection1 - 360;

if(CalDirection1 < 0)
CalDirection1 = CalDirection1 + 360;
if(CalDirection2 > 360)
CalDirection2 = CalDirection2 - 360;

if(CalDirection2 < 0)
CalDirection2 = CalDirection2 + 360;

// Only update the display if change greater than 2 degrees.
if(abs(CalDirection1 - LastValue) > 5)
{
Serial.print(VaneValue); Serial.print("\t\t");
Serial.print(CalDirection1); Serial.print("\t\t");
getHeading(CalDirection1);
LastValue = CalDirection1;
}
if(abs(CalDirection2 - LastValue2) > 5)
{
Serial.print(VaneValue2); Serial.print("\t\t");
Serial.print(CalDirection2); Serial.print("\t\t");
getHeading(CalDirection2);
LastValue2 = CalDirection2;
}

Rotations1 = 0; // Set Rotations count to 0 ready for calculations
// Rotations2 = 0; // Set Rotations count to 0 ready for calculations

sei(); // Enables interrupts
delay (3000); // Wait 3 seconds to average
cli(); // Disable interrupts

// build the data string
dataString = String(Rotations1) + "," + String(CalDirection1) ; // convert to CSV
//  sprintf (timestamp, "%4d-%02d-%02d %02d:%02d:%02d", year(), month(),day(), hour(), minute(), second());
  // Serial.println(timestamp);
saveData(); // save to SD card
delay(2000); // delay before next write to SD Card, adjust as required

}

// Converts compass direction to heading
void getHeading(int direction) {
if(direction < 22)
Serial.println("N");
else if (direction < 67)
Serial.println("NE");
else if (direction < 112)
Serial.println("E");
else if (direction < 157)
Serial.println("SE");
else if (direction < 212)
Serial.println("S");
else if (direction < 247)
Serial.println("SW");
else if (direction < 292)
Serial.println("W");
else if (direction < 337)
Serial.println("NW");
else
Serial.println("N");
}



/*
Writing Sensor Data to an SD card
//
This example shows how to write data
to an SD card using the SD library.
//
The circuit:
* SD card attached to SPI bus as follows:
** MOSI - pin 11
** MISO - pin 12
** CLK - pin 13
** CS - pin 10 Uno (53 on Mega)
Based on code by Tom Igoe
*/
//

//

void saveData(){
if(SD.exists("datawind.csv")){ // check the card is still there
// now append new data file
sensorData = SD.open("datawind.csv", FILE_WRITE);
if (sensorData){
sensorData.println(dataString);
sensorData.close(); // close the file
}
}
else{
Serial.println("Error writing to file !");
}
}
