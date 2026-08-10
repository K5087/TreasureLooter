module time;

Time::Time() {
    m_cur_time = std::chrono::steady_clock::now();
}

void Time::Update() {
    auto cur_time = std::chrono::steady_clock::now();
    auto elapsed_time = cur_time - m_cur_time;
    m_cur_time = cur_time;
    m_elapsed_time =
        std::chrono::duration_cast<
            std::chrono::duration<TimeType, std::ratio<1>>>(elapsed_time)
            .count();

    m_elapsed_time = std::max(m_elapsed_time, MinElapseTime);
}

TimeType Time::GetElapsedTime() {
    return m_elapsed_time;
}
