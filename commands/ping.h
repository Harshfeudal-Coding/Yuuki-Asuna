#pragma once

#include "../include.h"

namespace ping_h
{
	void execute(const dpp::interaction_create_t& event, dpp::command_interaction command_data)
	{
		int ping = event.from->websocket_ping * 1000;

		dpp::message mess;
		mess.set_flags(dpp::m_ephemeral);
		std::string str = "Ping: " + std::to_string(ping) + "ms";
		mess.set_content(str);

		event.reply(dpp::ir_channel_message_with_source, mess);
	}
}
