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