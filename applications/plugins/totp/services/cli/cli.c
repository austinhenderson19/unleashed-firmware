// Original idea: https://github.com/br0ziliy

#include "cli.h"
#include <lib/toolbox/args.h>
#include "cli_helpers.h"
#include "commands/list/list.h"
#include "commands/add/add.h"
#include "commands/delete/delete.h"
#include "commands/timezone/timezone.h"
#include "commands/help/help.h"

static void totp_cli_print_unknown_command(FuriString* unknown_command) {
    TOTP_CLI_PRINTF(
        "Command \"%s\" is unknown. Use \"" TOTP_CLI_COMMAND_HELP
        "\" command to get list of available commands.",
        furi_string_get_cstr(unknown_command));
}

static void totp_cli_handler(Cli* cli, FuriString* args, void* context) {
    PluginState* plugin_state = (PluginState*)context;

    FuriString* cmd = furi_string_alloc();

    args_read_string_and_trim(args, cmd);

    if(furi_string_cmp_str(cmd, TOTP_CLI_COMMAND_HELP) == 0 ||
       furi_string_cmp_str(cmd, TOTP_CLI_COMMAND_HELP_ALT) == 0 ||
       furi_string_cmp_str(cmd, TOTP_CLI_COMMAND_HELP_ALT2) == 0 || furi_string_empty(cmd)) {
        totp_cli_command_help_handle();
    } else if(
        furi_string_cmp_str(cmd, TOTP_CLI_COMMAND_ADD) == 0 ||
        furi_string_cmp_str(cmd, TOTP_CLI_COMMAND_ADD_ALT) == 0 ||
        furi_string_cmp_str(cmd, TOTP_CLI_COMMAND_ADD_ALT2) == 0) {
        totp_cli_command_add_handle(plugin_state, args, cli);
    } else if(
        furi_string_cmp_str(cmd, TOTP_CLI_COMMAND_LIST) == 0 ||
        furi_string_cmp_str(cmd, TOTP_CLI_COMMAND_LIST_ALT) == 0) {
        totp_cli_command_list_handle(plugin_state, cli);
    } else if(
        furi_string_cmp_str(cmd, TOTP_CLI_COMMAND_DELETE) == 0 ||
        furi_string_cmp_str(cmd, TOTP_CLI_COMMAND_DELETE_ALT) == 0) {
        totp_cli_command_delete_handle(plugin_state, args, cli);
    } else if(
        furi_string_cmp_str(cmd, TOTP_CLI_COMMAND_TIMEZONE) == 0 ||
        furi_string_cmp_str(cmd, TOTP_CLI_COMMAND_TIMEZONE_ALT) == 0) {
        totp_cli_command_timezone_handle(plugin_state, args, cli);
    } else {
        totp_cli_print_unknown_command(cmd);
    }

    furi_string_free(cmd);
}

void totp_cli_register_command_handler(PluginState* plugin_state) {
    Cli* cli = furi_record_open(RECORD_CLI);
    cli_add_command(
        cli, TOTP_CLI_COMMAND_NAME, CliCommandFlagParallelSafe, totp_cli_handler, plugin_state);
    furi_record_close(RECORD_CLI);
}

void totp_cli_unregister_command_handler() {
    Cli* cli = furi_record_open(RECORD_CLI);
    cli_delete_command(cli, TOTP_CLI_COMMAND_NAME);
    furi_record_close(RECORD_CLI);
}