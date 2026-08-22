#pragma once
#include <XColors.h>

class MaterialManager
{
public:
	static MaterialManager* Get();

	void OnNewFrame();

	void SetMaterialEmissive(const X::Color& color);
	void SetMaterialAmbient(const X::Color& color);
	void SetMaterialDiffuse(const X::Color& color);
	void SetMaterialSpecular(const X::Color& color);
	void SetMaterialShininess(float shininess);

	const X::Color& GetMaterialEmissive()const;
	const X::Color& GetMaterialAmbient()const;
	const X::Color& GetMaterialDiffuse()const;
	const X::Color& GetMaterialSpecular()const;
	const float GetMaterialShininess()const;

private:
	X::Color mEmissive = X::Colors::Black;
	X::Color mAmbient = X::Colors::White;
	X::Color mDiffuse = X::Colors::White;
	X::Color mSpecular = X::Colors::White;
	float mShininess = 10.0f;
};

