/**********************************************************************
*
* MIT License
*
* Copyright (c) 2018 Awot Ghirmai
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
* 
* Authors: 
* Awot Ghirmai; ghirmai.awot@gmail.com
* 
**********************************************************************/

#include <Arduino-MAX17055_Driver.h>
#include <Wire.h>

MAX17055 sensor;

void setup() {
  //Important that Wire and Serial initialize before using the MAX17055 Library
  Wire.begin();
  Serial.begin(9600);
  delay(500); //Just a small delay before first communications to MAX chip
  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }
  
  //only call if you are not using the default internal resistor
  //sensor.setResistSensor(0.02); 
  sensor.setCapacity(4500);
}

void loop() {
  Serial.println("Using the 'Get' functions \n\n");

  Serial.println("Get Capacity");
  float capacity = sensor.getCapacity();
  Serial.print("Capacity of plugged in battery is: ");
  Serial.print(capacity, 4);
  Serial.println(" mAH \n\n");
  delay(5000);

  Serial.println("Get Resist Sensor");
  float resistSensorValue = sensor.getResistSensor();
  Serial.print("Resist sensor value is: ");
  Serial.print(resistSensorValue, 4);
  Serial.println(" ohm \n\n");
  delay(5000);

  Serial.println("Get State of Charge");
  float SOC = sensor.getSOC();
  Serial.print("State of Charge value is: %");
  Serial.println(SOC, 4);
  Serial.println("\n\n");
  delay(5000);

  Serial.println("Get instantaneous voltage");
  float voltage = sensor.getInstantaneousVoltage();
  Serial.print("Instantaneous Voltage is: ");
  Serial.print(voltage, 4);
  Serial.println(" V \n\n");
  delay(5000);

  Serial.println("Get instantaneous current");
  float current = sensor.getInstantaneousCurrent();
  Serial.print("Instantaneous Current is: ");
  Serial.print(current, 4);
  Serial.println(" mA \n\n");
  delay(5000);

  Serial.println("Get time to empty");
  float TTE = sensor.getTimeToEmpty();
  Serial.print("Time to empty is: ");
  Serial.print(TTE, 4);
  Serial.println(" Hours \n\n");
  delay(5000);
}
=======
#include <MAX17055.h>
#include <Wire.h>

MAX17055 sensor;

void setup() {
  //Important that Wire and Serial initialize before using the MAX17055 Library
  Wire.begin();
  Serial.begin(9600);
  delay(500); //Just a small delay before first communications to MAX chip
  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }
  
  //only call if you are not using the default internal resistor
  //sensor.setResistSensor(0.02); 
  sensor.setCapacity(4500);
}

void loop() {
  Serial.println("Using the 'Get' functions \n\n");

  Serial.println("Get Capacity");
  float capacity = sensor.getCapacity();
  Serial.print("Capacity of plugged in battery is: ");
  Serial.print(capacity, 4);
  Serial.println(" mAH \n\n");
  delay(5000);

  Serial.println("Get Resist Sensor");
  float resistSensorValue = sensor.getResistSensor();
  Serial.print("Resist sensor value is: ");
  Serial.print(resistSensorValue, 4);
  Serial.println(" ohm \n\n");
  delay(5000);

  Serial.println("Get State of Charge");
  float SOC = sensor.getSOC();
  Serial.print("State of Charge value is: %");
  Serial.println(SOC, 4);
  Serial.println("\n\n");
  delay(5000);

  Serial.println("Get instantaneous voltage");
  float voltage = sensor.getInstantaneousVoltage();
  Serial.print("Instantaneous Voltage is: ");
  Serial.print(voltage, 4);
  Serial.println(" V \n\n");
  delay(5000);

  Serial.println("Get instantaneous current");
  float current = sensor.getInstantaneousCurrent();
  Serial.print("Instantaneous Current is: ");
  Serial.print(current, 4);
  Serial.println(" mA \n\n");
  delay(5000);

  Serial.println("Get time to empty");
  float TTE = sensor.getTimeToEmpty();
  Serial.print("Time to empty is: ");
  Serial.print(TTE, 4);
  Serial.println(" Hours \n\n");
  delay(5000);
}
