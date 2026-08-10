module animation;

void Animation::Play() {
    m_is_playing = true;
}

void Animation::Pause() {
    m_is_playing = false;
}

void Animation::Stop() {
    m_is_playing = false;
    Rewind();
}

void Animation::Rewind() {
    for (auto& track : m_tracks) {
        track->Rewind();
    }
}

void Animation::Update(float delta_time) {
    m_cur_time += delta_time;
    for (auto& track : m_tracks) {
        track->Update(delta_time);
    }
    if (m_cur_time >= m_max_time) {
        Pause();
    }
}
