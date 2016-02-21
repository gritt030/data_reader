#ifndef FILEREADER_H
#define FILEREADER_H

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string.h>

//using namespace std;

class FileReader
{
public:
  FileReader();
  FileReader(char* sonarFilename, char* posFilename);
  void createCoordFilePioneer(char* coordFilename);
  void createCoordFileBebop(float startTime, float dtIMU, int windowSize, char* coordFilename,
                                                                          char* posFilename,
                                                                          char* timeFilename,
                                                                          char* sonarFilename);
  void quatToRot(double *quat, double *rot);
  void rowToColumnFile(char* infile, char* outfile, int numRows);
  void createCoordFileBA(float startTime, float dtIMU, int windowSize, char* coordFilename,
                                                                       char* posFilename,
                                                                       char* timeFilename,
                                                                       char* sonarFilename);
  
private:
  std::ifstream sonarFile, posFile, timeFile;
  std::ofstream coordFile;
  double* posBuffer;
  long* sonarBuffer;
  int getPosCoord(double* buffer);
  int getSonarCoord(long* buffer);
  
  //Bebop
  void getQuatBebop(double* buffer);
  void getPosBebop(double* buffer);
  void getSonarBebop(long* buffer);
  double getTimeSonar();
  void nextLineBebop();
  long getTimePos(int window);
  
  //BA filter
  void skipNextBA();
  void getPosBA(double* buffer);
  void nextLineBA();
};

#endif // FILEREADER_H
