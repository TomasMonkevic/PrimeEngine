//
// Created by tomas on 2019-01-26.
//
#include "AndroidActivity.h"
#include <memory.h>
#include <Input.h>

namespace PrimeEngine
{

    /**
 * Process the next input event.
 */
    static int32_t engine_handle_input(struct android_app* app, AInputEvent* event) {
        AndroidActivity* engine = (AndroidActivity*)app->userData;
        Input::InputPC::isClear = false;

        if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION)
        {
            int32_t touchCount = AMotionEvent_getPointerCount(event);

            int action = AMotionEvent_getAction(event);
            int actionMasked = action & AMOTION_EVENT_ACTION_MASK;
            int ptrIndex = (action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK) >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;

            if (actionMasked == AMOTION_EVENT_ACTION_DOWN || actionMasked ==
                                                             AMOTION_EVENT_ACTION_POINTER_DOWN)
            {
                PRIME_INFO("ACTION DOWN ", ptrIndex);
            }
            else if (actionMasked == AMOTION_EVENT_ACTION_UP || actionMasked ==
                                                                  AMOTION_EVENT_ACTION_POINTER_UP)
            {
                PRIME_INFO("ACTION UP ", ptrIndex);
                if(touchCount == 1)
                {
                    Input::InputPC::isClear = true;
                }
            }
            else
            {
                PRIME_INFO("ACTION MOVE ", ptrIndex);
            }

            Input::InputPC::touchCount = touchCount;
            Input::InputPC::touches.clear();
            for(int i=0; i<touchCount; i++) {
                Input::Touch touch;
                touch.fingerId = AMotionEvent_getPointerId(event, i);
                Math::Vector2 currentPos(AMotionEvent_getX(event, i), AMotionEvent_getY(event, i));
                //touch.deltaPosition = touch.position - currentPos;
                touch.position = currentPos;
                Input::InputPC::touches.emplace_back(std::move(touch));
            }
        }
        return 0;
    }

/**
 * Process the next main command.
 */
    static void engine_handle_cmd(struct android_app* app, int32_t cmd) {
        AndroidActivity* engine = (AndroidActivity*)app->userData;
        switch (cmd) {
            case APP_CMD_SAVE_STATE:
                // The system has asked us to save our current state.  Do so.
                engine->GetNativeApp()->savedState = malloc(sizeof(NativeEngineSavedState));
                *((NativeEngineSavedState*)engine->GetNativeApp()->savedState) = engine->_state;
                engine->GetNativeApp()->savedStateSize = sizeof(NativeEngineSavedState);
                break;
            case APP_CMD_INIT_WINDOW:
                // The window is being shown, get it ready.
                if (engine->GetNativeApp()->window != NULL) {
                    engine->Init();
                    engine->Draw();
                }
                break;
            case APP_CMD_TERM_WINDOW:
                // The window is being hidden or closed, clean it up.
                engine->Kill();
                break;
            case APP_CMD_GAINED_FOCUS:
                break;
            case APP_CMD_LOST_FOCUS:
                // Also stop animating.
                //engine->animating = 0;
                engine->Draw();
                break;
        }
    }

    AndroidActivity::AndroidActivity(GameCreator gameCreation, struct android_app* app)
            : _gameCreation(gameCreation), _app(app)
    {
        _isAnimating = 0;
        memset(&_state, 0, sizeof(_state));
    }

    AndroidActivity::~AndroidActivity()
    {
        Kill();
    }

    void AndroidActivity::Init()
    {
        Input::InputPC::Initalize();
        _game = _gameCreation();
        _game->SetNativeAndroidWIndow(_app->window);
        _game->Awake();
        _isAnimating = 1;
    }
    void AndroidActivity::Draw()
    {
        if(_game)
        {
            _game->Step();
            Input::InputPC::ClearTouches();
        }
    }
    void AndroidActivity::Kill()
    {
        if(_game)
        {
            _isAnimating = 0;
            delete _game;
            _game = nullptr;
            Input::InputPC::ClearTouches();
        }
    }

    void AndroidActivity::Play()
    {
        _app->userData = this;
        _app->onAppCmd = engine_handle_cmd;
        _app->onInputEvent = engine_handle_input;

        if (_app->savedState != NULL) {
            // We are starting with a previous saved state; restore from it.
            _state = *(NativeEngineSavedState*)_app->savedState;
        }

        // loop waiting for stuff to do.

        while (1) {
            // Read all pending events.
            int ident;
            int events;
            struct android_poll_source* source;

            // If not animating, we will block forever waiting for events.
            // If animating, we loop until all events are read, then continue
            // to draw the next frame of animation.
            while ((ident=ALooper_pollAll(_isAnimating ? 0 : -1, NULL, &events,
                                          (void**)&source)) >= 0) {

                // Process this event.
                if (source != NULL) {
                    source->process(_app, source);
                }

                // Check if we are exiting.
                if (_app->destroyRequested != 0) {
                    return;
                }
            }

            if (_isAnimating) {
                // Drawing is throttled to the screen update rate, so there
                // is no need to do timing here.
                Draw();
            }
        }
    }
}
