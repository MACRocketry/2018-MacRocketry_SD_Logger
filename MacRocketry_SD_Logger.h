#ifndef MacRocketry_SD_Logger_h //include guard
#define MacRocketry_SD_Logger_h

#include <Arduino.h>  //include Arduino library
#include <SPI.h>      //SPI library
#include <SD.h>       //SD card library

#define SD_CS_Pin 10
#define fileNamePrefix "file_"
#define SD_Buffer 512

//comment out line to not log "bufferred"
//#define Log_Bufferred
#ifdef Log_Bufferred
  #define Log_Buffer_Word "\nbuffered\n"
  #define Write_Buffer (SD_Buffer-16)
#else
  #define Write_Buffer (SD_Buffer-4)
#endif

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
    bool connectSD, connectFile;
    File sdFile; //File object for SD
    
    int16_t bufferSize;     //buffer up to 512 char

    void init();
    bool openNextFile();

};

#endif