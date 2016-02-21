#include <iostream>
#include "filereader.h"

int main(int argc, char **argv) {
  char* posFile = "/home/owner/workspace/Datasets/smith_bebop/Dataset2/bebopH_smithbasement_motors/x_est_c.dat";
  char* timeFile = "/home/owner/workspace/Datasets/smith_bebop/Dataset2/bebopH_smithbasement_motors/state_time_stamps.dat";
  char* sonarFile = "/home/owner/workspace/Datasets/smith_bebop/Dataset2/sonar_ring_data/sonar_ring_data.txt";
  char* coordFile = "/home/owner/workspace/Datasets/smith_bebop/Dataset2/origCoord/coordsEstimate.txt";
  
//   char* sonarFile = "/home/owner/workspace/Datasets/output_ds2/dataset2.txt";
//   char* posFile = "/home/owner/workspace/Datasets/output_ds2/est_ba.txt";
//   char* coordFile = "/home/owner/workspace/Datasets/output_ds2/coordsAccurate.txt";
  
  //FileReader f(sonarFile, posFile);
  FileReader* f = new FileReader();
  //f.createCoordFilePioneer(coordFile);
  //2259.973305  dataset1
  //698.287191   dataset2
  f->createCoordFileBebop(698.287191, 0.011, 10, coordFile, posFile, timeFile, sonarFile);
  
//   char* inf = "/home/owner/workspace/Datasets/smith_bebop/Dataset2/bebopH_smithbasement_motors/xkk.txt";
//   char* otf = "/home/owner/workspace/Datasets/smith_bebop/Dataset2/bebopH_smithbasement_motors/xkk_columns.txt";
//   f.rowToColumnFile(inf, otf, 17);
  
  return 0;
}
