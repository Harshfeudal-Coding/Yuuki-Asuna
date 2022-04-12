#include "include.h"
#include "commands/commands.h"

using json = nlohmann::json;

int main()
{
	json config;
	std::ifstream file("./config.json");
	file >> config;
	file.close();

	dpp::cluster bot(config["token"], dpp::i_default_intents);
	bot.on_ready([&bot](const dpp::ready_t& event)
		{
			std::cout << "[Link started!] Login as " << bot.me.username << std::endl;
			bot.set_presence(dpp::presence(dpp::ps_dnd, dpp::at_watching, "Sword Art Online"));
		});

	bot.on_interaction_create([&bot](const dpp::interaction_create_t& event)
		{
			if (event.command.type == dpp::it_application_command)
			{
				dpp::command_interaction command_data = std::get<dpp::command_interaction>(event.command.data);

				//Commands tag
				if (command_data.name == "ping") ping_h::execute(event, command_data);
			}
		});

	bot.start(false);
	return 0;
}
