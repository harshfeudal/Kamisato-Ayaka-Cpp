// Project include
#include "ping.h"

// External include
#include <spdlog/fmt/fmt.h>

void ping_h(dpp::cluster& client, const dpp::slashcommand_t& event)
{
	// Make a ping variable
	const double ws_ping = client.get_shard(0)->websocket_ping;

	// Setup message reply
	const std::string message_content = fmt::format(
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
		event.command.usr.format_username()
	);
}