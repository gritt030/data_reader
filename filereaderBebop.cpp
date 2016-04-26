#include "filereader.h"
#include <cmath>

// FileReader::FileReader(char* sonarFilename, char* posFilename){
//   this->sonarFile.open(sonarFilename);
//   this->posFile.open(posFilename);
//   
//   this->posBuffer = new double[13];
//   this->sonarBuffer = new long[5];
// }

void FileReader::quatToRot(double* quat, double* rot){
  double qw = quat[3];
  double qx = quat[0];
  double qy = quat[1];
  double qz = quat[2];
  
  rot[0] = qx*qx - qy*qy - qz*qz + qw*qw;
  rot[1] = 2.0*(qx*qy + qz*qw);
  rot[2] = 2.0*(qx*qz - qy*qw);
  rot[3] = 2.0*(qx*qy - qz*qw);
  rot[4] = -qx*qx + qy*qy - qz*qz + qw*qw;
  rot[5] = 2.0*(qy*qz + qx*qw);
  rot[6] = 2.0*(qx*qz + qy*qw);
  rot[7] = 2.0*(qy*qz - qx*qw);
  rot[8] = -qx*qx - qy*qy + qz*qz + qw*qw;
  
//   rot[0] = 1 - 2.0*(qy*qy + qz*qz);
//   rot[1] = 2.0*(qx*qy - qz*qw);
//   rot[2] = 2.0*(qx*qz + qy*qw);
//   rot[3] = 2.0*(qx*qy + qz*qw);
//   rot[4] = 1 - 2.0*(qx*qx + qz*qz);
//   rot[5] = 2.0*(qy*qz - qx*qw);
//   rot[6] = 2.0*(qx*qz - qy*qw);
//   rot[7] = 2.0*(qy*qz + qx*qw);
//   rot[8] = 1 - 2.0*(qx*qx + qy*qy);
}


// function [A]=quat2rot(q)
// % quaternions_to_rot_matrix(q) takes a unit quaternion and returns the corresponding rotational matrix
// A(1,1) = q(1,1)^2 - q(2,1)^2 - q(3,1)^2 + q(4,1)^2  ;
// A(1,2) = 2*( q(1,1)*q(2,1) + q(3,1)*q(4,1) ); 
// A(1,3) = 2*( q(1,1)*q(3,1) - q(2,1)*q(4,1) );
// A(2,1) = 2*( q(1,1)*q(2,1) - q(3,1)*q(4,1) );
// A(2,2) = -q(1,1)^2 + q(2,1)^2 - q(3,1)^2 + q(4,1)^2;
// A(2,3) = 2*( q(2,1)*q(3,1) + q(1,1)*q(4,1) );
// A(3,1) = 2*( q(1,1)*q(3,1) + q(2,1)*q(4,1) );
// A(3,2) = 2*( q(2,1)*q(3,1) - q(1,1)*q(4,1) );
// A(3,3) = -q(1,1)^2 - q(2,1)^2 + q(3,1)^2 + q(4,1)^2;
// A = eye(3) - 2 * q(4) * skewsymm(q(1:3)) + 2 * skewsymm(q(1:3))^2;


void FileReader::createCoordFileBebop(float startTime, float dtIMU, int windowSize, char* coordFilename,
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
    getPosBebop(posBuf);
    nextLineBebop();
    
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
//        getSonarBebop(sonarBuf);
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
    
    //time, x, y, //z
    coordFile << (long)(time*1000.0) << " ";
    coordFile << (posBuf[0]*1000.0 - 20000.0) << " ";
//     coordFile << (posBuf[0]) << " ";
//     coordFile << (posBuf[1]*1000.0 - 20000.0) << " ";
        coordFile << (posBuf[1]*1000.0 - 35000.0) << " ";
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


// double* quatBuf = new double[4];
//   double* rotBuf = new double[9];
//   double* posBuf = new double[3];
//   long* sonarBuf = new long[4];
//   double* timeBuf = new double[2];


void FileReader::getQuatBebop(double* buffer){
  for (int i=0; i<4; i++){
    posFile >> buffer[i];
  }
}


void FileReader::getPosBebop(double* buffer){
  for (int i=0; i<3; i++){
    posFile >> buffer[i];
  }
}


void FileReader::getSonarBebop(long* buffer){
  for (int i=0; i<4; i++){
    sonarFile >> buffer[i];
  }
}


double FileReader::getTimeSonar(){
  double buffer;
  sonarFile >> buffer;
  return buffer;
}


void FileReader::nextLineBebop(){
  double toss;
//   for (int i=0; i<73; i++){
  for (int i=0; i<83; i++){
    posFile >> toss;
  }
}


long FileReader::getTimePos(int window){
  long buffer;
  
  for (int i=0; i<window; i++){
    timeFile >> buffer;
  }
  
  return buffer;
}


// 1) N: size of the window in filter (number of clones in each window)
// 2) data_path: data folder
// 3) imu_dt: the imu dt in seconds
// 4) first_imu_time_stamp: your time stamp of the first imu in seconds
// 
// Output format:
// a) x_est_filter: 8xM matrix, where M is the number of all the pose, and each column consists of: (1-4 quaternion) I_q_G, (5-7 position) G_p_I, (8) time_sync (don't need).
// b) time_stamps_sec: Mx1 vector, and the i-th element is the time stamp (in seconds) of the i-th poses.
// 
// %%%%%%%%%%%%%% state estimates %%%%%%%%%%%%
// N = 10 % put number of clones used here
// data_path = '/media/622f7f31-f883-4ad2-9dbc-d0baac80c10a/kejian/for_henry/ds3/results/';
// 
// time_stamps = dlmread([data_path, 'state_time_stamps.dat']);
// x_ba = load([data_path, 'xkk.txt']);
// x_filter = load([data_path, 'x_est_c.dat']);
// x_est_filter = [x_filter(:,1:8)',reshape(x_filter(end,9:end),8,N-1)];
// 
// %%%%%%%%%%%%%%% time stamps %%%%%%%%%%%%%
// 
// time_stamps = [time_stamps(N:end-1,1); time_stamps(end,:)'];
// imu_dt = 0.010004187367400;  % put imu_dt here in seconds
// time_stamps_sec = imu_dt * time_stamps;
// first_imu_time_stamp = ????;
// time_stamps_sec = time_stamps_sec + first_imu_time_stamp;



