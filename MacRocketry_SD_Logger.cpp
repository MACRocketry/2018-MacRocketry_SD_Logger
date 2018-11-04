#include <Arduino.h>                //Arduino library
#include <MacRocketry_SD_Logger.h> //header file
#include <SPI.h>     //SPI library
#include <SD.h>      //SD card library

MacRocketry_SD_Logger::MacRocketry_SD_Logger(){ //constructor
  init();
  connectSD = start(); //start
  connectFile = openNextFile();
}

MacRocketry_SD_Logger::MacRocketry_SD_Logger(String filePath){ //constructor
  init();
  connectSD = start(); //start
  connectFile = openFile(filePath);
}

void MacRocketry_SD_Logger::init(){ //initialize variables to null
  connectSD = false;
  connectFile = false;
  
  nextFileNum = 0;
  maxFileNum = maxInt();
  currentFileName = "";

  //variables for more efficient SD write
  bufferSize = 0;
  bufferAllow = 0;
  bufferString = "";
  bufferSubstring = "";
}

int MacRocketry_SD_Logger::maxInt(){ //just get max int number possible
  maxFileNum = (1 << (sizeof(int) * 8 - 1) ) - 1; //bit shifting, watch out for signed
  return maxFileNum;
}

bool MacRocketry_SD_Logger::openNextFile(){
  if (connectSD){ //if SD card is connected
    currentFileName = defaultFileName + String(nextFileNum);
    while ((SD.exists(currentFileName)) && (nextFileNum < maxFileNum)){
      nextFileNum++;
      currentFileName = defaultFileName + String(nextFileNum);
    }
    if (nextFileNum < maxFileNum){ //if file num does not exceed 1024
      return openFile(currentFileName);
    }
  }
  return false; //no SD card
}

bool MacRocketry_SD_Logger::start(){
  if (SD.begin(SD_CS_Pin)){
    return true; //able to connect to SD
  }
  return false; //no SD card
}

bool MacRocketry_SD_Logger::openFile(String filePath){
  if (connectSD){
    if (sdFile){ //if current file is open
      sdFile.close(); //close current file
      delay(5); //delay 5ms
    }
    sdFile = SD.open(filePath, FILE_WRITE); //open new file for write
    if (sdFile){ //if successful
      writeFile("start logging...");
      return true; //open file successfully
    }
  }
  return false; //cannot open file
}

bool MacRocketry_SD_Logger::writeFile(String data){
  if (connectFile){ //if file is open
    sdFile.println(data);
    sdFile.flush(); //flush all bytes to SD card
    return true;
  }
  return false; //cannot write to file
}

bool MacRocketry_SD_Logger::writeBuffer(String data){
  if (connectFile){ //if file is open
    bufferString += data; //append new string

    //calculate available space in buffer
    //String.length() returns length in unsigned int
    bufferAllow = min(SD_buffer - bufferSize, (int) bufferString.length());
    bufferSize += bufferAllow; //get current buffer size
    
    //pass string with enough space
    bufferSubstring = bufferString.substring(0, bufferAllow);
    sdFile.print(bufferSubstring);

    if (bufferSize >= SD_buffer){ //if buffer overflow
      sdFile.print("\nbuffered\n");
      sdFile.flush(); //actually record to SD
      bufferSize = 0; //reset buffer
    }

    //get the rest of string that was unable to pass
    bufferSubstring = bufferString.substring(bufferAllow);
    bufferString = bufferSubstring;
    return true;
  }
  return false;
}