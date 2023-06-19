#include "pitchy/midi/midi_note_monitor.h"

#include <catch2/catch_test_macros.hpp>
#include <algorithm>

using namespace pitchy;

namespace
{
  // Helper functions to build midi_parse_result variants.
  // The midi_note_monitor does not use the channel or
  // velocity information, so this is not set.

  midi_parse_result note_on(midi_note n)
  {
    return midi_note_on_message{.note = n};
  }

  midi_parse_result note_off(midi_note n)
  {
    return midi_note_off_message{.note = n};
  }

  midi_parse_result no_message()
  {
    return std::monostate{};
  }

} // namespace

TEST_CASE("MidiNoteMonitor_Monitors", "")
{
  note_on_collection_type notes_on;

  REQUIRE(!std::ranges::contains(notes_on, midi_note::C4));
  REQUIRE(!std::ranges::contains(notes_on, midi_note::F3));
  REQUIRE(!std::ranges::contains(notes_on, midi_note::G6));
  REQUIRE(notes_on.size() == 0);

  // Add C4 to the list
  REQUIRE(update_note_on(notes_on, note_on(midi_note::C4)));
  REQUIRE(std::ranges::contains(notes_on, midi_note::C4));
  REQUIRE(notes_on.size() == 1);

  // Add C4 again - should return false since there is no change to the list.
  REQUIRE(!update_note_on(notes_on, note_on(midi_note::C4)));

  // Add F3 to the list
  REQUIRE(update_note_on(notes_on, note_on(midi_note::F3)));
  REQUIRE(std::ranges::contains(notes_on, midi_note::C4));
  REQUIRE(std::ranges::contains(notes_on, midi_note::F3));
  REQUIRE(notes_on.size() == 2);

  // Add G6 to the list
  REQUIRE(update_note_on(notes_on, note_on(midi_note::G6)));
  REQUIRE(std::ranges::contains(notes_on, midi_note::C4));
  REQUIRE(std::ranges::contains(notes_on, midi_note::F3));
  REQUIRE(std::ranges::contains(notes_on, midi_note::G6));
  REQUIRE(notes_on.size() == 3);

  // Make sure the list is ordered
  REQUIRE(notes_on[0] == midi_note::F3);
  REQUIRE(notes_on[1] == midi_note::C4);
  REQUIRE(notes_on[2] == midi_note::G6);

  // Calling with an empty/monostate message has no effect
  REQUIRE(!update_note_on(notes_on, no_message()));
  REQUIRE(std::ranges::contains(notes_on, midi_note::C4));
  REQUIRE(std::ranges::contains(notes_on, midi_note::F3));
  REQUIRE(std::ranges::contains(notes_on, midi_note::G6));
  REQUIRE(notes_on.size() == 3);

  // Remove G6
  REQUIRE(update_note_on(notes_on, note_off(midi_note::G6)));
  REQUIRE(std::ranges::contains(notes_on, midi_note::C4));
  REQUIRE(std::ranges::contains(notes_on, midi_note::F3));
  REQUIRE(!std::ranges::contains(notes_on, midi_note::G6));
  REQUIRE(notes_on.size() == 2);

  // Remove C4
  REQUIRE(update_note_on(notes_on, note_off(midi_note::C4)));
  REQUIRE(!std::ranges::contains(notes_on, midi_note::C4));
  REQUIRE(std::ranges::contains(notes_on, midi_note::F3));
  REQUIRE(!std::ranges::contains(notes_on, midi_note::G6));
  REQUIRE(notes_on.size() == 1);

  // Remove F3
  REQUIRE(update_note_on(notes_on, note_off(midi_note::F3)));
  REQUIRE(!std::ranges::contains(notes_on, midi_note::C4));
  REQUIRE(!std::ranges::contains(notes_on, midi_note::F3));
  REQUIRE(!std::ranges::contains(notes_on, midi_note::G6));
  REQUIRE(std::ranges::empty(notes_on));

  // Remove F3 again - no change
  REQUIRE(!update_note_on(notes_on, note_off(midi_note::F3)));
  REQUIRE(!std::ranges::contains(notes_on, midi_note::C4));
  REQUIRE(!std::ranges::contains(notes_on, midi_note::F3));
  REQUIRE(!std::ranges::contains(notes_on, midi_note::G6));
  REQUIRE(std::ranges::empty(notes_on));
}