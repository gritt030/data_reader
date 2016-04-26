#include "filereader.h"
#include <cmath>

void FileReader::rowToColumnFile(char* infile, char* outfile, int numRows){
  std::cout << "Opening files...\n";
  std::ifstream inputFile(infile);
  //inputFile.open(infile);
  std::ofstream outputFile(outfile);
  //outputFile.open(outfile);
  
  std::cout << "    Making names...\n";
  char* names[numRows];
  char* a = new char[5]();
  a[0] = 'a';
  a[1] = '\0';
  
  for (int i=0; i<numRows; i++){
    names[i] = new char[255]();
    strcpy(names[i], outfile);
    strcat(names[i], a);
    a[0]++;
    strcat(names[i], ".txt\0");
  }
  
  std::cout << "    Getting lines...\n";
  std::string lines[numRows];
  
  for (int i=0; i<numRows; i++){
    std::getline(inputFile, lines[i]);
  }
  
  std::cout << "    Saving lines...\n";
  for (int i=0; i<numRows; i++){
    std::ofstream curOut(names[i]);
    curOut << lines[i];
    curOut.close();
  }
  
  std::cout << "    Opening files...\n";
  std::ifstream* streams[numRows];
  for (int i=0; i<numRows; i++){
    streams[i] = new std::ifstream(names[i]);
  }
  
  std::cout << "    Generating output...\n";
  int i=0;
  long double value;
  
  while (not streams[0]->eof()){
    std::cout << "        Row " << i++ << std::endl;
    
    for (int i=0; i<numRows; i++){
      (*streams[i]) >> value;
      outputFile << value << " ";
    }
    outputFile << "\n";
  }
  
  std::cout << "    Closing files...\n";
  for (int i=0; i<numRows; i++){
    streams[i]->close();
    std::remove(names[i]);
  }
  outputFile.close();
  
  std::cout << "Done!\n";
}



void FileReader::createCoordFileBA(float startTime, float dtIMU, int windowSize, char* coordFilename,
                                                                                    char* posFilename,
                                                                                    char* timeFilename,
                                                                                    char* sonarFilename){
  
  double* quatBuf = new double[4];
  double* rotBuf = new double[9];
  double* posBuf = new double[3];
  long* sonarBuf = new long[4];
  long* tmpSonarBuf = new long[4];
  long count;
  double sonarTime, posTime;
  
  std::cout << "Opening files...\n";
  coordFile.open(coordFilename);
  posFile.open(posFilename);
  sonarFile.open(sonarFilename);
  timeFile.open(timeFilename);
  
  std::cout << "    Aligning time file...\n";
  for (int i=2; i<windowSize; i++) {
    posTime = getTimePos(i);
  }
  
  std::cout << "    Starting coords...\n";
  int ind=0;
  double x,y,z,x2,y2,z2;
  double angle;
  double time;
  
  while (not posFile.eof()) {
    std::cout << "        Line " << ind++ << std::endl;
    
    getQuatBebop(quatBuf);
    skipNextBA();
    getPosBA(posBuf);
    nextLineBA();
    
    time = getTimePos(windowSize);
    time *= dtIMU;
    time += startTime;
    sonarTime = getTimeSonar();
    getSonarBebop(sonarBuf);
    count = 1;
    
    while (sonarTime < time){
      if (sonarFile.eof()) {
        coordFile.close();
        return;
      }
      
      sonarTime = getTimeSonar();
//       getSonarBebop(sonarBuf);
      getSonarBebop(tmpSonarBuf);
      sonarBuf[0] += tmpSonarBuf[0];
      sonarBuf[1] += tmpSonarBuf[1];
      sonarBuf[2] += tmpSonarBuf[2];
      sonarBuf[3] += tmpSonarBuf[3];
      count++;
    }
    
    sonarBuf[0] /= count;
    sonarBuf[1] /= count;
    sonarBuf[2] /= count;
    sonarBuf[3] /= count;
    
    quatToRot(quatBuf, rotBuf);
    
    //x, y, //z
    coordFile << (long)(time*1000.0) << " ";
    coordFile << (posBuf[0]*1000.0 - 20000.0) << " ";
//         coordFile << (posBuf[1]*1000.0 - 20000.0) << " ";
    coordFile << (posBuf[1]*1000.0 - 20000.0) << " ";
//     coordFile << posBuf[2]*1000.0 << " ";
    
    //orientation
    x = 1.0*rotBuf[0];
    y = 1.0*rotBuf[3];
    angle = atan2(y,x);
    coordFile << angle << " ";
    
    //w, nw, ne, e
    coordFile << sonarBuf[2]*10.0 << " ";
    coordFile << sonarBuf[0]*10.0 << " ";
    coordFile << sonarBuf[1]*10.0 << " ";
    coordFile << sonarBuf[3]*10.0 << std::endl;
    
//     //nw sonar
//     x = sonarBuf[0]*10.0 + 100.0;
//     y = 100.0;
//     z = 0.0;
//     x2 = x*rotBuf[0] + y*rotBuf[1];
//     y2 = x*rotBuf[3] + y*rotBuf[4];
//     z2 = x*rotBuf[6] + y*rotBuf[7];
//     coordFile << x2 << " ";
//     coordFile << y2 << " ";
//     coordFile << z2 << " ";
//     
//     //ne sonar
//     x = sonarBuf[1]*10.0 + 100.0;
//     y = -100.0;
//     z = 0.0;
//     x2 = x*rotBuf[0] + y*rotBuf[1];
//     y2 = x*rotBuf[3] + y*rotBuf[4];
//     z2 = x*rotBuf[6] + y*rotBuf[7];
//     coordFile << x2 << " ";
//     coordFile << y2 << " ";
//     coordFile << z2 << " ";
//     
//     //w sonar
//     x = 0.0;
//     y = sonarBuf[2]*10.0 + 100.0;
//     z = 0.0;
//     x2 = x*rotBuf[0] + y*rotBuf[1];
//     y2 = x*rotBuf[3] + y*rotBuf[4];
//     z2 = x*rotBuf[6] + y*rotBuf[7];
//     coordFile << x2 << " ";
//     coordFile << y2 << " ";
//     coordFile << z2 << " ";
//     
//     //e sonar
//     x = 0.0;
//     y = -sonarBuf[3]*10.0 - 100.0;
//     z = 0.0;
//     x2 = x*rotBuf[0] + y*rotBuf[1];
//     y2 = x*rotBuf[3] + y*rotBuf[4];
//     z2 = x*rotBuf[6] + y*rotBuf[7];
//     coordFile << x2 << " ";
//     coordFile << y2 << " ";
//     coordFile << z2 << std::endl;
  }
  
  std::cout << "    Closing\n";
  coordFile.close();
  std::cout << "Done!\n";
}


void FileReader::getPosBA(double* buffer){
  for (int i=0; i<3; i++){
    posFile >> buffer[i];
  }
}


void FileReader::skipNextBA(){
  double toss;
  for (int i=0; i<9; i++){
    posFile >> toss;
  }
}


void FileReader::nextLineBA(){
  double toss;
  posFile >> toss;
}

