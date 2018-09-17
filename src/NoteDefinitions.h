// This file is loaded into MidiFunctions.h
// Order: 1

#include <Arduino.h>

#define OCTAVE_NEGATIVE_2   0
#define OCTAVE_NEGATIVE_1   1
#define OCTAVE_0            2
#define OCTAVE_1            3
#define OCTAVE_2            4
#define OCTAVE_3            5
#define OCTAVE_4            6
#define OCTAVE_5            7
#define OCTAVE_6            8
#define OCTAVE_7            9
#define OCTAVE_8            10

#define NOTE_C              0
#define NOTE_C_SHARP        1
#define NOTE_D              2
#define NOTE_D_SHARP        3
#define NOTE_E              4
#define NOTE_F              5
#define NOTE_F_SHARP        6
#define NOTE_G              7
#define NOTE_G_SHARP        8
#define NOTE_A              9
#define NOTE_A_SHARP        10
#define NOTE_B              11

int lookup[11][12] = {
  { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 },
  { 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23 },
  { 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35 },
  { 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47 },
  { 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59 },
  { 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71 },
  { 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83 },
  { 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95 },
  { 96, 97, 98, 99, 100, 101, 102, 103, 104, 104, 106, 107 },
  { 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119 },
  { 120, 121, 122, 123, 124, 125, 126, 127, 127, 127, 127, 127 } // fill out the lookup table with the highest possible, 127
};

extern int lookup[11][12];

int midiNumberToNoteLookupTable[128] = {
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 0, 1, 2, 3, 4, 5, 6, 7
};

int midiNumberToOctaveLookupTable[128] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
  3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
  6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
  9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10
};

String noteLookupTable[12] = { "C", "C_SHARP", "D", "D_SHARP", "E", "F", "F_SHARP", "G", "G_SHARP", "A", "A_SHARP", "B" };

int octaveLookupTable[11] = { -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8 };

// http://www.c-thru-music.com/images/harmonic_table.gif
// https://i.imgur.com/mZBbe7h.gif
int harmonicTableLookup[1][7] = {
  // Root Position
  //      ___            ___            ___
  //  ___/ 1 \___    ___/ G \___    ___/ 79\___
  // / 2 \___/ 3 \  / D#\___/ E \  / 75\___/ 76\;
  // \___/ 4 \___/  \___/ C \___/  \___/ 72\___/
  // / 5 \___/ 7 \  / G#\___/ A \  / 68\___/ 69\;
  // \___/ 6 \___/  \___/ F \___/  \___/ 65\___/
  //     \___/          \___/          \___/
  // G4,D#4,E4,C4,G#3,F3,A3
  {
    lookup[OCTAVE_4][NOTE_G], lookup[OCTAVE_4][NOTE_D_SHARP], lookup[OCTAVE_4][NOTE_E], lookup[OCTAVE_4][NOTE_C],
    lookup[OCTAVE_3][NOTE_G_SHARP], lookup[OCTAVE_3][NOTE_F], lookup[OCTAVE_3][NOTE_A]
  }
};

extern int harmonicTableLookup[1][7];

extern String getNoteFromMidiNumber(int midiNumber) {
  return noteLookupTable[midiNumberToNoteLookupTable[midiNumber]];
}

extern int getOctaveFromMidiNumber(int midiNumber) {
  return octaveLookupTable[midiNumberToOctaveLookupTable[midiNumber]];
}
