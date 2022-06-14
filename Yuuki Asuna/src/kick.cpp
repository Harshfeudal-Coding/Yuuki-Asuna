// Project include
#include "../commands/handler.h"
#include "../commands/kick.h"

// Dpp include
#include <dpp/fmt/format.h>

void kick_h(dpp::cluster& client, const dpp::slashcommand_t& event)
{
	// Under-construction
	event.reply(
		dpp::message()
		.set_flags(dpp::m_ephemeral)
		.set_content("Still working, cannot kick")
	);

	// Interaction reply check
	fmt::print(
		"[running] kick command replied from {}\n",
		event.command.usr.format_username()
	);
}