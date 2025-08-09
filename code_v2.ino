#include <Wire.h>
#include <Adafruit_VL53L0X.h>
#include <LiquidCrystal_I2C.h>
#include <TM1637Display.h>

//Define pins for TM1637
#define CLK 3
#define DIO 2
//Define pin for button
#define BUTTON_PIN 4

TM1637Display display7seg(CLK, DIO); //display7seg is the object that controlls TM1637
LiquidCrystal_I2C lcd(0x27, 16, 2); //lcd is the object that controlls LCD, with I2C direction 0x27 and size 16x2
Adafruit_VL53L0X lox = Adafruit_VL53L0X(); //lox is the object that controlls VL53L0X

const float UMBRAL_SALTO = 20.0; //Minimum distance for detecting that there is nothing above the sensor (2cm = 20mm)
enum Estado { ESPERA, ESPERANDO_SALTO, MIDENDO }; //Defines the states of the program
Estado estado = ESPERA; //estado stores the value of the state of the program

bool enVuelo = false; //Boolean value that indicated if you are flying
unsigned long tiempoInicio = 0; //Moment when the fly starts
float distancia = 0; //Last measurement from the sensor

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP); //Configure pin_4 as an internal resistance

  lcd.init(); //Powers on the LCD
  lcd.backlight(); //Powers on the LCD backlight
  display7seg.clear(); //Clears the TM1637 display
 
  lcd.setCursor(0, 0); 
  lcd.print("JUMPING TRACKER");
  lcd.setCursor(0, 1);
  lcd.print("Press button...");

  if(!lox.begin()) { //Powers VL53L0X and if it gives an error, it prints it on LCD screen
    lcd.clear();
    lcd.print("VL53L0X ERROR");
    while(1);
  }
}

void loop() {
  VL53L0X_RangingMeasurementData_t medida; //Creates an stratuctre called "medida" to store data from the VL53L0X
  lox.rangingTest(&medida, false); //Reads the distance
  if(medida.RangeStatus == 0) { //If RangeStatus is =0, the measurement is valid and it is stored in mm
    distancia = medida.RangeMilliMeter;
  }

  switch (estado) {
    case ESPERA:
      if(digitalRead(BUTTON_PIN) == LOW) { //Waits till I press the button
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Ready...");
        delay(500); 
        estado = ESPERANDO_SALTO;
      }
      break;

    case ESPERANDO_SALTO:
      if(distancia > UMBRAL_SALTO) { //If the distance is bigger than 2cm
        enVuelo = true;
        tiempoInicio = millis();
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Jumping...");
        estado = MIDENDO;
      }
      break;

    case MIDENDO:
      if(distancia <= UMBRAL_SALTO && enVuelo) { //If the distance is <= 2cm and the enVuelo is still true
        enVuelo = false;
        unsigned long tiempoVuelo = millis() - tiempoInicio; //Calculate time of flight

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Flight Time:");
        lcd.setCursor(0, 1);
        lcd.print(tiempoVuelo);
        lcd.print(" ms");

        display7seg.showNumberDec(tiempoVuelo, false); //Shows the value in the 7seg display
        delay(3000); //Shows the value for 3 seconds
        display7seg.clear(); //Clears the 7seg display

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("JUMPING TRACKER");
        lcd.setCursor(0, 1);
        lcd.print("Press button...");
        estado = ESPERA;
      }
      break;
  }
}