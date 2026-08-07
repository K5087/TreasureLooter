module context;

#ifdef TL_ENABLE_EDITOR
const Path& Context::GetProjectPath() const {
    static Path path = "@CMAKE_CURRENT_SOURCE_DIR@";
    return path;
}
#endif
