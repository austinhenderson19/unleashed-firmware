#pragma once

#include <cli/cli.h>
#include "../../../../types/plugin_state.h"

#define TOTP_CLI_COMMAND_ADD "add"
#define TOTP_CLI_COMMAND_ADD_ALT "mk"
#define TOTP_CLI_COMMAND_ADD_ALT2 "new"

void totp_cli_command_add_handle(PluginState* plugin_state, FuriString* args, Cli* cli);
void totp_cli_command_add_docopt_commands();
void totp_cli_command_add_docopt_usage();
void totp_cli_command_add_docopt_arguments();
void totp_cli_command_add_docopt_options();