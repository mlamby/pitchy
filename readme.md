# Pitchy Chord Detector

Simple command line application that will listen for midi note data from a connected midi device and display the chord being played.


## Examples

Playing the notes of the C Major triad.

```
Midi:[C4] Notes:[C] Chords:[]
Midi:[C4,E4] Notes:[C,E] Chords:[]
Midi:[C4,E4,G4] Notes:[C,E,G] Chords:[C Major]
```

Playing the notes of C Major over G (second inversion)

```
Midi:[G3] Notes:[G] Chords:[]
Midi:[G3,C4] Notes:[C,G] Chords:[]
Midi:[G3,C4,E4] Notes:[C,E,G] Chords:[C Major / G]
```

Playing the notes of E Major with the base note doubled and the G# and B swapped.

```
Midi:[E2] Notes:[E] Chords:[]
Midi:[E2,E3] Notes:[E] Chords:[]
Midi:[E2,E3,G#4] Notes:[E,G#] Chords:[]
Midi:[E2,E3,B3,G#4] Notes:[E,G#,B] Chords:[E Major]
```

## Why?

This is my attempt at coming up with an algorithm to detect the presence of a chord amongst a series of notes. There algorithm I came up with is captured in `recognise_chord()` defined within [chord.h](include/pitchy/chord.h). It relies on processing a list of notes that have had their octave number removed. This can be seen in the examples above in the 'Notes:' collection. There are most likely much better recognised algorithms for doing this!

A big limitation at the moment is that it doesn't recognise enharmonics. All black notes are represented as sharps. This means a common chord like Bb Major will be recognised as the less common A# Major.

Also as a proof of concept I've only added a limited sub-set of chord extensions. It currently detects Major, Minor, Dominant, Major 7th, Minor 7th, Suspended 2nd, and Suspended 4th.

This was also a chance to try out some of the newer (> c++17) C++ features, such as Ranges, Format and even Variants. Since I had it available to me, I've used some C++23 ranges features, including `std::ranges::to`, since it makes life so much easier.

## Building

This project uses vcpkg for package management and CMake to build. I use vscode and msvc and  the CMake/vcpkg integration just works. You milage will definitely vary on other platforms.
