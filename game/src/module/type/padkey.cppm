export module padkey;

export {
enum class GamepadAxisType {
    Invalid = -1,
    LeftX = 0,
    LeftY = 1,
    RightX = 2,
    RightY = 3,
    LeftTrigger = 4,
    RightTrigger = 5,
};

enum class GamepadButtonType {
    Invalid = -1,
    South = 0, /**< Bottom face button (e.g. Xbox A button) */
    East = 1,  /**< Right face button (e.g. Xbox B button) */
    West = 2,  /**< Left face button (e.g. Xbox X button) */
    North = 3, /**< Top face button (e.g. Xbox Y button) */
    Back = 4,
    Guide = 5,
    Start = 6,
    LeftStick = 7,
    RightStick = 8,
    LeftShoulder = 9,
    RightShoulder = 10,
    DpadUp = 11,
    DpadDown = 12,
    DpadLeft = 13,
    DpadRight = 14,
    Misc1 = 15, /**< Additional button (e.g. Xbox Series X share button, PS5
               microphone button, Nintendo Switch Pro capture button, Steam
               Controller QAM button, Amazon Luna microphone button, Google
               Stadia capture button) */
    RightPaddle1 = 16, /**< Upper or primary paddle, under your right hand (e.g.
                       Xbox Elite paddle P1, DualSense Edge RB button, Right
                       Joy-Con SR button, Steam Controller R4 button) */
    LeftPaddle1 = 17,  /**< Upper or primary paddle, under your left hand (e.g.
                       Xbox  Elite paddle P3, DualSense Edge LB button, Left
                       Joy-Con SL  button, Steam Controller L4 button) */
    RightPaddle2 =
        18, /**< Lower or secondary paddle, under your right hand (e.g.
            Xbox Elite paddle P2, DualSense Edge right Fn button,
            Right Joy-Con SL button, Steam Controller R5 button) */
    LeftPaddle2 = 19, /**< Lower or secondary paddle, under your left hand (e.g.
                      Xbox Elite paddle P4, DualSense Edge left Fn button, Left
                      Joy-Con SR button, Steam Controller L5 button) */
    Touchpad = 20,    /**< PS4/PS5 touchpad button */
    Misc2 = 21,       /**< Additional button */
    Misc3 = 22, /**< Additional button (e.g. Nintendo GameCube left trigger
                   click) */
    Misc4 =
        23, /**< Additional button (e.g. Nintendo GameCube right trigger click)
             */
    Misc5 = 24, /**< Additional button */
    Misc6 = 25, /**< Additional button */
};
}
