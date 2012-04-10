#ifdef _DEBUG
#include <vld.h>
#endif

#include "Engine/Core/Engine.h"

#include "Game/Logic/TestState.h"

int main(int argc, char *argv[]) {
    try {
        Engine engine;

        if (engine.initialize()) {
            engine.getStateManager()->queueState(new TestState(&engine));
            engine.execute();
        }
    } catch (std::exception& ex) {
#if OGRE_PLATFORM == PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WIN32
        MessageBoxA(NULL, ex.what(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
        cout << "Unhandled exception: " << ex.what() << endl;
#endif
    }
}