#pragma once

// Cpp include
#include <functional>

// External include
#include <dpp/dpp.h>

// Using shorten
using cmd_function = std::function<void(dpp::cluster&, const dpp::slashcommand_t&)>;

// Make a command definition - Handling commands
struct cmd_def
{
	// Slash command description
	std::string des;

	// Slash command function
	cmd_function func;

	// Slash command parameter
	std::vector<dpp::command_option> param = {};
};