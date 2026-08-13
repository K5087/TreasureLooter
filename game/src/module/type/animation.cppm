export module animation.type;

export {
enum class AnimationTrackType {
    Linear,
    Discrete,
};

enum class AnimationBindingPoint {
    Unknown,
    TransformPosition,
    TransformScale,
    TransformRotation,

    SpriteRegion,
    SpriteSize,
    SpriteImage,
    SpriteFlip,
};
}
