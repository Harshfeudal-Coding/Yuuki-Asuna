#pragma once

// Cpp include
#include <functional>

// Dpp include
#include <dpp/dpp.h>

// Using shorten
using function = std::function<void(dpp::cluster&, const dpp::slashcommand_t& event)>;

// Make a command definition
struct cmd_def
{
	// Slash command description
	std::string des;

	// Slash command function
	function func;

	// Slash command parameter
	std::vector<dpp::command_option> param{};
};