#include "util.hpp"
#include "input.hpp"
#include "app.hpp"

void Input::update(SDL_Event e) {
    switch (e.type) {
        CASE(SDL_KEYDOWN) {
            int keysym = e.key.keysym.sym;
            if (e.key.repeat) {
                // ignore key repeats
                return;
            }

            app->keyboard.hit_key(keysym, e.key.timestamp);
            break;
        }
        CASE(SDL_KEYUP) {
            int keysym = e.key.keysym.sym;
            app->keyboard.release_key(keysym, e.key.timestamp);
            break;
        }
    }
}
