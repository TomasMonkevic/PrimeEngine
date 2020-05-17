#include <Utilities/FileUtils.h>

#include <fstream>
#include <cstring>

#include <Utilities/Log.h>

namespace PrimeEngine {
	
    ByteArray ReadFileBytes(const char* path)
    {
        FILE* file;
        #ifdef _WIN32
            fopen_s(&file, path, "rb"); //using C file reading for faster performance
        #else
            file = fopen(path, "rb"); //using C file reading for faster performance
        #endif
        if (!file)
        {
            PRIME_ERROR("File failed to open ", path, '\n');
            return ByteArray();
        }
        fseek(file, 0, SEEK_END); //navigate to the end of file
        unsigned long length = ftell(file); //get the size(nuber of bytes) of the file
        ByteArray data(length);
        fseek(file, 0, SEEK_SET); //reset to the begging for reading
        size_t successfullyReadLength = fread(data.data.get(), 1, length, file); //read the data
        if (successfullyReadLength != data.size) 
        {
            PRIME_ERROR("Failed to fully read file ", path, '\n');
            fclose(file);
            return ByteArray();
        }
        fclose(file);
        return data;
    }
}