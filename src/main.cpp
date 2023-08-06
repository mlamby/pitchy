#include <pitchy/midi/midi_source.h>

#include "midi_processor.h"

#include <iostream>
#include <format>
#include <string_view>

#include "argh.h"

std::string_view help_message = R"(
pitchy [-l | --list] [-h | --help] <midi_device_name>

  <midi_device_name>  The name (or part of the name) of the midi input device to open.
                      The midi device name is case-insensitive.
                      If no value is given then the default midi device will be used.

  [-l | --list]       Print a list of available midi devices
  [-h | --help]       Print this help message

)";

int main(int argc, char *argv[])
{
  try
  {
    auto cmdl = argh::parser(argc, argv);
    const auto &pos_args = cmdl.pos_args();
    pitchy::midi_source source;

    if (source.port_count() == 0)
    {
      std::cout << "No midi input ports available\n";
      return 1;
    }

    if (cmdl[{"-l", "--list"}])
    {
      std::cout << "Available midi ports:\n";
      for (auto p : source.port_names())
      {
        std::cout << std::format("  {}\n", p);
      }
    }
    else if (cmdl[{"-h", "--help"}])
    {
      std::cout << help_message;
    }
    else if (pos_args.size() > 1)
    {
      source.open_named_device(pos_args[1]);
    }
    else
    {
      source.open_default_device();
    }

    if (source.is_open())
    {
      // Start processing midi messages.
      process_midi_messages(source);
    }
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }

  return 0;
}