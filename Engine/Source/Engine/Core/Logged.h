#pragma once

#include <OgrePrerequisites.h>

#include "Engine/StlCommon.h"

class Logged {
public:
    Logged(const std::string& logName);
    virtual ~Logged() { }

    void logInfo(const std::string& message);
    void logWarning(const std::string& message);

private:
    void ensureInitialized();
    void initializeLog();
    static void initializeGlobalLog();

    bool initialized;
    std::string logName;
    Ogre::Log* log;

    static std::map<std::string, Ogre::Log*> logs;

    static bool globalLogInitialized;
    static Ogre::Log* globalLog;    
};