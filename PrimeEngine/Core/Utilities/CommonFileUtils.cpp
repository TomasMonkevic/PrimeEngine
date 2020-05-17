#include <Utilities/FileUtils.h>

namespace PrimeEngine {
	
    std::string ReadFileString(const char* path)
    {
        ByteArray data = ReadFileBytes(path);
        return std::string(reinterpret_cast<char*>(data.data.get()), data.size);
    }
}