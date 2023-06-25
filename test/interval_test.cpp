#include "pitchy/interval.h"

#include <catch2/catch_test_macros.hpp>

using namespace pitchy;

TEST_CASE("to_semitones", "interval_test")
{
  REQUIRE(0 == semitones(interval::root));
  REQUIRE(1 == semitones(interval::minor_second));
  REQUIRE(2 == semitones(interval::major_second));
  REQUIRE(3 == semitones(interval::minor_third));
  REQUIRE(4 == semitones(interval::major_third));
  REQUIRE(5 == semitones(interval::perfect_fourth));
  REQUIRE(6 == semitones(interval::augmented_fourth));
  REQUIRE(7 == semitones(interval::perfect_fifth));
  REQUIRE(8 == semitones(interval::minor_sixth));
  REQUIRE(9 == semitones(interval::major_sixth));
  REQUIRE(10 == semitones(interval::minor_seventh));
  REQUIRE(11 == semitones(interval::major_seventh));
  REQUIRE(12 == semitones(interval::perfect_octave));

  constexpr auto cu = semitones(interval::root);
  REQUIRE(0 == cu);
}

TEST_CASE("raise_midi", "interval_test")
{
  REQUIRE(midi_note::C5 == raise_midi(midi_note::C5, interval::root));
  REQUIRE(midi_note::Cs5 == raise_midi(midi_note::C5, interval::minor_second));
  REQUIRE(midi_note::D5 == raise_midi(midi_note::C5, interval::major_second));
  REQUIRE(midi_note::Ds5 == raise_midi(midi_note::C5, interval::minor_third));
  REQUIRE(midi_note::E5 == raise_midi(midi_note::C5, interval::major_third));
  REQUIRE(midi_note::F5 == raise_midi(midi_note::C5, interval::perfect_fourth));
  REQUIRE(midi_note::Fs5 == raise_midi(midi_note::C5, interval::augmented_fourth));
  REQUIRE(midi_note::G5 == raise_midi(midi_note::C5, interval::perfect_fifth));
  REQUIRE(midi_note::Gs5 == raise_midi(midi_note::C5, interval::minor_sixth));
  REQUIRE(midi_note::A5 == raise_midi(midi_note::C5, interval::major_sixth));
  REQUIRE(midi_note::As5 == raise_midi(midi_note::C5, interval::minor_seventh));
  REQUIRE(midi_note::B5 == raise_midi(midi_note::C5, interval::major_seventh));
  REQUIRE(midi_note::C6 == raise_midi(midi_note::C5, interval::perfect_octave));

  constexpr auto cu = raise_midi(midi_note::C5, interval::root);
  REQUIRE(midi_note::C5 == cu);
}

TEST_CASE("raise_note", "interval_test")
{
  REQUIRE(note::C == raise_note(note::C, interval::root));
  REQUIRE(note::Cs == raise_note(note::C, interval::minor_second));
  REQUIRE(note::D == raise_note(note::C, interval::major_second));
  REQUIRE(note::Ds == raise_note(note::C, interval::minor_third));
  REQUIRE(note::E == raise_note(note::C, interval::major_third));
  REQUIRE(note::F == raise_note(note::C, interval::perfect_fourth));
  REQUIRE(note::Fs == raise_note(note::C, interval::augmented_fourth));
  REQUIRE(note::G == raise_note(note::C, interval::perfect_fifth));
  REQUIRE(note::Gs == raise_note(note::C, interval::minor_sixth));
  REQUIRE(note::A == raise_note(note::C, interval::major_sixth));
  REQUIRE(note::As == raise_note(note::C, interval::minor_seventh));
  REQUIRE(note::B == raise_note(note::C, interval::major_seventh));
  REQUIRE(note::C == raise_note(note::C, interval::perfect_octave));
}

TEST_CASE("lower_midi", "interval_test")
{
  REQUIRE(midi_note::C5 == lower_midi(midi_note::C5, interval::root));
  REQUIRE(midi_note::B4 == lower_midi(midi_note::C5, interval::minor_second));
  REQUIRE(midi_note::As4 == lower_midi(midi_note::C5, interval::major_second));
  REQUIRE(midi_note::A4 == lower_midi(midi_note::C5, interval::minor_third));
  REQUIRE(midi_note::Gs4 == lower_midi(midi_note::C5, interval::major_third));
  REQUIRE(midi_note::G4 == lower_midi(midi_note::C5, interval::perfect_fourth));
  REQUIRE(midi_note::Fs4 == lower_midi(midi_note::C5, interval::augmented_fourth));
  REQUIRE(midi_note::F4 == lower_midi(midi_note::C5, interval::perfect_fifth));
  REQUIRE(midi_note::E4 == lower_midi(midi_note::C5, interval::minor_sixth));
  REQUIRE(midi_note::Ds4 == lower_midi(midi_note::C5, interval::major_sixth));
  REQUIRE(midi_note::D4 == lower_midi(midi_note::C5, interval::minor_seventh));
  REQUIRE(midi_note::Cs4 == lower_midi(midi_note::C5, interval::major_seventh));
  REQUIRE(midi_note::C4 == lower_midi(midi_note::C5, interval::perfect_octave));

  constexpr auto cu = lower_midi(midi_note::C5, interval::root);
  REQUIRE(midi_note::C5 == cu);
}

TEST_CASE("lower_note", "interval_test")
{
  REQUIRE(note::C  == lower_note(note::C, interval::root));
  REQUIRE(note::B  == lower_note(note::C, interval::minor_second));
  REQUIRE(note::As == lower_note(note::C, interval::major_second));
  REQUIRE(note::A  == lower_note(note::C, interval::minor_third));
  REQUIRE(note::Gs == lower_note(note::C, interval::major_third));
  REQUIRE(note::G  == lower_note(note::C, interval::perfect_fourth));
  REQUIRE(note::Fs == lower_note(note::C, interval::augmented_fourth));
  REQUIRE(note::F  == lower_note(note::C, interval::perfect_fifth));
  REQUIRE(note::E  == lower_note(note::C, interval::minor_sixth));
  REQUIRE(note::Ds == lower_note(note::C, interval::major_sixth));
  REQUIRE(note::D  == lower_note(note::C, interval::minor_seventh));
  REQUIRE(note::Cs == lower_note(note::C, interval::major_seventh));
  REQUIRE(note::C  == lower_note(note::C, interval::perfect_octave));
}

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