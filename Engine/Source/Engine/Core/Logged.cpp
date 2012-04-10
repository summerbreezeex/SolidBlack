#include <OgreLogManager.h>

#include "Logged.h"

bool Logged::globalLogInitialized = false;
Ogre::Log* Logged::globalLog = nullptr;

Logged::Logged(const std::string& logName) :
        initialized(false),
        logName(logName),
        log(nullptr) {
}

Logged::~Logged() {
    if (initialized) {
        forceDestroy();
    }
}

void Logged::logInfo(const std::string& message) {
    ensureInitialized();

    if (log) {
        log->logMessage(message);
    }

    if (globalLog) {
        globalLog->logMessage(logName + ": " + message);
    }
}

void Logged::logWarning(const std::string& message) {
    ensureInitialized();

    std::string warningMessage(std::string("WARNING: ") + message);

    if (log) {
        log->logMessage(warningMessage);
    }

    if (globalLog) {
        globalLog->logMessage(logName + ": " + warningMessage);
    }
}

void Logged::forceDestroy() {
    initialized = false;
    if (log) {
        Ogre::LogManager::getSingleton().destroyLog(log);
    }
}

void Logged::ensureInitialized() {
    if (!initialized) {
        initializeLog();
    }

    if (!globalLogInitialized) {
        initializeGlobalLog();
    }
}

void Logged::initializeLog() {
    initialized = true;
    log = Ogre::LogManager::getSingleton().createLog(std::string("Logs/") + logName + ".log");
}

void Logged::initializeGlobalLog() {
    globalLogInitialized = true;
    globalLog = Ogre::LogManager::getSingleton().createLog("Logs/SolidBlack.log");
}