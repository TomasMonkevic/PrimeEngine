#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "../Utilities/Log.h"
#ifdef PE_ANDROID
#include <Graphics/Window.h>
#endif

namespace PrimeEngine { namespace Graphics {

	Texture::Texture(const Color& color) //TODO remove duplicate code
	{
		glGenTextures(1, &_Id);

		GLubyte data[] = { color[0] * 255, color[1] * 255, color[2] * 255, color[3] * 255 };

		glBindTexture(GL_TEXTURE_2D, _Id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		_width = 1;
		_height = 1;
	}

	Texture::Texture(const char* path)
		: _path(path)
	{
		_Id = Load();
	}

	Texture::~Texture()
	{
		Unbind();
		glDeleteTextures(1, &_Id);
	}

	GLuint Texture::Load()
	{
		GLuint result;
		glGenTextures(1, &result);
		glBindTexture(GL_TEXTURE_2D, result);

		stbi_set_flip_vertically_on_load(1);
#ifdef PE_ANDROID
		//TODO move to readfile
		AAssetManager* assetManager = Graphics::Window::GetWindow()->GetNativeActivity()->assetManager;
        AAssetDir* assetDir = AAssetManager_openDir(assetManager, "Textures");
        const char* filename = (const char*)NULL;
        while ((filename = AAssetDir_getNextFileName(assetDir)) != NULL) {
            PRIME_INFO(filename, '\n');
        }
		AAsset* asset = AAssetManager_open(assetManager, _path, AASSET_MODE_BUFFER);
		unsigned long length = AAsset_getLength64(asset); //get the size(number of bytes) of the file
		uint8_t* data = new uint8_t[length + 1]; //TODO use unique ptr
		memset(data, 0, length + 1); //char 1 byte so => lenght+1
		//AAsset_seek64(AAsset *asset, off64_t offset, int whence) seek to zero?
		int len = AAsset_read(asset, data, length);

		unsigned char* image = stbi_load_from_memory(data, length + 1, &_width, &_height, nullptr, 4);
		delete[] data;
#else
		unsigned char* image = stbi_load(_path, &_width, &_height, nullptr, 4);
#endif
		if(!image)
		{
			PRIME_WARNING(
				_path, " Width: ", _width, " Height:", _height, '\n', 
				stbi_failure_reason(), " ", errno, '\n');
		}

		// Set the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		//glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(image);
		return result;
	}

	void Texture::Bind() const
	{
		glBindTexture(GL_TEXTURE_2D, _Id);
	}

	void Texture::Activate(unsigned i)
	{
		glActiveTexture(GL_TEXTURE0 + i);
	}

	void Texture::Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}}