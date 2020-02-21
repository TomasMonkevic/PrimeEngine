#pragma once

#include <Utilities/Time.h>
#include <Graphics/BasicWindow.h>
#include <Scene.h>
#include <DllExport.h>
#ifndef PE_ANDROID
#include <Platforms/Desktop/DesktopWindow.h>
#else
#include <Platforms/Android/AndroidWindow.h>
#endif

namespace PrimeEngine {

	class PRIMEENGINEAPI PrimeEngineBase
	{
	private:
		Scene* _activeScene = nullptr;
		unsigned int _fpsCounter = 0;
		float _deltaTime, _prevDeltatime = 0;

	private:
		void Run();

	protected:
		virtual void Tick() { };
		virtual void Update() { };
		virtual void Render();

		void SetActiveScene(Scene* scene) { _activeScene = scene; }

		inline unsigned int GetFPS() const
		{
			return _fpsCounter;
		}

		inline float GetDeltaTime() const
		{
			return _deltaTime;
		}

	public:
		virtual ~PrimeEngineBase();
		virtual void Awake() = 0;
		void Play();
		void Step();

#ifdef PE_ANDROID
		AndroidWindow* GetWindow();
#else
		DesktopWindow* GetWindow();
#endif
	};
}