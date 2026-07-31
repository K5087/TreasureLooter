export module button;

export class Button {
public:
    virtual ~Button() = default;
    virtual bool IsPressing() const = 0;
    virtual bool IsReleasing() const = 0;
    virtual bool IsReleased() const = 0;
    virtual bool IsPressed() const = 0;
};
