//mode
#define COMBO_DIRECT_MODE 0x01
#define SINGLE_PIN_CONTINUOUS 0x2
#define SINGLE_PIN_TIMEOUT 0x3
#define SINGLE_OUTPUT 0x4

//PWM speed steps
#define PWM_FLT 0x0
#define PWM_FWD1 0x1
#define PWM_FWD2 0x2
#define PWM_FWD3 0x3
#define PWM_FWD4 0x4
#define PWM_FWD5 0x5
#define PWM_FWD6 0x6
#define PWM_FWD7 0x7
#define PWM_BRK 0x8
#define PWM_REV7 0x9
#define PWM_REV6 0xA
#define PWM_REV5 0xB
#define PWM_REV4 0xC
#define PWM_REV3 0xD
#define PWM_REV2 0xE
#define PWM_REV1 0xf

//speed
#define RED_FLT 0x0
#define RED_FWD 0x1
#define RED_REV 0x2
#define RED_BRK 0x3
#define BLUE_FLT 0x0
#define BLUE_FWD 0x4
#define BLUE_REV 0x8
#define BLUE_BRK 0xC


//channel
#define CH1 0x0
#define CH2 0x1
#define CH3 0x2
#define CH4 0x3

//output
#define RED 0x0
#define BLUE 0x1

int IRPin = 13;
int toggle[4] = {0,0,0,0};

void setup()
{
  pinMode(IRPin, OUTPUT);
  digitalWrite(IRPin, LOW);
  //Serial.begin(9600);
  //delay(2);
  
}

void loop()
{
  ComboMode(BLUE_REV, RED_FWD, CH1);
  delay(2000);
  
}

void pf_send(int code1, int code2)
{
  int x = 128;
  
  start_stop_bit();
  
  while (x)
  {
    oscillationWrite(IRPin, 156);
    
    if (code1 & x) //high bit
      high_pause();
    else //low bit
      low_pause();
    
    x >>= 1;  //next bit
  }
  
  x = 128;
  while (x)
  {
    oscillationWrite(IRPin, 156);
    
    if (code2 & x) // high bit
      high_pause();
    else //low bit
      low_pause();

    x >>= 1;  //next bit
  }
  
  start_stop_bit();
  delay(10);
}

void ComboMode(int blue_speed, int red_speed, int channel)
{
  int nib1, nib2, nib3, nib4, i;
   
  //set nibs
  nib1 = channel;
  nib2 = COMBO_DIRECT_MODE;
  nib3 = blue_speed | red_speed;
  nib4 = 0xf ^ nib1 ^ nib2 ^ nib3;

  for(i = 0; i < 6; i++)
  {
    message_pause(channel, i);
    pf_send(nib1 << 4 | nib2, nib3 << 4 | nib4);    
  }
}


void SingleOutput(int pwm, int output, int channel)
{
   int nib1, nib2, nib3, nib4, i;

   //set nibs
   nib1 = toggle[channel] | channel;
   nib2 = SINGLE_OUTPUT | output;
   nib3 = pwm;
   nib4 = 0xf ^ nib1 ^ nib2 ^ nib3;
   
   for(i = 0; i < 6; i++)
   {
     message_pause(channel, i);
     pf_send(nib1 << 4 | nib2, nib3 << 4 | nib4);    
   }
   
   if(toggle[channel] == 0)
     toggle[channel] = 8;
   else
     toggle[channel] = 0; 
}

void start_pause()
{
  delayMicroseconds(1014);
}

void high_pause()
{
  delayMicroseconds(546);
}

void low_pause()
{
  delayMicroseconds(260);
}

void tx_pause()
{
  delayMicroseconds(156);
}

void message_pause(int channel, int count)
{
  unsigned char a = 0;
  
  if(count == 0)
    a = 4 - channel + 1;
  else if(count == 1 || count == 2)
    a = 5;
  else if(count == 3 || count == 4)
    a = 5 + (channel + 1) * 2;
      
  delayMicroseconds(a * 77);
}


void start_stop_bit()
{
  oscillationWrite(IRPin, 156);  
  //digitalWrite(IRPin, HIGH);
  //tx_pause();
  //digitalWrite(IRPin, LOW);
  start_pause(); 
}

void oscillationWrite(int pin, int time) {
  for(int i = 0; i <= time/26; i++) {
    digitalWrite(pin, HIGH);
    delayMicroseconds(13);
    digitalWrite(pin, LOW);
    delayMicroseconds(13);
  }
}