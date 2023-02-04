float RPS_prev=0;


#define encoderZ 2

float RPS=0;
long counter = 0;
long lastTime = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(encoderZ, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), do_task, RISING);
  // pinMode(3,OUTPUT);
  // pinMode(A0, INPUT); 
  pinMode(LED_BUILTIN, OUTPUT); 
  pinMode(8, OUTPUT); 
  
}

void do_task() {
  counter++;
}

void loop() {
  // put your main code here, to run repeatedly:
RPS_prev=RPS;
  if (millis() - lastTime > 100) {
    RPS = ((double) counter)/(millis() - lastTime)*1000*60;
    lastTime = millis();
    counter = 0;
  }
  // counter = 0;
  // Serial.print("Counter = ");
  // Serial.print(counter);
  // Serial.print(" RPM = ");
  RPS = RPS/(1024*2);
  // Serial.write(RPS);
  char buffer[100];

  // print "My age is " and age variable to buffer variable
  if(RPS>130)
{  
  // digitalWrite(3, HIGH);
   Serial.write("brakeapplied");

  //  Serial.write(buffer);
}
  else if(RPS<130 && RPS_prev>130)
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

}


// void setup()
// {

// }

// void loop()
// {
//  while(!Serial.available()); 
//   String data;
//   data=Serial.readString();
//   Serial.println(data);
//   // Serial.println(typeof(data));
//  if(data[0]=='1')
//  {
//  digitalWrite(8,HIGH );
// //  Serial.println('1');
//  }
//  else if(data[0]=='0')
//  {
// //  Serial.println('0');
//  digitalWrite(8,LOW );
//  }
//  else{
//     Serial.println("else");

//     digitalWrite(LED_BUILTIN,HIGH );
// delay(1000);
//     digitalWrite(LED_BUILTIN,LOW );

//  }
// // delay(1000);
 
// }

