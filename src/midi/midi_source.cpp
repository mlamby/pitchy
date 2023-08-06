#include "pitchy/midi/midi_source.h"
#include "pitchy/blocking_queue.h"

#include <cstdint>
#include <algorithm>
#include <ranges>
#include <iterator>
#include <string_view>
#include <optional>
#include <vector>
#include <cctype>
#include <format>

#include "RtMidi.h"

namespace pitchy
{
  namespace detail
  {
    using midi_queue = pitchy::queue<midi_parse_result>;

    struct midi_source_state
    {
      RtMidiIn input;
      midi_queue queue = {20};
    };

    std::optional<uint32_t> get_named_port_index(RtMidi &src, std::string_view name)
    {
      auto is_named_port = [&src, name](uint32_t index)
      {
        return std::ranges::contains_subrange(
            src.getPortName(index),
            name,
            [](char c1, char c2)
            {
              return std::tolower(c1) == std::tolower(c2);
            });
      };

      auto indexes = std::views::iota(0u, src.getPortCount());
      auto loc = std::ranges::find_if(indexes, is_named_port);
      if (std::ranges::end(indexes) != loc)
      {
        return *loc;
      }

      return std::nullopt;
    }

    auto get_port_names(RtMidi &src)
    {
      auto get_port_name = [&src](uint32_t index)
      {
        return src.getPortName(index);
      };

      midi_source::port_names_type result;

      std::ranges::copy(
          std::views::iota(0u, src.getPortCount()) | std::views::transform(get_port_name),
          std::back_inserter(result));

      return result;
    }

    void midi_callback(double delta_time, std::vector<unsigned char> *message, void *user_data)
    {
      (void)delta_time;
      (void)message;
      auto q = static_cast<midi_queue *>(user_data);

      q->push(parse_midi_event(*message));
    }
  }

  midi_source::midi_source() : state{std::make_unique<detail::midi_source_state>()}
  {
  }

  midi_source::~midi_source()
  {
  }

  uint32_t midi_source::port_count() const
  {
    return state->input.getPortCount();
  }

  midi_source::port_names_type midi_source::port_names() const
  {
    return detail::get_port_names(state->input);
  }

  void midi_source::open_device(uint32_t index)
  {
    if (index < port_count())
    {
      state->input.openPort(index);
      state->input.ignoreTypes(true, true, true);
      state->input.setCallback(&detail::midi_callback, &(state->queue));

      if (is_open())
      {
        std::cout << std::format("Midi Input Device Open: {}\n", state->input.getPortName(index));
      }
      else
      {
        throw std::runtime_error(std::format("Can't open midi devices: {}", state->input.getPortName(index)));
      }
    }
    else
    {
      throw std::runtime_error(std::format("midi device index out of range: {}", index));
    }

    state->queue.clear();
  }

  void midi_source::open_named_device(std::string_view name)
  {
    auto input_idx = detail::get_named_port_index(state->input, name);

    if (input_idx)
    {
      open_device(*input_idx);
    }
    else
    {
      throw std::runtime_error(std::format("No matching input device: {}\n", name));
    }
  }

  void midi_source::open_default_device()
  {
    open_device(0U);
  }

  bool midi_source::is_open() const
  {
    return state->input.isPortOpen();
  }

  midi_parse_result midi_source::get_next_midi_message()
  {
    midi_parse_result i{};
    state->queue.pop(i);
    return i;
  }
}