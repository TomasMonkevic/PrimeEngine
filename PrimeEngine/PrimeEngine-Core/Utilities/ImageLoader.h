#ifndef PRIME_IMAGE_LOADER
#define PRIME_IMAGE_LOADER

#include <FreeImage.h>
#include <iostream> //temp

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

		//BYTE* bits = new BYTE[*width * *height * 4];
		//for (unsigned i = 0; i < *width * *height; i++) //form BGRA to RGBA
		//{
		//	bits[i * 4 + 0] = pixels[i * 4 + 2];
		//	//std::cout << bits[i * 4 + 0] << " ";
		//	bits[i * 4 + 1] = pixels[i * 4 + 1];
		//	//std::cout << bits[i * 4 + 1] << " ";
		//	bits[i * 4 + 2] = pixels[i * 4 + 0];
		//	//std::cout << bits[i * 4 + 2] << " ";
		//	bits[i * 4 + 3] = pixels[i * 4 + 3];
		//	//std::cout << bits[i * 4 + 3] << std::endl;
		//}

		//FreeImage_Unload(dib);
		//clean up memory
		return pixels;
	}
}

#endif // !PRIME_IMAGE_LOADER

