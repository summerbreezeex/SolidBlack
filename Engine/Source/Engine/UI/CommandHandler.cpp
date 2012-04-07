#include "CommandHandler.h"

void CommandHandler::executeCommand(const std::string& command) {
    commands[command]();
}

void CommandHandler::addCommand(const std::string& command, std::function<void()> const& f) {
    commands[command] = f;
}

bool CommandHandler::hasCommand(const std::string& command) const {
    return commands.find(command) != commands.end();
}