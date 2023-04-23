#include "Boss.h"

Boss::Boss() {
	mHp = mMaxHp = 200;
	mTurnTime = 0;
	mIsAppear = false;
	mXVal = -2;
	mAtk = mMaxAtk = 5;
	mRect.x = SCREEN_WIDTH;
	mRect.y = rand() % 400;
	mMaxBullet = 6;
	addSkill(SkillType::BUFF_HP_SKILL);
	mName = new Text();
}

void Boss::handleMove() {
	Bot::handleMove();
	if (mRect.x <= 500) {
		mRect.x = 500;
	}
}

void Boss::restart(SDL_Renderer* renderer) {
	Bot::restart(renderer);
	mIsAppear = false;
	mXVal = mYVal = 0;
}

// xử lý skill và sử dụng luôn
void Boss::handleSkill() {
	Airplane::handleSkill();
	for (auto it : mSkillList) {
		useSkill(it);
	}
}

void Boss::renderText(SDL_Renderer* renderer, TTF_Font* font) {
	mName->loadText(renderer, font, "BOSS");
	mName->setRect(mRect.x + 50, mRect.y);
	mName->render(renderer);
}

