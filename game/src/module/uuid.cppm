export module uuid;

import std;

export {
struct UUID {
    friend class std::hash<UUID>;
    static UUID CreateV4();
    static UUID CreateFromString(const std::string_view&);

    UUID();
    operator bool() const;

    bool operator==(const UUID& o) const;

    std::string ToString() const;

private:
    std::array<std::byte, 16> m_data;
};

namespace std {
template <>
struct hash<UUID> {
    using argument_type = UUID;
    using result_type = std::size_t;

    [[nodiscard]] result_type operator()(
        const argument_type& uuid) const noexcept;
};
}  // namespace std
}
