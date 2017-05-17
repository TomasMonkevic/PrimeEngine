#include <fstream>
#include <string>

namespace PrimeEngine {

	class File
	{
		//might need to seperate into 2 files (h, cpp); create a file reading class?
	public:
		static std::string ReadFile(const char* path)
		{
			//preprocessor in game and engine
			FILE *file;
			fopen_s(&file, path, "rt"); //using C file reading for faster performance
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
		}
	};

}