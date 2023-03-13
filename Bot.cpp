#include "Bot.h"

Bot::Bot() {
	mRect.x = SCREEN_WIDTH;
	mRect.y = 10;
	mAttack = 1;
};

Bot::~Bot() {
	
}


void Bot::handleMove() {
	if (checkToMove(20)) {
		mRect.x -= 2;
		handleBulletMove();
	}
}


void Bot::handleBulletMove() {
	for (int i = 0; i < mBulletList.size(); i++) {
		SDL_Rect rect = mBulletList[i]->getRect();
		rect.x = rect.x - 10;
		rect.y = mRect.y + 100;
		mBulletList[i]->setRect(rect.x, rect.y);

		if (rect.x <= 0) {
			mBulletList[i]->setIsMove(false);
		}
	}
}



void Bot::handleState() {
	if (mHeart == 0 && mState != DESTROYED) {
		mState = DESTROYED;
		mCurrentFrame = mMaxFrames[int(mState)] - 1;
	}

	if (mRect.x <= 0 || (mState == DESTROYED && mCurrentFrame == 0)) {
		mState = NORMAL;
		mCurrentFrame = mMaxFrames[int(mState)] - 1;
		mHeart = 100;
		mRect.x = SCREEN_WIDTH;
		mRect.y = rand() % 400;
	}
	if (mState == DESTROYED) {
		for (int i = 0; i < int(mBulletList.size()); i++) {
			mBulletList[i]->free();
			delete mBulletList[i];
			mBulletList[i] = nullptr;
			mBulletList.erase(mBulletList.begin() + i);
		}
	}
}

void Bot::fire(SDL_Renderer *renderer) {
		Bullet* newBullet = new Bullet();
		newBullet->loadImage(renderer, "Image_folder/Airplane/Bomber/Charge_1.png");
		newBullet->setIsMove(true);
		newBullet->setRect(mRect.x, mRect.y + 100);
		mBulletList.push_back(newBullet);
}
bool Bot::checkToFire(int t) {
	if (SDL_GetTicks64() - mFireTime >= 500) {
		mFireTime = SDL_GetTicks64();
		return true;
	}
	return false;
}

void Bot::handleAction(SDL_Renderer *renderer) {
	if (checkToFire(1000)) {
		fire(renderer);
	}
}