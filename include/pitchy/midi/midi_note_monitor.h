#ifndef PITCHY_MIDI_NOTE_MONITOR_H
#define PITCHY_MIDI_NOTE_MONITOR_H

#include "midi_source.h"

#include <vector>
#include <algorithm>

namespace pitchy
{
  namespace detail
  {
    // Helper class for creating a type matching visitor for a variant.
    // Taken from https://en.cppreference.com/w/cpp/utility/variant/visit
    template <class... Ts>
    struct overloaded : Ts...
    {
      using Ts::operator()...;
    };
  } // namespace detail

  using note_on_collection_type = std::vector<midi_note>;

  // Updates the collection of currently on notes with the information contained
  // within the passed in midi message.
  //
  // If the midi message is a note on event then the note is added to the notes_on
  // collection, provided it is not already in the collection. New notes are
  // ordered when inserted into the collection such that all the notes in the
  // collection are ordered by midi note value.
  //
  // If the midi message is a note off event then the note is removed from
  // the collection.
  //
  // Returns a boolean indicating if the collection was updated as a result
  // of handling the midi message.
  //
  bool update_note_on(note_on_collection_type &notes_on, const midi_parse_result &msg)
  {
    bool changed = false;

    std::visit(
        detail::overloaded{
            [&notes_on, &changed](midi_note_on_message msg)
            {
              if (!std::ranges::contains(notes_on, msg.note))
              {
                // Note isn't already in the list - insert it whilst
                // keeping the list ordered.
                notes_on.insert(std::ranges::upper_bound(notes_on, msg.note), msg.note);
                changed = true;
              }
            },
            [&notes_on, &changed](midi_note_off_message msg)
            {
              if (std::ranges::contains(notes_on, msg.note))
              {
                notes_on.erase(std::ranges::find(notes_on, msg.note));
                changed = true;
              }
            },
            [](auto msg)
            {
              (void)msg;
            }},
        msg);

    return changed;
  }
} // namespace pitchy

#endif