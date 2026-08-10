export module animation;
import time;
import std;

export {
template <typename T>
struct KeyFrame {
    T m_value{};
    TimeType m_time{};
};

class AnimationTrackBase {
public:
    virtual ~AnimationTrackBase() = default;
    virtual void Update(TimeType delta_time) = 0;

    virtual void Rewind() = 0;
    virtual TimeType GetFinishTime() const = 0;
};

enum class AnimationTrackType {
    Linear,
    Discrete,
};

template <typename T>
class AnimationTrack : public AnimationTrackBase {
public:
    using keyframe_type = KeyFrame<T>;

    AnimationTrack(AnimationTrackType type) : m_type(type) {}

    ~AnimationTrack() override = default;

    void Update(TimeType delta_time) override {
        if (m_cur_frame >= m_keyframes.size()) {
            return;
        }
        m_cur_time += delta_time;
        while (m_cur_frame + 1 < m_keyframes.size()) {
            auto& cur_frame = m_keyframes[m_cur_frame];
            auto& next_frame = m_keyframes[m_cur_frame + 1];

            if (next_frame.m_time <= m_cur_time) {
                m_cur_frame++;
            } else {
                break;
            }
        }
        m_cur_time = std::min(m_keyframes.back().m_time, m_cur_time);
    }

    T GetValue() const {
        if (m_type == AnimationTrackType::Discrete) {
            return m_keyframes[m_cur_frame].m_value;
        }
        if (m_cur_frame + 1 >= m_keyframes.size()) {
            return m_keyframes[m_cur_frame].m_value;
        }
        auto& cur_frame = m_keyframes[m_cur_frame];
        auto& next_frame = m_keyframes[m_cur_frame + 1];
        float t = (m_cur_time - cur_frame.m_time) /
                  (next_frame.m_time - cur_frame.m_time);
        return std::lerp(cur_frame.m_value, next_frame.m_value, t);
    }

    void AddKeyFrame(const keyframe_type& keyframe) {
        m_keyframes.emplace_back(keyframe);
    }

    TimeType GetFinishTime() const override {
        if (m_keyframes.empty()) {
            return 0;
        }
        return m_keyframes.back().m_time;
    }

    void Rewind() override {
        m_cur_frame = 0;
        m_cur_time = 0;
    }

private:
    std::vector<keyframe_type> m_keyframes;
    TimeType m_cur_time{};
    std::size_t m_cur_frame{};
    AnimationTrackType m_type;
};

class Animation {
public:
    template <typename T>
    void AddTrack(std::unique_ptr<AnimationTrack<T>> track) {
        m_max_time = std::max(m_max_time, track->GetFinishTime());
        m_tracks.emplace_back(std::move(track));
    }

    void Play();
    void Pause();
    void Stop();
    void Rewind();

    void Update(float delta_time);

    auto& GetTracks() const { return m_tracks; }

private:
    bool m_is_playing = false;
    TimeType m_max_time{};
    TimeType m_cur_time{};
    std::vector<std::unique_ptr<AnimationTrackBase>> m_tracks;
};
}
