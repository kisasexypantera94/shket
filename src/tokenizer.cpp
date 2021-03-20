#include "tokenizer.h"

namespace shket {

void Tokenizer::tokenize(const std::string &text, const TokenProcessor &processor) {
    std::for_each(std::sregex_token_iterator(text.cbegin(), text.cend(), delimiter_regex_),
                  std::sregex_token_iterator(),
                  [this, processor](std::string token) {
                      if (!std::regex_match(token, stop_word_regex_) && token.size() > 2) {
                          processor(std::move(token));
                      }
                  });
}

}