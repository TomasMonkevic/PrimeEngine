#pragma once

#include "Utilities\Time.h"
#include "Graphics\Window.h"
#include "DllExport.h"

namespace PrimeEngine {

	class PRIMEENGINEAPI PrimeEngineBase
	{
	private:
		Graphics::Window* _window = NULL;
		unsigned int _fpsCounter = 0;
		float _deltaTime, _prevDeltatime = 0;

	private:
		void Run();
	protected:
		virtual void Awake() = 0;
		virtual void Tick() { };
		virtual void Update() { };
		virtual void Render() = 0;

		PrimeEngineBase()
		{

		}

		virtual ~PrimeEngineBase()
		{
			_window->Destroy();
		}

		void CreateWin(const char* title, int width, int height);
		void CreateWin(const char* title);

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
		void Play();
	};
}