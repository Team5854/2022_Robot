char tf;

void setup() {
  // put your setup code here, to run once:
  pinMode(13,OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() >= 1){
    tf = Serial.read();
    if(tf == 't'){
      digitalWrite(13,HIGH);
      tf = "";
    }
    else if(tf == 'f'){
      digitalWrite(13,LOW);
      tf = "";
    }
  }
}
