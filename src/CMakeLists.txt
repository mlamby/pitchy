# Find the location where vcpkg has installed rtmidi.
# Not sure why targetting the RtMidi link library doesn't
# automatically add the include path.
find_path(RTMIDI_INCLUDE_DIR NAMES RtMidi.h PATH_SUFFIXES rtmidi)

add_library(pitchy_lib
  midi/midi_source.cpp
  midi/midi_message.cpp)

target_include_directories(pitchy_lib 
  PUBLIC 
    ../include
  PRIVATE
    ${RTMIDI_INCLUDE_DIR})

target_link_libraries(pitchy_lib
  PRIVATE
    RtMidi::rtmidi
    project_options 
    project_warnings
)

add_executable(pitchy 
    main.cpp)

target_link_libraries(pitchy 
    PRIVATE
      project_options 
      project_warnings
      argh
      pitchy_lib
  )
