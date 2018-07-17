#pragma once

#include "Utilities\Time.h"
#include "Graphics\Window.h"
#include "Scene.h"
#include "DllExport.h"

namespace PrimeEngine {

	class PRIMEENGINEAPI PrimeEngineBase
	{
	private:
		Graphics::Window* _window = nullptr;
		Scene* _activeScene = nullptr;
		unsigned int _fpsCounter = 0;
		float _deltaTime, _prevDeltatime = 0;

	private:
		void Run();
	protected:
		virtual void Awake() = 0;
		virtual void Tick() { };
		virtual void Update() { };
		virtual void Render();

		PrimeEngineBase()
		{

		}

		virtual ~PrimeEngineBase()
		{
			_window->Destroy();
		}

		void CreateWin(const char* title, int width, int height);
		void CreateWin(const char* title);

		void SetActiveScene(Scene* scene) { _activeScene = scene; }

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