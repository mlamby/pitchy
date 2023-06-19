#include "pitchy/midi/midi_message.h"

namespace pitchy
{
  namespace
  {

    enum class midi_status : uint8_t
    {
      note_off = 0x80,
      note_on = 0x90,
      polyphonic_aftertouch = 0xA0,
      contol_mode_change = 0xB0,
      program_change = 0xC0,
      channel_aftertouch = 0xD0,
      pitch_bend = 0xE0,
      sysex = 0xF0,
      midi_time_code = 0xF1,
      song_position = 0xF2,
      song_select = 0xF3,
      tune_request = 0xF6,
      sysex_end = 0xF7,
      timing_clock = 0xF8,
      midi_start = 0xFA,
      midi_continue = 0xFB,
      midi_stop = 0xFC,
      active_sensing = 0xFE,
      system_reset = 0xFF
    };

    constexpr bool is_data_byte(uint8_t byte) { return (byte & 0x80) == 0; }
    constexpr bool is_valid_channel(uint8_t byte)
    {
      return (byte >= 0) && (byte <= 15);
    }
    constexpr bool is_valid_velocity(uint8_t byte)
    {
      return (byte >= 0) && (byte <= 127);
    }

    template <MidiNoteMsg TMsgType>
    midi_parse_result parse_midi_note_msg(uint8_t b1, uint8_t b2, uint8_t b3)
    {
      uint8_t channel = b1 & 0x0f;

      if (is_valid_channel(channel) && is_valid_midi_value(b2) && is_valid_velocity(b3))
      {
        return TMsgType {
            .note = midi_value_to_note(b2),
            .channel = static_cast<midi_channel_type>(channel),
            .velocity = static_cast<midi_velocity_type>(b3)};
      }
      
      // Return empty result if no valid message was parsed.
      return midi_parse_result {};
    }


  } // namespace

  midi_parse_result parse_midi_event(const std::vector<uint8_t> &data)
  {
    // Currently the parser only handles midi note on/off messages

    if (std::size(data) != 3)
    {
      return midi_parse_result{};
    }

    auto status = static_cast<midi_status>(data[0] & 0xf0);

    if (status == midi_status::note_on)
    {
      return parse_midi_note_msg<midi_note_on_message>(data[0], data[1], data[2]);
    }

    if (status == midi_status::note_off)
    {
      return parse_midi_note_msg<midi_note_off_message>(data[0], data[1], data[2]);
    }

    return midi_parse_result{};
  }
} // namespace pitchy
