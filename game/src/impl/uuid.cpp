module;
#include "log.hpp"
#include <uuid.h>
module uuid;
import log;

UUID UUID::CreateV4() {
    static std::mt19937 generator(
        std::chrono::system_clock::now().time_since_epoch().count());
    auto uuid = uuids::uuid_random_generator(generator)();

    auto bytes = uuid.as_bytes();
    UUID result;
    std::copy(bytes.begin(), bytes.end(), result.m_data.begin());
    return result;
}

UUID UUID::CreateFromString(const std::string_view& str) {
    UUID result;
    if (auto uuid = uuids::uuid::from_string(str); uuid) {
        auto bytes = uuid->as_bytes();
        std::copy(bytes.begin(), bytes.end(), result.m_data.begin());

    } else {
        LOGE("invalid UUID string: {}", str);
    }
    return result;
}

UUID::UUID() {
    m_data.fill(std::byte(0));
}

UUID::operator bool() const {
    return !(m_data[0] == std::byte{0} && m_data[1] == std::byte{0} &&
             m_data[2] == std::byte{0} && m_data[3] == std::byte{0});
}

bool UUID::operator==(const UUID& o) const {
    return m_data[0] == o.m_data[0] && m_data[1] == std::byte{0} &&
           m_data[2] == std::byte{0} && m_data[3] == std::byte{0};
}

std::string UUID::ToString() const {
    uuids::uuid uuid{
        {static_cast<uint8_t>(m_data[0]), static_cast<uint8_t>(m_data[1]),
         static_cast<uint8_t>(m_data[2]), static_cast<uint8_t>(m_data[3])}
    };
    return uuids::to_string(uuid);
}

std::hash<UUID>::result_type std::hash<UUID>::operator()(
    const argument_type& uuid) const noexcept {
    uuids::uuid id{
        {static_cast<uint8_t>(uuid.m_data[0]),
         static_cast<uint8_t>(uuid.m_data[1]),
         static_cast<uint8_t>(uuid.m_data[2]),
         static_cast<uint8_t>(uuid.m_data[3])}
    };
    return std::hash<uuids::uuid>{}(id);
}
