#ifndef PITCHY_MIDI_PROCESSOR_H
#define PITCHY_MIDI_PROCESSOR_H

#include <pitchy/midi/midi_source.h>
#include <pitchy/midi/midi_note_monitor.h>
#include <pitchy/note.h>
#include <pitchy/chord.h>

#include <iostream>
#include <format>
#include <vector>
#include <ranges>

namespace pitchy
{
  namespace detail
  {
    template <std::ranges::viewable_range R>
    void print_collection(std::string_view name, R &&collection)
    {
      std::cout << std::format("{}:[", name);
      for (auto c : collection | std::views::transform([](auto n)
                                                       { return to_string(n); }) |
                        std::views::join_with(','))
      {
        std::cout << c;
      }
      std::cout << "] ";
    }
  }

  void process_midi_messages(pitchy::midi_source &source)
  {
    // A collection of notes that are currently being held down
    // on the midi device.
    std::vector<pitchy::midi_note> notes_on = {};

    while (source.is_open())
    {
      // Get the next midi message from the hardware device.
      // This call will block until a midi message becomes available.
      auto msg = source.get_next_midi_message();

      // Procecss the midi messages and update the collection of notes that
      // are currently on.
      if (pitchy::update_note_on(notes_on, msg))
      {
        // Remove all the octave info.
        // After removing the octave info there may be two instances of the
        // same note - e.g. C3 and C4 becomes C and C, the remove_octaves
        // function also removes any resulting duplicates.
        const auto &[notes_only, lowest_note] = pitchy::remove_octaves(notes_on);

        // Find all the chords that could be made with the combination
        // of currently playing notes (if any).
        const auto &chords = pitchy::recognise_chord(notes_only, lowest_note);

        // Print the collection of currently playing raw midi notes.
        detail::print_collection("Midi", notes_on);

        // Also print the collection of de-duplicated notes with their octaves
        // removed.
        detail::print_collection("Notes", notes_only);

        // Print the chords.
        detail::print_collection("Chords", chords);
        std::cout << "\n";
      }
    }
  }
}

#endif