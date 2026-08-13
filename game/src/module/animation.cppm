export module animation;
export import animation.type;

import path;
import entity;
import handle;
import time;
import manager;
import asset.manager;

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
    virtual AnimationTrackType GetType() const = 0;
};

template <typename T>
class IAnimationTrack : public AnimationTrackBase {
public:
    using keyframe_type = KeyFrame<T>;

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

    virtual T GetValue() const = 0;

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

    auto& GetKeyFrames() const { return m_keyframes; }

protected:
    std::vector<keyframe_type> m_keyframes;
    TimeType m_cur_time{};
    std::size_t m_cur_frame{};
};

template <typename T, AnimationTrackType type>
class AnimationTrack;

template <typename T>
class AnimationTrack<T, AnimationTrackType::Linear>
    : public IAnimationTrack<T> {
public:
    AnimationTrackType GetType() const override {
        return AnimationTrackType::Linear;
    }

    T GetValue() const override {
        if (this->m_cur_frame + 1 >= this->m_keyframes.size()) {
            return this->m_keyframes[this->m_cur_frame].m_value;
        }
        auto& cur_frame = this->m_keyframes[this->m_cur_frame];
        auto& next_frame = this->m_keyframes[this->m_cur_frame + 1];
        float t = (this->m_cur_time - cur_frame.m_time) /
                  (next_frame.m_time - cur_frame.m_time);
        return std::lerp(cur_frame.m_value, next_frame.m_value, t);
    }
};

template <typename T>
class AnimationTrack<T, AnimationTrackType::Discrete>
    : public IAnimationTrack<T> {
public:
    AnimationTrackType GetType() const override {
        return AnimationTrackType::Discrete;
    }

    T GetValue() const override {
        return this->m_keyframes[this->mp_cur_frame].m_value;
    }
};

class Animation {
public:
    static constexpr int InfLoop = -1;

    void AddTrack(AnimationBindingPoint binding,
                  std::unique_ptr<AnimationTrackBase> track) {
        m_max_time = std::max(m_max_time, track->GetFinishTime());
        m_tracks[binding] = std::move(track);
    }

    void Play();
    void Pause();
    void Stop();
    void Rewind();
    void SetLoop(int count);

    void Update(float delta_time);

    auto& GetTracks() const { return m_tracks; }

    void Sync(Entity entity);

    int GetLoopCount() const;

private:
    bool m_is_playing = false;
    int m_loop{0};
    TimeType m_max_time{};
    TimeType m_cur_time{};
    std::unordered_map<AnimationBindingPoint,
                       std::unique_ptr<AnimationTrackBase>>
        m_tracks;
};

class AnimationComponentManager : public ComponentManager<Animation> {
public:
    void Update(TimeType delta_time);

private:
};

using AnimationHandle = Handle<Animation>;

class AnimationManager : public AssetManagerBase<Animation> {
public:
    AnimationHandle Load(const Path& filename) override {
        // TODO: not impl
        return {};
    };

    AnimationHandle Create();
};
}
