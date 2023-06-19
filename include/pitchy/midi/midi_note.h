#ifndef PITCHY_MIDI_NOTE_H
#define PITCHY_MIDI_NOTE_H

#include <cstdint>
#include <cstddef>

namespace pitchy
{
  // Midi note enumeration.
  // The underlying enum value is not equal to the midi value on the wire.
  // The note must be converted using note_to_midi_value().
  enum class midi_note : uint8_t
  {
    A0,
    As0,
    B0,
    C1,
    Cs1,
    D1,
    Ds1,
    E1,
    F1,
    Fs1,
    G1,
    Gs1,
    A1,
    As1,
    B1,
    C2,
    Cs2,
    D2,
    Ds2,
    E2,
    F2,
    Fs2,
    G2,
    Gs2,
    A2,
    As2,
    B2,
    C3,
    Cs3,
    D3,
    Ds3,
    E3,
    F3,
    Fs3,
    G3,
    Gs3,
    A3,
    As3,
    B3,
    C4, // Middle C
    Cs4,
    D4,
    Ds4,
    E4,
    F4,
    Fs4,
    G4,
    Gs4,
    A4,
    As4,
    B4,
    C5,
    Cs5,
    D5,
    Ds5,
    E5,
    F5,
    Fs5,
    G5,
    Gs5,
    A5,
    As5,
    B5,
    C6,
    Cs6,
    D6,
    Ds6,
    E6,
    F6,
    Fs6,
    G6,
    Gs6,
    A6,
    As6,
    B6,
    C7,
    Cs7,
    D7,
    Ds7,
    E7,
    F7,
    Fs7,
    G7,
    Gs7,
    A7,
    As7,
    B7,
    C8,
    Cs8,
    D8,
    Ds8,
    E8,
    F8,
    Fs8,
    G8,
    Gs8,
    A8,
    As8,
    B8,
    C9,
    Cs9,
    D9,
    Ds9,
    E9,
    F9,
    Fs9,
    G9,
  };

  // Convert the midi note enum to a midi note value per the midi spec.
  constexpr uint8_t note_to_midi_value(midi_note n)
  {
    // A0 is equal to midi value 21.
    return static_cast<uint8_t>(n) + 21;
  }

  // Convert the midi value to an enum.
  // This expects that the midi value is a valid midi value, which can 
  // be checked using is_valid_midi_value().
  constexpr midi_note midi_value_to_note(uint8_t n)
  {
    return static_cast<midi_note>(n - 21);
  }

  // Checks that the value is a valid midi value.
  constexpr bool is_valid_midi_value(uint8_t v)
  {
    // Midi values must be between 21 (A0) and 127 (G9)
    return (v >= 21) && (v <= 127);
  }
}

#endif