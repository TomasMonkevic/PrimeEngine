#ifndef PRIME_IMAGE_LOADER
#define PRIME_IMAGE_LOADER

#include <FreeImage.h>
#include <iostream> //teamp

namespace PrimeEngine {

	static BYTE* LoadImage(const char* path, unsigned* width, unsigned* height)
	{
		#ifdef FREEIMAGE_LIB //this should not be here
					FreeImage_Initialise();
		#endif
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		FIBITMAP* dib = NULL;
		fif = FreeImage_GetFileType(path, 0);
		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(path);
		if (fif == FIF_UNKNOWN)
			return NULL;
		if (FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, path);
		if (!dib)
			return NULL;

		BYTE* result = FreeImage_GetBits(dib);
		*width = FreeImage_GetWidth(dib);
		*height = FreeImage_GetHeight(dib);

		if ((result == 0) || (width == 0) || (height == 0))
			return NULL;

		//Delete this later:

		//std::cout << *width << " " << *height << std::endl;
		//std::cout << FreeImage_GetImageType(dib) << std::endl;
		//unsigned bytespp = FreeImage_GetPitch(dib);
		//for (unsigned y = 0; y < *height; y++)
		//{
		//	BYTE *pixel = (BYTE*)result;
		//	for (unsigned x = 0; x < *width; x++)
		//	{
		//		// Set pixel color to green with a transparency of 128
		//		std::cout << +pixel[FI_RGBA_RED] << " " << +pixel[FI_RGBA_GREEN] << " " << +pixel[FI_RGBA_BLUE] << " " << +pixel[FI_RGBA_ALPHA] << std::endl;
		//		pixel += 4;
		//		// jump to next pixel
		//	}
		//	result += bytespp;
		//}

		//FreeImage_Unload(dib);
		return result;
	}
}

#endif // !PRIME_IMAGE_LOADER

