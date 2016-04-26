#ifndef PGMTOPNG_H
#define PGMTOPNG_H

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string.h>
#include "png_writer.h"

class PgmToPng
{
public:
  PgmToPng(char* inputFile, char* outputFile);
};

#endif // PGMTOPNG_H
