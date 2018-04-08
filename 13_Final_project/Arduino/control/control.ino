
int value = 0;

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  value = Serial.read();

  if( value > '0' && value <= '9' ){
    value = value - '0';
    
    for(int i=0; i<value; i++){
        digitalWrite(2, HIGH);
        delay(100);
        digitalWrite(2, LOW);
        delay(100);
        digitalWrite(3, HIGH);
        delay(100);
        digitalWrite(3, LOW);
        delay(100);
        digitalWrite(9, HIGH);
        delay(100);
        digitalWrite(9, LOW);
        delay(100);
        digitalWrite(10, HIGH);
        delay(100);
        digitalWrite(10, LOW);
        delay(100);

        digitalWrite(9, HIGH);
        delay(100);
        digitalWrite(9, LOW);
        delay(100);
        digitalWrite(3, HIGH);
        delay(100);
        digitalWrite(3, LOW);
        delay(100);
        digitalWrite(2, HIGH);
        delay(100);
        digitalWrite(2, LOW);
        delay(100);

        digitalWrite(2, HIGH);
        digitalWrite(3, HIGH);
        digitalWrite(9, HIGH);
        digitalWrite(10, HIGH);
        delay(1000);
        digitalWrite(2, LOW);
        digitalWrite(3, LOW);
        digitalWrite(9, LOW);
        digitalWrite(10, LOW);
        delay(100);
    }

    Serial.flush();
    
  }

}


