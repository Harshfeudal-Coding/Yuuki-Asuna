#pragma once

// Internal include
#include <iostream>

// External include
#include <dpp/dpp.h>

namespace ping_h
{
	void ping(const dpp::interaction_create_t& event, dpp::command_interaction commands)
	{
		auto measure = static_cast<int>(event.from->websocket_ping * 1000);

		dpp::message message;
		std::string reply_ping = "The ping latecy is: " + std::to_string(measure) + " ms.";

		message.set_flags(dpp::m_ephemeral);
		message.set_content(reply_ping);

		event.reply(dpp::ir_channel_message_with_source, message);
	}
}
