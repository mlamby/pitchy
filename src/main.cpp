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

template <std::ranges::viewable_range R>
void print_collection(std::string_view name, R&& collection)
{
  std::cout << std::format("{}:[", name);
  for (auto c : collection 
          | std::views::transform([](auto n) { return to_string(n); })
          | std::views::join_with(','))
  {
    std::cout << c;
  }
  std::cout << "] ";
}

void process_midi_messages(pitchy::midi_source &source)
{
  std::vector<pitchy::midi_note> notes_on = {};

  while (source.is_open())
  {
    auto msg = source.get_next_midi_message();
    if (pitchy::update_note_on(notes_on, msg))
    {
      if(std::ranges::empty(notes_on))
      {
        continue;
      }

      // Remove all the octave info and deduplicate.
      const auto& [notes_only, lowest_note] = pitchy::remove_octaves(notes_on);

      print_collection("Midi", notes_on);
      print_collection("Notes", notes_only);
      print_collection("Chords", pitchy::recognise_chord(notes_only, lowest_note));
      std::cout << "\n";
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