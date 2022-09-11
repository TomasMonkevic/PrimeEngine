#include <Platforms/Android/AndroidWindow.h>

#include <Utilities/Log.h>
#include <memory.h>

namespace PrimeEngine
{
	namespace Graphics
	{
        BasicWindow* GetWindow() {
            static std::unique_ptr<BasicWindow> window(new AndroidWindow());
            return window.get();
        }

		AndroidWindow::~AndroidWindow() {}

        void AndroidWindow::SetNativeAndroidWIndow(ANativeWindow* nativeWindow)
        {
            _nativeWindow = nativeWindow;
        }

        void AndroidWindow::SetNativeAndroidActivity(ANativeActivity* nativeActivity)
        {
            _nativeActivity = nativeActivity;
        }

        ANativeActivity* AndroidWindow::GetNativeActivity() {
            return _nativeActivity;
        }

		void AndroidWindow::Initialize()
		{
			const int attrib_list[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
			const EGLint attribs[] = {
					EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT, // request OpenGL ES 2.0
					EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
					EGL_BLUE_SIZE, 8,
					EGL_GREEN_SIZE, 8,
					EGL_RED_SIZE, 8,
					EGL_DEPTH_SIZE, 16,
					EGL_NONE
			};
			EGLint format;
			EGLint numConfigs;
			EGLConfig config;

			_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

			eglInitialize(_display, 0, 0);

			/* Here, the application chooses the configuration it desires.
             * find the best match if possible, otherwise use the very first one
             */
			eglChooseConfig(_display, attribs, nullptr,0, &numConfigs);
			std::unique_ptr<EGLConfig[]> supportedConfigs(new EGLConfig[numConfigs]);
			//assert(supportedConfigs);
			eglChooseConfig(_display, attribs, supportedConfigs.get(), numConfigs, &numConfigs);
			//assert(numConfigs);
			auto i = 0;
			for (; i < numConfigs; i++) {
				auto& cfg = supportedConfigs[i];
				EGLint r, g, b, d;
				if (eglGetConfigAttrib(_display, cfg, EGL_RED_SIZE, &r)   &&
					eglGetConfigAttrib(_display, cfg, EGL_GREEN_SIZE, &g) &&
					eglGetConfigAttrib(_display, cfg, EGL_BLUE_SIZE, &b)  &&
					eglGetConfigAttrib(_display, cfg, EGL_DEPTH_SIZE, &d) &&
					r == 8 && g == 8 && b == 8 && d == 0 ) {

					config = supportedConfigs[i];
					break;
				}
			}
			if (i == numConfigs) {
				config = supportedConfigs[0];
			}

			/* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
             * guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
             * As soon as we picked a EGLConfig, we can safely reconfigure the
             * ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
			eglGetConfigAttrib(_display, config, EGL_NATIVE_VISUAL_ID, &format);
			_surface = eglCreateWindowSurface(_display, config, _nativeWindow, NULL);
			_context = eglCreateContext(_display, config, NULL, attrib_list);

			if (eglMakeCurrent(_display, _surface, _surface, _context) == EGL_FALSE) {
				PRIME_WARNING("Unable to eglMakeCurrent");
				return;
			}

			eglQuerySurface(_display, _surface, EGL_WIDTH, &_width);
			eglQuerySurface(_display, _surface, EGL_HEIGHT, &_height);

			GlCall(glViewport(0, 0, _width, _height));

			GlCall(glEnable(GL_BLEND));
			GlCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

			//GlCall(glEnable(GL_MULTISAMPLE));

			PRIME_INFO(glGetString(GL_VERSION), "\n");
			PRIME_INFO(glGetString(GL_VENDOR), "\n");
			PRIME_INFO(glGetString(GL_RENDERER), "\n");
		}

		void AndroidWindow::Update()
		{
            eglSwapBuffers(_display, _surface);
		}

		bool AndroidWindow::IsReady() const {
			return _display;
		}

		void AndroidWindow::Destroy()
		{
			if (_display != EGL_NO_DISPLAY)
            {
                eglMakeCurrent(_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
                if (_context != EGL_NO_CONTEXT)
                {
                    eglDestroyContext(_display, _context);
                }
                if (_surface != EGL_NO_SURFACE)
                {
                    eglDestroySurface(_display, _surface);
                }
                eglTerminate(_display);
            }
            _display = EGL_NO_DISPLAY;
            _context = EGL_NO_CONTEXT;
            _surface = EGL_NO_SURFACE;
		}

		bool AndroidWindow::IsClosed() const
		{
			return false;
		}
	}
}