#include <iostream>
#include <cmath>
#include "filereader.h"

int main(int argc, char **argv) {
  char* posFile = "/home/owner/workspace/Datasets/smith_bebop/Dataset1/bebopH_smithbasement/xkk_columns.txt";
  char* timeFile = "/home/owner/workspace/Datasets/smith_bebop/Dataset1/bebopH_smithbasement/state_time_stamps.dat";
  char* sonarFile = "/home/owner/workspace/Datasets/smith_bebop/Dataset1/sonar_ring_data/sonar_ring_data.txt";
  char* coordFile = "/home/owner/workspace/Datasets/NewFormat/S1coordsAccurate.txt";
  
//   char* sonarFile = "/home/owner/workspace/Datasets/output_ds3/dataset3.txt";
//   char* posFile = "/home/owner/workspace/Datasets/output_ds3/est_ba.txt";
//   char* coordFile = "/home/owner/workspace/Datasets/NewFormat/K3coordsAccurate.txt";
  
//   FileReader f(sonarFile, posFile);
  FileReader* f = new FileReader();
//   f.createCoordFilePioneer(coordFile);
  //2259.973305  dataset1
  //698.287191   dataset2
  f->createCoordFileBA(2259.973305 , 0.011, 10, coordFile, posFile, timeFile, sonarFile);
  
//   char* inf = "/home/owner/workspace/Datasets/smith_bebop/Dataset2/bebopH_smithbasement_motors/xkk.txt";
//   char* otf = "/home/owner/workspace/Datasets/smith_bebop/Dataset2/bebopH_smithbasement_motors/xkk_columns.txt";
//   f.rowToColumnFile(inf, otf, 17);
  
  return 0;
}
