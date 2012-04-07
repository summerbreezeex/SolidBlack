#pragma once

#include <OgrePrerequisites.h>

#include "Engine/StlCommon.h"

class StateManager;

class State {
public:
    State(const std::string& name);
    virtual ~State() { }

    virtual void begin(StateManager* stateManager);
    virtual void end();

    virtual void logicUpdate(Ogre::Real timeStep) { }
    virtual void frameUpdate(Ogre::Real frameDelta) { }

    void setAsInactive();

    const std::string& getName() const;
    bool isActive() const;

protected:
    StateManager* getStateManager();

private:
    StateManager* stateManager;

    std::string name;
    bool active;
};

typedef std::shared_ptr<State> StatePtr;