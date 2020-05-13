#include "ImageMng.h"
#include <Dxlib.h>
#include <Vector2.h>


std::unique_ptr <ImageMng, ImageMng::ImageMngDeleter> ImageMng::sInstance(new ImageMng());

const VecInt & ImageMng::GetID(const std::string&key)
{
	return GetID(key, key);
}

const VecInt & ImageMng::GetID(const std::string&key, const std::string & fileName)
{
	if (imgMap.find(key) == imgMap.end())
	{
		imgMap[key].resize(1);
		imgMap[key][0] = LoadGraph(fileName.c_str());
	}
	return imgMap[key];
}

const VecInt & ImageMng::GetID(const std::string & key, const std::string & fileName, const Vector2 & divSize, const Vector2 & divCnt)
{
	if (imgMap.find(key)==imgMap.end())
	{
		imgMap[key].resize(divCnt.x*divCnt.y);
		LoadDivGraph(fileName.c_str(), divCnt.x*divCnt.y, divCnt.x, divCnt.y, divSize.x, divSize.y, &imgMap[key][0]);
	}	
	return imgMap[key];	
}


const VecInt & ImageMng::GetSound(const std::string & key)
{
	return GetSound(key, key);
}

const VecInt & ImageMng::GetSound(const std::string & key, const std::string & fileName)
{
	if (soundMng.find(key) == soundMng.end())
	{
		soundMng[key].resize(1);
		soundMng[key][0] = LoadSoundMem(fileName.c_str());
		LoadSoundMem(fileName.c_str(), soundMng[key][0]);
	}

	return soundMng[key];
}


ImageMng::ImageMng()
{
}

ImageMng::~ImageMng()
{
}