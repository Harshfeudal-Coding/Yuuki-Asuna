// Internal include
#include <iostream>
#include <fstream>

// External include
#include <dpp/dpp.h>
#include <dpp/nlohmann/json.hpp>

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

	dpp::cluster client(token);
	client.on_ready([&client](const dpp::ready_t& event) {
		std::cout << "[Link started!] Log in as Yuuki Asuna." << std::endl;
		client.set_presence(dpp::presence(dpp::ps_dnd, dpp::at_watching, "Sword Art Online"));
	});

	// Starting the bot
	client.start(false);
	return 0;
}
