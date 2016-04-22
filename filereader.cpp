#include "filereader.h"
#include <cmath>

FileReader::FileReader(char* sonarFilename, char* posFilename){
  this->sonarFile.open(sonarFilename);
  this->posFile.open(posFilename);
  
  this->posBuffer = new double[13];
  this->sonarBuffer = new long[5];
}

FileReader::FileReader(){}


void FileReader::createCoordFilePioneer(char* coordFilename){
  std::cout << "Opening coordinate file...\n";
  this->coordFile.open(coordFilename);
  
  std::cout << "    Starting coordinates\n";
  getPosCoord(posBuffer);
  getSonarCoord(sonarBuffer);
  
  double initPosTime = posBuffer[0];
  long initSonarTime = sonarBuffer[0];
  
  //initial time, x, y, //z
  coordFile << initSonarTime << " ";
  coordFile << posBuffer[1]*1000.0 << " ";
  coordFile << posBuffer[2]*1000.0 << " ";
//   coordFile << posBuffer[3]*1000.0 << " ";
  
  //orientation
  double x = 1.0*posBuffer[4];
  double y = 1.0*posBuffer[5];
  double angle = atan2(y,x);
  coordFile << angle << " ";
  
  //w, nw, ne, e
  coordFile << sonarBuffer[3]*10.0 << " ";
  coordFile << sonarBuffer[1]*10.0 << " ";
  coordFile << sonarBuffer[2]*10.0 << " ";
  coordFile << sonarBuffer[4]*10.0 << std::endl;
  
//   //initial nw coords
//   double x = sonarBuffer[1]*10.0 + 100.0;
//   double y = 100.0;
//   double z = 0.0;
//   double x2 = x*posBuffer[4] + y*posBuffer[7];
//   double y2 = x*posBuffer[5] + y*posBuffer[8];
//   double z2 = x*posBuffer[6] + y*posBuffer[9];
//   coordFile << x2 << " ";
//   coordFile << y2 << " ";
//   coordFile << z2 << " ";
//   
//   //initial ne coords
//   x = sonarBuffer[2]*10.0 + 100.0;
//   y = -100.0;
//   z = 0.0;
//   x2 = x*posBuffer[4] + y*posBuffer[7];
//   y2 = x*posBuffer[5] + y*posBuffer[8];
//   z2 = x*posBuffer[6] + y*posBuffer[9];
//   coordFile << x2 << " ";
//   coordFile << y2 << " ";
//   coordFile << z2 << " ";
//   
//   //initial w coords
//   x = 0.0;
//   y = sonarBuffer[3]*10.0 + 100.0;
//   z = 0.0;
//   x2 = x*posBuffer[4] + y*posBuffer[7];
//   y2 = x*posBuffer[5] + y*posBuffer[8];
//   z2 = x*posBuffer[6] + y*posBuffer[9];
//   coordFile << x2 << " ";
//   coordFile << y2 << " ";
//   coordFile << z2 << " ";
//   
//   //initial e coords
//   x = 0.0;
//   y = -sonarBuffer[4]*10.0 - 100.0;
//   z = 0.0;
//   x2 = x*posBuffer[4] + y*posBuffer[7];
//   y2 = x*posBuffer[5] + y*posBuffer[8];
//   z2 = x*posBuffer[6] + y*posBuffer[9];
//   coordFile << x2 << " ";
//   coordFile << y2 << " ";
//   coordFile << z2 << std::endl;
  
  std::cout << "    Writing coordinates...\n";
  while(getPosCoord(posBuffer) != 0){
    double dt = (posBuffer[0] - initPosTime)*1000000.0;
    while ((sonarBuffer[0] - initSonarTime) < dt){
      int result = getSonarCoord(sonarBuffer);
      if (result==0) return;
    }
    
    coordFile << sonarBuffer[0] << " ";
    coordFile << posBuffer[1]*1000.0 << " ";
    coordFile << posBuffer[2]*1000.0 << " ";
//     coordFile << posBuffer[3]*1000.0 << " ";
    
    //orientation
    x = 1.0*posBuffer[4];
    y = 1.0*posBuffer[5];
    angle = atan2(y,x);
    coordFile << angle << " ";
    
    //w, nw, ne, e
    coordFile << sonarBuffer[3]*10.0 << " ";
    coordFile << sonarBuffer[1]*10.0 << " ";
    coordFile << sonarBuffer[2]*10.0 << " ";
    coordFile << sonarBuffer[4]*10.0 << std::endl;
    
    
//     x = sonarBuffer[1]*10.0 + 100.0;
//     y = 100.0;
//     z = 0.0;
//     x2 = x*posBuffer[4] + y*posBuffer[7];
//     y2 = x*posBuffer[5] + y*posBuffer[8];
//     z2 = x*posBuffer[6] + y*posBuffer[9];
//     coordFile << x2 << " ";
//     coordFile << y2 << " ";
//     coordFile << z2 << " ";
//     x = sonarBuffer[2]*10.0 + 100.0;
//     y = -100.0;
//     z = 0.0;
//     x2 = x*posBuffer[4] + y*posBuffer[7];
//     y2 = x*posBuffer[5] + y*posBuffer[8];
//     z2 = x*posBuffer[6] + y*posBuffer[9];
//     coordFile << x2 << " ";
//     coordFile << y2 << " ";
//     coordFile << z2 << " ";
//     x = 0.0;
//     y = sonarBuffer[3]*10.0 + 100.0;
//     z = 0.0;
//     x2 = x*posBuffer[4] + y*posBuffer[7];
//     y2 = x*posBuffer[5] + y*posBuffer[8];
//     z2 = x*posBuffer[6] + y*posBuffer[9];
//     coordFile << x2 << " ";
//     coordFile << y2 << " ";
//     coordFile << z2 << " ";
//     x = 0.0;
//     y = -sonarBuffer[4]*10.0 - 100.0;
//     z = 0.0;
//     x2 = x*posBuffer[4] + y*posBuffer[7];
//     y2 = x*posBuffer[5] + y*posBuffer[8];
//     z2 = x*posBuffer[6] + y*posBuffer[9];
//     coordFile << x2 << " ";
//     coordFile << y2 << " ";
//     coordFile << z2 << std::endl;
  }
  
  std::cout << "    Closing\n";
  coordFile.close();
  std::cout << "Done!\n";
}


int FileReader::getPosCoord(double* buffer){
  for (int i=0; i<13; i++){
    posFile >> buffer[i];
  }
  
  if (posFile.eof()) return 0;
  else return 1;
}


int FileReader::getSonarCoord(long* buffer){
  for (int i=0; i<5; i++){
    sonarFile >> buffer[i];
  }
  
  if (sonarFile.eof()) return 0;
  else return 1;
}




