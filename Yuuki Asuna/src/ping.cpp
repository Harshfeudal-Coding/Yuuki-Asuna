// Project include
#include "../commands/ping.h"

// Dpp include
#include <dpp/fmt/format.h>

void ping(dpp::cluster& client, const dpp::slashcommand_t& event)
{
	// Make a ping variable
	double ws_ping = client.get_shard(0)->websocket_ping;

	// Setup message reply
	dpp::message message;
	std::string message_content = fmt::format("Asuna measured: {0:.02f} ms", (client.rest_ping + ws_ping) * 1000);

	// Message output ready
	message.set_flags(dpp::m_ephemeral);
	message.set_content(message_content);
	event.reply(dpp::ir_channel_message_with_source, message_content);
}