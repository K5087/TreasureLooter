export module editor;

import path;
import asset;
import input;
import prefab;
import inputconfig;

import std;

using AssetTypes = std::variant<std::monostate, AssetLoadResult<EntityInstance>,
                                AssetLoadResult<InputConfig>>;

export {
class Editor {
public:
    void Update();

private:
    enum class Mode {
        None,
        Open,
        Create,
    };
    Mode m_mode = Mode::None;
    AssetTypes m_asset;
    Path m_filename;
    std::optional<std::size_t> m_asset_index;

    bool m_open = true;
};
}
