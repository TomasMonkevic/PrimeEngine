#ifndef PRIME_ENGINE_H
#define PRIME_ENGINE_H

#include "Utilities\Time.h"
#include "Graphics\Window.h"
//#include <FreeImage.h>
#include "DllExport.h"

namespace PrimeEngine {

	class PrimeEngine
	{
	private:
		Graphics::Window* _window;
		unsigned int _fpsCounter;
		float _deltaTime, _prevDeltatime = 0;

	private:
		void Run()
		{
			Time timer;
			_fpsCounter = 0;
			while (!_window->Closed())
			{
				_window->Clear();
				Update(); //first frame fps and delta time is 0
				Render();
				_window->Update();
				_fpsCounter++;
				_deltaTime = timer.Elapsed() - _prevDeltatime;
				_prevDeltatime = timer.Elapsed();
				if (timer.Elapsed() >= 1.0f)
				{
					Tick();
					_fpsCounter = 0;
					_prevDeltatime = 0;
					timer.Reset();
				}
			}
		}
	protected:
		virtual void Awake() = 0;
		virtual void Tick() { };
		virtual void Update() { };
		virtual void Render() = 0;

		PrimeEngine()
		{

		}

		virtual ~PrimeEngine()
		{
			_window->Destroy();
		}

		void CreateWin(const char* title, int width, int height)
		{
			Graphics::Window::SetWindow(title, width, height);
			_window = Graphics::Window::GetWindow();
			_window->Initialize();
		}

		void CreateWin(const char* title)
		{
			Graphics::Window::SetWindow(title);
			_window = Graphics::Window::GetWindow();
			_window->Initialize();
		}


		inline Graphics::Window* GetWindow()
		{
			return _window;
		}

		inline unsigned int GetFPS() const
		{
			return _fpsCounter;
		}

		inline float GetDeltaTime() const
		{
			return _deltaTime;
		}

	public:
		void Play()
		{
//#ifdef FREEIMAGE_LIB //this should not be here
//			FreeImage_Initialise();
//#endif
			Awake();
			Run();
//#ifdef FREEIMAGE_LIB
//			FreeImage_DeInitialise();
//#endif
		}
	};
}

#endif // !PRIME_ENGINE_H