#ifndef MacRocketry_SD_Logger_h //include guard
#define MacRocketry_SD_Logger_h

#include <Arduino.h> //Arduino library
#include <SPI.h>     //SPI library
#include <SD.h>      //SD card library

#define SD_CS_Pin 10
#define defaultFileName "file_"
#define SD_buffer 256

class MacRocketry_SD_Logger {
  public:
    bool connectSD, connectFile;

    MacRocketry_SD_Logger(void); //declare constructor
    MacRocketry_SD_Logger(String filePath);
    bool openFile(String filePath); //open file
    bool writeFile(String data); //write to file
    bool writeBuffer(String data); //faster write
    int maxInt(); //largest num representable by int

  private:
    File sdFile; //File object for SD
    
    int nextFileNum, maxFileNum; //for default file
    String currentFileName; //file incremental name
    
    int bufferSize, bufferAllow; //buffer up to 512 char
    String bufferString, bufferSubstring; //string to be buffered

    bool start();
    void init();
    bool openNextFile();

};

#endif