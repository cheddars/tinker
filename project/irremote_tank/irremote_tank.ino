// / / IR receive : KSM-603LM
// / / NEC format remote control
// / / 603LM pin1 - Arduino digital pin 2 (external interrupt 0) IR Signal
// / / 603LM pin2 - GND
// / / 603LM pin3 - VCC(5V)
//인터럽트 서비스 루틴에 사용되는 변수인 경우 volatile 선언을 해준다.
volatile unsigned long time,new_time,old_time;
volatile unsigned char ir_check=1, IR_start=0;
volatile unsigned long mask=0x00000001, IR_rx_data=0x00000000, IR_code, before_value = 0x00000001;

int motor_left = 0;
int motor_right = 0;
const int leftMotor1Pin = 3;    // H-bridge leg 1 (pin 2, 1A)
const int leftMotor2Pin = 4;    // H-bridge leg 2 (pin 7, 2A)
const int rightMotor1Pin = 5;    // H-bridge leg 1 (pin 2, 1A)
const int rightMotor2Pin = 6;    // H-bridge leg 2 (pin 7, 2A)  
const int irvcc = 8;
const int ledPin = 13;
const int FORWARD = 1;
const int STOP = 0;
const int BACKWARD = -1;

void setup(){
  Serial.begin(9600);
 // pinMode(leftMotor1Pin, OUTPUT); 
 // pinMode(leftMotor2Pin, OUTPUT); 
 // pinMode(rightMotor1Pin, OUTPUT); 
//  pinMode(rightMotor2Pin, OUTPUT);   
//  pinMode(irvcc, OUTPUT);
  pinMode(ledPin, OUTPUT);

  attachInterrupt(0, IR_remote, FALLING);
}

void loop(){
//  digitalWrite(irvcc, HIGH);     // ir vcc ON
  while(ir_check);
  ir_check=1;
  digitalWrite(ledPin, HIGH);    // set the LED off
  delay(100);
  digitalWrite(ledPin, LOW);    // set the LED off
}

void IR_remote()
{
  char before_value_str[256];
  new_time = micros(); // 현재시간 저장
  time=new_time - old_time; // 엣지 사이의 시간 계산
  old_time=new_time; // 이전시간을 현재시간으로 갱신
  if(time > 13000 && time <14000) IR_start=1; // lead code 13.5ms의 리드코드를 확인합니다.
  else if(time > 9000 && time <12000) // repeat code 일때는 무시 입력은 1번만
  {
    Serial.println("R"); // repeat code 가 들어오면 LCD에 'R' 을 출력합니다.
    IR_start=0; // 변수 초기화
    mask=0x00000001;
    IR_rx_data=0x00000000;
  }else if(IR_start==1) // 리드코드가 들어 왔다면...
  {
    if(time > 1025 && time < 1225) // 1.125ms 0을 받습니다.
    {
      IR_rx_data &= ~mask;
      mask=mask<<1; // mask를 1비트씩 시프트 하면서 데이터를 쌓습니다.
    }
    else if(time > 2125 && time < 2325) // 2.25ms 1을 받습니다.
    {
      IR_rx_data |= mask;
      mask=mask<<1; // mask를 1비트씩 시프트 하면서 데이터를 쌓습니다.
    }
    if(mask==0) // mask가 모두 시프트되어 0이되면(32bit data를 모두 받으면.. )
    {
      IR_code = IR_rx_data;
//     snprintf(before_value_str, sizeof(before_value_str), "before %d",before_value );
//     Serial.println(before_value_str);
//      Serial.println(IR_code, HEX);
      if(before_value == IR_code){
        Serial.println("toggle");
        before_value = 0x00000001;
        motor_left = 0; 
        motor_right = 0;
      }else{
        if(IR_code == 0x280B87EE){          
          motor_left = FORWARD; 
          motor_right = FORWARD;        
          Serial.println("forward");
        }else if(IR_code == 0x280887EE){
          motor_left = BACKWARD; 
          motor_right = FORWARD;
          Serial.println("left");
        }else if(IR_code == 0x280787EE){
          motor_left = FORWARD; 
          motor_right = BACKWARD;
          Serial.println("right");
        }else if(IR_code == 0x280D87EE){
          motor_left = BACKWARD; 
          motor_right = BACKWARD;        
          Serial.println("backward"); 
        }else if(IR_code == 0x280487EE){
          motor_left = FORWARD; 
          motor_right = FORWARD;        
          Serial.println("center"); 
        }else if(IR_code == 0x280287EE){
           motor_left = 0; 
          motor_right = 0;       
          Serial.println("menu"); 
        }else if(IR_code == 0x280487EE){
          motor_left = FORWARD; 
          motor_right = FORWARD;        
          Serial.println("play"); 
        }
        before_value = IR_code;
      }
      
        switch(motor_left){
    case FORWARD:
      digitalWrite(leftMotor1Pin, HIGH);   // set leg 1 of the H-bridge low
      digitalWrite(leftMotor2Pin, LOW);  // set leg 2 of the H-bridge high 
      break;
    case STOP:
      digitalWrite(leftMotor1Pin, LOW);   // set leg 1 of the H-bridge low
      digitalWrite(leftMotor2Pin, LOW);  // set leg 2 of the H-bridge high     
      break;
    case BACKWARD:
      digitalWrite(leftMotor1Pin, LOW);   // set leg 1 of the H-bridge low
      digitalWrite(leftMotor2Pin, HIGH);  // set leg 2 of the H-bridge high   
      break;  
  }
    
  switch(motor_right){
    case 1:
      digitalWrite(rightMotor1Pin, HIGH);   // set leg 1 of the H-bridge low
      digitalWrite(rightMotor2Pin, LOW);  // set leg 2 of the H-bridge high 
      break;
    case 0:
      digitalWrite(rightMotor1Pin, LOW);   // set leg 1 of the H-bridge low
      digitalWrite(rightMotor2Pin, LOW);  // set leg 2 of the H-bridge high 
      break;
    case BACKWARD:
      digitalWrite(rightMotor1Pin, LOW);   // set leg 1 of the H-bridge low
      digitalWrite(rightMotor2Pin, HIGH);  // set leg 2 of the H-bridge high 
      break;
  }

      // 변수 초기화
      IR_start=0;
      mask=0x00000001;
      IR_rx_data=0x00000000;
      ir_check=0;
    }
  }
}


