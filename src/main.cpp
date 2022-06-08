// Cpp include
#include <iostream>
#include <fstream>

// External include
#include <dpp/dpp.h>
#include <dpp/nlohmann/json.hpp>
#include <dpp/fmt/core.h>

// Project include
#include "../commands/ping.h"

using json = nlohmann::json;

int main()
{
	// Reading JSON file
	json reader;
	std::ifstream reading("./config.json", std::ifstream::binary);
	reading >> reader;
	reading.close();

	// Constant
	const auto token = reader["token"].get<std::string>();
	const auto guild_id = reader["guild_id"].get<dpp::snowflake>();

	// Token access
	dpp::cluster client(token);

	// Bot ready
	client.on_ready([&client](const dpp::ready_t& event) {
		fmt::print("Log in as {}.\n", client.me.format_username());
		client.set_presence(dpp::presence(dpp::ps_dnd, dpp::at_watching, "Sword Art Online"));
		});

	// Make commands
	std::vector<dpp::slashcommand> commands
	{
		dpp::slashcommand()
			.set_name("Ping")
			.set_description("Testing ping command")
			.set_application_id(client.me.id),

		dpp::slashcommand()
			.set_name("Hi")
			.set_description("Onli say hi")
			.set_application_id(client.me.id),
	};

	// Guild command create
	client.guild_bulk_command_create(commands, guild_id);
	
	// Starting the bot
	client.start(false);
	dpp::utility::log_error();
	return 0;
}