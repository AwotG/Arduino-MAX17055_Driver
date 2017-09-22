#ifndef MAX17055_h
#define MAX17055_h

#include <Arduino.h>

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
    MAX17055(uint16_t batteryCapacity); //Constuctor allowing user to set capacity of battery
    
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



