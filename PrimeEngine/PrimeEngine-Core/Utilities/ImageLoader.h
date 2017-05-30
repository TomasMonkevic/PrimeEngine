#ifndef PRIME_IMAGE_LOADER
#define PRIME_IMAGE_LOADER

#include "Log.h"
#include <FreeImage.h>

namespace PrimeEngine {

	static BYTE* LoadImage(const char* path, unsigned* width, unsigned* height)
	{
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		FIBITMAP* dib = NULL;
		fif = FreeImage_GetFileType(path, 0);

		if (fif == FIF_UNKNOWN)
		{
			fif = FreeImage_GetFIFFromFilename(path);
		}
		if (fif == FIF_UNKNOWN)
		{
			return NULL;
		}
		if (FreeImage_FIFSupportsReading(fif))
		{
			dib = FreeImage_Load(fif, path);
		}
		if (!dib)
		{
			return NULL;
		}

		//if not 32 bit depth -> convert to it
		if (FreeImage_GetBPP(dib) != 32)
		{
			FIBITMAP* tempImage = dib;
			dib = FreeImage_ConvertTo32Bits(tempImage);
		}

		*width = FreeImage_GetWidth(dib);
		*height = FreeImage_GetHeight(dib);
		BYTE* pixels = (BYTE*)FreeImage_GetBits(dib);

		if ((pixels == 0) || (*width == 0) || (*height == 0))
		{
			return NULL;
		}

		BYTE* result = new BYTE[*width * *height * 4];
		memcpy(result, pixels, *width * *height * 4);

		FreeImage_Unload(dib);
		return result;
	}
}

#endif // !PRIME_IMAGE_LOADER

