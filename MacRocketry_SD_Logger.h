#ifndef MacRocketry_SD_Logger_h //include guard
#define MacRocketry_SD_Logger_h

#include <Arduino.h>  //Arduino library
#include <SPI.h>      //SPI library
#include <SD.h>       //SD card library

#define SD_CS_Pin 10
#define fileNamePrefix "file_"
#define SD_Buffer 512
#define Write_Buffer (SD_Buffer-16)

class MacRocketry_SD_Logger {
  public:
    MacRocketry_SD_Logger(void);              //default constructor
    MacRocketry_SD_Logger(String filePath);   //filePath
    
    bool openFile(String filePath);    //open file
    bool writeFile(String data);      //write to file
    bool writeBuffer(String data);    //faster write
    uint16_t maxUInt(); //largest num representable by uint

    bool getConnectSD(void);
    bool getConnectFile(void);

  private:
    uint8_t connectState;
    File sdFile; //File object for SD

    //for incremental file name
    uint16_t numNext;
    
    int16_t bufferSize, bufferAllow;     //buffer up to 512 char

    void init();
    bool openNextFile();

};

#endif