#include "utils.h"

#include <fstream>

#include <nlohmann/json.hpp>

namespace shket::utils {

void to_json(nlohmann::json &j, const Movie &m) {
    j = nlohmann::json{{"id",           m.id},
                       {"title",        m.title},
                       {"poster",       m.poster},
                       {"overview",     m.overview},
                       {"release_date", m.release_date}};

}

void from_json(const nlohmann::json &j, Movie &m) {
    j.at("id").get_to(m.id);
    j.at("title").get_to(m.title);
    j.at("poster").get_to(m.poster);
    j.at("overview").get_to(m.overview);
    j.at("release_date").get_to(m.release_date);
}

template<typename Format>
auto read_json(const std::string &filename) -> std::vector<Format> {
    using json = nlohmann::json;

    json json_data;
    std::ifstream ifs(filename);
    ifs >> json_data;

    std::vector<Format> items;
    for (auto &element : json_data) {
        items.push_back(element.get<Format>());
    }

    return items;
}

template auto read_json<Movie>(const std::string &filename) -> std::vector<Movie>;

}