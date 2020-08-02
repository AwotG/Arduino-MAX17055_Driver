# Arduino driver for MAX17055 Fuel Gauge Sensor

The MAX17055 is a low power (7μA) IC that makes monitoring lithium batteries easier for the end user. The IC handles alot of calculations under the hood so that you can focus on just the stats you want (i.e. Average current/voltage over time, instantaneous current/voltage, battery capacity, state of charge (percentage of battery left) along with other features.

More advanced features could include terminating system functionaity if MAX17055 detects that there isn't enough power, or switching your overall system to power saving mode. 

## Prerequisites 
- Ability to solder 
- Knowledge of importing external Arduino libraries in your .ino file


## What you'll need

##### Hardware
- Computer (PC/Mac/Linux)
- Arduino Uno
- [MAX17055 Evaluation Kit](https://www.digikey.com/catalog/en/partgroup/max17055-evaluation-kit/67117)
- Logic Level Converter (I used [sparkfun's](https://www.sparkfun.com/products/12009))
- Jumper wires (a combination of Male-Male and Male-Female connectors)
- Breadboard
- Lithium ion battery (I used this [sparkfun](https://www.sparkfun.com/products/13813) one)
- [JST Connector](https://www.sparkfun.com/products/9749) (if using sparkfun lithium ion battery above)
- 3-5V Power source for MAX17055 Evaluation board (if not using Arduino Uno)

##### Software
- Arduino IDE


### Getting the hardware setup
You will first need to solder on the headers to the MAX17055 Evaluation kit. I'd recommend soldering all of them, though for this you will only be using the:
- I2C pins (SDA/SCL)
- System Power (SYSPWR/SYSGND)
- Battery Connections (PACK+/PACK-)

Next will be soldering on the headers for the Logic Level Converter.

Once those are complete, you will then need to connect the Arduino, Logic Level Converter and MAX17055 Eval board. Here is what the pinout should look like:

**Key used for Pinout**

**Full Name** | **Abbreviation Used**
:-----:|:-----:
Arduino|A
Logic Level Converter|LLC
MAX17055 Evaluation Board|Max

**Pinout**

**Output**|**Input**
:-----:|:-----:
3.3V (A)|LV (LLC), SYSPWR (Max)
5V (A)|HV (LLC)
GND (A)|GND (LLC, HV side), GND (LLC, LV side), SYSGND (Max)
A4 (A)|HV1 (LLC)
A5 (A)|HV4 (LLC)
LV1 (LLC)|SDA (Max)
LV4 (LLC)|LV4 (LLC)



`float instantaneousCurrent();`
**Return type represents: mA**
Gives the amount of current being used by the battery in that moment. If implementing this to continuously get readings, consider a reasonable delay time (i.e 0.5 seconds)

`float instantaneousVoltage();`
**Return type represents: V**
Gives the current Voltage of the plugged in battery. If implementing this to continuously get readings, consider a reasonable delay time (i.e 0.5 seconds)

`void  setCapacity(uint16_t batteryCapacity);`
**No return type.** 
**Input represents: mAH**
Set the capacity of your battery to the MAX17055 chip. This is important in accurately calculating many of the chips data points (battery life, current percentage of power left etc)

`float getCapacity();`
**Return type represents: mAH**
Get what the MAX17055 considers the capacity of the battery is. You need to set this, because it will make a guess otherwise

`void  setResistSensor(float resistorValue);` 
**No return type.** 
**Input represents: ohm**
Resist sensor is important in calculating the voltage and current (aong with all other stats tied to it). If you are not using the default internal sensor, and have wired up an internal one, you would need to set the correct value so that you are getting accurate readings when checking voltage, current, state of charge etc

`float getResistSensor();` 
**Return type represents: ohms**
Resist sensor is important in calculating the voltage and current (aong with all other stats tied to it). By default, the MAX17055 chip has an internal 0.01 ohm resistor, which this library has set to.

`float getSOC();` 
**Return type represents: Percentage**
Get the current State of Charge of the battery. This is the percentage of power left in the battery, and is based on average current usage, total capacity and a few other factors. This percentage becomes more accurate as you go through discharge/charge cycles. 

`float timeToEmpty();`
**Return type represents: Hours**
Estimated time before battery reaches empty capacity. This is given in Hours

## Example Code
Before running the code, make sure that everything is wired up (follow pinouts above).

**Note:** This code is just a small portion of the MAX17055_example.ino file. It gives you a basic idea of how to use the library. Run the full example to test out the other features.

```c++
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
}
```
## Versioning
We use [SemVer](http://semver.org/) for versioning.

### Current version: 
1.0.1: adoptions to meet the specs for the built-in Arduino Library Manager

### History:
1.0.0: Initial work

## Authors
* **Awot Ghirmai** - *Initial work* - [AwotG](https://github.com/AwotG)
* **Ole Dreessen** - *Arduino library adoptions* - [amperpirat](https://github.com/amperpirat)

## License

This project is licensed under the MIT  License - see the [LICENSE.md](LICENSE.md) file for details.








