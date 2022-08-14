#include "FileSystem.h"

std::string FileSystem::get_path(const std::string& path)
{
    static std::string (*path_builder)(std::string const&) = get_path_builder();
    return (*path_builder)(path);
}

std::string const& FileSystem::get_root()
{
    static char const* env_root = getenv("LOGL_ROOT_PATH");
    static char const* given_root = (env_root != nullptr ? env_root : "");
    static std::string root = (given_root != nullptr ? given_root : "");
    return root;
}

FileSystem::builder FileSystem::get_path_builder()
{
    if (!get_root().empty())
        return &FileSystem::get_path_relative_root;
    else
        return &FileSystem::get_path_relative_binary;
}

std::string FileSystem::get_path_relative_root(const std::string& path)
{
    return get_root() + std::string("/") + path;
}

std::string FileSystem::get_path_relative_binary(const std::string& path)
{
    return "../../../" + path;
}
