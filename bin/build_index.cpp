#include <iostream>
#include <string>

#include <tokenizer.h>
#include <index.h>
#include <utils.h>


using namespace std;

int main() {
    auto data = shket::utils::read_json<shket::utils::Movie>("/Users/chingachgook/dev/shket/resources/movies.json");
    std::cout << data.size() << std::endl;
//    data.resize(10000);

    shket::Tokenizer t;
    shket::Index idx;

    for (const auto &movie : data) {
        t.tokenize(movie.overview, [&idx, movie](std::string &&token) {
            idx.index(movie.title, token);
        });
    }

    idx.print();
}