#pragma once
#include "Texture.h"

class TextureManager
{
public:
    static TextureManager* Get();

    void Clear();
    void SetUseFilter(bool useFilter);
    void SetAddressMode(AddressMode addressMode);
    void SetTexture(const std::string& fileName);

    // "Hack" is to use color with -z- to flag color as uv coordinates
    X::Color SampleColor(const X::Color& uv) const;

private:
    std::vector<std::unique_ptr<Texture>> mTextures;
    const Texture* mCurrentTexture = nullptr;

    bool mUseFilter = false;
    AddressMode mAddressMode = AddressMode::Clamp;
};
