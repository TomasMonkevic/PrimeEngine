#ifndef PRIME_ENGINE_H
#define PRIME_ENGINE_H

#include "Utilities\Time.h"
#include "Graphics\Window.h"
#include <FreeImage.h>
#include "DllExport.h"

namespace PrimeEngine {

	class PRIMEENGINEAPI PrimeEngine
	{
	private:
		Graphics::Window* _window;
		unsigned int _fpsCounter;
		float _deltaTime, _prevDeltatime = 0;

	private:
		void Run();
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

#endif // !PRIME_ENGINE_H