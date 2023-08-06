#ifndef PITCHY_MIDI_SOURCE_H
#define PITCHY_MIDI_SOURCE_H

#include "pitchy/midi/midi_message.h"

#include <memory>
#include <string>
#include <string_view>
#include <vector>

namespace pitchy
{
  namespace detail
  {
    struct midi_source_state;
  }

  class midi_source
  {
    public:
      using port_names_type = std::vector<std::string>;  

    public:
      midi_source();
      ~midi_source();

      uint32_t port_count() const;
      port_names_type port_names() const;

      void open_named_device(std::string_view name);
      void open_default_device();
      void open_device(uint32_t index);

      bool is_open() const;

      // Blocking call to get the next midi message.
      midi_parse_result get_next_midi_message();

    private:
      std::unique_ptr<detail::midi_source_state> state;
  };

}

#endif