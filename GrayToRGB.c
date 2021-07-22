#include "GrayToRGB.h"
#define MAX_STR_LEN 257
double GrayToRGB(unsigned int* RGBImage, unsigned char* GrayImage, int LVLineWidthRGB, int LVLineWidthGray, int LVWidth, int LVHeight, char* ColorMap, char* CsvPath)
{
	double time_spent = 0.0;
	clock_t begin = clock(); // Take clock time and end of time dll, calculate processing time.
	FILE* bookFile; 
	/* allocation of the buffer for every line in the File */
	char* buf = malloc(MAX_STR_LEN);
	char* tmp;
	/* if the space could not be allocated, return an error */
	if (buf == NULL)
	{
		MessageBoxA(0, "Not enough memory.", "Error", MB_OK);

		return 1;
	}
	bookFile = fopen(CsvPath, "r"); // Open the file that whose path was taken from labview.
	if (bookFile == NULL) //Reading the file
	{
		MessageBoxA(0, "CSV file could not be opened.", "Error", MB_OK);
		free(buf);
		return 1;
	}
	unsigned char C[256][3]; // Colormap value 2-D array.

	fgets(buf, 256, bookFile);// First row just shows Colormap names in the CSV file and it has nothing to do with processing, so it can be ignored. Take and dump it. 
	char* temp1; 
	int i = 0; // If a non-valid Colormap name is inserted, use "parula" colormap.
	unsigned char C[256][3];
	
	if (!strcmp("parula", ColorMap))
	{
		i = 0;
	}
	else if (!strcmp("turbo", ColorMap))
	{
		i = 1;
	}
	else if (!strcmp("hsv", ColorMap))
	{
		i = 2;
	}
	else if (!strcmp("hot", ColorMap))
	{
		i = 3;
	}
	else if (!strcmp("cool", ColorMap))
	{
		i = 4;
	}
	else if (!strcmp("spring", ColorMap))
	{
		i = 5;
	}
	else if (!strcmp("summer", ColorMap))
	{
		i = 6;
	}
	else if (!strcmp("autumn", ColorMap))
	{
		i = 7;
	}
	else if (!strcmp("winter", ColorMap))
	{
		i = 8;
	}
	else if (!strcmp("bone", ColorMap))
	{
		i = 9;
	}
	else if (!strcmp("pink", ColorMap))
	{
		i = 10;
	}
	else if (!strcmp("jet", ColorMap))
	{
		i = 11;
	}
	else if (!strcmp("lines", ColorMap))
	{
		i = 12;
	}
	else if (!strcmp("colorcube", ColorMap))
	{
		i = 13;
	}
	else if (!strcmp("prism", ColorMap))
	{
		i = 14;
	}
	else if (!strcmp("flag", ColorMap))
	{
		i = 15;
	}


	for (int j = 0; j < 256; j++)
	{
		fgets(buf, 256, bookFile); // Read a line from the with length 256 and take it into buf char array.
		tmp = strtok(buf, ";"); // Since we are using .csv file, buf contains elements that seperated with ;;; values. Hence, we are using strtok function to get wanted colormap values.
		if (i == 0) // If parula is inserted, take first three columns from row 2 to end of the csv file row.
		{
			temp1 = strdup(tmp);
			C[j][0]= (unsigned char)atoi(temp1);
			tmp = strtok(NULL, ";");
			temp1 = strdup(tmp);
			C[j][1] =(unsigned char) atoi(temp1);
			tmp = strtok(NULL, ";");
			temp1 = strdup(tmp);
			C[j][2] =(unsigned char) atoi(temp1);
		}
		else
		{
			// If another colormap value is inserted, we need to dump unnecessary values. With the help of this for loop, we can take the necessary columns to our C matrix.
			// For example, if "hot" colormap value is inserted, which means i = 3, this for loop takes and dumps the first nine columns (hot is 4'th colormap, that means first 3 colormaps(3x3= 9 columns) are unnecessary.)
			// This for loop takes and dumps. It process (i*3)-1 times here, but in line 98 we already take one so we can dump i*3 values.
			for (int l = 1; l < i * 3; l++) 
				tmp = strtok(NULL, ";"); 

			tmp = strtok(NULL, ";"); // Now we can get the R channel of wanted colormap.
			temp1 = strdup(tmp); // Duplicate the tmp value, it was needed because we encountered an error in C processing point of view. Moreover, we need to implement it by our hand because it was not in the built in functions of Labview "string.h" library. However, in Visual Studio there is a built in function indeed.
			C[j][0]= (unsigned char)atoi(temp1); // Change R value to integer then take it as unsigned char because R, G, B must be 8 bits. (Coloured images held with 32 bits (4 bytes) where each of them corresponds to Alpha(1 byte = 8 bits) Red(1 byte = 8 bits) Green(1 byte = 8 bits) Blue (1 byte = 8 bits). Alpha value corresponds to transparency, which is not used for our purposes here, so we gave it as 255.
			tmp = strtok(NULL, ";"); // Take the G channel of wanted colormap.
			temp1 = strdup(tmp); // Duplicate it.
			C[j][1] =(unsigned char) atoi(temp1); // Change G channel to integer then to unsigned char. (8 bits)
			tmp = strtok(NULL, ";"); // Take the B channel of wanted colormap.
			temp1 = strdup(tmp); // Duplicate it.
			C[j][2] =(unsigned char) atoi(temp1); // Change B channel to integer then to unsigned char. (8 bits)

		}
	}


	// Gray Image to RGB conversion is made in this way: Each GrayImage pixel value is between 0-255 (unsigned-256 values) (8 bits representation) and
	// there are 256 rows for each colormap with three channels (RGB respectively). Value of the pixel is mapped to row of the colormap and
    // RGB values are taken accordingly from that row. In conclusion, Gray Image pixel gives us to RGB values according to row of the Colormap matrix and
	// conversion is made. Conversion is explained below.
	unsigned int ColorRow = 0; // ColorRow is indeed the value of the pixel of GrayImage. 
	// As we can see, alpha, red, green, blue variables are defined as "unsigned char" where each of them have 1 byte. (1x4 bytes = 32 bits)
	unsigned char alpha = 255; // It is constant as explained above, transperancy value.
	unsigned char red = 0; // Red value of the ARGB.
	unsigned char green = 0; // Green value of the ARGB.
	unsigned char blue = 0; // Blue value of the ARGB.
	
	unsigned int RGB; // Unsigned int are 4 bytes in our machines, but to not have 2-4 bytes issue it can be defined as uint32_t with the addition of <stdint.h> header. We did not want to increase binary size for just a type definition, but we know the danger of it and how it can be solved if 32bits machines are used.
	// Please refer to here, https://www.tutorialspoint.com/cprogramming/c_data_types.htm
	for( int y = 0; y < LVHeight; y++) // For travelling the rows of image.
	{
		for ( int x = 0; x < LVWidth; x++) // For travelling to columns of image.
		{
			ColorRow = *(GrayImage); // As explained above, take the pixel value of Gray Image which is between 0-255 values.
			red = C[ColorRow][0]; // Take red channel.
			green = C[ColorRow ][1]; // Take green channel.
			blue = C[ColorRow][2]; // Take blue channel.
			RGB = alpha << 24 | red << 16 | green << 8 | blue; // ARGB values are hold in memory with 4 bytes, so we need bit shifting. Labview holds ARGB type. (it can change according to software languages) 
			// Most significant 8 bits are alpha values so shift 24 bits, then shift 16 bits red values, shift 8 bits green values, no need to shift blue values.
			// These 4 channels are concatenated in memory now with the "|" operator between them, and the beauty of it is, it is fast.
			// Please refer here: https://crazybiocomputing.blogspot.com/2017/10/readwrite-pixels-in-rgb-image.html
			*(RGBImage) = RGB; // Assign the RGB value to corresponding pixel value of RGB image.
			
			GrayImage++; // Increase pointers so we can travel the image.
			RGBImage++;

		}
		GrayImage += LVLineWidthGray - LVWidth; // We need to go to new row because all columns are processed, so decrease pointer with the amount columns(LVWidth) then increase LVLineWidth so we can go to new row. LVLineWidthGray is explained in the report.
		RGBImage += LVLineWidthRGB - LVWidth; // Same logic here except that LineWidth is for RGB.
	}
	free(buf); // Free the dynamic buf.
	fclose(bookFile); // Close the file. For video processing, opening and closing the file for each frame maybe not the best choice, but there are ways to open the file as long as it was wanted and close when the all processing is done. However, we did not want to make it more complex our project because it is already satisfying as you will see in the live demo.
	clock_t end = clock(); // Take the new clock time.
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC; // Calculate the time spent.
	return time_spent; // Return the time spent.
}