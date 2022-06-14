// Project include
#include "../commands/handler.h"
#include "../commands/ping.h"

// Dpp include
#include <dpp/fmt/format.h>

// Get username (haven't done)
dpp::user user;

void ping(dpp::cluster& client, const dpp::slashcommand_t& event)
{
	// Make a ping variable
	double ws_ping = client.get_shard(0)->websocket_ping;

	// Setup message reply
	std::string message_content = fmt::format(
		"Asuna measured: {0:.02f} ms", 
		(client.rest_ping + ws_ping) * 1000
	);

	// Message reply
	event.reply(
		dpp::message()
		.set_flags(dpp::m_ephemeral)
		.set_content(message_content)
	);

	// Interaction reply check
	fmt::print(
		"[running] ping command replied from {}\n", 
		user.username
	);
}