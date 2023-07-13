#include <fmt/format.h>
#include "app.hpp"
#include "util.hpp"

int octave = 0;

void Keyboard::update(SDL_Event e) {
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
                CASE('q') { app->synth.hit(C*4>>octave); break; }
                CASE('2') { app->synth.hit(Cis*4>>octave); break; }
                CASE('w') { app->synth.hit(D*4>>octave); break; }
                CASE('3') { app->synth.hit(Dis*4>>octave); break; }
                CASE('e') { app->synth.hit(E*4>>octave); break; }
                CASE('r') { app->synth.hit(F*4>>octave); break; }
                CASE('5') { app->synth.hit(Fis*4>>octave); break; }
                CASE('t') { app->synth.hit(G*4>>octave); break; }
                CASE('6') { app->synth.hit(Gis*4>>octave); break; }
                CASE('z') { app->synth.hit(A*4>>octave); break; }
                CASE('7') { app->synth.hit(Ais*4>>octave); break; }
                CASE('u') { app->synth.hit(B*4>>octave); break; }
                CASE('i') { app->synth.hit(C*5>>octave); break; }
                CASE('9') { app->synth.hit(Cis*5>>octave); break; }
                CASE('o') { app->synth.hit(D*5>>octave); break; }
                CASE('0') { app->synth.hit(Dis*5>>octave); break; }
                CASE('p') { app->synth.hit(E*5>>octave); break; }
                CASE('y') { app->synth.hit(C*3>>octave); break; }
                CASE('s') { app->synth.hit(Cis*3>>octave); break; }
                CASE('x') { app->synth.hit(D*3>>octave); break; }
                CASE('d') { app->synth.hit(Dis*3>>octave); break; }
                CASE('c') { app->synth.hit(E*3>>octave); break; }
                CASE('v') { app->synth.hit(F*3>>octave); break; }
                CASE('g') { app->synth.hit(Fis*3>>octave); break; }
                CASE('b') { app->synth.hit(G*3>>octave); break; }
                CASE('h') { app->synth.hit(Gis*3>>octave); break; }
                CASE('n') { app->synth.hit(A*3>>octave); break; }
                CASE('j') { app->synth.hit(Ais*3>>octave); break; }
                CASE('m') { app->synth.hit(B*3>>octave); break; }
                CASE(',') { app->synth.hit(C*4>>octave); break; }
                CASE('l') { app->synth.hit(Cis*4>>octave); break; }
                CASE('.') { app->synth.hit(D*4>>octave); break; }
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
                CASE('q') { app->synth.release(C*4>>octave); break; }
                CASE('2') { app->synth.release(Cis*4>>octave); break; }
                CASE('w') { app->synth.release(D*4>>octave); break; }
                CASE('3') { app->synth.release(Dis*4>>octave); break; }
                CASE('e') { app->synth.release(E*4>>octave); break; }
                CASE('r') { app->synth.release(F*4>>octave); break; }
                CASE('5') { app->synth.release(Fis*4>>octave); break; }
                CASE('t') { app->synth.release(G*4>>octave); break; }
                CASE('6') { app->synth.release(Gis*4>>octave); break; }
                CASE('z') { app->synth.release(A*4>>octave); break; }
                CASE('7') { app->synth.release(Ais*4>>octave); break; }
                CASE('u') { app->synth.release(B*4>>octave); break; }
                CASE('i') { app->synth.release(C*5>>octave); break; }
                CASE('9') { app->synth.release(Cis*5>>octave); break; }
                CASE('o') { app->synth.release(D*5>>octave); break; }
                CASE('0') { app->synth.release(Dis*5>>octave); break; }
                CASE('p') { app->synth.release(E*5>>octave); break; }
                CASE('y') { app->synth.release(C*3>>octave); break; }
                CASE('s') { app->synth.release(Cis*3>>octave); break; }
                CASE('x') { app->synth.release(D*3>>octave); break; }
                CASE('d') { app->synth.release(Dis*3>>octave); break; }
                CASE('c') { app->synth.release(E*3>>octave); break; }
                CASE('v') { app->synth.release(F*3>>octave); break; }
                CASE('g') { app->synth.release(Fis*3>>octave); break; }
                CASE('b') { app->synth.release(G*3>>octave); break; }
                CASE('h') { app->synth.release(Gis*3>>octave); break; }
                CASE('n') { app->synth.release(A*3>>octave); break; }
                CASE('j') { app->synth.release(Ais*3>>octave); break; }
                CASE('m') { app->synth.release(B*3>>octave); break; }
                CASE(',') { app->synth.release(C*4>>octave); break; }
                CASE('l') { app->synth.release(Cis*4>>octave); break; }
                CASE('.') { app->synth.release(D*4>>octave); break; }
                DEFAULT() {
                    fmt::print("key up: 0x{:x}\n", keysym);
                }
            }
            break;
        }
    }
}
