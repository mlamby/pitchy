#ifndef MIDI_LIB_INTERVAL_H
#define MIDI_LIB_INTERVAL_H

#include "pitchy/midi/midi_note.h"
#include "pitchy/note.h"

namespace pitchy
{
  // Interval enumeration.
  // The underlying enum value represents the number of semitones.
  enum class interval : int8_t
  {
    root = 0,
    minor_second,
    major_second,
    minor_third,
    major_third,
    perfect_fourth,
    augmented_fourth,
    perfect_fifth,
    minor_sixth,
    major_sixth,
    minor_seventh,
    major_seventh,
    perfect_octave
  };

  // Convert the interval the number of semitones.
  constexpr int8_t semitones(interval i)
  {
    return static_cast<int8_t>(i);
  }

  constexpr midi_note raise(midi_note root, interval i)
  {
    return midi_value_to_note(note_to_midi_value(root) + semitones(i));
  }

  constexpr midi_note lower(midi_note root, interval i)
  {
    return midi_value_to_note(note_to_midi_value(root) - semitones(i));
  }

  constexpr int8_t difference(midi_note first, midi_note second)
  {
    auto f = note_to_midi_value(first);
    auto s = note_to_midi_value(second);

    if (f > s)
      return f - s;

    return s - f;
  }

  // Return the interval between a pair of notes.
  // The interval is always calculated as moving up from the root
  // note to the second note.
  constexpr interval note_interval(note root_note, note second_note)
  {
    auto root_value = static_cast<std::underlying_type_t<note>>(root_note);
    auto second_value = static_cast<std::underlying_type_t<note>>(second_note);
    std::underlying_type_t<interval> result = 0;

    if (root_value > second_value)
    {
      // The second note is below the root note in enumerated value.
      // Move the second note up by an octave.
      second_value += 12;
    }

    result = second_value - root_value;
    return static_cast<interval>(result);
  }
  
} // namespace pitchy

#endif