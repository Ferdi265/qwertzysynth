#include "state.h"

int octave = 0;
void keyboard_init() {

}

void keyboard_fini() {

}

void keyboard_update(SDL_Event e) {
    switch (e.type) {
        CASE(SDL_KEYDOWN) {
            int keysym = e.key.keysym.sym;
            switch (keysym) {
                CASE('+') {
                    int new_octave = ++octave;
                    fmt::print("octave: {}\n", new_octave);
                    break;
                }
                CASE('-') {
                    int new_octave = --octave;
                    fmt::print("octave: {}\n", new_octave);
                    break;
                }
                CASE('q') { synth_note(C*4>>octave); break; }
                CASE('2') { synth_note(Cis*4>>octave); break; }
                CASE('w') { synth_note(D*4>>octave); break; }
                CASE('3') { synth_note(Dis*4>>octave); break; }
                CASE('e') { synth_note(E*4>>octave); break; }
                CASE('r') { synth_note(F*4>>octave); break; }
                CASE('5') { synth_note(Fis*4>>octave); break; }
                CASE('t') { synth_note(G*4>>octave); break; }
                CASE('6') { synth_note(Gis*4>>octave); break; }
                CASE('z') { synth_note(A*4>>octave); break; }
                CASE('7') { synth_note(Ais*4>>octave); break; }
                CASE('u') { synth_note(B*4>>octave); break; }
                CASE('i') { synth_note(C*5>>octave); break; }
                CASE('9') { synth_note(Cis*5>>octave); break; }
                CASE('o') { synth_note(D*5>>octave); break; }
                CASE('0') { synth_note(Dis*5>>octave); break; }
                CASE('p') { synth_note(E*5>>octave); break; }
                CASE('y') { synth_note(C*3>>octave); break; }
                CASE('s') { synth_note(Cis*3>>octave); break; }
                CASE('x') { synth_note(D*3>>octave); break; }
                CASE('d') { synth_note(Dis*3>>octave); break; }
                CASE('c') { synth_note(E*3>>octave); break; }
                CASE('v') { synth_note(F*3>>octave); break; }
                CASE('g') { synth_note(Fis*3>>octave); break; }
                CASE('b') { synth_note(G*3>>octave); break; }
                CASE('h') { synth_note(Gis*3>>octave); break; }
                CASE('n') { synth_note(A*3>>octave); break; }
                CASE('j') { synth_note(Ais*3>>octave); break; }
                CASE('m') { synth_note(B*3>>octave); break; }
                CASE(',') { synth_note(C*4>>octave); break; }
                CASE('l') { synth_note(Cis*4>>octave); break; }
                CASE('.') { synth_note(D*4>>octave); break; }
                DEFAULT() {
                    fmt::print("key down: 0x{:x}\n", keysym);
                }
            }
            break;
        }
        CASE(SDL_KEYUP) {
            int keysym = e.key.keysym.sym;
            switch (keysym) {
                CASE('+') {
                    break;
                }
                CASE('-') {
                    break;
                }
                CASE('q') { synth_release(C*4>>octave); break; }
                CASE('2') { synth_release(Cis*4>>octave); break; }
                CASE('w') { synth_release(D*4>>octave); break; }
                CASE('3') { synth_release(Dis*4>>octave); break; }
                CASE('e') { synth_release(E*4>>octave); break; }
                CASE('r') { synth_release(F*4>>octave); break; }
                CASE('5') { synth_release(Fis*4>>octave); break; }
                CASE('t') { synth_release(G*4>>octave); break; }
                CASE('6') { synth_release(Gis*4>>octave); break; }
                CASE('z') { synth_release(A*4>>octave); break; }
                CASE('7') { synth_release(Ais*4>>octave); break; }
                CASE('u') { synth_release(B*4>>octave); break; }
                CASE('i') { synth_release(C*5>>octave); break; }
                CASE('9') { synth_release(Cis*5>>octave); break; }
                CASE('o') { synth_release(D*5>>octave); break; }
                CASE('0') { synth_release(Dis*5>>octave); break; }
                CASE('p') { synth_release(E*5>>octave); break; }
                CASE('y') { synth_release(C*3>>octave); break; }
                CASE('s') { synth_release(Cis*3>>octave); break; }
                CASE('x') { synth_release(D*3>>octave); break; }
                CASE('d') { synth_release(Dis*3>>octave); break; }
                CASE('c') { synth_release(E*3>>octave); break; }
                CASE('v') { synth_release(F*3>>octave); break; }
                CASE('g') { synth_release(Fis*3>>octave); break; }
                CASE('b') { synth_release(G*3>>octave); break; }
                CASE('h') { synth_release(Gis*3>>octave); break; }
                CASE('n') { synth_release(A*3>>octave); break; }
                CASE('j') { synth_release(Ais*3>>octave); break; }
                CASE('m') { synth_release(B*3>>octave); break; }
                CASE(',') { synth_release(C*4>>octave); break; }
                CASE('l') { synth_release(Cis*4>>octave); break; }
                CASE('.') { synth_release(D*4>>octave); break; }
                DEFAULT() {
                    fmt::print("key up: 0x{:x}\n", keysym);
                }
            }
            break;
        }
    }
}
