#include "pitchy/midi/midi_message.h"

#include <catch2/catch_test_macros.hpp>
#include <initializer_list>

using namespace pitchy;

namespace
{
  auto build_messsage(std::initializer_list<uint8_t> lst)
  {
    return std::vector<uint8_t>{lst};
  }

} // namespace

TEST_CASE("InvalidMidiMessages", "")
{
  // Empty data vector is handled.
  auto result = parse_midi_event(build_messsage({}));
  REQUIRE(0 == result.index());
  REQUIRE(std::holds_alternative<std::monostate>(result));

  // Partal message.
  result = parse_midi_event(build_messsage({0x91}));
  REQUIRE(0 == result.index());
  REQUIRE(std::holds_alternative<std::monostate>(result));

  // Too many bytes.
  result = parse_midi_event(build_messsage({0xAB, 0x00, 0xFF, 0xCD}));
  REQUIRE(0 == result.index());
  REQUIRE(std::holds_alternative<std::monostate>(result));
}

TEST_CASE("NoteOnMidiMessage", "")
{
  // A valid midi message
  //   note on for channel 1  - 0x91.
  //   note F3                - 0x35
  //   velocity 120           - 0x78
  auto result = parse_midi_event(build_messsage({0x91, 0x35, 0x78}));
  auto msg = std::get<midi_note_on_message>(result);
  REQUIRE(midi_note::F3 == msg.note);
  REQUIRE(0x78 == msg.velocity);
  REQUIRE(0x01 == msg.channel);

  // 2nd byte is not a data byte (ie it has the highest bit set.)
  result = parse_midi_event(build_messsage({0x91, 0xF5, 0x78}));
  REQUIRE(std::holds_alternative<std::monostate>(result));

  // 3rd byte is not a data byte (ie it has the highest bit set.)
  result = parse_midi_event(build_messsage({0x91, 0x35, 0xF8}));
  REQUIRE(std::holds_alternative<std::monostate>(result));
}

TEST_CASE("NoteOffMidiMessage", "")
{
  // A valid midi message
  //   note off for channel 7  - 0x97.
  //   note C4                 - 0x3C
  //   velocity 64             - 0x3F
  auto result = parse_midi_event(build_messsage({0x87, 0x3C, 0x3F}));
  auto msg = std::get<midi_note_off_message>(result);
  REQUIRE(midi_note::C4 == msg.note);
  REQUIRE(0x3F == msg.velocity);
  REQUIRE(0x07 == msg.channel);

  // 2nd byte is not a data byte (ie it has the highest bit set.)
  result = parse_midi_event(build_messsage({0x87, 0xFC, 0x3F}));
  REQUIRE(std::holds_alternative<std::monostate>(result));

  // 3rd byte is not a data byte (ie it has the highest bit set.)
  result = parse_midi_event(build_messsage({0x87, 0x35, 0xFF}));
  REQUIRE(std::holds_alternative<std::monostate>(result));
}

namespace
{
  template <typename T>
  typename std::vector<T>::iterator insert_sorted(std::vector<T> &vec, const T &item)
  {
    return vec.insert(std::upper_bound(vec.begin(), vec.end(), item), item);
  }

  template <typename T>
  bool contains(const std::vector<T> &vec, const T &item)
  {
    return std::find(vec.begin(), vec.end(), item) != std::end(vec);
  }
} // namespace
