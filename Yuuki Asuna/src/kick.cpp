// Project include
#include "../commands/handler.h"
#include "../commands/kick.h"

// Dpp include
#include <dpp/fmt/format.h>

void kick_h(dpp::cluster& client, const dpp::slashcommand_t& event)
{
	// Target a user mentioned
	auto target_user = event.get_parameter("member");

	// Making reason
	std::string reason;	// Still making

	// Check the user if they have permission to kick
	if (event.command.usr != dpp::p_kick_members)
	{
		// Set reply connect when can't kick
		std::string message_content = "Asuna cannot kick because you have no permission :(";

		// Reply when can't kick
		event.reply(
			dpp::message()
			.set_flags(dpp::m_ephemeral)
			.set_content(message_content)
		);
	}
	else
	{
		// Set reply connect when kick
		std::string message_content = fmt::format(
			// I'll soon put the target_user, event.command.usr and reason here
			"Asuna has kicked `{}`, requested from `{}` :(\nFor reason: {}"
		);

		// Reply when kick
		event.reply(
			dpp::message()
			.set_content(message_content)
		);
	}

	// Interaction reply check
	fmt::print(
		"[running] kick command replied from {}\n",
		event.command.usr.format_username()
	);
}