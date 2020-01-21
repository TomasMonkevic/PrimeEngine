#include <Utilities/FileUtils.h>

#include <Graphics/Window.h>
#include <Utilities/Log.h>

namespace PrimeEngine {

    ByteArray ReadFileBytes(const char* path)
    {
        AAssetManager* assetManager = Graphics::Window::GetWindow()->GetNativeActivity()->assetManager;
        AAsset* asset = AAssetManager_open(assetManager, path, AASSET_MODE_BUFFER);
        if (!asset) 
        {
            PRIME_ERROR("File failed to open ", path, '\n');
            return ByteArray();
        }
        unsigned long length = AAsset_getLength64(asset);
        ByteArray data(length);
        int successfullyReadLength = AAsset_read(asset, data.data.get(), length);
        if (successfullyReadLength != data.size)
        {
            PRIME_ERROR("Failed to fully read file ", path, '\n');
            AAsset_close(asset);
            return ByteArray();
        }
        AAsset_close(asset);
        return data;
    }
}