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
			Color _color = Color::White();
			int _width, _height;
			GLFWwindow* _window;
			bool _isFullScreen;

		public:
			virtual ~DesktopWindow();

			void SetFullscreen(bool isFullscreen);
			void EnableVSync(bool isEnabled);
			void Close();

			// overriden from BasicWindow
			void Initialize() override;
			void Update() override;
			void Clear() override;
			bool IsReady() const override;
			void Destroy() override;
			bool IsClosed() const override;

			void SetTitle(const char* title) override;
			const char* GetTitle() const override;

			void SetSize(int width, int height) override;
			Math::Vector2 GetSize() const override;

			void SetColor(const Color& color) override;
			const Color& GetColor() const override;
		};
	}
}