--[[
    ============================================================================
    WARNING: This file is generated automatically by schema_parser.
    Any manual changes will be overwritten.
    ============================================================================
]]

---@meta

---@class KeyboardInput
---@field m_key Key
---@field m_scale float


---@class GamepadButtonInput
---@field m_button GamepadButtonType
---@field m_scale float


---@class GamepadAxisInput
---@field m_axis GamepadAxisType
---@field m_scale float


---@class MouseButtonInput
---@field m_type MouseButtonType
---@field m_scale float


---@class InputActionConfig
---@field m_name std::string
---@field m_keyboard std::vector<Key>
---@field m_gamepad std::vector<GamepadButtonType>


---@class InputAxisConfig
---@field m_name std::string
---@field m_keyboard std::vector<KeyboardInput>
---@field m_gamepad_axis std::vector<GamepadAxisInput>
---@field m_gamepad_button std::vector<GamepadButtonInput>
---@field m_mouse_vertical std::optional<float>
---@field m_mouse_horizontal std::optional<float>


---@class InputConfig
---@field m_action std::vector<InputActionConfig>
---@field m_axis std::vector<InputAxisConfig>





