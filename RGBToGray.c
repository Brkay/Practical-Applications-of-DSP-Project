#include "RGBtoGRAY.h"
double  RGBtoGray(unsigned int* RGBImage, unsigned char* GrayImage, int LVLineWidthRGB, int LVLineWidthGray, int LVWidth, int LVHeight)
{
	clock_t begin = clock();
	for(int y = 0; y < LVHeight; y++)
	{
		for (int x = 0; x < LVWidth; x++)
		{
			unsigned char R = ((*RGBImage) & 0xFF0000)>>16;// Do bitwise comparision for just red values and shift 2 bytes(16 bits)
			unsigned char G = ((*RGBImage) & 0x00FF00)>>8;// Do bitwise comparision for just green values and shift 1 byte (8 bits)
			unsigned char B = ((*RGBImage) & 0x0000FF); // Do bitwise comparision for just blue values and there is no need for shifting.
			*GrayImage = 0.299f * R + 0.587f * G + 0.114f * B; // Apply the formula.
			GrayImage++;
			RGBImage++;
		}
		GrayImage += LVLineWidthGray - LVWidth;
		RGBImage += LVLineWidthRGB - LVWidth;
	}
	clock_t end = clock();
	double time_spent = (double)(end - begin) / (double)(CLOCKS_PER_SEC) ;
	return time_spent;
	
}

