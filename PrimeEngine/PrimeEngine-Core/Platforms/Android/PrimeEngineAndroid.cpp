/*
 * Copyright 2013 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <jni.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "PrimeEngineAndroid.h"
#include "Game.h"
#include <EGL/egl.h>


static void printGlString(const char* name, GLenum s) {
    const char* v = (const char*)glGetString(s);
    ALOGV("GL %s: %s\n", name, v);
}

static TestGame* testGame = nullptr;

extern "C" {
JNIEXPORT void JNICALL Java_com_tomasmonkevic_primeengineandroid_PrimeEngineLib_init(JNIEnv* env, jobject obj);
JNIEXPORT void JNICALL Java_com_tomasmonkevic_primeengineandroid_PrimeEngineLib_resize(JNIEnv* env, jobject obj, jint width, jint height);
JNIEXPORT void JNICALL Java_com_tomasmonkevic_primeengineandroid_PrimeEngineLib_step(JNIEnv* env, jobject obj);
};

#if !defined(DYNAMIC_ES3)
static GLboolean gl3stubInit() {
    return GL_TRUE;
}
#endif

JNIEXPORT void JNICALL
Java_com_tomasmonkevic_primeengineandroid_PrimeEngineLib_init(JNIEnv* env, jobject obj) {
    if (testGame) {
        delete testGame;
        testGame = nullptr;
    }

    printGlString("Version", GL_VERSION);
    printGlString("Vendor", GL_VENDOR);
    printGlString("Renderer", GL_RENDERER);
    printGlString("Extensions", GL_EXTENSIONS);

    const char* versionStr = (const char*)glGetString(GL_VERSION);
    if (strstr(versionStr, "OpenGL ES 3.")&& gl3stubInit()) {
        eglGetCurrentContext();
        testGame = new TestGame();
        testGame->Awake();
    } else if (strstr(versionStr, "OpenGL ES 2.")) {
    } else {
        ALOGE("Unsupported OpenGL ES version");
    }
}

JNIEXPORT void JNICALL
Java_com_tomasmonkevic_primeengineandroid_PrimeEngineLib_resize(JNIEnv* env, jobject obj, jint width, jint height) {
    if (testGame) {
        //TODO add later
    }
}

JNIEXPORT void JNICALL
Java_com_tomasmonkevic_primeengineandroid_PrimeEngineLib_step(JNIEnv* env, jobject obj) {
    if (testGame) {
        testGame->Step();
    }
}
