// Internal include
#include <iostream>
#include <fstream>

// External include
#include <dpp/dpp.h>
#include <dpp/nlohmann/json.hpp>
#include <dpp/fmt/core.h>

using json = nlohmann::json;

int main()
{
	// Reading JSON file
	json reader;
	std::ifstream reading("./config.json", std::ifstream::binary);
	reading >> reader;

	// Constant
	const auto &token = reader["token"];
	const auto &guild_id = reader["guild_id"];

	// Token access
	dpp::cluster client(token);

	// Bot ready
	client.on_ready([&client](const dpp::ready_t& event) {
		fmt::print("Log in as {}.\n", client.me.format_username());
		client.set_presence(dpp::presence(dpp::ps_dnd, dpp::at_watching, "Sword Art Online"));
	});
	
	// Starting the bot
	client.start(false);
	return 0;
}
