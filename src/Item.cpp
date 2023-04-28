#include "Item.h"

void Item::loadImage(SDL_Renderer* renderer, ItemType t) {
	mItemType = t;
	BaseClass::loadImage(renderer, ITEM_PATHS[int(t)]);
}
void Item::handleMove() {
	if (checkToMove(10)) {
		BaseClass::handleMove();
	}
	if(mRect.y < 0) {
		mRect.y = 0; mYVal = -mYVal;
	}
	if(mRect.y > SCREEN_HEIGHT - mRect.h) {
		mRect.y = SCREEN_HEIGHT - mRect.h; mYVal = -mYVal;
	}
}
Item::Item() {
	mHeight = mWidth = 0;
	mXVal = -3;
	mYVal = 2 - 2 * rand()%3; // -2 0 2
	mItemType = BUFF_HP;
}
Item::~Item() {
	
}

ItemType Item::getItemType() {
	return mItemType;
}