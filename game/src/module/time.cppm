export module time;

import std;
export {
using TimeType = std::chrono::duration<double>;

class Time {
public:
    Time();

    void Update();

    TimeType GetElapsedTime();

private:
    TimeType m_elapsed_time;
    std::chrono::steady_clock::time_point m_cur_time{};
};
}
