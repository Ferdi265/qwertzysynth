#pragma once

enum struct note_name {
    C = 0,
    Cis = 1,
    Des = 1,
    D = 2,
    Dis = 3,
    Es = 3,
    E = 4,
    F = 5,
    Fis = 6,
    Ges = 6,
    G = 7,
    Gis = 8,
    As = 8,
    A = 9,
    Ais = 10,
    Bes = 10,
    B = 11
};
using enum note_name;

constexpr float TET_STEP = 1.0594630943592953f;

struct note {
    explicit constexpr note(int n) : n(n) {}
    constexpr note(note_name n) : n((int)n) {}

    constexpr float freq() const noexcept {
        float f = 440;
        int n = this->n - (int)A;

        if (n > 0) {
            while (n >= 12) {
                f *= 2;
                n -= 12;
            }
        } else {
            while (n < 0) {
                f /= 2;
                n += 12;
            }
        }

        while (n > 0) {
            f *= TET_STEP;
            n -= 1;
        }

        return f;
    }

    int n;
};

constexpr note operator*(note_name nn, int octave) {
        int n = (int)nn;
        octave -= 4;

        if (octave > 0) {
            while (octave > 0) {
                n += 12;
                octave -= 1;
            }
        } else {
            while (octave < 0) {
                n -= 12;
                octave += 1;
            }
        }

        return note(n);
}

constexpr note operator>>(note nn, int octave) {
    return note_name(nn.n) * (octave+4);
}
constexpr note operator<<(note nn, int octave) {
    return note_name(nn.n) * (4-octave);
}
