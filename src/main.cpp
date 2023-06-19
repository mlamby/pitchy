#include <pitchy/midi/midi_note_monitor.h>
#include <pitchy/midi/midi_source.h>
#include <pitchy/note.h>
#include <pitchy/chord.h>

#include <cstdint>
#include <iostream>
#include <thread>
#include <vector>
#include <format>

#include "argh.h"

void process_midi_messages(pitchy::midi_source &source)
{
  std::vector<pitchy::midi_note> notes_on = {};

  while (source.is_open())
  {
    auto msg = source.get_next_midi_message();
    if (pitchy::update_note_on(notes_on, msg))
    {
      for (auto r : pitchy::recognise_chord(notes_on))
      {
        std::cout << std::format("{}\n", pitchy::to_string(r));
      }
    }
  }
}

int main(int argc, char *argv[])
{
  try
  {
    auto cmdl = argh::parser(argc, argv);
    pitchy::midi_source source;

    if(source.port_count() == 0)
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
    else
    {
      source.open_named_device("roland");
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