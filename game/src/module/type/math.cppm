module;
export module math;

import simdjson;
import std;

export {
struct Vec2 final {
    union {
        float x;
        float w;
    };

    union {
        float y;
        float h;
    };

    Vec2();
    Vec2(float x, float y);

    Vec2& operator*=(const Vec2&);
    Vec2& operator*=(float);
    Vec2& operator/=(const Vec2&);
    Vec2& operator/=(float);
    Vec2& operator+=(const Vec2&);
    Vec2& operator-=(const Vec2&);
    float Dot(const Vec2&) const;
    float Cross(const Vec2&) const;
    float LengthSquared() const;
    float Length() const;
};

Vec2 operator*(float, const Vec2&);
Vec2 operator*(const Vec2&, float);
Vec2 operator*(const Vec2&, const Vec2&);
Vec2 operator/(const Vec2&, float);
Vec2 operator/(const Vec2&, const Vec2&);
Vec2 operator+(const Vec2&, const Vec2&);
Vec2 operator-(const Vec2&, const Vec2&);
float Dot(const Vec2&, const Vec2&);
float Cross(const Vec2&, const Vec2&);
Vec2 operator-(const Vec2&);

struct Color {
    float r{};
    float g{};
    float b{};
    float a = 1;
};

struct Rect {
    Vec2 m_center;
    Vec2 m_half_size;
};

struct Circle {
    float m_radius = 0;
    Vec2 m_position;
};

struct Radians;

struct Degrees {
    Degrees() = default;
    Degrees(float value);
    Degrees(Radians);
    Degrees& operator=(Radians);
    Degrees& operator=(float);

    Degrees& operator+=(Degrees o);
    Degrees& operator-=(Degrees o);
    Degrees& operator*=(Degrees o);
    Degrees& operator/=(Degrees o);

    float Value() const { return m_value; }

private:
    float m_value{};
};

Degrees operator-(Degrees d1, Degrees d2);
Degrees operator+(Degrees d1, Degrees d2);
Degrees operator*(Degrees d1, Degrees d2);
Degrees operator/(Degrees d1, Degrees d2);

struct Mat33 {
    static Mat33 CreateTranslation(const Vec2& v);
    static Mat33 CreateScale(const Vec2& v);
    static Mat33 CreateRotation(Degrees d);

    Mat33();
    float Get(std::size_t x, std::size_t y) const;
    float& Get(std::size_t x, std::size_t y);
    void Set(std::size_t x, std::size_t y, float value);

    Mat33& operator*=(const Mat33& o);

private:
    float m_data[3][3] = {0};
};

Mat33 operator*(const Mat33& m1, const Mat33& m2);

struct Radians {
    Radians() = default;
    Radians(float value);
    Radians(Degrees);
    Radians& operator=(Degrees);
    Radians& operator=(float);

    float Value() const { return m_value; }

private:
    float m_value{};
};

struct Region {
    Vec2 m_topleft;
    Vec2 m_size;
};

struct Transform {
    Vec2 m_position;
    Degrees m_rotation;
    Vec2 m_scale{1.0, 1.0};

    const Mat33& GetLocalMat() const;
    const Mat33& GetGlobalMat() const;
    void UpdateMat(const Transform* parent);

private:
    Mat33 m_mat;
    Mat33 m_global_mat;
};

namespace simdjson {
template <typename builder_type>
void tag_invoke(serialize_tag, builder_type& builder, const Degrees& payload) {
    builder.append(payload.Value());
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value& val, Degrees& payload) {
    double value;
    auto error = val.get_double().get(value);
    if (error) {
        return error;
    }
    payload = value;

    return simdjson::SUCCESS;
}

template <typename builder_type>
void tag_invoke(serialize_tag, builder_type& builder, const Radians& payload) {
    builder.append(payload.Value());
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value& val, Radians& payload) {
    double value;
    auto error = val.get_double().get(value);
    if (error) {
        return error;
    }
    payload = value;

    return simdjson::SUCCESS;
}
}  // namespace simdjson
}
