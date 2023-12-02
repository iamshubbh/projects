#include <LiquidCrystal.h>
#include <SoftwareSerial.h>


LiquidCrystal lcd(2, 3, 4, 5, 6,7);
const int buzzer_Pin = 8;
const int led_Pin = 9;
char sleep_status = 0;

void setup() {
  Serial.begin(9600);  
  pinMode(buzzer_Pin, OUTPUT);
  pinMode(led_Pin, OUTPUT);
  lcd.begin(16, 2);
  lcd.print("Driver Sleep ");
  lcd.setCursor(0,2);
  lcd.print("Detection SYSTEM");
  digitalWrite(buzzer_Pin, LOW); 
  digitalWrite(led_Pin, LOW);
}
SoftwareSerial GPRS(10, 11);   // RX, TX

void setup1() {
  Serial.begin(9600);
  GPRS.begin(9600); 
  delay(1000);
}

void loops() {
  // Send SMS
  GPRS.println("AT+CMGF=1"); // set message format to text mode
  delay(100);
  GPRS.println("AT+CMGS=\"9708145188\""); // set recipient's mobile number
  delay(100);
  GPRS.println("Driver is drowsy"); // message to be sent
  delay(100);
  GPRS.write(26); // Ctrl+Z character to end the message
  delay(1000);

  // Make call
  GPRS.println("ATD 9708145188;"); // call the specified mobile number
  delay(8000); // wait for 5 seconds
  GPRS.println("ATH"); // hang up the call
  delay(1000);

  while(1); // loop indefinitely
}
void loop() 
{
    while (Serial.available() > 0) 
  {
    sleep_status = Serial.read();
    if(sleep_status == 'a')
    { 
        lcd.clear();
        lcd.print("Please wake up");
        digitalWrite(buzzer_Pin, HIGH); 
        digitalWrite(led_Pin, HIGH);
        delay(2000);
        digitalWrite(buzzer_Pin, LOW); 
        digitalWrite(led_Pin, LOW);
        
        delay(100);
    }
    else if(sleep_status == 'b')
    {
        lcd.clear();
        lcd.print("All Ok");
        lcd.setCursor(0,2);
        lcd.print("Drive Safe");
        digitalWrite(buzzer_Pin, LOW); 
        digitalWrite(led_Pin, LOW);
        delay(2000);
    }
    else
    {
      /* Do Nothing */
    }
  }
}
