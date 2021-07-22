#include <stdio.h> // FILE operations.
#include <string.h> // string operations.
#include <stdlib.h> // atoi and free functions.
// Above headers are included for string and processing operations.

#include <time.h>
// For calculating processing time.
#include <windows.h>
// For Message Box.

char * strdup(const char * s) // This function is string duplicate, it is used in the process of taking values from csv file.
{
  size_t len = 1+strlen(s);
  char *p = malloc(len);

  return p ? memcpy(p, s, len) : NULL;
}

double GrayToRGB(unsigned int* RGBImage, unsigned char* GrayImage, int LVLineWidthRGB, int LVLineWidthGray, int LVWidth, int LVHeight, char* ColorMap, char* CsvPath);

// Function returns processing time.
