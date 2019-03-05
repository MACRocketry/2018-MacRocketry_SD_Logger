//main ====================================================================
#include <MacRocketry_GPS_Shield.h>
MacRocketry_GPS_Shield gps;
MacRocketry_SD_Logger sd;

void setup(){
}

int i = 0;
void loop() {
  if (gps.readData()){
    Serial.print(gps.data); //access NMEA data
    
    if (sd.writeFile(gps.data)){ //succesfully write data
      Serial.print("UTC: ");
      Serial.print(gps.utc); //access UTC [float]
      Serial.print(" Fix: ");
      Serial.print(gps.fix); //acess fix [int]
      Serial.print(" Altitude ");
      Serial.println(gps.altitude); //acess altitude [float]
    } else {
      Serial.println("Cannot write GPS");
    }
  } else {
    Serial.println("No data");
  }
  
  i++;
  if (sd.writeFile("data_" + String(i))){
    Serial.println(i);
  } else {
    Serial.println("Cannot write " + String(i));
  }
}
