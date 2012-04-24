#include <OgreLogManager.h>

#include "Logged.h"

std::map<std::string, Ogre::Log*> Logged::logs;

bool Logged::globalLogsInitialized = false;
Ogre::Log* Logged::globalLog = nullptr;
Ogre::Log* Logged::warningLog = nullptr;
Ogre::Log* Logged::errorLog = nullptr;

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

    if (warningLog) {
        warningLog->logMessage(logName + ": " + warningMessage);
    }
}

void Logged::logError(const std::string& message) {
    ensureInitialized();

    std::string errorMessage(std::string("ERROR: ") + message);

    if (log) {
        log->logMessage(errorMessage);
    }

    if (globalLog) {
        globalLog->logMessage(logName + ": " + errorMessage);
    }

    if (errorLog) {
        errorLog->logMessage(logName + ": " + errorMessage);
    }
}

void Logged::ensureInitialized() {
    if (!initialized) {
        initializeLog();
    }

    if (!globalLogsInitialized) {
        initializeGlobalLogs();
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

void Logged::initializeGlobalLogs() {
    globalLogsInitialized = true;
    globalLog = Ogre::LogManager::getSingleton().createLog("Logs/SolidBlack.log");
    warningLog = Ogre::LogManager::getSingleton().createLog("Logs/Warnings.log");
    errorLog = Ogre::LogManager::getSingleton().createLog("Logs/Errors.log");
}