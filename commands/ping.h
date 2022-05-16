#pragma once

// Internal include
#include <iostream>

// External include
#include <dpp/dpp.h>
#include <dpp/fmt/format.h>

namespace ping_h
{
	void ping(const dpp::interaction_create_t& event, dpp::command_interaction commands)
	{
		// Measure the ping latecy
		auto measure = static_cast<int>(event.from->websocket_ping * 1000);

		// Message setup
		dpp::message message;
		std::string reply_ping = fmt::format("The ping latecy is {} ms.", std::to_string(measure));

		// Message interface
		message.set_flags(dpp::m_ephemeral);
		message.set_content(reply_ping);

		// Message send
		event.reply(dpp::ir_channel_message_with_source, message);
	}
}
