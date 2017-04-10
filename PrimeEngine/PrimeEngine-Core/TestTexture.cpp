#include "TestTexture.h"


namespace PrimeEngine {

	bool TestTexture(const char* filename)
	{
#ifdef FREEIMAGE_LIB
		FreeImage_Initialise();
#endif
		//image format
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		//pointer to the image, once loaded
		FIBITMAP *dib(0);
		//pointer to the image data
		BYTE* bits(0);
		//image width and height
		unsigned int width(0), height(0);
		//OpenGL's image ID to map to
		GLuint gl_texID;

		//check the file signature and deduce its format
		fif = FreeImage_GetFileType(filename, 0);
		//if still unknown, try to guess the file format from the file extension
		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(filename);
		//if still unkown, return failure
		if (fif == FIF_UNKNOWN)
			return false;

		//check that the plugin has reading capabilities and load the file
		if (FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, filename);
		//if the image failed to load, return failure
		if (!dib)
			return false;

		//retrieve the image data
		bits = FreeImage_GetBits(dib);
		//get the image width and height
		width = FreeImage_GetWidth(dib);
		height = FreeImage_GetHeight(dib);
		//if this somehow one of these failed (they shouldn't), return failure
		if ((bits == 0) || (width == 0) || (height == 0))
			return false;
		std::cout << width << " " << height << std::endl;
		std::cout << FreeImage_GetImageType(dib) << std::endl;
		unsigned bytespp = FreeImage_GetPitch(dib);
		for (unsigned y = 0; y < height; y++) 
		{
			BYTE *pixel = (BYTE*)bits;
			for (unsigned x = 0; x < width; x++)
			{
				// Set pixel color to green with a transparency of 128
				std::cout << +pixel[FI_RGBA_RED] << " " << +pixel[FI_RGBA_GREEN] << " " << +pixel[FI_RGBA_BLUE] << " " << +pixel[FI_RGBA_ALPHA] << std::endl;
				pixel += 4;
				// jump to next pixel
			}
			bits += bytespp;
		}		FreeImage_Unload(dib);
		system("PAUSE");
	}
}