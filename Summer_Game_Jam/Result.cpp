#include "Result.h"
#include "Title.h"
#include "main.h"
#include "DxLib.h"

BaseScene* Result::Update() {
	//z�L�[�Ń^�C�g����ʂֈړ�
	if (g_KeyFlg & PAD_INPUT_A) {
		return new Title();
	}
	else {
		return this;
	}
}

void Result::Draw() const {
	DrawGraph(0, 0, Result_img, FALSE);
}