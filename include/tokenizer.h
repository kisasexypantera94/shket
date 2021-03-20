#pragma once

#include "common/vector.h"

#include <functional>
#include <regex>
#include <string>

namespace shket {

using namespace common;

class Tokenizer {
public:
    using TokenProcessor = std::function<void(std::string &&token)>;

public:
    Tokenizer() = default;

    ~Tokenizer() = default;

public:
    void tokenize(const std::string &text, const TokenProcessor &processor);

private:
    std::regex delimiter_regex_{"[^\\s,:;._'\"`’]+"};
    std::regex stop_word_regex_{"(и|-|)"};
};

} // namespace shket
