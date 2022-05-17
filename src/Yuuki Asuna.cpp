// Internal include
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

	// Constant
	const auto &token = reader["token"];
	const auto &guild_id = reader["guild_id"];

	// Token access
	dpp::cluster client(token);

	// Interaction create
	client.on_interaction_create([&client](const dpp::interaction_create_t &event) {
		if (event.command.type == dpp::it_application_command)
		{
			// Export command data
			dpp::command_interaction command_data = std::get<dpp::command_interaction>(event.command.data);

			// Slash command lists
			if (command_data.name == "ping") ping_command::ping(event, command_data);
		}
	});

	// Guild command
	client.guild_commands_get(guild_id, [&client, &guild_id](const dpp::confirmation_callback_t& callback) {
		if (!callback.is_error()) {
			auto command_map = std::get<dpp::slashcommand_map>(callback.value);
			for (auto& [name, command] : command_map) {
				client.guild_command_delete(name, guild_id);
			}
		}
		});

	// Bot ready
	client.on_ready([&client](const dpp::ready_t &event) {
		fmt::print("Log in as {}.\n", client.me.format_username());
		client.set_presence(dpp::presence(dpp::ps_dnd, dpp::at_watching, "Sword Art Online"));
	});
	
	// Starting the bot
	client.start(false);
	return 0;
}
