#ifndef MIDI_LIB_INTERVAL_H
#define MIDI_LIB_INTERVAL_H

#include "midi/midi_note.h"

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
} // namespace pitchy

#endif