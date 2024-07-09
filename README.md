# Qwertzysynth

A simple program to make sounds with, using the Chromatic Button Accordeon B
System layout. Inspired by [shric/midi](https://github.com/shric/midi/) and
[Qwertuoso](https://www.linusakesson.net/software/qwertuoso/index.php). I have
recently extended this to also include a keyboard layout similar to
[Padme](https://www.linusakesson.net/music/padme/index.php).

![qwertzysynth](https://github.com/Ferdi265/qwertzysynth/assets/4077106/1aefd88f-dd4d-44e8-bb29-14f7010347f2)

## Features

Qwertzysynth is quite hacky, and doesn't support many things yet and lacks many
features that Qwertuoso and Padme have, but it does have a few things.

- Three Keyboard Layouts:
  - Piano Layout (similar to Famitracker)
  - Qwertuoso (B-Griff) Layout
  - Padme (5ths and 3rds in Circle of Fifths) Layout
- Octave Select (Numpad +/- and via GUI)
- Semitone Transposition (via GUI)
- Fully synthesized modulated Triangle wave (currently with hardcoded ADSR envelope)

## Usage

```
usage: qwertzysynth [OPTIONS]

OPTIONS:
  -h, --help ............ show this help
  -l L, --layout L ...... set initial layout (default qwertuoso)
    b, b-griff .......... chromatic button accordion B-Griff (default)
    q, qwertuoso ........ alias for b-griff
    p, piano ............ piano key layout
    P, padme ............ padme key layout
  -t T, --transpose T ... transpose by T half steps
  -o O, --octave O ...... transpose by O octaves

LAYOUTS:
  All QwertzySynth layouts are designed for QWERTZ keyboard layouts.
  Support for QWERTY might be provided in a future version.

B-GRIFF LAYOUT:

   KEY | NOTE || KEY | NOTE || KEY | NOTE || KEY | NOTE
  ------------------------------------------------------
       |      ||     |      ||     |      ||  <  | C-3
    1  | C-3  ||  Q  | C#3  ||  A  | D-3  ||  Y  | D#3
    2  | D#3  ||  W  | E-3  ||  S  | F-3  ||  X  | F#3
    3  | F#3  ||  E  | G-3  ||  D  | G#3  ||  C  | A-3
    4  | A-3  ||  R  | A#3  ||  F  | B-3  ||  V  | C-4
    5  | C-4  ||  T  | C#4  ||  G  | D-4  ||  B  | D#4
    6  | D#4  ||  Z  | E-4  ||  H  | F-4  ||  N  | F#4
    7  | F#4  ||  U  | G-4  ||  J  | G#4  ||  M  | A-4
    8  | A-4  ||  I  | A#4  ||  K  | B-4  ||  ,  | C-5
    9  | C-5  ||  O  | C#5  ||  L  | D-5  ||  .  | D#5
    0  | D#5  ||  P  | E-5  ||  Ö  | F-5  ||  -  | F#5
    ß  | F#5  ||  Ü  | G-5  ||  Ä  | G#5  ||     |
    ´  |      ||  +  | A#5  ||  #  | B-5  ||     |

PIANO LAYOUT:

   KEY | NOTE || KEY | NOTE || KEY | NOTE || KEY | NOTE
  ------------------------------------------------------
       |      ||     |      ||     |      ||  <  | D#3
    1  |      ||  Q  | C-4  ||  A  |      ||  Y  | C-3
    2  | C#4  ||  W  | D-4  ||  S  | C#3  ||  X  | D-3
    3  | D#4  ||  E  | E-4  ||  D  | D#3  ||  C  | E-3
    4  |      ||  R  | F-4  ||  F  |      ||  V  | F-3
    5  | F#4  ||  T  | G-4  ||  G  | F#3  ||  B  | G-3
    6  | G#4  ||  Z  | A-4  ||  H  | G#3  ||  N  | A-3
    7  | A#4  ||  U  | B-4  ||  J  | A#3  ||  M  | B-3
    8  |      ||  I  | C-5  ||  K  |      ||  ,  | C-4
    9  | C#5  ||  O  | D-5  ||  L  | C#4  ||  .  | D-4
    0  | D#5  ||  P  | E-5  ||  Ö  | D#4  ||  -  | E-4
    ß  |      ||  Ü  | F-5  ||  Ä  |      ||     |
    ´  |      ||  +  | G-5  ||  #  | F#4  ||     |

PADME LAYOUT:

   KEY |  NOTE  || KEY |  NOTE  || KEY |  NOTE  || KEY |  NOTE 
  --------------------------------------------------------------
       |        ||     |        ||     |        ||  <  | E  5th
    1  | B  3rd ||  Q  | F# 3rd ||  A  | B  5th ||  Y  | F# 5th
    2  | Db 3rd ||  W  | Ab 3rd ||  S  | Db 5th ||  X  | Ab 5th
    3  | Eb 3rd ||  E  | Bb 3rd ||  D  | Eb 5th ||  C  | Bb 5th
    4  | F  3rd ||  R  | C  3rd ||  F  | F  5th ||  V  | C  5th
    5  | G  3rd ||  T  | D  3rd ||  G  | G  5th ||  B  | D  5th
    6  | A  3rd ||  Z  | E  3rd ||  H  | A  5th ||  N  | E  5th
    7  | B  3rd ||  U  | F# 3rd ||  J  | B  5th ||  M  | F# 5th
    8  | Db 3rd ||  I  | Ab 3rd ||  K  | Db 5th ||  ,  | Ab 5th
    9  | Eb 3rd ||  O  | Bb 3rd ||  L  | Eb 5th ||  .  | Bb 5th
    0  | F  3rd ||  P  | C  3rd ||  Ö  | F  5th ||  -  | C  5th
    ß  | G  3rd ||  Ü  | D  3rd ||  Ä  | G  5th ||     |
    ´  |        ||  +  | E  3rd ||  #  | A  5th ||     |
```

The layout can also be interactively switched using the ImGui UI.

## Building

- Install `cmake`, `SDL2`, and `fmt` from the package manager of your choice
- Run `cmake -B build`
- Run `cmake --build build`
- Run `./build/qwertzysynth` and enjoy
