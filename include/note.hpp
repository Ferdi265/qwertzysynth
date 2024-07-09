#pragma once

#include <compare>
#include <fmt/core.h>

enum class HitType {
    HIT_NORMAL,
    HIT_PADME,
    HIT_PADME_FIFTH,
    HIT_PADME_THIRD
};

constexpr const char * HIT_TYPES[] = {
    "Normal",
    "Padme",
    "Padme Fifth",
    "Padme Third",
};

enum struct NoteName {
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
using enum NoteName;

constexpr double TET_STEP = 1.0594630943592953f;

struct Note {
    explicit constexpr Note(int n) : n(n) {}
    constexpr Note(NoteName n) : n((int)n) {}

    constexpr double freq() const noexcept {
        double f = 440;
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

    constexpr friend auto operator<=>(Note, Note) = default;

    constexpr NoteName name() const noexcept {
        int n = this->n;
        if (n > 0) {
            while (n >= 12) {
                n -= 12;
            }
        } else {
            while (n < 0) {
                n += 12;
            }
        }

        return NoteName(n);
    }

    constexpr int octave() const noexcept {
        int n = this->n;
        int octave = 4;
        if (n > 0) {
            while (n >= 12) {
                octave++;
                n -= 12;
            }
        } else {
            while (n < 0) {
                octave--;
                n += 12;
            }
        }

        return octave;
    }

    int n;
};

template <>
struct fmt::formatter<HitType> {
    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(const HitType& type, FormatContext& ctx) {
        return fmt::format_to(ctx.out(), "{}",
            (
                type == HitType::HIT_NORMAL ? "" :
                type == HitType::HIT_PADME ? " (Pad)" :
                type == HitType::HIT_PADME_FIFTH ? " (Pad Fifth)" :
                type == HitType::HIT_PADME_THIRD ? " (Pad Third)" :
                "?"
            )
        );
    }
};

template <>
struct fmt::formatter<Note> {
    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(const Note& nt, FormatContext& ctx) {
        int octave = nt.octave();
        NoteName n = nt.name();
        return fmt::format_to(ctx.out(), "{}{}",
            (
                n == C ? "C-" :
                n == Cis ? "C#" :
                n == D ? "D-" :
                n == Dis ? "D#" :
                n == E ? "E-" :
                n == F ? "F-" :
                n == Fis ? "F#" :
                n == G ? "G-" :
                n == Gis ? "G#" :
                n == A ? "A-" :
                n == Ais ? "A#" :
                n == B ? "B-" :
                "?"
            ),
            octave
        );
    }
};

constexpr Note operator*(NoteName nn, int octave) {
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

        return Note(n);
}

constexpr Note operator>>(Note nn, int octave) {
    return NoteName(nn.n) * (octave+4);
}
constexpr Note operator<<(Note nn, int octave) {
    return NoteName(nn.n) * (4-octave);
}
constexpr Note operator+(Note nn, int i) {
    return Note(nn.n + i);
}
constexpr Note operator-(Note nn, int i) {
    return Note(nn.n - i);
}
