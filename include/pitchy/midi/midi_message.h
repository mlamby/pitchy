#ifndef PITCHY_MIDI_MESSAGE_H
#define PITCHY_MIDI_MESSAGE_H

#include "midi_note.h"

#include <cstdint>
#include <variant>
#include <vector>
#include <type_traits>

namespace pitchy
{
  // Midi velocity value.
  // The midi standard says this value should be between 0 and 127.
  using midi_velocity_type = uint8_t;

  // Midi channel value.
  // The midi standard says this value should be between 0 and 15.
  using midi_channel_type = uint8_t;

  struct midi_note_on_message
  {
    midi_note note;
    midi_channel_type channel;
    midi_velocity_type velocity;
  };

  struct midi_note_off_message
  {
    midi_note note;
    midi_channel_type channel;
    midi_velocity_type velocity;
  };

  // Not sure if this is the correct way to use a concept...
  template<typename T>
  concept MidiNoteMsg = requires(T a)
  {
    a.note;
    a.channel;
    a.velocity;
  };

  // A midi parse result is a variant containing all the types of 
  // midi messages that parse_midi_event() handles.
  // Empty (monostate) is used to indicate that result contains nothing.
  using midi_parse_result = std::variant<
    std::monostate,
    midi_note_on_message,
    midi_note_off_message>;

  // Parse the vector of midi event bytes and attempt to extract a 
  // midi event from the data. The result is a variant containing the 
  // extracted message or empty if no message was found.
  // 
  // The parser currently has quite a few limitations:
  // 
  //   1) Only note on and off messages are handled.
  //   2) Partial messages are not handled.
  //   3) Will not parse if the data vector contains too many bytes.
  //      For example if the vector contains two messages, this is
  //      is invalid.
  //
  // All of these limitations are acceptable for the use case of this
  // program, and the midi source being used.
  //
  midi_parse_result parse_midi_event(const std::vector<uint8_t>& data);
}

#endif