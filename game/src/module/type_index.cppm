export module type_index;

import std;

export {
using TypeIndex = std::uint32_t;

class TypeIndexGenerator {
public:
    template <typename>
    static TypeIndex Get() {
        static TypeIndex index = m_type_index++;
        return index;
    }

private:
    static TypeIndex m_type_index;
};
}
