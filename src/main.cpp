#include <SDL.h>
#include <fmt/format.h>
#include <span>
#include <atomic>
#include "note.h"

constexpr static uint32_t SAMPLE_LENGTH = 256;
constexpr static uint32_t SAMPLE_RATE = 48000;
constexpr static uint32_t freq_sample_step(float freq, float rate) {
    return (SAMPLE_LENGTH / ((1 / freq) * rate)) * (1 << 16);
}
constexpr static uint32_t note_sample_step(note n, float rate) {
    return freq_sample_step(n.freq(), rate);
}

int16_t sample_triangle(uint8_t duty, uint8_t offset, int16_t volume) {
    if (offset < duty) return offset * (2*volume) / duty - volume;
    else return (SAMPLE_LENGTH - offset) * (2*volume) / (SAMPLE_LENGTH - duty) - volume;
}

constexpr static uint32_t sample_steps[] = {
    note_sample_step(A*2, SAMPLE_RATE),
    note_sample_step(A*3, SAMPLE_RATE),
    note_sample_step(C*3, SAMPLE_RATE),
    note_sample_step(C*4, SAMPLE_RATE)
};

struct beat_state {
    constexpr static uint32_t baseduty = 32;
    constexpr static uint32_t lfofreq = 1;
    constexpr static uint32_t lfosize = 32;
    constexpr static uint32_t volume = 64;

    uint32_t t = 0, t2 = 0;
    uint32_t fbase = 0;

    note cur_note = A*2;
    uint32_t ctr = 0, ctrstep = note_sample_step(A*2, SAMPLE_RATE);
    uint32_t lfo = 0;
    constexpr static uint32_t lfostep = freq_sample_step(lfofreq, SAMPLE_RATE);

    int8_t sample() {
        uint8_t duty = baseduty + sample_triangle(128, (uint8_t)(lfo >> 16), lfosize);
        int8_t sample = sample_triangle(duty, (uint8_t)(ctr >> 16), volume);
        return sample;
    }

    void update() {
        ctr += ctrstep;
        if (ctr > (SAMPLE_LENGTH << 16)) ctr -= SAMPLE_LENGTH << 16;
        lfo += lfostep;
        if (lfo > (SAMPLE_LENGTH << 16)) lfo -= SAMPLE_LENGTH << 16;

        if ((t2 & ((1 << 18) - 1)) == 0) { t = 0; if (t2 & (1 << 18)) {
            fbase = 2;
        } else {
            fbase = 0;
        } }
        if ((t & ((1 << 13) - 1)) == 0) { lfo = 0; ctr = 0;
            if ((t >> 13) % 3 != 2) {
                ctrstep = note_sample_step(cur_note, SAMPLE_RATE);
            } else {
                ctrstep = note_sample_step(cur_note>>1, SAMPLE_RATE);
            }
        }
        t++;
        t2++;
    }
};

std::atomic<int> octave = 0;
std::atomic<note> cur_note = A*2;

bool fade_in = true;
beat_state state;
void update_audio(void * userdata, uint8_t * raw_buffer, int raw_len) {
    (void)userdata;

    state.cur_note = cur_note>>octave;

    std::span<int16_t> buffer(reinterpret_cast<int16_t *>(raw_buffer), reinterpret_cast<int16_t *>(raw_buffer + raw_len));
    for (size_t i = 0; i < buffer.size(); i++) {
        buffer[i] = (state.sample() * (1 << 7));
        state.update();

        if (fade_in) {
            buffer[i] *= ((float)i/buffer.size());
        }
    }

    fade_in = false;
}

constexpr static uint32_t WIDTH = 640;
constexpr static uint32_t HEIGHT = 480;

void update(SDL_Renderer * renderer, SDL_Texture * texture) {

    //SDL_UpdateTexture(texture, nullptr, framebuffer.data(), WIDTH);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}

#define CASE(value) case value:
#define DEFAULT() default:

void run(SDL_Renderer * renderer, SDL_Texture * texture) {
    while (true) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                CASE(SDL_QUIT) {
                    return;
                }

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
                        CASE('q') { cur_note = C*4; break; }
                        CASE('2') { cur_note = Cis*4; break; }
                        CASE('w') { cur_note = D*4; break; }
                        CASE('3') { cur_note = Dis*4; break; }
                        CASE('e') { cur_note = E*4; break; }
                        CASE('r') { cur_note = F*4; break; }
                        CASE('5') { cur_note = Fis*4; break; }
                        CASE('t') { cur_note = G*4; break; }
                        CASE('6') { cur_note = Gis*4; break; }
                        CASE('z') { cur_note = A*4; break; }
                        CASE('7') { cur_note = Ais*4; break; }
                        CASE('u') { cur_note = B*4; break; }
                        CASE('i') { cur_note = C*5; break; }
                        CASE('9') { cur_note = Cis*5; break; }
                        CASE('o') { cur_note = D*5; break; }
                        CASE('0') { cur_note = Dis*5; break; }
                        CASE('p') { cur_note = E*5; break; }
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
                        DEFAULT() {
                            fmt::print("key up: 0x{:x}\n", keysym);
                        }
                    }
                }
            }
        }

        update(renderer, texture);
    }
}

int main() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    SDL_Window * window = SDL_CreateWindow("Music", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE | SDL_RENDERER_PRESENTVSYNC);
    SDL_Texture * texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);

    int samplerate = 48000;
    SDL_AudioSpec audio_config {
        .freq = samplerate,
        .format = AUDIO_S16SYS,
        .channels = 1,
        .silence = 0,
        .samples = 0,
        .padding = 0,
        .size = 0,
        .callback = update_audio,
        .userdata = nullptr
    };

    SDL_AudioDeviceID audio_dev = SDL_OpenAudioDevice(
        nullptr, false, &audio_config, &audio_config, SDL_AUDIO_ALLOW_SAMPLES_CHANGE | SDL_AUDIO_ALLOW_FREQUENCY_CHANGE
    );
    if (audio_dev <= 0) {
        fmt::print("error: failed to open audio device\n");
        return 1;
    }

    if (audio_config.freq != samplerate) {
        fmt::print("warn: samplerate changed to {} Hz\n", audio_config.freq);
    }

    fmt::print("info: buffer size is {} samples\n", audio_config.samples);

    SDL_PauseAudioDevice(audio_dev, false);

    run(renderer, texture);

    SDL_CloseAudioDevice(audio_dev);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
