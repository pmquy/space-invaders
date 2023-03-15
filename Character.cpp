#include "Character.h"

Character::Character() {
	mXVal = 0;
	mYVal = 0;
	mHeart = 100;
	mAttack = 3;
}

Character::~Character() {

}


void Character::handleAction(const SDL_Event &event, SDL_Renderer* renderer) {
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_UP:
			mYVal = -1;
			break;
		case SDLK_DOWN:
			mYVal = 1;
			break;
		case SDLK_RIGHT:
			mXVal = 1;
			break;
		case SDLK_LEFT:
			mXVal = -1;
			break;
		}
		
	}
	else if (event.type == SDL_KEYUP) {
		
		switch (event.key.keysym.sym) {
		case SDLK_UP:
			mYVal = 0;
			break;
		case SDLK_DOWN:
			mYVal = 0;
			break;
		case SDLK_RIGHT:
			mXVal = 0;
			break;
		case SDLK_LEFT:
			mXVal = 0;
			break;
		}
	}
	else if (event.type == SDL_MOUSEBUTTONDOWN) {
		Bullet *newBullet = new Bullet();
		newBullet->setRect(mRect.x + mRect.w, mRect.y + mRect.h/2);
		newBullet->setIsMove(true);
		newBullet->setType(Type::XUOI);
		newBullet->loadImage(renderer, "Image_folder/laser.png");
		mBulletList.push_back(newBullet);
	}
	else if (event.type == SDL_MOUSEBUTTONUP) {

	}
	else {

	}
}

void Character::handleMove() {

	mRect.x += mXVal;
	mRect.y += mYVal;
	
	if (mRect.x <= 0) mRect.x = 0;
	if (mRect.x >= 1200 - 192) mRect.x = 1200 - 192;
	if (mRect.y <= 0) mRect.y = 0;
	if (mRect.y >= 600 - 192) mRect.y = 600 - 192;

	if (checkToMove(10)) {
		handleBulletMove();
	}
	
}

void Character::handleBulletMove() {
	for (int i = 0; i < int(mBulletList.size()); i++) {
		mBulletList[i]->handleMove();
	}
}

void Character::handleState() {
	if (mHeart == 0 && mState != DESTROYED) {
		mState = DESTROYED;
		mCurrentFrame = 0;
	}

	if (mState == DESTROYED) {
		for (int i = 0; i < int(mBulletList.size()); i++) {
			mBulletList[i]->free();
			delete mBulletList[i];
			mBulletList[i] = nullptr;
			mBulletList.erase(mBulletList.begin() + i);
		}
	}

	if (mState == DESTROYED && mCurrentFrame == mMaxFrames[int(mState)] - 1) {
		reborn();
	}

}


bool Character::checkIsDestroyed() {
	return mState == DESTROYED && mCurrentFrame == mMaxFrames[int(mState)] - 1;
}