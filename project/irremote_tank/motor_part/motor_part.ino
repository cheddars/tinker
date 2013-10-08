int switchPin = 2; // switch input
int leftMotor1Pin1 = 3; // pin 2 on L293D
int leftMotor1Pin2 = 4; // pin 7 on L293D
int rightMotor1Pin1 = 5; // pin 2 on L293D
int rightMotor1Pin2 = 6; // pin 7 on L293D
int leftEnablePin = 8; // pin 1 on L293D
int rightEnablePin = 9; // pin 1 on L293D

void setup() {
    // set the switch as an input:
    pinMode(switchPin, INPUT);

    // set all the other pins you're using as outputs:
    pinMode(leftMotor1Pin1, OUTPUT);
    pinMode(leftMotor1Pin2, OUTPUT);
    pinMode(rightMotor1Pin1, OUTPUT);
    pinMode(rightMotor1Pin2, OUTPUT);    
    pinMode(leftEnablePin, OUTPUT);
    pinMode(rightEnablePin, OUTPUT);    

    // set enablePin high so that motor can turn on:
    digitalWrite(leftEnablePin, HIGH);
    digitalWrite(rightEnablePin, HIGH);
}

void loop() {
    // if the switch is high, motor will turn on one direction:
    if (digitalRead(switchPin) == HIGH) {
        digitalWrite(leftMotor1Pin1, LOW); // set pin 2 on L293D low
        digitalWrite(leftMotor1Pin2, HIGH); // set pin 7 on L293D high
        digitalWrite(rightMotor1Pin1, LOW); // set pin 2 on L293D low
        digitalWrite(rightMotor1Pin2, HIGH); // set pin 7 on L293D high        
    }
    // if the switch is low, motor will turn in the opposite direction:
    else{
        digitalWrite(leftMotor1Pin1, HIGH); // set pin 2 on L293D high
        digitalWrite(leftMotor1Pin2, LOW); // set pin 7 on L293D low
        digitalWrite(rightMotor1Pin1, HIGH); // set pin 2 on L293D low
        digitalWrite(rightMotor1Pin2, LOW); // set pin 7 on L293D high                
    }
}
