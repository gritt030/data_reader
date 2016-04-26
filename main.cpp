#include <iostream>
#include <cmath>
#include "filereader.h"
#include "pngwriter/pgmtopng.h"

int main(int argc, char **argv) {

//   char* infile = (char*)argv[1];
//   char* outfile = (char*)argv[2];
//   PgmToPng* p = new PgmToPng(infile, outfile);
  
//   char* posFile1 = "/home/owner/workspace/Datasets/flying/walib_sonars_3/xkk_columns.txt";
//   char* posFile2 = "/home/owner/workspace/Datasets/flying/walib_sonars_3/x_est_c.dat";
//   char* timeFile = "/home/owner/workspace/Datasets/flying/walib_sonars_3/state_time_stamps.dat";
//   char* sonarFile = "/home/owner/workspace/Datasets/flying/walib_sonars_3/sonar_ring_data.txt";
//   char* coordFile1 = "/home/owner/workspace/Datasets/flying/walib_sonars_3/W1coordsAccurate.txt";
//   char* coordFile2 = "/home/owner/workspace/Datasets/flying/walib_sonars_3/W1coordsEstimate.txt";
  
  char* posFile1 = "/home/owner/workspace/Datasets/smith_bebop/Dataset2/bebopH_smithbasement_motors/xkk_columns.txt";
  char* posFile2 = "/home/owner/workspace/Datasets/smith_bebop/Dataset2/bebopH_smithbasement_motors/x_est_c.dat";
  char* timeFile = "/home/owner/workspace/Datasets/smith_bebop/Dataset2/bebopH_smithbasement_motors/state_time_stamps.dat";
  char* sonarFile = "/home/owner/workspace/Datasets/smith_bebop/Dataset2/sonar_ring_data/sonar_ring_data.txt";
  char* coordFile1 = "/home/owner/workspace/Datasets/testAcc.txt";
  char* coordFile2 = "/home/owner/workspace/Datasets/testEst.txt";
  
//   char* sonarFile = "/home/owner/workspace/Datasets/output_ds3/dataset3.txt";
//   char* posFile = "/home/owner/workspace/Datasets/output_ds3/est_ba.txt";
//   char* coordFile = "/home/owner/workspace/Datasets/NewFormat/K3coordsAccurate.txt";
  
//   FileReader f(sonarFile, posFile);
  FileReader* f = new FileReader();
//   f.createCoordFilePioneer(coordFile);
  //2259.973305  dataset1
  //698.287191   dataset2
  //210.973383   walter1
  //191.146192   walter2
  //564.341802   walter3
  f->createCoordFileBA(698.287191, 0.011, 10, coordFile1, posFile1, timeFile, sonarFile);
//   f->createCoordFileBebop(564.341802, 0.011, 10, coordFile2, posFile2, timeFile, sonarFile);
  
//   FileReader* f = new FileReader();
//   char* inf = "/home/owner/workspace/Datasets/flying/walib_sonars_3/xkk.txt";
//   char* otf = "/home/owner/workspace/Datasets/flying/walib_sonars_3/xkk_columns.txt";
//   f->rowToColumnFile(inf, otf, 17);
  
  return 0;
}
