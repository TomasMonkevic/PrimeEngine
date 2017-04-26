#include "PrimeEngine.h"

namespace PrimeEngine {

	void PrimeEngineBase::Run()
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

	void PrimeEngineBase::CreateWin(const char* title, int width, int height)
	{
		Graphics::Window::SetWindow(title, width, height);
		_window = Graphics::Window::GetWindow();
		_window->Initialize();
	}

	void PrimeEngineBase::CreateWin(const char* title)
	{
		Graphics::Window::SetWindow(title);
		_window = Graphics::Window::GetWindow();
		_window->Initialize();
	}

	void PrimeEngineBase::Play()
	{
#ifdef FREEIMAGE_LIB
		FreeImage_Initialise();
#endif
		Awake();
		Run();
#ifdef FREEIMAGE_LIB
		FreeImage_DeInitialise();
#endif
	}
}