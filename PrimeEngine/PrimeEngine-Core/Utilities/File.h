#pragma once

#include <fstream>
#include <cstring>
#ifdef PE_ANDROID
#include <Graphics/Window.h>
#endif

namespace PrimeEngine {

	class File
	{
		//might need to seperate into 2 files (h, cpp); create a file reading class?
	public:
		// TODO later remove ifdefs and move to dedicated files
		static std::string ReadFile(const char* path) //return uint8_t array
		{
#ifdef PE_ANDROID
			AAssetManager* assetManager = Graphics::Window::GetWindow()->GetNativeActivity()->assetManager;
			AAsset* asset = AAssetManager_open(assetManager, path, AASSET_MODE_BUFFER);
			unsigned long length = AAsset_getLength64(asset); //get the size(number of bytes) of the file
			uint8_t* data = new uint8_t[length + 1]; //TODO use unique ptr
			memset(data, 0, length + 1); //char 1 byte so => lenght+1
			//AAsset_seek64(AAsset *asset, off64_t offset, int whence) seek to zero?
			int len = AAsset_read(asset, data, length);
			std::string result((char*)data); //moving data to string is not needed
			delete[] data;
			return result;
#else
			//preprocessor in game and engine
			FILE* file;
			#ifdef _WIN32
				fopen_s(&file, path, "rt"); //using C file reading for faster performance
			#else
				file = fopen(path, "rt"); //using C file reading for faster performance
			#endif
			if (!file)
			{
				throw "File failed to open";
			}
			fseek(file, 0, SEEK_END); //navigate to the end of file
			unsigned long lenght = ftell(file); //get the size(nuber of bytes) of the file
			char* data = new char[lenght + 1];
			memset(data, 0, lenght + 1); //char 1 byte so => lenght+1
			fseek(file, 0, SEEK_SET); //reset to the begging for reading
			fread(data, 1, lenght + 1, file); //read the data

			std::string result(data);
			delete[] data;
			return result;
#endif
		}

        static bool ReadFileBytes(const char* path, uint8_t** dataOut, size_t& lenOut) //return uint8_t array
        {
#ifdef PE_ANDROID
            AAssetManager *assetManager = Graphics::Window::GetWindow()->GetNativeActivity()->assetManager;
            AAsset *asset = AAssetManager_open(assetManager, path, AASSET_MODE_BUFFER);
            unsigned long length = AAsset_getLength64(
                    asset); //get the size(number of bytes) of the file
            *dataOut = new uint8_t[length + 1]; //TODO use unique ptr
            memset(*dataOut, 0, length + 1); //char 1 byte so => lenght+1
            //AAsset_seek64(AAsset *asset, off64_t offset, int whence) seek to zero?
            int len = AAsset_read(asset, *dataOut, length);
            lenOut = len;
            return true;
#endif
        }
	};
}