#include "texturemanger.h"
#include <filesystem>
#include <algorithm>

namespace fs = std::filesystem;

vector<Texture2D> texturemanger::importFolder(const string& folder, const string& suffix)
{
    vector<Texture2D> vec;

    if (!fs::exists(folder))
    {
        TraceLog(LOG_WARNING, "texturemanger::importFolder folder<%s> not exists", folder.data());
        return vec;
    }

    vector<fs::path> files;
    fs::directory_iterator iter(folder);
    for (auto& entry : iter)
    {
        if (entry.is_regular_file())
            files.push_back(entry.path());
    }

    sort(files.begin(), files.end());

    for (auto& p : files)
    {
        string path = p.generic_string();
        if (suffix != "all" && !path.ends_with(suffix))
            continue;

        Texture2D tex = LoadTexture(path.data());
        if (IsTextureValid(tex))
            vec.push_back(tex);
    }

    return vec;
}

animationmap texturemanger::importFolderex(const string& folder, const string& suffix)
{
    animationmap amap;

    if (!fs::exists(folder))
    {
        TraceLog(LOG_WARNING, "texturemanger::importFolderex folder<%s> not exists", folder.data());
        return amap;
    }

    vector<fs::path> dirs;
    fs::directory_iterator iter(folder);
    for (auto& entry : iter)
    {
        if (entry.is_directory())
            dirs.push_back(entry.path());
    }

    sort(dirs.begin(), dirs.end());

    for (auto& p : dirs)
    {
        auto tex = importFolder(p.generic_string(), suffix);
        if (!tex.empty())
            amap[p.filename().generic_string()] = tex;
    }

    return amap;
}