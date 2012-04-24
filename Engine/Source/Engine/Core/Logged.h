#pragma once

#include <OgrePrerequisites.h>

#include "Engine/StlCommon.h"

class Logged {
public:
    Logged(const std::string& logName);
    virtual ~Logged() { }

    void logInfo(const std::string& message);
    void logWarning(const std::string& message);
    void logError(const std::string& message);

private:
    void ensureInitialized();
    void initializeLog();
    static void initializeGlobalLogs();

    bool initialized;
    std::string logName;
    Ogre::Log* log;

    static std::map<std::string, Ogre::Log*> logs;

    static bool globalLogsInitialized;
    static Ogre::Log* globalLog;
    static Ogre::Log* warningLog;
    static Ogre::Log* errorLog;
};