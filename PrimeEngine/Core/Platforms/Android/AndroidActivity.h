//
// Created by tomas on 2019-01-26.
//

#pragma once

#include <PrimeEngineBase.h>
#include <android_native_app_glue.h>

namespace PrimeEngine
{
    struct NativeEngineSavedState  {
    };

    class AndroidActivity
    {
        using GameCreator = PrimeEngineBase*(&)();
    private:
        GameCreator _gameCreation;
        struct android_app* _app;

        int _isAnimating;

        PrimeEngineBase* _game;
    public:
        NativeEngineSavedState _state; //TODO add getters and setters
        AndroidActivity(GameCreator gameCreation, struct android_app* app);
        ~AndroidActivity();
        void Play();
        void Init();
        void Draw();
        void Kill();
        inline android_app* GetNativeApp() { return _app; }
    };
}
