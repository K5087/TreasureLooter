export module time;

import std;
export {
using TimeType = double;

class Time {
public:
    Time();

    void Update();

    TimeType GetElapsedTime();

private:
    static constexpr TimeType MinElapseTime = 0.000001;
    TimeType m_elapsed_time{MinElapseTime};
    std::chrono::steady_clock::time_point m_cur_time{};
};
}
