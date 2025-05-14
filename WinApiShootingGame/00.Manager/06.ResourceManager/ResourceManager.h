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
	void LoadImage(const string& key, const wstring& filePath);
	void UnloadImage(const string& key);
	Image* GetImage(const string& key);

};