module;
#include <log.hpp>
export module serialize;

import log;
import simdjson;

import std;

export {
template <typename T>
std::string Serialize(const T& payload) {
    auto result = simdjson::to_json(payload);

    if (result.error()) {
        LOGE("Serialize error: ", simdjson::error_message(result.error()));
        return "";
    }
    return result.value();
}

template <typename T>
void Deserialize(std::string& json, T& payload) {
    simdjson::ondemand::parser parser;
    simdjson::ondemand::document doc = parser.iterate(simdjson::pad(json));
    simdjson::error_code result = doc.get(payload);

    if (result) {
        LOGE("Deserialize error: ", simdjson::error_message(result));
        return;
    }
}
}
