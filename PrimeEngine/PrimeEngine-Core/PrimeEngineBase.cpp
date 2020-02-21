#include "PrimeEngineBase.h"

namespace PrimeEngine {

	PrimeEngineBase::~PrimeEngineBase()
	{
		GetWindow()->Destroy();
	}

	void PrimeEngineBase::Render()
	{
		_activeScene->Render();
	}

	void PrimeEngineBase::Run()
	{
		Time timer;
		_fpsCounter = 0;
		while (GetWindow() && !GetWindow()->IsClosed())
		{
			//TODO should call step func
			GetWindow()->Clear();
			Update(); //first frame fps and delta time is 0
			Render();
			GetWindow()->Update();
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

	void PrimeEngineBase::Step()
	{
        if(!GetWindow()->IsReady())
        {
            return;
        }
		static Time timer;
		GetWindow()->Clear();
		Update(); //first frame fps and delta time is 0
		Render();
		GetWindow()->Update();
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

	void PrimeEngineBase::Play()
	{
		Awake();
		Run();
	}

#ifdef PE_ANDROID
	AndroidWindow* PrimeEngineBase::GetWindow() {
		return reinterpret_cast<Graphics::AndroidWindow*>(Graphics::GetWindow());
	}
#else
	DesktopWindow* PrimeEngineBase::GetWindow() {
		return reinterpret_cast<Graphics::DesktopWindow*>(Graphics::GetWindow());
	}
#endif
}