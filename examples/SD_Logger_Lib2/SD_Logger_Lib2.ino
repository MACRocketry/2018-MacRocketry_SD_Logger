#include <MacRocketry_SD_Logger.h>
#include <MacRocketry_GPS_Shield.h>

MacRocketry_SD_Logger sd;
MacRocketry_GPS_Shield gps;

void setup() {
  Serial.begin(115200);
  if (sd.connectSD){
    Serial.println("SD recognized");
  } else {
    Serial.println("no SD input");
  }

  if (sd.connectFile){
    Serial.println("File IO");
  } else {
    Serial.println("cannot open file");
  }

  Serial.println(sd.maxInt());
}

int i = 0;
void loop() {
  i++;
  if (sd.writeBuffer("data_" + String(i) + "\r\n")){
    Serial.println(i);
  } else {
    Serial.println("Cannot write " + String(i));
  }
  if (gps.readData()){
    Serial.print(gps.data);
    if (sd.writeBuffer(gps.data)){
      Serial.println("write GPS");
    }
  } else {
    Serial.println("No GPS"); 
  }
}
