#pragma once
#include <memory>
#include <vector>
#include <functional>
#include <common/Vector2.h>
#include <Graphic/ImageMng.h>
#include <Scene/BaseScene.h>
#include <Scene/TitleScene.h>
#include <Scene/CharSelectScene.h>
#include <Scene/GameScene.h>

#define SceneMngIns SceneMng::getInstance()

class SceneMng
{
public:
	// Singleton
	static SceneMng& getInstance()
	{
		if (sInstance == nullptr)
		{
			sInstance = new SceneMng();
		}
		return *sInstance;
	}

	static void Destroy()
	{
		if (sInstance != nullptr)
		{
			delete sInstance;
		}
		sInstance = nullptr;
	}

	void Run(void);				// ゲームループ

	int GetPad(void)const;							// 現在のゲームパッドの状態を渡す
	int GetPadOld(void)const;						// 1フレ前のゲームパッドの状態を渡す
	Vector2Template<int> GetStick(void)const;		// 現在のアナログスティックの状態を渡す
	Vector2Template<int> GetStickOld(void)const;	// 1フレ前のアナログスティックの状態を渡す

	void StartVib(int pad, int power, int time)const;	// ゲームパッドを振動させる

	const Vector2Template<int> ScreenSize;			// 画面の大きさ
	const Vector2Template<int> ScreenCenter;		// 画面の中央

private:
	static SceneMng* sInstance;
	int _padInput;					// 現在のゲームパッドの状態
	int _padInputOld;				// 1フレ前のゲームパッドの状態
	Vector2Template<int> _stick;	// 現在のアナログスティックの状態
	Vector2Template<int> _stickOld;	// 1フレ前のアナログスティックの状態

	Base_unq _runScene;				// 現在のシーン

	bool SystemInit(void);			// 初期化
	void UpdatePad(void);			// ゲームパッドの状態の更新

	SceneMng();
	~SceneMng();

public:
	int _charSelFram;
};

