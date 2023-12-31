#include <span>
#include <fmt/format.h>
#include "log.hpp"
#include "audio.hpp"
#include "app.hpp"

Audio::Audio() {
    SDL_AudioSpec audio_config {
        .freq = SAMPLE_RATE,
        .format = AUDIO_S16SYS,
        .channels = 1,
        .silence = 0,
        .samples = BUF_SIZE,
        .padding = 0,
        .size = 0,
        .callback = &Audio::update,
        .userdata = nullptr
    };

    device = SDL_OpenAudioDevice(
        nullptr, false, &audio_config, &audio_config, SDL_AUDIO_ALLOW_SAMPLES_CHANGE | SDL_AUDIO_ALLOW_FREQUENCY_CHANGE
    );
    if (device <= 0) {
        error("failed to open audio device\n");
        return;
    }

    if (audio_config.freq != SAMPLE_RATE) {
        warn("samplerate changed to {} Hz\n", audio_config.freq);
    }

    info("buffer size is {} samples\n", audio_config.samples);

    SDL_PauseAudioDevice(device, false);
}

Audio::~Audio() {
    SDL_CloseAudioDevice(device);
}

void Audio::update(void * userdata, uint8_t * raw_buffer, int raw_len) {
    (void)userdata;
    std::span<int16_t> buffer((int16_t *)raw_buffer, (int16_t *)(raw_buffer + raw_len));
    app->synth.update(buffer);
}
