#ifndef PITCHY_CHORD_H
#define PITCHY_CHORD_H

#include "pitchy/midi/midi_note.h"
#include "pitchy/note.h"
#include "pitchy/interval.h"

#include <cstdint>
#include <tuple>
#include <ranges>
#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string_view>
#include <format>

namespace pitchy
{
  enum class chord_type
  {
    major,
    major7,
    minor,
    minor7,
    dominant,
    sus2,
    sus4
  };

  constexpr std::string_view to_string(chord_type t)
  {
    switch (t)
    {
    case chord_type::major:
      return "Major";
      break;
    case chord_type::major7:
      return "Major7";
      break;
    case chord_type::minor:
      return "Minor";
      break;
    case chord_type::minor7:
      return "Minor7";
      break;
    case chord_type::dominant:
      return "Dominant";
      break;
    case chord_type::sus2:
      return "Sus2";
      break;
    case chord_type::sus4:
      return "Sus4";
      break;
    }
    return "";
  }

  // A chord recognition result, consisting of:
  // root note, chord_type, lowest_note_interval
  using lowest_note_interval = interval;
  using chord_recognition_result = std::tuple<note, chord_type, lowest_note_interval>;

  inline std::string to_string(const chord_recognition_result &v)
  {
    const auto &[n, chord, lowest_interval] = v;

    if (interval::root == lowest_interval)
    {
      return std::format(
          "{} {}",
          to_string(n),
          to_string(chord));
    }

    return std::format(
        "{} {} / {}",
        to_string(n),
        to_string(chord),
        to_string(raise_note(n, lowest_interval)));
  }

  namespace detail
  {
    // Mapping of chord type to the intervals that make up the chord.
    static std::unordered_map<chord_type, std::vector<interval>> chord_intervals = {
        {chord_type::major, {interval::root, interval::major_third, interval::perfect_fifth}},
        {chord_type::minor, {interval::root, interval::minor_third, interval::perfect_fifth}},
        {chord_type::major7, {interval::root, interval::major_third, interval::perfect_fifth, interval::major_seventh}},
        {chord_type::minor7, {interval::root, interval::minor_third, interval::perfect_fifth, interval::minor_seventh}},
        {chord_type::dominant, {interval::root, interval::major_third, interval::perfect_fifth, interval::minor_seventh}},
        {chord_type::sus2, {interval::root, interval::major_second, interval::perfect_fifth}},
        {chord_type::sus4, {interval::root, interval::perfect_fourth, interval::perfect_fifth}}};
  }

  // Given a range of octaveless notes, attempts to find an entry in the chord_intervals
  // mapping that matches the intervals between the notes.
  template <std::ranges::viewable_range R>
  std::vector<chord_recognition_result> recognise_chord(R &&notes, note lowest_note)
  {
    std::vector<chord_recognition_result> results;

    // Try each note in the range as the root note.
    // For example if notes is the following range [E, G, C]
    // Try E as the root, then G, then C.
    for (auto potential_root : notes)
    {
      // Calculate the intervals between the potential_root and each note in the range.
      // Given the example of [E, G, C]
      // When potential_root is E, this transform will return:
      //   - [root, minor_third, minor_sixth]
      // When potential_root is G, returns:
      //   - [major_sixth, root, perfect_fourth]
      // When potential_root is C, returns:
      //   - [mafor_third, perfect_fifth, root]
      auto intervals = notes | std::views::transform([&potential_root](note n)
                                                     { return note_interval(potential_root, n); });

      // Search through the reference chord interval collection
      for (const auto &[chord_name, reference_intervals] : detail::chord_intervals)
      {
        // Check if the current set of intervals is a permutation of the
        // reference intervals. Need to do a permutation check because a chord
        // could be inverted.
        // In the example given above, only the third set of intervals will match
        // a major chord with the root of C.
        if (std::ranges::is_permutation(reference_intervals, intervals))
        {
          results.push_back(chord_recognition_result{
              potential_root,
              chord_name,
              note_interval(potential_root, lowest_note)});
        }
      }
    }

    return results;
  }

  // Given a collection of midi notes return a collection of notes without octave
  // number and then duplicates removed.
  // E.g. Given [A4, A5, C4] returns [A,C]
  std::pair<std::vector<note>, note> remove_octaves(const std::vector<midi_note> &midi_notes)
  {
    if (std::ranges::empty(midi_notes))
    {
      return {};
    }
    
    // Find the lowest note that is being played.
    const auto lowest_note = pitchy::remove_octave(std::ranges::min(midi_notes));

    auto notes_only = midi_notes | std::views::transform(remove_octave) | std::ranges::to<std::vector>();

    // Remove duplicates by sorting and calling unique()
    std::ranges::sort(notes_only);
    const auto [first, last] = std::ranges::unique(notes_only);
    notes_only.erase(first, last);

    return {notes_only, lowest_note};
  }

  // Convenience function that takes a collection of midi notes and returns any
  // chords that are found.
  std::vector<chord_recognition_result> find_all_chords(const std::vector<midi_note> &midi_notes)
  {
    const auto &[notes_only, lowest_note] = pitchy::remove_octaves(midi_notes);
    return recognise_chord(notes_only, lowest_note);
  }
}

#endif