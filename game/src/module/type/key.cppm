export module key;

export {
enum Key {
    Unknown = 0x00000000u,       /**< 0 */
    Return = 0x0000000du,        /**< '\r' */
    Escape = 0x0000001bu,        /**< '\x1B' */
    Backspace = 0x00000008u,     /**< '\b' */
    Tab = 0x00000009u,           /**< '\t' */
    Space = 0x00000020u,         /**< ' ' */
    Exclaim = 0x00000021u,       /**< '!' */
    Dblapostrophe = 0x00000022u, /**< '"' */
    Hash = 0x00000023u,          /**< '#' */
    Dollar = 0x00000024u,        /**< '$' */
    Percent = 0x00000025u,       /**< '%' */
    Ampersand = 0x00000026u,     /**< '&' */
    Apostrophe = 0x00000027u,    /**< '\'' */
    Leftparen = 0x00000028u,     /**< '(' */
    Rightparen = 0x00000029u,    /**< ')' */
    Asterisk = 0x0000002au,      /**< '*' */
    Plus = 0x0000002bu,          /**< '+' */
    Comma = 0x0000002cu,         /**< ',' */
    Minus = 0x0000002du,         /**< '-' */
    Period = 0x0000002eu,        /**< '.' */
    Slash = 0x0000002fu,         /**< '/' */
    Num_0 = 0x00000030u,         /**< '0' */
    Num_1 = 0x00000031u,         /**< '1' */
    Num_2 = 0x00000032u,         /**< '2' */
    Num_3 = 0x00000033u,         /**< '3' */
    Num_4 = 0x00000034u,         /**< '4' */
    Num_5 = 0x00000035u,         /**< '5' */
    Num_6 = 0x00000036u,         /**< '6' */
    Num_7 = 0x00000037u,         /**< '7' */
    Num_8 = 0x00000038u,         /**< '8' */
    Num_9 = 0x00000039u,         /**< '9' */
    Colon = 0x0000003au,         /**< ':' */
    Semicolon = 0x0000003bu,     /**< ';' */
    Less = 0x0000003cu,          /**< '<' */
    Equals = 0x0000003du,        /**< '=' */
    Greater = 0x0000003eu,       /**< '>' */
    Question = 0x0000003fu,      /**< '?' */
    AT = 0x00000040u,            /**< '@' */
    LeftBracket = 0x0000005bu,   /**< '[' */
    Backslash = 0x0000005cu,     /**< '\\' */
    RightBracket = 0x0000005du,  /**< ']' */
    Caret = 0x0000005eu,         /**< '^' */
    Underscore = 0x0000005fu,    /**< '_' */
    Grave = 0x00000060u,         /**< '`' */
    A = 0x00000061u,             /**< 'a' */
    B = 0x00000062u,             /**< 'b' */
    C = 0x00000063u,             /**< 'c' */
    D = 0x00000064u,             /**< 'd' */
    E = 0x00000065u,             /**< 'e' */
    F = 0x00000066u,             /**< 'f' */
    G = 0x00000067u,             /**< 'g' */
    H = 0x00000068u,             /**< 'h' */
    I = 0x00000069u,             /**< 'i' */
    J = 0x0000006au,             /**< 'j' */
    K = 0x0000006bu,             /**< 'k' */
    L = 0x0000006cu,             /**< 'l' */
    M = 0x0000006du,             /**< 'm' */
    N = 0x0000006eu,             /**< 'n' */
    O = 0x0000006fu,             /**< 'o' */
    P = 0x00000070u,             /**< 'p' */
    Q = 0x00000071u,             /**< 'q' */
    R = 0x00000072u,             /**< 'r' */
    S = 0x00000073u,             /**< 's' */
    T = 0x00000074u,             /**< 't' */
    U = 0x00000075u,             /**< 'u' */
    V = 0x00000076u,             /**< 'v' */
    W = 0x00000077u,             /**< 'w' */
    X = 0x00000078u,             /**< 'x' */
    Y = 0x00000079u,             /**< 'y' */
    Z = 0x0000007au,             /**< 'z' */
    LeftBrace = 0x0000007bu,     /**< '{' */
    Pipe = 0x0000007cu,          /**< '|' */
    RightBrace = 0x0000007du,    /**< '}' */
    Tilde = 0x0000007eu,         /**< '~' */
    Delete = 0x0000007fu,        /**< '\x7F' */
    Plusminus = 0x000000b1u,     /**< '\xB1' */
    Capslock =
        0x40000039u,   /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CAPSLOCK) */
    F1 = 0x4000003au,  /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F1) */
    F2 = 0x4000003bu,  /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F2) */
    F3 = 0x4000003cu,  /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F3) */
    F4 = 0x4000003du,  /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F4) */
    F5 = 0x4000003eu,  /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F5) */
    F6 = 0x4000003fu,  /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F6) */
    F7 = 0x40000040u,  /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F7) */
    F8 = 0x40000041u,  /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F8) */
    F9 = 0x40000042u,  /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F9) */
    F10 = 0x40000043u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F10) */
    F11 = 0x40000044u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F11) */
    F12 = 0x40000045u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F12) */
    Printscreen =
        0x40000046u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PRINTSCREEN) */
    Scrolllock =
        0x40000047u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SCROLLLOCK) */
    Pause = 0x40000048u,  /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAUSE) */
    Insert = 0x40000049u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_INSERT) */
    Home = 0x4000004au,   /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_HOME) */
    Pageup = 0x4000004bu, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAGEUP) */
    End = 0x4000004du,    /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_END) */
    Pagedown =
        0x4000004eu,     /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAGEDOWN) */
    Right = 0x4000004fu, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RIGHT) */
    Left = 0x40000050u,  /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LEFT) */
    Down = 0x40000051u,  /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_DOWN) */
    Up = 0x40000052u,    /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_UP) */
    Numlockclear =
        0x40000053u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_NUMLOCKCLEAR) */
    KP_Divide =
        0x40000054u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DIVIDE) */
    KP_Multiply =
        0x40000055u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MULTIPLY) */
    KP_Minus =
        0x40000056u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MINUS) */
    KP_Plus = 0x40000057u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PLUS) */
    KP_Enter =
        0x40000058u,    /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_ENTER) */
    KP_1 = 0x40000059u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_1) */
    KP_2 = 0x4000005au, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_2) */
    KP_3 = 0x4000005bu, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_3) */
    KP_4 = 0x4000005cu, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_4) */
    KP_5 = 0x4000005du, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_5) */
    KP_6 = 0x4000005eu, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_6) */
    KP_7 = 0x4000005fu, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_7) */
    KP_8 = 0x40000060u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_8) */
    KP_9 = 0x40000061u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_9) */
    KP_0 = 0x40000062u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_0) */
    KP_Period =
        0x40000063u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PERIOD) */
    Application =
        0x40000065u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_APPLICATION) */
    Power = 0x40000066u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_POWER) */
    KP_Equals =
        0x40000067u,   /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_EQUALS) */
    F13 = 0x40000068u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F13) */
    F14 = 0x40000069u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F14) */
    F15 = 0x4000006au, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F15) */
    F16 = 0x4000006bu, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F16) */
    F17 = 0x4000006cu, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F17) */
    F18 = 0x4000006du, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F18) */
    F19 = 0x4000006eu, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F19) */
    F20 = 0x4000006fu, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F20) */
    F21 = 0x40000070u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F21) */
    F22 = 0x40000071u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F22) */
    F23 = 0x40000072u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F23) */
    F24 = 0x40000073u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F24) */
    Execute = 0x40000074u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_EXECUTE) */
    Help = 0x40000075u,    /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_HELP) */
    Menu = 0x40000076u,    /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MENU) */
    Select = 0x40000077u,  /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SELECT) */
    Stop = 0x40000078u,    /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_STOP) */
    Again = 0x40000079u,   /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AGAIN) */
    Undo = 0x4000007au,    /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_UNDO) */
    Cut = 0x4000007bu,     /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CUT) */
    Copy = 0x4000007cu,    /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_COPY) */
    Paste = 0x4000007du,   /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PASTE) */
    Find = 0x4000007eu,    /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_FIND) */
    Mute = 0x4000007fu,    /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MUTE) */
    VolumeUp =
        0x40000080u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_VOLUMEUP) */
    VolumeDown =
        0x40000081u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_VOLUMEDOWN) */
    KP_Comma =
        0x40000085u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_COMMA) */
    KP_Equalsas400 =
        0x40000086u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_EQUALSAS400)
                      */
    Alterase =
        0x40000099u,      /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_ALTERASE) */
    Sysreq = 0x4000009au, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SYSREQ) */
    Cancel = 0x4000009bu, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CANCEL) */
    Clear = 0x4000009cu,  /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CLEAR) */
    Prior = 0x4000009du,  /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PRIOR) */
    Return2 = 0x4000009eu, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RETURN2) */
    Separator =
        0x4000009fu,    /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SEPARATOR) */
    Out = 0x400000a0u,  /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_OUT) */
    Oper = 0x400000a1u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_OPER) */
    Clearagain =
        0x400000a2u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CLEARAGAIN) */
    Crsel = 0x400000a3u,  /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CRSEL) */
    Exsel = 0x400000a4u,  /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_EXSEL) */
    KP_00 = 0x400000b0u,  /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_00) */
    KP_000 = 0x400000b1u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_000) */
    Thousandsseparator =
        0x400000b2u, /**<
                        SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_THOUSANDSSEPARATOR)
                      */
    Decimalseparator =
        0x400000b3u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_DECIMALSEPARATOR)
                      */
    Currencyunit =
        0x400000b4u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CURRENCYUNIT) */
    Currencysubunit =
        0x400000b5u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CURRENCYSUBUNIT)
                      */
    KP_leftparen =
        0x400000b6u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_LEFTPAREN) */
    KP_rightparen =
        0x400000b7u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_RIGHTPAREN) */
    KP_leftbrace =
        0x400000b8u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_LEFTBRACE) */
    KP_rightbrace =
        0x400000b9u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_RIGHTBRACE) */
    KP_tab = 0x400000bau, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_TAB) */
    KP_backspace =
        0x400000bbu, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_BACKSPACE) */
    KP_a = 0x400000bcu,   /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_A) */
    KP_b = 0x400000bdu,   /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_B) */
    KP_c = 0x400000beu,   /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_C) */
    KP_d = 0x400000bfu,   /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_D) */
    KP_e = 0x400000c0u,   /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_E) */
    KP_f = 0x400000c1u,   /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_F) */
    KP_Xor = 0x400000c2u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_XOR) */
    KP_Power =
        0x400000c3u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_POWER) */
    KP_Percent =
        0x400000c4u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PERCENT) */
    KP_Less = 0x400000c5u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_LESS) */
    KP_Greater =
        0x400000c6u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_GREATER) */
    KP_Ampersand =
        0x400000c7u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_AMPERSAND) */
    KP_Dblampersand =
        0x400000c8u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DBLAMPERSAND)
                      */
    KP_Verticalbar =
        0x400000c9u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_VERTICALBAR)
                      */
    KP_Dblverticalbar =
        0x400000cau, /**<
                        SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DBLVERTICALBAR)
                      */
    KP_Colon =
        0x400000cbu, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_COLON) */
    KP_Hash = 0x400000ccu, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_HASH) */
    KP_Space =
        0x400000cdu,     /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_SPACE) */
    KP_AT = 0x400000ceu, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_AT) */
    KP_Exclam =
        0x400000cfu, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_EXCLAM) */
    KP_Memstore =
        0x400000d0u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMSTORE) */
    KP_Memrecall =
        0x400000d1u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMRECALL) */
    KP_Memclear =
        0x400000d2u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMCLEAR) */
    KP_Memadd =
        0x400000d3u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMADD) */
    KP_Memsubtract =
        0x400000d4u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMSUBTRACT)
                      */
    KP_Memmultiply =
        0x400000d5u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMMULTIPLY)
                      */
    KP_Memdivide =
        0x400000d6u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMDIVIDE) */
    KP_Plusminus =
        0x400000d7u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PLUSMINUS) */
    KP_Clear =
        0x400000d8u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_CLEAR) */
    KP_Clearentry =
        0x400000d9u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_CLEARENTRY) */
    KP_Binary =
        0x400000dau, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_BINARY) */
    KP_Octal =
        0x400000dbu, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_OCTAL) */
    KP_Decimal =
        0x400000dcu, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DECIMAL) */
    KP_Hexadecimal =
        0x400000ddu, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_HEXADECIMAL)
                      */
    Lctrl = 0x400000e0u,  /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LCTRL) */
    Lshift = 0x400000e1u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LSHIFT) */
    Lalt = 0x400000e2u,   /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LALT) */
    Lgui = 0x400000e3u,   /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LGUI) */
    Rctrl = 0x400000e4u,  /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RCTRL) */
    Rshift = 0x400000e5u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RSHIFT) */
    Ralt = 0x400000e6u,   /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RALT) */
    Rgui = 0x400000e7u,   /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RGUI) */
    Mode = 0x40000101u,   /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MODE) */
    Sleep = 0x40000102u,  /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SLEEP) */
    Wake = 0x40000103u,   /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_WAKE) */
    Channel_Increment =
        0x40000104u, /**<
                        SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CHANNEL_INCREMENT)
                      */
    Channel_Decrement =
        0x40000105u, /**<
                        SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CHANNEL_DECREMENT)
                      */
    MediaPlay =
        0x40000106u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MEDIA_PLAY) */
    MediaPause =
        0x40000107u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MEDIA_PAUSE) */
    MediaRecord =
        0x40000108u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MEDIA_RECORD) */
    MediaFast_forward =
        0x40000109u, /**<
                        SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MEDIA_FAST_FORWARD)
                      */
    MediaRewind =
        0x4000010au, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MEDIA_REWIND) */
    MediaNext_track =
        0x4000010bu, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MEDIA_NEXT_TRACK)
                      */
    MediaPrevious_track =
        0x4000010cu, /**<
                        SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MEDIA_PREVIOUS_TRACK)
                      */
    MediaStop =
        0x4000010du, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MEDIA_STOP) */
    MediaEject =
        0x4000010eu, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MEDIA_EJECT) */
    MediaPlay_pause =
        0x4000010fu, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MEDIA_PLAY_PAUSE)
                      */
    MediaSelect =
        0x40000110u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MEDIA_SELECT) */
    Ac_New = 0x40000111u,  /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_NEW) */
    Ac_Open = 0x40000112u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_OPEN) */
    Ac_Close =
        0x40000113u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_CLOSE) */
    Ac_Exit = 0x40000114u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_EXIT) */
    Ac_Save = 0x40000115u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_SAVE) */
    Ac_Print =
        0x40000116u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_PRINT) */
    Ac_Properties =
        0x40000117u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_PROPERTIES) */
    Ac_Search =
        0x40000118u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_SEARCH) */
    Ac_Home = 0x40000119u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_HOME) */
    Ac_Back = 0x4000011au, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_BACK) */
    Ac_Forward =
        0x4000011bu, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_FORWARD) */
    Ac_Stop = 0x4000011cu, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_STOP) */
    Ac_Refresh =
        0x4000011du, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_REFRESH) */
    Ac_Bookmarks =
        0x4000011eu, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_BOOKMARKS) */
    SoftLeft =
        0x4000011fu, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SOFTLEFT) */
    SoftRight =
        0x40000120u,    /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SOFTRIGHT) */
    Call = 0x40000121u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CALL) */
    EndCall = 0x40000122u, /**< SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_ENDCALL) */
    LeftTab = 0x20000001u, /**< Extended key Left Tab */
    Level5_Shift = 0x20000002u,    /**< Extended key Level 5 Shift */
    MultiKeyCompose = 0x20000003u, /**< Extended key Multi-key Compose */
    LMeta = 0x20000004u,           /**< Extended key Left Meta */
    RMeta = 0x20000005u,           /**< Extended key Right Meta */
    LHyper = 0x20000006u,          /**< Extended key Left Hyper */
    RHyper = 0x20000007u,          /**< Extended key Right Hyper */
};
}
