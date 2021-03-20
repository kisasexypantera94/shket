#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace shket::utils {

//"id": "29751",
//"title": "Batman Unmasked: The Psychology of the Dark Knight",
//"poster": "https://image.tmdb.org/t/p/w1280/jjHu128XLARc2k4cJrblAvZe0HE.jpg",
//"overview": "Delve into the world of Batman and the vigilante justice tha",
//"release_date": "2008-07-15"
struct Movie {
    std::string id;
    std::string title;
    std::string poster;
    std::string overview;
    int release_date;
};

template<typename Format>
auto read_json(const std::string &filename) -> std::vector<Format>;

}