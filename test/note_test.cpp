#include "pitchy/note.h"

#include <catch2/catch_test_macros.hpp>

using namespace pitchy;

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