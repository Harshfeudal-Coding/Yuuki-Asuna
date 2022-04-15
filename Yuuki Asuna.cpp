#include "include.h"
#include "commands/commands.h"

using json = nlohmann::json;

int main()
{
	json config;
	std::ifstream file("./config.json");
	file >> config;
	file.close();

	const dpp::snowflake GUILD_ID = 874245742888366150;

	dpp::cluster bot(config["token"], dpp::i_default_intents);
	bot.on_ready([&bot](const dpp::ready_t& event)
		{
			std::cout << "[Link started!] Login as " << bot.me.username << std::endl;
			bot.set_presence(dpp::presence(dpp::ps_dnd, dpp::at_watching, "Sword Art Online"));
		});

	bot.start(false);
	return 0;
}
