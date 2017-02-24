#ifndef PRIMEENGINE_H
#define PRIMEENGINE_H

#include "Utilities\Time.h"
#include "Graphics\Window.h"
#include "DllExport.h"

namespace PrimeEngine {

	class PrimeEngine
	{
	private:
		Graphics::Window* _window;
		unsigned int _fpsCounter, _deltaTime; //not implemented
		bool _vSync; //yet to be implemented

	private:
		void Run()
		{
			Time timer;
			_fpsCounter = 0;
			while (!_window->Closed())
			{
				_window->Clear();
				Update();
				Render();
				_window->Update();
				_fpsCounter++;
				if (timer.Elapsed() >= 1.0f)
				{
					Tick();
					_fpsCounter = 0;
					timer.Reset();
				}
			}
		}
	protected:
		virtual void Awake() = 0;
		virtual void Tick() { };
		virtual void Update() { };
		virtual void Render() = 0;

		PrimeEngine(bool vSync) : _vSync(vSync)
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

		inline unsigned int GetDeltaTime() const
		{
			return _deltaTime;
		}

	public:
		void Play()
		{
			Awake();
			Run();
		}
	};
}

#endif // !PRIMEENGINE_H