
#include <Servo.h>

Servo servoMotor;

void setup() {
//  Iniciamos el monitor serie para mostrar el resultado
  Serial.begin(9600);

//  Iniciamos el servo para que empiece a trabajar junto con el pin 5
//  pinMode(5, OUTPUT);
  pinMode(6, INPUT);
  servoMotor.attach(5);
}

int value;

void loop() {

    if(digitalRead(6) == HIGH)
      servoMotor.write(0);
    else
      servoMotor.write(360);

/*    for(int i=0; i<=180; i++){
      servoMotor.write(i);
      delay(50);
    }

    for(int i=179; i>0; i--){
      servoMotor.write(i);
      delay(50);
    }
*/
    
}

