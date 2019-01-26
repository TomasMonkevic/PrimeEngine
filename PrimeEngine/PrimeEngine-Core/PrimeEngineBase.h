#pragma once

#include "Utilities/Time.h"
#include "Graphics/Window.h"
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
#ifdef PE_ANDROID
		ANativeWindow* _nativeWindow;
#endif

	private:
		void Run();
	protected:
		virtual void Tick() { };
		virtual void Update() { };
		virtual void Render();



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
		PrimeEngineBase()
		{

		}

		virtual ~PrimeEngineBase()
		{
			_window->Destroy();
		}
#ifdef PE_ANDROID
		inline void SetNativeAndroidWIndow(ANativeWindow* nativeWindow)
		{
			_nativeWindow = nativeWindow;
		}
#endif
		virtual void Awake() = 0;
		void Play();
		void Step();
	};
}