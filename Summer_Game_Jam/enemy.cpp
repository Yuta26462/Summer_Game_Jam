#include "DxLib.h"
#include"enemy.h"

void DrawEnemy() {
	PosX = GetRand(RandMaxX);
	PosY = GetRand(RandMaxY);
	//ランダムに描画
	DrawCircle(PosX, PosY, Radius, 0x000000);
}

void MoveEnemy() {
	PosX += MoveX;
	PosY += MoveY;
}