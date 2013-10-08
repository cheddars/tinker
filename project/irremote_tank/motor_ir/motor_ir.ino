//인터럽트 서비스 루틴에 사용되는 변수인 경우 volatile 선언을 해준다.
volatile unsigned long time,new_time,old_time;
volatile unsigned char ir_check=1, IR_start=0;
volatile unsigned long mask=0x00000001, IR_rx_data=0x00000000, IR_code, before_value = 0x00000001;

const int switchPin = 12; // switch input
const int leftMotor1Pin1 = 3, leftMotor1Pin2 = 4; // 
const int rightMotor1Pin1 = 5, rightMotor1Pin2 = 6; // 
const int leftEnablePin = 8, rightEnablePin = 9; // 


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
    if (false) {
      backward(leftMotor1Pin1, leftMotor1Pin2);
      backward(rightMotor1Pin1, rightMotor1Pin2);        
    }
    // if the switch is low, motor will turn in the opposite direction:
    else if(false){
      forward(leftMotor1Pin1, leftMotor1Pin2);
      forward(rightMotor1Pin1, rightMotor1Pin2);
    }
}

void forward(int pin1, int pin2) {
    digitalWrite(pin1, HIGH); // set pin 2 on L293D low
    digitalWrite(pin2, LOW); // set pin 7 on L293D high 
}

void backward(int pin1, int pin2) {
    digitalWrite(pin1, LOW); // set pin 2 on L293D low
    digitalWrite(pin2, HIGH); // set pin 7 on L293D high 
}
