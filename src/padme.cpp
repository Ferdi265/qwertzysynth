#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <fmt/format.h>
#include "if_guard.hpp"
#include "padme.hpp"
#include "app.hpp"

const std::unordered_map<int, std::pair<Note, HitType>> Padme::KEY_MAP = [](){
    std::unordered_map<int, std::pair<Note, HitType>> key_map;

    key_map.emplace('y', std::make_pair(Ges*4, HitType::HIT_PADME_FIFTH));
    key_map.emplace('x', std::make_pair(As*4, HitType::HIT_PADME_FIFTH));
    key_map.emplace('c', std::make_pair(Bes*4, HitType::HIT_PADME_FIFTH));
    key_map.emplace('v', std::make_pair(C*4, HitType::HIT_PADME_FIFTH));
    key_map.emplace('b', std::make_pair(D*4, HitType::HIT_PADME_FIFTH));
    key_map.emplace('n', std::make_pair(E*4, HitType::HIT_PADME_FIFTH));
    key_map.emplace('m', std::make_pair(Ges*4, HitType::HIT_PADME_FIFTH));
    key_map.emplace(',', std::make_pair(As*4, HitType::HIT_PADME_FIFTH));
    key_map.emplace('.', std::make_pair(Bes*4, HitType::HIT_PADME_FIFTH));
    key_map.emplace('-', std::make_pair(C*4, HitType::HIT_PADME_FIFTH));

    key_map.emplace('a', std::make_pair(B*4, HitType::HIT_PADME_FIFTH));
    key_map.emplace('s', std::make_pair(Des*4, HitType::HIT_PADME_FIFTH));
    key_map.emplace('d', std::make_pair(Es*4, HitType::HIT_PADME_FIFTH));
    key_map.emplace('f', std::make_pair(F*4, HitType::HIT_PADME_FIFTH));
    key_map.emplace('g', std::make_pair(G*4, HitType::HIT_PADME_FIFTH));
    key_map.emplace('h', std::make_pair(A*4, HitType::HIT_PADME_FIFTH));
    key_map.emplace('j', std::make_pair(B*4, HitType::HIT_PADME_FIFTH));
    key_map.emplace('k', std::make_pair(Des*4, HitType::HIT_PADME_FIFTH));
    key_map.emplace('l', std::make_pair(Es*4, HitType::HIT_PADME_FIFTH));
    key_map.emplace(0xf6 /* 'ö' */, std::make_pair(F*4, HitType::HIT_PADME_FIFTH));
    key_map.emplace(0xe4 /* 'ä' */, std::make_pair(G*4, HitType::HIT_PADME_FIFTH));
    key_map.emplace('#', std::make_pair(A*4, HitType::HIT_PADME_FIFTH));

    key_map.emplace('q', std::make_pair(Ges*4, HitType::HIT_PADME_THIRD));
    key_map.emplace('w', std::make_pair(As*4, HitType::HIT_PADME_THIRD));
    key_map.emplace('e', std::make_pair(Bes*4, HitType::HIT_PADME_THIRD));
    key_map.emplace('r', std::make_pair(C*4, HitType::HIT_PADME_THIRD));
    key_map.emplace('t', std::make_pair(D*4, HitType::HIT_PADME_THIRD));
    key_map.emplace('z', std::make_pair(E*4, HitType::HIT_PADME_THIRD));
    key_map.emplace('u', std::make_pair(Ges*4, HitType::HIT_PADME_THIRD));
    key_map.emplace('i', std::make_pair(As*4, HitType::HIT_PADME_THIRD));
    key_map.emplace('o', std::make_pair(Bes*4, HitType::HIT_PADME_THIRD));
    key_map.emplace('p', std::make_pair(C*4, HitType::HIT_PADME_THIRD));
    key_map.emplace(0xfc /* 'ü' */, std::make_pair(D*4, HitType::HIT_PADME_THIRD));
    key_map.emplace('*', std::make_pair(E*4, HitType::HIT_PADME_THIRD));

    key_map.emplace('1', std::make_pair(B*4, HitType::HIT_PADME_THIRD));
    key_map.emplace('2', std::make_pair(Des*4, HitType::HIT_PADME_THIRD));
    key_map.emplace('3', std::make_pair(Es*4, HitType::HIT_PADME_THIRD));
    key_map.emplace('4', std::make_pair(F*4, HitType::HIT_PADME_THIRD));
    key_map.emplace('5', std::make_pair(G*4, HitType::HIT_PADME_THIRD));
    key_map.emplace('6', std::make_pair(A*4, HitType::HIT_PADME_THIRD));
    key_map.emplace('7', std::make_pair(B*4, HitType::HIT_PADME_THIRD));
    key_map.emplace('8', std::make_pair(Des*4, HitType::HIT_PADME_THIRD));
    key_map.emplace('9', std::make_pair(Es*4, HitType::HIT_PADME_THIRD));
    key_map.emplace('0', std::make_pair(F*4, HitType::HIT_PADME_THIRD));
    key_map.emplace(0xdf /* ß */, std::make_pair(G*4, HitType::HIT_PADME_THIRD));

    return key_map;
}();

void Padme::print_layout_table() {
    // TODO: layout table
}

std::optional<std::pair<Note, HitType>> Padme::map_key(int keysym) {
    auto it = KEY_MAP.find(keysym);
    if (it ==  KEY_MAP.end()) {
        return std::nullopt;
    } else {
        return it->second;
    }
}

void Padme::render() {
    // TODO: render
}