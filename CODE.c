#include <Servo.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include<LiquidCrystal.h>
const int rs=12, en=11, d4=5, d5=4, d6=3, d7=2 ;
const int in=8,out=10;
int temp=0,i,o;

LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

Servo myservo1;  


#define SDA A4
#define SCL A5
int pos1,pos2;

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  pinMode(in,INPUT);
  pinMode(out,INPUT);
  lcd.print("Hi Welcome!");

  pinMode(SDA,INPUT);
  pinMode(SCL,OUTPUT);
  myservo1.attach(7);  
  myservo1.write(90);
  mlx.begin();  
 lcd.begin(2,16);


}


void loop() {
         
        //LiquidCrystal_I2C lcd(0x27,20,4);
  
        int montion = digitalRead(SDA);
        
        if(montion == 1){
          
          Serial.print("Ready");
          Serial.print("\n");
          lcd.setCursor(0,0);
          lcd.print("ObjectTemp:");
          lcd.setCursor(0,1);
          lcd.print(" Place your fist "); 
          delay(2000);         
          lcd.clear();
          kaiguan();
          }

          i=digitalRead(in);
          delay(1000);
  Serial.println("i");
  Serial.println(i);
  delay(1000);
  Serial.println("o");
  Serial.println(o);
  
  o=digitalRead(out);
if(i==1)
  { 
    if (temp<=4&&temp>=0)
    {
    temp=temp+1;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Person Entering");
    Serial.println("Person Entering");
    lcd.setCursor(1,1);
    
     lcd.print(temp);
     Serial.println(temp);
     delay(2000); 
     }
     }
if(o==1)
{
  if (temp>=0&&temp<=4)
    {   
   temp=temp-1;
   lcd.clear();
    lcd.setCursor(0,1);
     lcd.print("Person Leaving");
     Serial.println("Person Leaving");
   lcd.setCursor(1,1);
   lcd.print(temp);
   Serial.println(temp);
      delay(1000);
    }
  
}
           
}
          
void kaiguan(){
  
   int temp_obj = mlx.readObjectTempF();
   Serial.print(temp_obj);
   Serial.print("\n");
   if(temp_obj < 87)
   {
   lcd.setCursor(0,1);
   lcd.print(temp_obj);
   delay(500);
   Serial.print(temp_obj);
   lcd.setCursor(0,2);
   lcd.print("Not detected");
              
   }
   if(temp_obj > 86 && temp_obj <102)
     {  
      lcd.setCursor(0,1);
     lcd.print("F");
     delay(2000);
     lcd.setCursor(0,13);
     lcd.print(temp_obj);
     Serial.print(temp_obj);
     //execute for IR sensor 
     for(pos1 = 90; pos1 <= 180; pos1 += 1)
     {                                 
      myservo1.write(pos1);         
      delay(15);
       }
      delay(2000);

     for(pos1 = 180; pos1>=90; pos1 -=1)
      {
      myservo1.write(pos1);
           
      delay(15);                     
      }

      } 
     else  if(temp_obj>101)
      {
      analogWrite(SDA,HIGH);
      lcd.setCursor(0,1);
      lcd.print(temp_obj);
      Serial.print(temp_obj);
      lcd.setCursor(0,2); 
      lcd.print("     Keep out!       ");
      delay(1000);
     analogWrite(SDA,LOW);
     } 
      delay(2000);
            
      }
