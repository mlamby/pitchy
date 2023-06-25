#include "pitchy/chord.h"

#include <catch2/catch_test_macros.hpp>

using namespace pitchy;

namespace {
  std::vector<chord_recognition_result>
  expected(note n, chord_type t, lowest_note_type slash_note)
  {
    return {chord_recognition_result(n, t, slash_note)};
  }

  std::vector<chord_recognition_result> merge(
    const std::vector<chord_recognition_result>& v1,
    const std::vector<chord_recognition_result>& v2)
  {
    std::vector<chord_recognition_result> result {std::begin(v1), std::end(v1)};
    for (auto r : v2) {
      result.push_back(r);
    }
    return result;
  }
} // namespace

namespace Catch {
  template <> struct StringMaker<chord_recognition_result> {
    static std::string convert(chord_recognition_result const& value)
    {
      return to_string(value);
    }
  };
} // namespace Catch

TEST_CASE("chord_to_string", "")
{
  REQUIRE(to_string(chord_type::major) == "Major");
  REQUIRE(to_string(chord_type::major7) == "Major7");
  REQUIRE(to_string(chord_type::minor) == "Minor");
  REQUIRE(to_string(chord_type::minor7) == "Minor7");
  REQUIRE(to_string(chord_type::dominant) == "Dominant");
  REQUIRE(to_string(chord_type::sus2) == "Sus2");
  REQUIRE(to_string(chord_type::sus4) == "Sus4");
}

TEST_CASE("chord_result_to_string", "")
{
  REQUIRE(
    to_string(chord_recognition_result(note::C, chord_type::major, note::C)) ==
    "C Major");

  REQUIRE(
    to_string(chord_recognition_result(note::D, chord_type::major7, note::D)) ==
    "D Major7");
  REQUIRE(
    to_string(chord_recognition_result(note::E, chord_type::minor, note::E)) ==
    "E Minor");
  REQUIRE(
    to_string(chord_recognition_result(note::F, chord_type::minor7, note::F)) ==
    "F Minor7");
  REQUIRE(
    to_string(chord_recognition_result(
      note::G, chord_type::dominant, note::G)) == "G Dominant");
  REQUIRE(
    to_string(chord_recognition_result(note::A, chord_type::sus2, note::A)) ==
    "A Sus2");
  REQUIRE(
    to_string(chord_recognition_result(note::B, chord_type::sus4, note::B)) ==
    "B Sus4");

  REQUIRE(
    to_string(chord_recognition_result(note::C, chord_type::major, note::E)) ==
    "C Major / E");
  REQUIRE(
    to_string(chord_recognition_result(
      note::D, chord_type::major7, note::Cs)) == "D Major7 / C#");
  REQUIRE(
    to_string(chord_recognition_result(note::E, chord_type::minor, note::Ds)) ==
    "E Minor / D#");
  REQUIRE(
    to_string(chord_recognition_result(
      note::F, chord_type::minor7, note::Gs)) == "F Minor7 / G#");
  REQUIRE(
    to_string(chord_recognition_result(
      note::G, chord_type::dominant, note::As)) == "G Dominant / A#");
  REQUIRE(
    to_string(chord_recognition_result(note::A, chord_type::sus2, note::B)) ==
    "A Sus2 / B");
  REQUIRE(
    to_string(chord_recognition_result(note::B, chord_type::sus4, note::G)) ==
    "B Sus4 / G");
}

TEST_CASE("chord_recognise_major_test", "")
{
  auto c_major_root_position = expected(note::C, chord_type::major, note::C);
  auto c_major_over_e = expected(note::C, chord_type::major, note::E);
  auto b_major_root_position = expected(note::B, chord_type::major, note::B);
  auto b_major_over_fs = expected(note::B, chord_type::major, note::Fs);

  REQUIRE(
    find_all_chords({midi_note::C4, midi_note::E4, midi_note::G4}) ==
    c_major_root_position);
  REQUIRE(
    find_all_chords({midi_note::B3, midi_note::Ds4, midi_note::Fs4}) ==
    b_major_root_position);

  // The ordering of the notes in the array is not important
  REQUIRE(
    find_all_chords({midi_note::E4, midi_note::G4, midi_note::C4}) ==
    c_major_root_position);
  REQUIRE(
    find_all_chords({midi_note::Ds4, midi_note::B3, midi_note::Fs4}) ==
    b_major_root_position);

  // Repeated notes are ignored
  REQUIRE(
    find_all_chords(
      {midi_note::C3, midi_note::G3, midi_note::C4, midi_note::E4}) ==
    c_major_root_position);
  REQUIRE(
    find_all_chords(
      {midi_note::B3, midi_note::Ds4, midi_note::Fs4, midi_note::B4}) ==
    b_major_root_position);

  // Slash chords are recognised
  REQUIRE(
    find_all_chords({midi_note::E4, midi_note::G4, midi_note::C5}) ==
    c_major_over_e);
  REQUIRE(
    find_all_chords({midi_note::Fs4, midi_note::Ds5, midi_note::B5}) ==
    b_major_over_fs);

  REQUIRE(
    find_all_chords(
      {midi_note::E3,
       midi_note::C4,
       midi_note::E4,
       midi_note::G4,
       midi_note::C5}) == c_major_over_e);
  REQUIRE(
    find_all_chords(
      {midi_note::Fs4,
       midi_note::Ds5,
       midi_note::B5,
       midi_note::Fs5,
       midi_note::B6}) == b_major_over_fs);
}

TEST_CASE("chord_recognise_minor_test", "")
{
  auto c_minor_root_position = expected(note::C, chord_type::minor, note::C);
  auto c_minor_over_eb = expected(note::C, chord_type::minor, note::Ds);
  auto b_minor_root_position = expected(note::B, chord_type::minor, note::B);
  auto b_minor_over_fs = expected(note::B, chord_type::minor, note::Fs);

  REQUIRE(
    find_all_chords({midi_note::C4, midi_note::Ds4, midi_note::G4}) ==
    c_minor_root_position);
  REQUIRE(
    find_all_chords({midi_note::B3, midi_note::D4, midi_note::Fs4}) ==
    b_minor_root_position);

  // The ordering of the notes in the array is not important
  REQUIRE(
    find_all_chords({midi_note::Ds4, midi_note::G4, midi_note::C4}) ==
    c_minor_root_position);
  REQUIRE(
    find_all_chords({midi_note::D4, midi_note::B3, midi_note::Fs4}) ==
    b_minor_root_position);

  // Repeated notes are ignored
  REQUIRE(
    find_all_chords(
      {midi_note::C3, midi_note::G3, midi_note::C4, midi_note::Ds4}) ==
    c_minor_root_position);
  REQUIRE(
    find_all_chords(
      {midi_note::B3, midi_note::D4, midi_note::Fs4, midi_note::B4}) ==
    b_minor_root_position);

  // Slash chords are recognised
  REQUIRE(
    find_all_chords({midi_note::Ds4, midi_note::G4, midi_note::C5}) ==
    c_minor_over_eb);
  REQUIRE(
    find_all_chords({midi_note::Fs4, midi_note::D5, midi_note::B5}) ==
    b_minor_over_fs);

  REQUIRE(
    find_all_chords(
      {midi_note::Ds4, midi_note::G4, midi_note::C5, midi_note::Ds5}) ==
    c_minor_over_eb);
  REQUIRE(
    find_all_chords(
      {midi_note::Fs4,
       midi_note::D5,
       midi_note::B5,
       midi_note::Fs5,
       midi_note::B6}) == b_minor_over_fs);
}

TEST_CASE("chord_recognise_major7_test", "")
{
  auto d_major7_root_position = expected(note::D, chord_type::major7, note::D);
  auto d_major7_over_cs = expected(note::D, chord_type::major7, note::Cs);

  REQUIRE(
    find_all_chords(
      {midi_note::D3, midi_note::Fs3, midi_note::A3, midi_note::Cs4}) ==
    d_major7_root_position);

  REQUIRE(
    find_all_chords(
      {midi_note::D3,
       midi_note::D4,
       midi_note::Fs3,
       midi_note::Fs4,
       midi_note::A3,
       midi_note::A4,
       midi_note::Cs4}) == d_major7_root_position);

  REQUIRE(
    find_all_chords(
      {midi_note::Cs3, midi_note::Fs3, midi_note::A3, midi_note::D4}) ==
    d_major7_over_cs);
}

TEST_CASE("chord_recognise_minor7_test", "")
{
  auto e_minor7_root_position = expected(note::E, chord_type::minor7, note::E);
  auto e_minor7_over_d = expected(note::E, chord_type::minor7, note::D);

  REQUIRE(
    find_all_chords(
      {midi_note::E3, midi_note::G3, midi_note::B3, midi_note::D4}) ==
    e_minor7_root_position);

  REQUIRE(
    find_all_chords(
      {midi_note::E3,
       midi_note::E4,
       midi_note::G3,
       midi_note::G4,
       midi_note::B3,
       midi_note::B4,
       midi_note::D4}) == e_minor7_root_position);

  REQUIRE(
    find_all_chords(
      {midi_note::D3, midi_note::B3, midi_note::G4, midi_note::E5}) ==
    e_minor7_over_d);
}

TEST_CASE("chord_recognise_dominant_test", "")
{
  auto f_dom_root_position = expected(note::F, chord_type::dominant, note::F);
  auto f_dom_over_ds = expected(note::F, chord_type::dominant, note::Ds);

  REQUIRE(
    find_all_chords(
      {midi_note::F2, midi_note::A2, midi_note::C3, midi_note::Ds3}) ==
    f_dom_root_position);

  REQUIRE(
    find_all_chords(
      {midi_note::F3,
       midi_note::F4,
       midi_note::A3,
       midi_note::A4,
       midi_note::C4,
       midi_note::C5,
       midi_note::Ds4}) == f_dom_root_position);

  REQUIRE(
    find_all_chords(
      {midi_note::Ds3, midi_note::F3, midi_note::A3, midi_note::C4}) ==
    f_dom_over_ds);
}

TEST_CASE("chord_recognise_sus_chords_test", "")
{
  const auto g_sus2_root_position =
    expected(note::G, chord_type::sus2, note::G);
  const auto g_sus2_over_d = expected(note::G, chord_type::sus2, note::D);
  const auto d_sus4_root_position =
    expected(note::D, chord_type::sus4, note::D);
  const auto d_sus4_over_g = expected(note::D, chord_type::sus4, note::G);

  // Sus2 and Sus4 chords are invesions of each other.

  REQUIRE(
    find_all_chords({midi_note::G3, midi_note::A3, midi_note::D4}) ==
    merge(d_sus4_over_g, g_sus2_root_position));

  REQUIRE(
    find_all_chords(
      {midi_note::G3,
       midi_note::G4,
       midi_note::A3,
       midi_note::A4,
       midi_note::D4,
       midi_note::D5}) == merge(d_sus4_over_g, g_sus2_root_position));

  REQUIRE(
    find_all_chords({midi_note::D3, midi_note::A3, midi_note::G4}) ==
    merge(d_sus4_root_position, g_sus2_over_d));
}