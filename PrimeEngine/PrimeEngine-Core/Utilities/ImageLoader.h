#ifndef PRIME_IMAGE_LOADER
#define PRIME_IMAGE_LOADER

#include <FreeImage.h>

namespace PrimeEngine {

	static BYTE* LoadImage(const char* path, unsigned* width, unsigned* height)
	{
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

		unsigned bitsPerPixel = FreeImage_GetBPP(dib);
		//if not 32 bit depth -> convert to it
		//is converting the best solution?
		if (bitsPerPixel != 32)
		{
			FIBITMAP* tempImage = dib;
			dib = FreeImage_ConvertTo32Bits(tempImage);
		}
		//----
		*width = FreeImage_GetWidth(dib);
		*height = FreeImage_GetHeight(dib);
		BYTE* pixels = (BYTE*)FreeImage_GetBits(dib);

		if ((pixels == 0) || (*width == 0) || (*height == 0))
			return NULL;
		//FreeImage_Unload(dib);
		//clean up memory
		return pixels;
	}
}

#endif // !PRIME_IMAGE_LOADER

