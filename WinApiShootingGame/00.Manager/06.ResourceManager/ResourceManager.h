#pragma once
#include "../99.SingTonManager/SingTonManager.h"

class ResourceManager : public SingleTon<ResourceManager>
{
	friend class SingleTon<ResourceManager>;
private:
	explicit ResourceManager();
public:
	virtual ~ResourceManager();
public:
	bool Init();
	void Release();
	Bitmap* LoadSprite(const wstring& filePath);
	Bitmap* GetSprite(const wstring& filePath);
private:
	static ULONG_PTR GdiplusToken;
	static map<wstring, Gdiplus::Bitmap*> ImageMap;
};