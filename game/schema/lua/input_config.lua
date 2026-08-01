--[[
    ============================================================================
    WARNING: This file is generated automatically by schema_parser.
    Any manual changes will be overwritten.
    ============================================================================
]]

---@meta

---@class KeyboardInput
---@field key Key
---@field scale float


---@class GamepadButtonInput
---@field button GamepadButtonType
---@field scale float


---@class GamepadAxisInput
---@field axis GamepadAxisType
---@field scale float


---@class MouseButtonInput
---@field type MouseButton
---@field scale float


---@class InputActionConfig
---@field name std::string
---@field keyboard std::vector<KeyboardInput>
---@field gamepad std::vector<GamepadButtonInput>


---@class InputAxisConfig
---@field name std::string
---@field keyboard std::vector<KeyboardInput>
---@field gamepad std::vector<GamepadAxisInput>
---@field mouse_vertical std::optional<float>
---@field mouse_horizontal std::optional<float>


---@class InputConfig
---@field action std::vector<InputActionConfig>
---@field axis std::vector<InputAxisConfig>





