#pragma once

static int box_x, box_y;
static int WeaponImage;
static int Mosquito_SE;
static int BoxNumber_x,BoxNumber_y;
static int AttackCount;
static float BoxColor;
extern int AreaNum;
extern bool AttackFlg;

void Player_Initialize();
void Player_Finalize();
void Player_Update();
void Player_Draw();