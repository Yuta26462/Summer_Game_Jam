#include "SceneManager.h"
#include "Title.h"
#include "main.h"
#include "DxLib.h"

int	g_OldKey;				// 前回の入力キー
int	g_NowKey;				// 今回の入力キー
int	g_KeyFlg;				// 入力キー情報

//画像用変数
int Title_img;
int GameMain_img;
int Result_img;

int JoyPadX, JoyPadY, PadTimer;
int SelectX, SelectY;

int LoadImages();           //画像読み込み関数

int WINAPI WinMain(HINSTANCE hlnstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    SetMainWindowText("タイトル未定");

    ChangeWindowMode(TRUE); //ウィンドウモードを有効
    SetWindowSize(1280, 960);
    
    if (DxLib_Init() == -1) return -1;	// DXライブラリの初期化処理
    if (LoadImages() == -1)return -1;

    SetDrawScreen(DX_SCREEN_BACK);	// 描画先画面を裏にする
    
    ChangeFontType(DX_FONTTYPE_ANTIALIASING_4X4);   //フォントをアンチエイジング対応4×4にする。

    SceneManager scenMG(new Title());
    // ゲームループ
    while (scenMG.Update() != nullptr && ProcessMessage() == 0) {
        // 入力キー取得
        g_OldKey = g_NowKey;
        //g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
        g_NowKey = GetJoypadInputState(DX_INPUT_PAD1);
        g_KeyFlg = g_NowKey & ~g_OldKey;

        GetJoypadAnalogInput(&JoyPadX, &JoyPadY, DX_INPUT_PAD1);    //アナログスティック座標を取得
        SetJoypadDeadZone(DX_INPUT_PAD1, 0.3f);     //角度の制限を緩和

        SelectX = 0;
        SelectY = 0;

        if (++PadTimer > 10) {
            PadTimer = 0;
            if (JoyPadX > 100)SelectX = 1;
            if (JoyPadX < -100)SelectX = -1;
            if (JoyPadY > 100)SelectY = 1;
            if (JoyPadY < -100)SelectY = -1;
        }

        ClearDrawScreen();		// 画面の初期化


        scenMG.Draw();

        ScreenFlip();			// 裏画面の内容を表画面に反映

    }

    DxLib_End();	// DXライブラリ使用の終了処理

    return 0;	// ソフトの終了
}

int LoadImages() {
    if ((Title_img = LoadGraph("Resource/Images/Title.png")) == -1)return -1;
    if ((GameMain_img = LoadGraph("Resource/Images/background.png")) == -1)return -1;
    if ((Result_img = LoadGraph("Resource/Images/Ranking.png")) == -1)return -1;
    return 0;
}

int GetSelectX(void) {
    if (SelectX == 1 || SelectX == -1) {
        int Key = SelectX;
        return Key;
    }
    else { return 0; }
}

int GetSelectY(void) {
    if (SelectY == 1 || SelectY == -1) {
        int Key = SelectY;
        return Key;
    }else{ return 0; }
}

int GetJoyPadX(void) { 
    if (-1000 <= JoyPadX && JoyPadX <= 1000) {
        int PadX = JoyPadX;
        return PadX;
    }else { return 0; }
}

int GetJoyPadY(void) {
    if (-1000 <= JoyPadY && JoyPadY <= 1000) {
        int PadY = JoyPadY;
        return PadY;
    }
    else { return 0; }
}