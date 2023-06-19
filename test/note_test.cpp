#include "pitchy/note.h"

#include <catch2/catch_test_macros.hpp>

using namespace pitchy;

TEST_CASE("note_interval_test", "")
{
  REQUIRE(note_interval(note::C, note::C) == interval::root);
  REQUIRE(note_interval(note::C, note::Cs) == interval::minor_second);
  REQUIRE(note_interval(note::C, note::D) == interval::major_second);
  REQUIRE(note_interval(note::C, note::Ds) == interval::minor_third);
  REQUIRE(note_interval(note::C, note::E) == interval::major_third);
  REQUIRE(note_interval(note::C, note::F) == interval::perfect_fourth);
  REQUIRE(note_interval(note::C, note::Fs) == interval::augmented_fourth);
  REQUIRE(note_interval(note::C, note::G) == interval::perfect_fifth);
  REQUIRE(note_interval(note::C, note::Gs) == interval::minor_sixth);
  REQUIRE(note_interval(note::C, note::A) == interval::major_sixth);
  REQUIRE(note_interval(note::C, note::As) == interval::minor_seventh);
  REQUIRE(note_interval(note::C, note::B) == interval::major_seventh);

  REQUIRE(note_interval(note::G, note::G) == interval::root);
  REQUIRE(note_interval(note::G, note::Gs) == interval::minor_second);
  REQUIRE(note_interval(note::G, note::A) == interval::major_second);
  REQUIRE(note_interval(note::G, note::As) == interval::minor_third);
  REQUIRE(note_interval(note::G, note::B) == interval::major_third);
  REQUIRE(note_interval(note::G, note::C) == interval::perfect_fourth);
  REQUIRE(note_interval(note::G, note::Cs) == interval::augmented_fourth);
  REQUIRE(note_interval(note::G, note::D) == interval::perfect_fifth);
  REQUIRE(note_interval(note::G, note::Ds) == interval::minor_sixth);
  REQUIRE(note_interval(note::G, note::E) == interval::major_sixth);
  REQUIRE(note_interval(note::G, note::F) == interval::minor_seventh);
  REQUIRE(note_interval(note::G, note::Fs) == interval::major_seventh);

  REQUIRE(note_interval(note::B, note::B) == interval::root);
  REQUIRE(note_interval(note::B, note::C) == interval::minor_second);
  REQUIRE(note_interval(note::B, note::Cs) == interval::major_second);
  REQUIRE(note_interval(note::B, note::D) == interval::minor_third);
  REQUIRE(note_interval(note::B, note::Ds) == interval::major_third);
  REQUIRE(note_interval(note::B, note::E) == interval::perfect_fourth);
  REQUIRE(note_interval(note::B, note::F) == interval::augmented_fourth);
  REQUIRE(note_interval(note::B, note::Fs) == interval::perfect_fifth);
  REQUIRE(note_interval(note::B, note::G) == interval::minor_sixth);
  REQUIRE(note_interval(note::B, note::Gs) == interval::major_sixth);
  REQUIRE(note_interval(note::B, note::A) == interval::minor_seventh);
  REQUIRE(note_interval(note::B, note::As) == interval::major_seventh);
} 

TEST_CASE("remove_octave_test", "")
{
  REQUIRE(note::A  == remove_octave(midi_note::A0));
  REQUIRE(note::As == remove_octave(midi_note::As0));
  REQUIRE(note::B  == remove_octave(midi_note::B0));

  REQUIRE(note::C  == remove_octave(midi_note::C2));
  REQUIRE(note::Cs == remove_octave(midi_note::Cs1));
  REQUIRE(note::D  == remove_octave(midi_note::D1));
  REQUIRE(note::Ds == remove_octave(midi_note::Ds1));
  REQUIRE(note::E  == remove_octave(midi_note::E1));
  REQUIRE(note::F  == remove_octave(midi_note::F1));
  REQUIRE(note::Fs == remove_octave(midi_note::Fs1));
  REQUIRE(note::G  == remove_octave(midi_note::G1));
  REQUIRE(note::Gs == remove_octave(midi_note::Gs1));
  REQUIRE(note::A  == remove_octave(midi_note::A1));
  REQUIRE(note::As == remove_octave(midi_note::As1));
  REQUIRE(note::B  == remove_octave(midi_note::B1));

  REQUIRE(note::C  == remove_octave(midi_note::C2));
  REQUIRE(note::Cs == remove_octave(midi_note::Cs2));
  REQUIRE(note::D  == remove_octave(midi_note::D2));
  REQUIRE(note::Ds == remove_octave(midi_note::Ds2));
  REQUIRE(note::E  == remove_octave(midi_note::E2));
  REQUIRE(note::F  == remove_octave(midi_note::F2));
  REQUIRE(note::Fs == remove_octave(midi_note::Fs2));
  REQUIRE(note::G  == remove_octave(midi_note::G2));
  REQUIRE(note::Gs == remove_octave(midi_note::Gs2));
  REQUIRE(note::A  == remove_octave(midi_note::A2));
  REQUIRE(note::As == remove_octave(midi_note::As2));
  REQUIRE(note::B  == remove_octave(midi_note::B2));

  REQUIRE(note::C  == remove_octave(midi_note::C3));
  REQUIRE(note::Cs == remove_octave(midi_note::Cs3));
  REQUIRE(note::D  == remove_octave(midi_note::D3));
  REQUIRE(note::Ds == remove_octave(midi_note::Ds3));
  REQUIRE(note::E  == remove_octave(midi_note::E3));
  REQUIRE(note::F  == remove_octave(midi_note::F3));
  REQUIRE(note::Fs == remove_octave(midi_note::Fs3));
  REQUIRE(note::G  == remove_octave(midi_note::G3));
  REQUIRE(note::Gs == remove_octave(midi_note::Gs3));
  REQUIRE(note::A  == remove_octave(midi_note::A3));
  REQUIRE(note::As == remove_octave(midi_note::As3));
  REQUIRE(note::B  == remove_octave(midi_note::B3));

  REQUIRE(note::C  == remove_octave(midi_note::C4));
  REQUIRE(note::Cs == remove_octave(midi_note::Cs4));
  REQUIRE(note::D  == remove_octave(midi_note::D4));
  REQUIRE(note::Ds == remove_octave(midi_note::Ds4));
  REQUIRE(note::E  == remove_octave(midi_note::E4));
  REQUIRE(note::F  == remove_octave(midi_note::F4));
  REQUIRE(note::Fs == remove_octave(midi_note::Fs4));
  REQUIRE(note::G  == remove_octave(midi_note::G4));
  REQUIRE(note::Gs == remove_octave(midi_note::Gs4));
  REQUIRE(note::A  == remove_octave(midi_note::A4));
  REQUIRE(note::As == remove_octave(midi_note::As4));
  REQUIRE(note::B  == remove_octave(midi_note::B4));

  REQUIRE(note::C  == remove_octave(midi_note::C5));
  REQUIRE(note::Cs == remove_octave(midi_note::Cs5));
  REQUIRE(note::D  == remove_octave(midi_note::D5));
  REQUIRE(note::Ds == remove_octave(midi_note::Ds5));
  REQUIRE(note::E  == remove_octave(midi_note::E5));
  REQUIRE(note::F  == remove_octave(midi_note::F5));
  REQUIRE(note::Fs == remove_octave(midi_note::Fs5));
  REQUIRE(note::G  == remove_octave(midi_note::G5));
  REQUIRE(note::Gs == remove_octave(midi_note::Gs5));
  REQUIRE(note::A  == remove_octave(midi_note::A5));
  REQUIRE(note::As == remove_octave(midi_note::As5));
  REQUIRE(note::B  == remove_octave(midi_note::B5));

  REQUIRE(note::C  == remove_octave(midi_note::C6));
  REQUIRE(note::Cs == remove_octave(midi_note::Cs6));
  REQUIRE(note::D  == remove_octave(midi_note::D6));
  REQUIRE(note::Ds == remove_octave(midi_note::Ds6));
  REQUIRE(note::E  == remove_octave(midi_note::E6));
  REQUIRE(note::F  == remove_octave(midi_note::F6));
  REQUIRE(note::Fs == remove_octave(midi_note::Fs6));
  REQUIRE(note::G  == remove_octave(midi_note::G6));
  REQUIRE(note::Gs == remove_octave(midi_note::Gs6));
  REQUIRE(note::A  == remove_octave(midi_note::A6));
  REQUIRE(note::As == remove_octave(midi_note::As6));
  REQUIRE(note::B  == remove_octave(midi_note::B6));

  REQUIRE(note::C  == remove_octave(midi_note::C7));
  REQUIRE(note::Cs == remove_octave(midi_note::Cs7));
  REQUIRE(note::D  == remove_octave(midi_note::D7));
  REQUIRE(note::Ds == remove_octave(midi_note::Ds7));
  REQUIRE(note::E  == remove_octave(midi_note::E7));
  REQUIRE(note::F  == remove_octave(midi_note::F7));
  REQUIRE(note::Fs == remove_octave(midi_note::Fs7));
  REQUIRE(note::G  == remove_octave(midi_note::G7));
  REQUIRE(note::Gs == remove_octave(midi_note::Gs7));
  REQUIRE(note::A  == remove_octave(midi_note::A7));
  REQUIRE(note::As == remove_octave(midi_note::As7));
  REQUIRE(note::B  == remove_octave(midi_note::B7));

  REQUIRE(note::C  == remove_octave(midi_note::C8));
  REQUIRE(note::Cs == remove_octave(midi_note::Cs8));
  REQUIRE(note::D  == remove_octave(midi_note::D8));
  REQUIRE(note::Ds == remove_octave(midi_note::Ds8));
  REQUIRE(note::E  == remove_octave(midi_note::E8));
  REQUIRE(note::F  == remove_octave(midi_note::F8));
  REQUIRE(note::Fs == remove_octave(midi_note::Fs8));
  REQUIRE(note::G  == remove_octave(midi_note::G8));
  REQUIRE(note::Gs == remove_octave(midi_note::Gs8));
  REQUIRE(note::A  == remove_octave(midi_note::A8));
  REQUIRE(note::As == remove_octave(midi_note::As8));
  REQUIRE(note::B  == remove_octave(midi_note::B8));

  REQUIRE(note::C  == remove_octave(midi_note::C9));
  REQUIRE(note::Cs == remove_octave(midi_note::Cs9));
  REQUIRE(note::D  == remove_octave(midi_note::D9));
  REQUIRE(note::Ds == remove_octave(midi_note::Ds9));
  REQUIRE(note::E  == remove_octave(midi_note::E9));
  REQUIRE(note::F  == remove_octave(midi_note::F9));
  REQUIRE(note::Fs == remove_octave(midi_note::Fs9));
  REQUIRE(note::G  == remove_octave(midi_note::G9));
}

TEST_CASE("Note_as_string", "")
{
  REQUIRE(to_string(note::C)  == "C");
  REQUIRE(to_string(note::Cs) == "C#");
  REQUIRE(to_string(note::D)  == "D");
  REQUIRE(to_string(note::Ds) == "D#");
  REQUIRE(to_string(note::E)  == "E");
  REQUIRE(to_string(note::F)  == "F");
  REQUIRE(to_string(note::Fs) == "F#");
  REQUIRE(to_string(note::G)  == "G");
  REQUIRE(to_string(note::Gs) == "G#");
  REQUIRE(to_string(note::A)  == "A");
  REQUIRE(to_string(note::As) == "A#");
  REQUIRE(to_string(note::B)  == "B");
}