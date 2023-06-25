#ifndef PITCHY_NOTE_H
#define PITCHY_NOTE_H

#include <cstdint>
#include <type_traits>
#include <string_view>

namespace pitchy
{
  // Represents a note name without an octave.
  enum class note : int8_t
  {
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
    B,
  };

  constexpr std::string_view to_string(note n)
  {
    switch (n)
    {
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
}

#endif