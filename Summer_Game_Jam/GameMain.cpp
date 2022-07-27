#include "GameMain.h"
#include "Result.h"
#include "enemy.h"
#include "main.h"
#include "DxLib.h"
#include "player.h"
#include "sleep.h"

GameMain::GameMain() {
	Main_BGM = LoadSoundMem("Resource/Sounds/BGM/GameMain.wav");
	MainUp_BGM = LoadSoundMem("Resource/Sounds/BGM/GameMain_UP.wav");
	PlaySoundMem(Main_BGM, DX_PLAYTYPE_BACK, TRUE);
	static bool StartFlg = true;
	TimeLimt = 1800;
	Sleep_Initialize();
	//Enemy::Enemy();
}

BaseScene* GameMain::Update() {
	static int StartFlg = TRUE;
	if (StartFlg) {
		enemy->InitEnemy(enemy);
		StartFlg = false;
	}
	
	enemy->MoveEnemy(enemy,TimeLimt);
	enemy->CheckEnemyAlive(enemy);
	Player_Update();
	Sleep_Update(enemy);
	//デバッグ用		Yボタンでリザルト画面へ
	if (TimeLimt-- < 1 || g_KeyFlg & 128 || finishFlg == true) {
		return new Result();
	}
	else {
		return this;
	}
}
void GameMain::Initialize() const {
	Player_Initialize();
	Sleep_Initialize();
}

void GameMain::Finalize() const {
	Player_Finalize();
	Sleep_Finalize();
}

void GameMain::Draw() const {
	DrawExtendGraph(0, 0,641,481, GameMain_img, FALSE);
	for (int i = 0; i < 10; i++) {
		enemy->DrawEnemy(enemy[i]);
	}
	for (int j = 0; j < 6; j++) {
		DrawFormatString(30 * j, 200, 0xffffff, "%d", enemy->GetEnemyIntoArea(j));
	}
	
	DrawFormatString(100, 400, 0xffffff, "Score:%d", enemy->GetScore());
	DrawFormatString(100, 450, 0xffffff, "Combo:%d", enemy->GetCombo());
	//DrawFormatString(100, 400, 0x000000, "Died_Enemy:%d", enemy->GetDied_enemy());
	DrawFormatString(500, 100, 0x000000, "Time:%d", GetTime()/60);
	Player_Draw();
	Sleep_Draw();
}

int GameMain::GetTime() const {
	return TimeLimt;
}