// Cpp include
#include <iostream>
#include <fstream>

// Project include
#include "../commands/ping.h"

// Dpp include
#include <dpp/dpp.h>
#include <dpp/fmt/format.h>
#include <dpp/nlohmann/json.hpp>

// Using shorten
using json = nlohmann::json;

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

	// Bot access
	dpp::cluster client(token);

	// Bot ready
	client.on_ready([&client, &reader](const dpp::ready_t& event) {
		fmt::print("Log in as {}.\n", client.me.format_username());
		client.set_presence(dpp::presence(dpp::ps_dnd, dpp::at_watching, "Sword Art Online"));

		// Make slash commands
		std::vector<dpp::slashcommand> commands
		{
			dpp::slashcommand()
				.set_name("Ping")
				.set_description("Testing ping command")
				.set_application_id(client.me.id),
			dpp::slashcommand()
				.set_name("Hi")
				.set_description("Only say hi")
				.set_application_id(client.me.id),

			/* Please note:
				- The slash commands are under-construction!
				- If you want to use it in Visual Studio, make a new file called `config.json`
				- Place your token and guild ID in there, at the same directory of `.gitignore`
				
				Thanks!
			*/
		};

		// Guild slash command create
		client.guild_bulk_command_create(
			commands, 
			reader["guild_id"].get<dpp::snowflake>()
		);

		// End of the on_ready
		});

	// Bot start
	client.start(false);
	return 0;
}