#include <DxLib.h>
#include <Scene/SceneMng.h>

SceneMng* SceneMng::sInstance = nullptr;

void SceneMng::Run(void)
{
	SystemInit();
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		UpdatePad();

		_runScene = _runScene->Update(std::move(_runScene));

		ImageMngIns.Draw();
	}
}

int SceneMng::GetPad(void)const
{
	return _padInput;
}

int SceneMng::GetPadOld(void)const
{
	return _padInputOld;
}

Vector2Template<int> SceneMng::GetStick(void)const
{
	return _stick;
}

Vector2Template<int> SceneMng::GetStickOld(void)const
{
	return _stickOld;
}

void SceneMng::StartVib(int pad, int power, int time)const
{
	StartJoypadVibration(pad, power, time);
}

bool SceneMng::SystemInit(void)
{
	SetWindowText("cube!");
	SetGraphMode(SceneMngIns.ScreenSize.x, SceneMngIns.ScreenSize.y, 16);			// 1024 * 764ドット、65536色モードに設定
	ChangeWindowMode(true);															// true:window false:フルスクリーン

	if (DxLib_Init() == -1)															// Dxライブラリの初期化
	{
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);		// 描画先をバックバッファに設定

	// 画像読み込み	
	ImageMngIns.getImage("image/cursor.png", "cursor");
	ImageMngIns.getImage("image/stage.png", "stage", 200, 100, 3, 1);
	ImageMngIns.getImage("image/stage_chip.png", "s_cube", 32, 32, 8, 8);
	//ImageMngIns.getImage("image/cube.png", "cube", 32, 32, 3, 1);

	ImageMngIns.getImage("image/TitleBack.png", "TitleBack");
	ImageMngIns.getImage("image/TitleBack2.png", "TitleBack2");
	ImageMngIns.getImage("image/space.png", "space");
	ImageMngIns.getImage("image/title.png", "TitleName");
	ImageMngIns.getImage("image/char.png", "player", 34, 32, 2, 2);	
	ImageMngIns.getImage("image/player.png", "playerSel", 96, 128, 2, 2);
	ImageMngIns.getImage("image/charSelFram.png", "charSelFram");
	ImageMngIns.getImage("image/stageSelFram.png", "stageSelFram");
	ImageMngIns.getImage("image/back.png", "back");



	// ゲームパッドの状態の初期化
	_stick = { 0,0 };
	_padInput = 0;
	_stickOld = { 0,0 };
	_padInputOld = INT_MAX;

	_charSelFram++;
	
	// 最初のシーンのを設定
	_runScene = std::make_unique<TitleScene>();

	return true;
}

void SceneMng::UpdatePad(void)
{
	_padInputOld = _padInput;
	_stickOld = _stick;
	_padInput = GetJoypadInputState(DX_INPUT_PAD1);
	GetJoypadAnalogInput(&_stick.x, &_stick.y, DX_INPUT_PAD1);

	
}

SceneMng::SceneMng() :ScreenSize{ 1024,768 }, ScreenCenter(ScreenSize / 2), _charSelFram{ 0 }
{
}


SceneMng::~SceneMng()
{
}
