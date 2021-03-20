#include "index.h"

namespace shket {

void Index::index(const std::string &doc_id, const std::string &token) {
    auto it = word_to_docs_.find(token);
    if (it.has_value()) {
        auto &docs = it->get().second;
        if (!docs.binary_search(doc_id).first) {
            docs.push_back(doc_id);
        }
    } else {
        word_to_docs_.insert({token, {doc_id}});
    }
}

void Index::print() const {
    word_to_docs_.traverse([](const auto item) {
        std::cout << item.first << ": {";
        const auto &docs = item.second;
        for (size_t j = 0; j < docs.size(); ++j) {
            std::cout << docs[j] << (j == docs.size() - 1 ? "" : ", ");
        }
        std::cout << "}" << std::endl;
    });
}

}