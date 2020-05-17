#pragma once

#include <DllExport.h>
#include <Graphics/OpenGL.h>
#include <Graphics/BasicWindow.h>

namespace PrimeEngine
{
	namespace Graphics
	{
		class PRIMEENGINEAPI DesktopWindow : public BasicWindow
		{
		private:
			const char* _title = "PrimeEngine";
			GLFWwindow* _window;
			bool _isFullScreen;

		public:
			virtual ~DesktopWindow();

			void SetFullscreen(bool isFullscreen);
			void EnableVSync(bool isEnabled);
			void Close();

			void SetTitle(const char* title);
			const char* GetTitle() const;

			// overriden from BasicWindow
			void Initialize() override;
			void Update() override;
			bool IsReady() const override;
			void Destroy() override;
			bool IsClosed() const override;
		};
	}
}