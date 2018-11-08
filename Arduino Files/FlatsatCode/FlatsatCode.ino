#include <xSW01.h>
#include <xSL01.h>
#include <SSD1306Ascii.h>
#include <SSD1306AsciiWire.h>
#include <SSD1306init.h>
#include <xOD01.h>
#include <xConfig.h>
#include <xCore.h>
#include <xVersion.h>

void setup() {
  Wire.begin(2,14);     //Starts the xChips talking to each other
  Serial.begin(9600);   //Define serial monitor connection parameters

  OLED.begin();         //Turn on the OLED Screen
  SL01.begin();         //Turn on the light sensor
  SW01.begin();         //Turn on the temperature/humidity/pressure/altitude sensor

  while (!Serial.available()){  //Wait for serial monitor to be opened.
    delay(1000);
  }

//This prints to the serial monitor   
  Serial.println("    Connection Established    ");
  Serial.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");

  Serial.println("Type 'a' for UVA, 'b' for UVB, 'c' for Altitude, 'd' for Pressure, 'e' for Light, 'f' for Humidity, 'g' Temperature");                 //Initial prompt
  Serial.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");    //Decorative divider

  OD01.clear();   //Clear OLED screen
  OD01.set2X();   //Set font size
  delay(1000);
  
}

void loop() {
  if (Serial.available() > 0) {   //If the serial monitor is open, do the following
    int text = Serial.read();     //Get text from user
    SL01.poll();                  //Read data from SL01 sensor
    SW01.poll();

    switch(text){
    //Depending on input text, do one of the following
      case 'a':
        Serial.println("UVA Intensity: ");
        Serial.print(SL01.getUVA());
        Serial.println(" microWatts/cm^2");
        Serial.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        break;
      case 'b':
        Serial.println("UVB Intensity: ");
        Serial.print(SL01.getUVB());
        Serial.println(" microWatts/cm^2");
        Serial.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        break;
      case 'c':
      //Display Pressure
        Serial.println("Pressure: ");
        Serial.print(SW01.getPressure()/100);   //display the Pressure
        Serial.println(" hPa");
        Serial.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        break;
      case 'd':
      //Display Altitude
        Serial.println("Altitude:");
        Serial.print(SW01.getAltitude()); //Display the altitude on the OLED screen
        Serial.println(" m above the sea");
        Serial.println();Serial.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        break;
      case 'e':
        Serial.println("Light Level: ");  
        Serial.print(SL01.getLUX());      //Read information from sensor and print it
        Serial.println(" LUX");
        Serial.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        break;
      case 'f':
        Serial.println("Humidity: ");
        Serial.print(SW01.getHumidity());
        Serial.println(" %");
        Serial.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        break;
      case 'g': 
        Serial.println("Temperature: ");
        Serial.print(SW01.getTemperature_F());
        Serial.println(" Degrees F");
        Serial.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");   
        break;
        
    }
  }

}
