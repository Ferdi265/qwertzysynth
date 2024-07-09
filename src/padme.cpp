#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <fmt/format.h>
#include "if_guard.hpp"
#include "padme.hpp"
#include "app.hpp"

const std::unordered_map<int, Note> Padme::KEY_MAP = [](){
    std::unordered_map<int, Note> key_map;

    // TODO: fix this
    return key_map;

    key_map.emplace('1', C*3);
    key_map.emplace('2', Dis*3);
    key_map.emplace('3', Fis*3);
    key_map.emplace('4', A*3);
    key_map.emplace('5', C*4);
    key_map.emplace('6', Dis*4);
    key_map.emplace('7', Fis*4);
    key_map.emplace('8', A*4);
    key_map.emplace('9', C*5);
    key_map.emplace('0', Dis*5);
    key_map.emplace(0xdf /* ß */, Fis*5);

    key_map.emplace('q', Cis*3);
    key_map.emplace('w', E*3);
    key_map.emplace('e', G*3);
    key_map.emplace('r', Ais*3);
    key_map.emplace('t', Cis*4);
    key_map.emplace('z', E*4);
    key_map.emplace('u', G*4);
    key_map.emplace('i', Ais*4);
    key_map.emplace('o', Cis*5);
    key_map.emplace('p', E*5);
    key_map.emplace(0xfc /* 'ü' */, G*5);
    key_map.emplace('+', Ais*5);

    key_map.emplace('a', D*3);
    key_map.emplace('s', F*3);
    key_map.emplace('d', Gis*3);
    key_map.emplace('f', B*3);
    key_map.emplace('g', D*4);
    key_map.emplace('h', F*4);
    key_map.emplace('j', Gis*4);
    key_map.emplace('k', B*4);
    key_map.emplace('l', D*5);
    key_map.emplace(0xf6 /* 'ö' */, F*5);
    key_map.emplace(0xe4 /* 'ä' */, Gis*5);
    key_map.emplace('#', B*5);

    key_map.emplace('<', C*3);
    key_map.emplace('y', Dis*3);
    key_map.emplace('x', Fis*3);
    key_map.emplace('c', A*3);
    key_map.emplace('v', C*4);
    key_map.emplace('b', Dis*4);
    key_map.emplace('n', Fis*4);
    key_map.emplace('m', A*4);
    key_map.emplace(',', C*5);
    key_map.emplace('.', Dis*5);
    key_map.emplace('-', Fis*5);

    return key_map;
}();

void Padme::print_layout_table() {
    // TODO: fix this
    return;

    fmt::print(
        "B-GRIFF LAYOUT:\n"
        "\n"
        "   KEY | NOTE || KEY | NOTE || KEY | NOTE || KEY | NOTE\n"
        "  ------------------------------------------------------\n"
        "       |      ||     |      ||     |      ||  <  | C-3\n"
        "    1  | C-3  ||  Q  | C#3  ||  A  | D-3  ||  Y  | D#3\n"
        "    2  | D#3  ||  W  | E-3  ||  S  | F-3  ||  X  | F#3\n"
        "    3  | F#3  ||  E  | G-3  ||  D  | G#3  ||  C  | A-3\n"
        "    4  | A-3  ||  R  | A#3  ||  F  | B-3  ||  V  | C-4\n"
        "    5  | C-4  ||  T  | C#4  ||  G  | D-4  ||  B  | D#4\n"
        "    6  | D#4  ||  Z  | E-4  ||  H  | F-4  ||  N  | F#4\n"
        "    7  | F#4  ||  U  | G-4  ||  J  | G#4  ||  M  | A-4\n"
        "    8  | A-4  ||  I  | A#4  ||  K  | B-4  ||  ,  | C-5\n"
        "    9  | C-5  ||  O  | C#5  ||  L  | D-5  ||  .  | D#5\n"
        "    0  | D#5  ||  P  | E-5  ||  Ö  | F-5  ||  -  | F#5\n"
        "    ß  | F#5  ||  Ü  | G-5  ||  Ä  | G#5  ||     |\n"
        "    ´  |      ||  +  | A#5  ||  #  | B-5  ||     |\n"
        "\n"
    );
}

std::optional<std::pair<Note, HitType>> Padme::map_key(int keysym) {
    auto it = KEY_MAP.find(keysym);
    if (it ==  KEY_MAP.end()) {
        return std::nullopt;
    } else {
        return std::make_pair(it->second, HitType::HIT_PADME);
    }
}

void Padme::render() {

}
