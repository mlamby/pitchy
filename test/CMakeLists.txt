add_executable(pitchy_tests 
  midi/test_midi_note.cpp
  midi/test_midi_message.cpp
  midi/test_midi_note_monitor.cpp
  note_test.cpp
  interval_test.cpp
  chord_recognise_test.cpp
)

target_link_libraries(pitchy_tests 
  PRIVATE
  project_options 
  project_warnings
  pitchy_lib
  Catch2::Catch2 
  Catch2::Catch2WithMain
)

add_test(pitchy_tests pitchy_tests)