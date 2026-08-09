export module animation;
import time;
import std;

export {
template <typename T>
struct KeyFrame {
    T m_value{};
    float m_time{};
};

class AnimationTrackBase {
public:
    virtual ~AnimationTrackBase() = default;
    virtual void Update(TimeType delta_time) = 0;
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
        while (m_cur_frame + 1 <= m_keyframes.size()) {
            auto& cur_frame = m_keyframes[m_cur_frame];
            auto& next_frame = m_keyframes[m_cur_frame + 1];

            m_cur_time += delta_time.count();
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

private:
    std::vector<keyframe_type> m_keyframes;
    T m_cur_time{};
    std::size_t m_cur_frame{};
    AnimationTrackType m_type;
};

class Animation {
public:
    void Play();
    void Pause();
    void Stop();
    void Rewind();

    void Update(float delta_time);

private:
    bool m_is_playing = false;
    std::vector<std::unique_ptr<AnimationTrackBase>> m_tracks;
};
}
