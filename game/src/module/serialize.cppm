module;
export module serialize;
import std;

export {
template <typename T>
void serialize(std::string_view name, T& t);

template <typename T>
void deserialize(T& t, std::string_view name);
}
