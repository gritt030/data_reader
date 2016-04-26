#include "pgmtopng.h"

PgmToPng::PgmToPng(char* inputFile, char* outputFile){
  std::ifstream infile;
  infile.open(inputFile);
  
  char trash;
  infile.read(&trash, 1);//P
  infile.read(&trash, 1);//6
  infile.read(&trash, 1);//\n
  infile.read(&trash, 1);// 
  infile.read(&trash, 1);// 
  
  int width, height, max;
  infile >> width;
  infile >> height;
  infile >> max;
  
  infile.read(&trash, 1);//\n
  
  PngWriter* w = new PngWriter();
  w->create_image(outputFile, width, height);
  
  char r,g,b;
  unsigned int red, green, blue;
  unsigned int color;
  
  for (int i=0; i<width; i++){
  for (int j=0; j<height; j++){
    infile.read(&r,1);
    infile.read(&g,1);
    infile.read(&b,1);
//     std::cout << (int)r << " " << (int)g << " " << (int)b << std::endl;
    red = r;
    red &= 0x000000ff;
    red <<= 24;
    green = g;
    green &= 0x000000ff;
    green <<= 16;
    blue = b;
    blue &= 0x000000ff;
    blue <<= 8;
    color = red | green | blue | 0x000000ff;
    w->set_pixel(j,i,color);
  }}
  
  w->output_image();
  delete w;
}

