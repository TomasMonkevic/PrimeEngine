#include <Graphics/OpenGL.h>
#include <Utilities/Log.h>

namespace PrimeEngine {
	void ClearGlErrors() {
        while(glGetError() != GL_NO_ERROR) {}
    }

	void LogGlCall(const char* file, int line) {
        while(GLenum error = glGetError())
        {
            std::string glErrorText;
            switch(error)
            {
                case GL_INVALID_ENUM:
                    glErrorText = "Invalid enum used";
                    break;
                case GL_INVALID_VALUE:
                    glErrorText = "Invalid value used";
                    break;
                case GL_INVALID_OPERATION:
                    glErrorText = "Invalid operation used";
                    break;
                case GL_INVALID_FRAMEBUFFER_OPERATION:
                    glErrorText = "Invalid framebuffer operation used";
                    break;
                case GL_OUT_OF_MEMORY:
                    glErrorText = "Out of memory";
                    break;
                default:
                    glErrorText = "Unknown OpenGL error";
                    break;
            }
            LogMessage(PRIME_ERROR_L, "[GL_ERROR:", SplitString(file,"\\/").back(), '(', line, ")] ", (int)error, " - ", glErrorText, '\n');
        }
    }
}