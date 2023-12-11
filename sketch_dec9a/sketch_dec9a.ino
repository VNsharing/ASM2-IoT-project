#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define LCD_I2C_ADDRESS 0x27 
#define LCD_DISP_COLS   16
#define LCD_DISP_ROWS   2
#define LCD_RESET -1

#define DHTPIN 2          // Digital pin 2
#define DHTTYPE DHT11     // DHT 11

LiquidCrystal_I2C lcd( LCD_I2C_ADDRESS, LCD_DISP_COLS, LCD_DISP_ROWS );


int gasLevel = 0;        
String quality ="";
DHT dht(DHTPIN, DHTTYPE);

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
  Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
lcd.clear();
lcd.setCursor (0,0);
lcd.print("Temp: ");
lcd.setCursor(7,0);
lcd.print(t);
lcd.setCursor (12,0);
lcd.print("*C");
lcd.setCursor (0,1);
lcd.print("RH  : ");
lcd.setCursor(7,1);
lcd.print(h);
lcd.setCursor (12,1);
lcd.print("%");
}

void air_sensor()
{
  gasLevel = analogRead(A0);

  if(gasLevel<182){
    quality = "  GOOD!";
  }
  else if (gasLevel >182 && gasLevel<225){
    quality = "  Poor!";
  }
  else if (gasLevel >225 && gasLevel<300){
    quality = "Very bad!";
  }
    else if (gasLevel >300 && gasLevel<350){
    quality = "ur dead!";
  }
    else{
    quality = " Toxic";   
}
  
lcd.clear();
lcd.setCursor (0,0);
lcd.print("Air Quality  ");
lcd.setCursor (3,1);
lcd.print(quality);
}




void setup() {
  Serial.begin(9600);                   
  dht.begin();
  lcd.init();
  lcd.init();

  lcd.backlight();
                   
  lcd.setCursor (0,0);                  
  lcd.print("                ");
  lcd.setCursor (0,1);
  lcd.print("                ");
  lcd.setCursor (0,0);
  lcd.print("  AIR QUALITY  ");
  lcd.setCursor (0,1);
  lcd.print("    MONITOR   ");
  delay(5000);                         
  
}

void loop() {
lcd.clear();
air_sensor();
delay(5000);
sendSensor();
delay(5000);
}
