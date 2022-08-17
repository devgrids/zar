#pragma once

#ifndef FILESYSTEM_H
#define FILESYSTEM_H

class __declspec(dllexport) FileSystem
{
private:
    typedef std::string (*builder)(const std::string& path);
public:
    static std::string get_path(const std::string& path);
    static std::string const& get_root();
    static builder get_path_builder();
    static std::string get_path_relative_root(const std::string& path);
    static std::string get_path_relative_binary(const std::string& path);
};

// FILESYSTEM_H
#endif
