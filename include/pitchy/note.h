#ifndef PITCHY_NOTE_H
#define PITCHY_NOTE_H

#include "midi/midi_note.h"
#include "interval.h"

#include <cstdint>
#include <type_traits>
#include <string_view>

namespace pitchy
{
  // Represents a note name without an octave.
  enum class note : int8_t
  {
    None,
    C,
    Cs,
    D,
    Ds,
    E,
    F,
    Fs,
    G,
    Gs,
    A,
    As,
    B
  };

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

  constexpr std::string_view to_string(note n)
  {
    switch (n)
    {
    case note::None:
      return "None";
      break;
    case note::C:
      return "C";
      break;
    case note::Cs:
      return "C#";
      break;
    case note::D:
      return "D";
      break;
    case note::Ds:
      return "D#";
      break;
    case note::E:
      return "E";
      break;
    case note::F:
      return "F";
      break;
    case note::Fs:
      return "F#";
      break;
    case note::G:
      return "G";
      break;
    case note::Gs:
      return "G#";
      break;
    case note::A:
      return "A";
      break;
    case note::As:
      return "A#";
      break;
    case note::B:
      return "B";
      break;
    }
    return "";
  }

  // Remove the octave from a midi note.
  // midi_note::A2 becomes note::A, etc.
  constexpr note remove_octave(midi_note n)
  {
    switch (n)
    {
    case midi_note::A0:
    case midi_note::A1:
    case midi_note::A2:
    case midi_note::A3:
    case midi_note::A4:
    case midi_note::A5:
    case midi_note::A6:
    case midi_note::A7:
    case midi_note::A8:
      return note::A;
      break;

    case midi_note::As0:
    case midi_note::As1:
    case midi_note::As2:
    case midi_note::As3:
    case midi_note::As4:
    case midi_note::As5:
    case midi_note::As6:
    case midi_note::As7:
    case midi_note::As8:
      return note::As;
      break;

    case midi_note::B0:
    case midi_note::B1:
    case midi_note::B2:
    case midi_note::B3:
    case midi_note::B4:
    case midi_note::B5:
    case midi_note::B6:
    case midi_note::B7:
    case midi_note::B8:
      return note::B;
      break;

    case midi_note::C1:
    case midi_note::C2:
    case midi_note::C3:
    case midi_note::C4:
    case midi_note::C5:
    case midi_note::C6:
    case midi_note::C7:
    case midi_note::C8:
    case midi_note::C9:
      return note::C;
      break;

    case midi_note::Cs1:
    case midi_note::Cs2:
    case midi_note::Cs3:
    case midi_note::Cs4:
    case midi_note::Cs5:
    case midi_note::Cs6:
    case midi_note::Cs7:
    case midi_note::Cs8:
    case midi_note::Cs9:
      return note::Cs;
      break;

    case midi_note::D1:
    case midi_note::D2:
    case midi_note::D3:
    case midi_note::D4:
    case midi_note::D5:
    case midi_note::D6:
    case midi_note::D7:
    case midi_note::D8:
    case midi_note::D9:
      return note::D;
      break;

    case midi_note::Ds1:
    case midi_note::Ds2:
    case midi_note::Ds3:
    case midi_note::Ds4:
    case midi_note::Ds5:
    case midi_note::Ds6:
    case midi_note::Ds7:
    case midi_note::Ds8:
    case midi_note::Ds9:
      return note::Ds;
      break;

    case midi_note::E1:
    case midi_note::E2:
    case midi_note::E3:
    case midi_note::E4:
    case midi_note::E5:
    case midi_note::E6:
    case midi_note::E7:
    case midi_note::E8:
    case midi_note::E9:
      return note::E;
      break;

    case midi_note::F1:
    case midi_note::F2:
    case midi_note::F3:
    case midi_note::F4:
    case midi_note::F5:
    case midi_note::F6:
    case midi_note::F7:
    case midi_note::F8:
    case midi_note::F9:
      return note::F;
      break;

    case midi_note::Fs1:
    case midi_note::Fs2:
    case midi_note::Fs3:
    case midi_note::Fs4:
    case midi_note::Fs5:
    case midi_note::Fs6:
    case midi_note::Fs7:
    case midi_note::Fs8:
    case midi_note::Fs9:
      return note::Fs;
      break;

    case midi_note::G1:
    case midi_note::G2:
    case midi_note::G3:
    case midi_note::G4:
    case midi_note::G5:
    case midi_note::G6:
    case midi_note::G7:
    case midi_note::G8:
    case midi_note::G9:
      return note::G;
      break;

    case midi_note::Gs1:
    case midi_note::Gs2:
    case midi_note::Gs3:
    case midi_note::Gs4:
    case midi_note::Gs5:
    case midi_note::Gs6:
    case midi_note::Gs7:
    case midi_note::Gs8:
      return note::Gs;
      break;

    default:
      return note::None;
    }
  }
}

#endif