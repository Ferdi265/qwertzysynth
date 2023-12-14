#pragma once

#include <array>
#include <utility>
#include <fmt/format.h>

#define CASE(value) case value:
#define DEFAULT() default:

#define CONCAT_INTERNAL__(a, b) a ## b
#define CONCAT(a, b) CONCAT_INTERNAL__(a, b)
#define UNIQUE_IDENT(a) CONCAT(a, __COUNTER__)
