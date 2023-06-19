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

TEST_CASE("raise", "interval_test")
{
  REQUIRE(midi_note::C5 == raise(midi_note::C5, interval::root));
  REQUIRE(midi_note::Cs5 == raise(midi_note::C5, interval::minor_second));
  REQUIRE(midi_note::D5 == raise(midi_note::C5, interval::major_second));
  REQUIRE(midi_note::Ds5 == raise(midi_note::C5, interval::minor_third));
  REQUIRE(midi_note::E5 == raise(midi_note::C5, interval::major_third));
  REQUIRE(midi_note::F5 == raise(midi_note::C5, interval::perfect_fourth));
  REQUIRE(midi_note::Fs5 == raise(midi_note::C5, interval::augmented_fourth));
  REQUIRE(midi_note::G5 == raise(midi_note::C5, interval::perfect_fifth));
  REQUIRE(midi_note::Gs5 == raise(midi_note::C5, interval::minor_sixth));
  REQUIRE(midi_note::A5 == raise(midi_note::C5, interval::major_sixth));
  REQUIRE(midi_note::As5 == raise(midi_note::C5, interval::minor_seventh));
  REQUIRE(midi_note::B5 == raise(midi_note::C5, interval::major_seventh));
  REQUIRE(midi_note::C6 == raise(midi_note::C5, interval::perfect_octave));

  constexpr auto cu = raise(midi_note::C5, interval::root);
  REQUIRE(midi_note::C5 == cu);
}

TEST_CASE("lower", "interval_test")
{
  REQUIRE(midi_note::C5 == lower(midi_note::C5, interval::root));
  REQUIRE(midi_note::B4 == lower(midi_note::C5, interval::minor_second));
  REQUIRE(midi_note::As4 == lower(midi_note::C5, interval::major_second));
  REQUIRE(midi_note::A4 == lower(midi_note::C5, interval::minor_third));
  REQUIRE(midi_note::Gs4 == lower(midi_note::C5, interval::major_third));
  REQUIRE(midi_note::G4 == lower(midi_note::C5, interval::perfect_fourth));
  REQUIRE(midi_note::Fs4 == lower(midi_note::C5, interval::augmented_fourth));
  REQUIRE(midi_note::F4 == lower(midi_note::C5, interval::perfect_fifth));
  REQUIRE(midi_note::E4 == lower(midi_note::C5, interval::minor_sixth));
  REQUIRE(midi_note::Ds4 == lower(midi_note::C5, interval::major_sixth));
  REQUIRE(midi_note::D4 == lower(midi_note::C5, interval::minor_seventh));
  REQUIRE(midi_note::Cs4 == lower(midi_note::C5, interval::major_seventh));
  REQUIRE(midi_note::C4 == lower(midi_note::C5, interval::perfect_octave));

  constexpr auto cu = lower(midi_note::C5, interval::root);
  REQUIRE(midi_note::C5 == cu);
}

TEST_CASE("difference", "interval_test")
{
  REQUIRE(0 == difference(midi_note::C5, midi_note::C5));
  REQUIRE(1 == difference(midi_note::C5, midi_note::B4));
  REQUIRE(2 == difference(midi_note::C5, midi_note::As4));
  REQUIRE(3 == difference(midi_note::C5, midi_note::A4));
  REQUIRE(4 == difference(midi_note::C5, midi_note::Gs4));
  REQUIRE(5 == difference(midi_note::C5, midi_note::G4));
  REQUIRE(6 == difference(midi_note::C5, midi_note::Fs4));
  REQUIRE(7 == difference(midi_note::C5, midi_note::F4));
  REQUIRE(8 == difference(midi_note::C5, midi_note::E4));
  REQUIRE(9 == difference(midi_note::C5, midi_note::Ds4));
  REQUIRE(10 == difference(midi_note::C5, midi_note::D4));
  REQUIRE(11 == difference(midi_note::C5, midi_note::Cs4));
  REQUIRE(12 == difference(midi_note::C5, midi_note::C4));

  REQUIRE(0 == difference(midi_note::C5, midi_note::C5));
  REQUIRE(1 == difference(midi_note::B4, midi_note::C5));
  REQUIRE(2 == difference(midi_note::As4, midi_note::C5));
  REQUIRE(3 == difference(midi_note::A4, midi_note::C5));
  REQUIRE(4 == difference(midi_note::Gs4, midi_note::C5));
  REQUIRE(5 == difference(midi_note::G4, midi_note::C5));
  REQUIRE(6 == difference(midi_note::Fs4, midi_note::C5));
  REQUIRE(7 == difference(midi_note::F4, midi_note::C5));
  REQUIRE(8 == difference(midi_note::E4, midi_note::C5));
  REQUIRE(9 == difference(midi_note::Ds4, midi_note::C5));
  REQUIRE(10 == difference(midi_note::D4, midi_note::C5));
  REQUIRE(11 == difference(midi_note::Cs4, midi_note::C5));
  REQUIRE(12 == difference(midi_note::C4, midi_note::C5));
}