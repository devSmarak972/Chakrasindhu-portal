
#define encoderZ 2

double RPS;
long counter = 0;
long lastTime = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(encoderZ, INPUT_PULLUP);
  attachInterrupt(0, do_task, RISING);
  pinMode(3,OUTPUT);
}

void do_task() {
  counter++;
}

void loop() {
  // put your main code here, to run repeatedly:

  if (millis() - lastTime > 100) {
    RPS = ((double) counter)/(millis() - lastTime)*1000*60;
    lastTime = millis();
    counter = 0;
  }
  // counter = 0;
  Serial.print("Counter = ");
  Serial.print(counter);
  Serial.print(" RPM = ");
  RPS = RPS/(1024*2);
  Serial.println(RPS);
  if(RPS>130)
  digitalWrite(3, HIGH);
  
  else
  digitalWrite(3, LOW);


}
