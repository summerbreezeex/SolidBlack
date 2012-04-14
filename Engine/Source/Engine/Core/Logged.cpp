#include <OgreLogManager.h>

#include "Logged.h"

std::map<std::string, Ogre::Log*> Logged::logs;

bool Logged::globalLogInitialized = false;
Ogre::Log* Logged::globalLog = nullptr;

Logged::Logged(const std::string& logName) :
        initialized(false),
        logName(logName),
        log(nullptr) {
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

    auto it = logs.find(logName);

    if (it != logs.end()) {
        log = (*it).second;
    } else {
        log = Ogre::LogManager::getSingleton().createLog(std::string("Logs/") + logName + ".log");
        logs[logName] = log;
    }
}

void Logged::initializeGlobalLog() {
    globalLogInitialized = true;
    globalLog = Ogre::LogManager::getSingleton().createLog("Logs/SolidBlack.log");
}