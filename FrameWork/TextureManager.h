#pragma once
#include"Global.h"
#include<unordered_map>

class Texture {
private:
	LPDIRECT3DTEXTURE9 texture;
public:
	Texture(const char* filePath)
	{
		D3DXIMAGE_INFO imageInfo;
		D3DXGetImageInfoFromFile(filePath, &imageInfo);
		D3DXCreateTextureFromFileEx(d3ddev, filePath, imageInfo.Width, imageInfo.Height, 1, D3DUSAGE_DYNAMIC,
			D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT,D3DCOLOR_XRGB(255,255,255), &imageInfo, NULL, &texture);
	}
	~Texture() { texture->Release(); };
	LPDIRECT3DTEXTURE9 getTexture() { return texture; };
};

class TextureManager {
private:

	static TextureManager* instance;
	std::unordered_map<Tag, LPDIRECT3DTEXTURE9> textures;

public:
	int getTextureHeight(Tag tag)
	{
		D3DSURFACE_DESC desc;
		LPDIRECT3DTEXTURE9 tex = textures[tag];
		tex->GetLevelDesc(0, &desc);
		return desc.Height;
	}
	int getTextureWidth(Tag tag)
	{
		D3DSURFACE_DESC desc;
		LPDIRECT3DTEXTURE9 tex = textures[tag];
		tex->GetLevelDesc(0, &desc);
		return desc.Width;
	}
	void loadResources();
	void addTexture(Tag tag, const char* filePath);
	static TextureManager* getInstance();
	LPDIRECT3DTEXTURE9 getTexture(Tag tag);
};