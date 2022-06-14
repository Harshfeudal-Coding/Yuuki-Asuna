// Cpp include
#include <iostream>
#include <fstream>
#include <map>

// Project include
#include "../commands/handler.h"
#include "../commands/ping.h"

// Dpp include
#include <dpp/dpp.h>
#include <dpp/fmt/format.h>
#include <dpp/nlohmann/json.hpp>

// Using shorten
using json = nlohmann::json;

// Building slash commands
std::map<std::string, cmd_def> commands
{
	// Inspired JSON style, remember the name is lowercase
	{
		"ping", { "Check Asuna latecy", ping }
	}
};

int main()
{
	// JSON reading setup
	json reader;
	{
		std::ifstream reading("config.json");
		reading >> reader;
		reading.close();
	}

	// Constant variables
	const std::string token = reader["token"];
	const dpp::snowflake guild_id = reader["guild_id"];
	const dpp::snowflake client_id = reader["client_id"];

	// Bot access
	dpp::cluster client(token);

	/* ------------ After here, we can use client ------------ */

	// Bot ready
	client.on_ready([&client, guild_id, client_id](const dpp::ready_t& event) {
		fmt::print("Log in as {}.\n", client.me.format_username());
		client.set_presence(dpp::presence(dpp::ps_dnd, dpp::at_watching, "Sword Art Online"));

		/*
			Please note:
				- The slash commands are under-construction!
				- If you want to use it in Visual Studio, make a new file called `config.json`.
				- Place your token and guild ID in there, at the same directory of `.gitignore`.
				- I confirmed it works ayyy :>

			Thanks!
		*/

		if (dpp::run_once<struct bulk_register>())
		{
			std::vector<dpp::slashcommand> slash_cmds;

			/*
				- This is the setup of the commands.
				- If you want to delete it, guild or global command(s),
				you just put the note here so that it will pass blank vector.
			*/
			for (auto& def : commands)
			{
				// Make slash commands
				dpp::slashcommand cmd;

				// Slash commands template
				cmd
					.set_name(def.first)
					.set_description(def.second.des)
					.set_application_id(client_id);

				// Option if added
				cmd.options = def.second.param;

				// Push back the vector
				slash_cmds.push_back(cmd);
			}

			
			// Guild slash command create
			client.guild_bulk_command_create(
				slash_cmds,
				guild_id,
				dpp::utility::log_error()	// This is custom, if you want to put it
			);

			// Global slash command create
			// client.global_bulk_command_create(slash_cmds);
		}
		});

	// Slash command ready
	client.on_slashcommand([&client](const dpp::slashcommand_t& event) 
	{
		dpp::command_interaction cmd_data = event.command.get_command_interaction();

		// Command existence check
		auto cmd_filter = commands.find(cmd_data.name);

		// Calling a handler when matching
		if (cmd_filter != commands.end()) 
		{
			cmd_filter->second.func(client, event);
		}
	});

	// Console log (if you don't want to log, just do the note like me)
	// client.on_log(dpp::utility::cout_logger());

	// Bot start
	client.start(false);
	return 0;
}