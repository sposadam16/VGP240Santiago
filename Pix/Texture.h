#pragma once

#include <XEngine.h>

enum class AddressMode
{
    Border,     // use a set color if outside of 0-1
    Clamp,      // whatever is on the edge of 0-1 use that color
    Wrap,       // repeat the image if outside of 0-1
    Mirror,     // mirror repeat if outside of 0-1
};
class Texture
{
public:
    void Load(const std::string& fileName);
    const std::string& GetFileName() const;

    X::Color GetPixel(float u, float v, bool useFilter, AddressMode addressMode) const;
    X::Color GetPixel(int u, int v) const;

    int GetWidth() const;
    int GetHeight() const;

private:

    std::string mFileName;
    std::unique_ptr<X::Color[]> mPixels;
    int mWidth = 0;
    int mHeight = 0;


};