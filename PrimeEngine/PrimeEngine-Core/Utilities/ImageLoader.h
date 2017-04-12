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
		FIBITMAP* bitmap32;
		//if not 32 bit depth -> convert to it
		//is converting the best solution?
		if (bitsPerPixel == 32)
		{
			bitmap32 = dib;
		}
		else
		{
			bitmap32 = FreeImage_ConvertTo32Bits(dib);
		}
		//----
		BYTE* result = FreeImage_GetBits(bitmap32);
		*width = FreeImage_GetWidth(bitmap32);
		*height = FreeImage_GetHeight(bitmap32);

		if ((result == 0) || (width == 0) || (height == 0))
			return NULL;
		//FreeImage_Unload(dib);
		return result;
	}
}

#endif // !PRIME_IMAGE_LOADER

