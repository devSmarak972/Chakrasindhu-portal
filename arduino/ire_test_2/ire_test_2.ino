float RPM_prev=0;
#define THRESH 130
// #define encoderZ 2
// float RPS=0;
long counter = 0;
long lastTime = 0;
// Motor encoder output pulses per 360 degree revolution (measured manually)
#define ENC_COUNT_REV 620
 
// Encoder output to Arduino Interrupt pin. Tracks the pulse count.
#define ENC_IN_RIGHT_A 2
 
// Other encoder output to Arduino to keep track of wheel direction
// Tracks the direction of rotation.
#define ENC_IN_RIGHT_B 4
 
// True = Forward; False = Reverse
boolean Direction_right = true;
 
// Keep track of the number of right wheel pulses
volatile long right_wheel_pulse_count = 0;
 
// One-second interval for measurements
int interval = 1000;
  
// Counters for milliseconds during interval
long previousMillis = 0;
long currentMillis = 0;
 
// Variable for RPM measuerment
float rpm_right = 0;
 
// Variable for angular velocity measurement
float ang_velocity_right = 0;
float ang_velocity_right_deg = 0;
 
const float rpm_to_radians = 0.10471975512;
const float rad_to_deg = 57.29578;
 
void setup() {
 
  // Open the serial port at 9600 bps
  Serial.begin(9600); 
 
  // Set pin states of the encoder
  pinMode(ENC_IN_RIGHT_A , INPUT_PULLUP);
  pinMode(ENC_IN_RIGHT_B , INPUT);
   pinMode(LED_BUILTIN, OUTPUT); 
  pinMode(8, OUTPUT); 
  
  // Every time the pin goes high, this is a pulse
  attachInterrupt(digitalPinToInterrupt(ENC_IN_RIGHT_A), right_wheel_pulse, RISING);
   
}
 
void loop() {
 RPM_prev=RPM;
  // Record the time
  currentMillis = millis();
 
  // If one second has passed, print the number of pulses
  if (currentMillis - previousMillis > interval) {
 
    previousMillis = currentMillis;
 
    // Calculate revolutions per minute
    rpm_right = (float)(right_wheel_pulse_count * 60 / ENC_COUNT_REV);
    ang_velocity_right = rpm_right * rpm_to_radians;   
    ang_velocity_right_deg = ang_velocity_right * rad_to_deg;
     
 
    right_wheel_pulse_count = 0;
   
  }
   if(rpm_right>THRESH)
  {  
  // digitalWrite(3, HIGH);
   Serial.write("brakeapplied");

  //  Serial.write(buffer);
  }
  else if(rpm_right<THRESH && RPM_prev>THRESH)
  {
      // sprintf(buffer, "brakestopped:%f;%d",RPS,counter);

  //  Serial.write(buffer);
   Serial.write("brakestopped");
  // digitalWrite(3, LOW);
  }
  if(Serial.available()){
  String data;
  data=Serial.readString();
  Serial.println(data);
  // Serial.println(typeof(data));
   if(data[0]=='1')
   {
  digitalWrite(8,HIGH );
  Serial.write("applying brakes ..");
 //  Serial.println('1');
 }
 else if(data[0]=='0')
 {
//  Serial.println('0');
 digitalWrite(8,LOW );
 Serial.write("stopping brakes ..");

 }
 else{
    Serial.println("else");
    digitalWrite(LED_BUILTIN,HIGH );
    delay(1000);
    digitalWrite(LED_BUILTIN,LOW );

 }
  
}








  


 
// Increment the number of pulses by 1
void right_wheel_pulse() {
   
  // Read the value for the encoder for the right wheel
  int val = digitalRead(ENC_IN_RIGHT_B);
 
  if(val == LOW) {
    Direction_right = false; // Reverse
  }
  else {
    Direction_right = true; // Forward
  }
   
  if (Direction_right) {
    right_wheel_pulse_count++;
  }
  else {
    right_wheel_pulse_count--;
  }
}
 