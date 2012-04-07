#pragma once

#include "Engine/StlCommon.h"

class CommandHandler {
public:
    void executeCommand(const std::string& command);
    void addCommand(const std::string& command, std::function<void()> const& f);

    bool hasCommand(const std::string& command) const;

private:
    std::map<std::string, std::function<void()>> commands;
};