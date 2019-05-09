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
* Ole Dreessen; ole.dreessen@maximintegrated.com
* 
**********************************************************************/

#ifndef Arduino-MAX17055_Driver.h_h
#define Arduino-MAX17055_Driver.h_h

#include <Arduino.h>

/**********************************************************************
* @brief MAX17055 - The MAX17055 is a low 7μA operating current fuel gauge that implements 
* Maxim ModelGauge™ m5 EZ algorithm. ModelGauge m5 EZ makes fuel gauge implementation
* easy by eliminating battery characterization requirements and simplifying host software interaction. 
* The ModelGauge m5 EZ robust algorithm provides tolerance against battery diversity for most 
* lithium batteries and applications. ModelGauge m5 EZ algorithm combines the short-term
* accuracy and linearity of a coulomb counter with the longterm stability of a voltage-based fuel 
* gauge, along with temperature compensation to provide industry-leading fuel gauge accuracy. 
* The MAX17055 automatically compensates for cell aging, temperature, and discharge rate, and 
* provides accurate state of charge (SOC in %) and remaining capacity in milliampere-hours (mAh). 
* As the battery approaches the critical region near empty, the ModelGauge m5 algorithm invokes 
* a special compensation that eliminates any error. It also provides three methods for reporting 
* the age of the battery: reduction in capacity, increase in battery resistance, and cycle odometer.
* The MAX17055 provides precision measurements of current, voltage, and temperature. Temperature 
* of the battery pack is measured using an internal temperature measurement or external thermistor. 
* A 2-wire I2C interface provides access to data and control registers. The MAX17055 is available 
* in a tiny, lead-free 0.4mm pitch 1.4mm x 1.5mm, 9-pin WLP package, and a 2mm x 2.5mm, 10-pin 
* TDFN package.
*
* Resources can be found at
* https://www.maximintegrated.com/en/products/power/battery-management/MAX17055.html
* https://www.maximintegrated.com/en/app-notes/index.mvp/id/6365
* https://www.maximintegrated.com/en/app-notes/index.mvp/id/6358
**********************************************************************/

// Currently, code only displays register values in hexadecimal format. User needs to state which register they're addressing by hand
// in the ino file.

class MAX17055
{
  public:
    // register addresses 
    enum regAddr
    {
      Status      = 0x00, //Maintains all flags related to alert thresholds and battery insertion or removal.
      VCell       = 0x09, //VCell reports the voltage measured between BATT and CSP.
      AvgVCell    = 0x19, //The AvgVCell register reports an average of the VCell register readings. 
      Current     = 0x0A, //Voltage between the CSP and CSN pins, and would need to convert to current
      AvgCurrent  = 0x0B, //The AvgCurrent register reports an average of Current register readings
      RepSOC      = 0x06, //The Reported State of Charge of connected battery. Refer to AN6358 page 23 and 13
      RepCap      = 0x05, //Reported Capacity. Refer to page 23 and 13 of AN6358.
      TimeToEmpty = 0x11, //How long before battery is empty (in ms). Refer to page 24 and 13 of AN6358 
      DesignCap   = 0x18, //Capacity of battery inserted, not typically used for user requested capacity
    };
    //variables
    
    
    //methods
    MAX17055(void); //Constructor prototype
    MAX17055(uint16_t batteryCapacity); //Constructor allowing user to set capacity of battery
    
    float getInstantaneousCurrent();
    float getInstantaneousVoltage();
    void  setCapacity(uint16_t batteryCapacity);
    float getCapacity();
    void  setResistSensor(float resistorValue); 
    float getResistSensor(); 
    float getSOC(); //SOC = State of Charge 
    float getTimeToEmpty();

private:
    //variables
    float resistSensor = 0.01; //default internal resist sensor
    uint8_t I2CAddress = 0x36;
    
    //Based on "Standard Register Formats" AN6358, figure 1.3. 
    //Multipliers are constants used to multiply register value in order to get final result
    float capacity_multiplier_mAH = (5e-3)/resistSensor; //refer to row "Capacity"
    float current_multiplier_mV = (1.5625e-3)/resistSensor; //refer to row "Current"
    float voltage_multiplier_V = 7.8125e-5; //refer to row "Voltage"
    float time_multiplier_Hours = 5.625/3600.0; //Least Significant Bit= 5.625 seconds, 3600 converts it to Hours. refer to AN6358 pg 13 figure 1.3 in row "Time"
    float percentage_multiplier = 1.0/256.0; //refer to row "Percentage"
    
    //methods
    uint16_t readReg16Bit(uint8_t reg);
    void writeReg16Bit(uint8_t reg, uint16_t value);
   };

#endif



