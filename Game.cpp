#include "Game.h"

Game::Game() {
	mRect.x = mRect.y = 0;
	mRect.w = SCREEN_WIDTH;
	mRect.h = SCREEN_HEIGHT;
	mState = START;
	mGameMusic = Mix_LoadMUS("Music_Folder/music.mp3");
	mBonkMusic = Mix_LoadWAV("Music_Folder/bonk.wav");
	mScoreText.setRect(0, 0);
	mCoinText.setRect(0, 50);
}

Game::~Game() {
	free();
}

void Game::handleMove() {
	if (mState != START && mState != SHOP && mState != DEAD && mState != UPGRADE && mState != VICTORY && checkToMove(20)) {
		mRect.x--;
		if (mRect.x <= -1200) mRect.x = 0;
	}
}

void Game::render(SDL_Renderer* renderer, const SDL_Rect* clip) {
	mTexture = mTextures[int(mState)];
	if (mState != START && mState != SHOP && mState != DEAD && mState != UPGRADE && mState != VICTORY) {
		BaseClass::render(renderer);
		mRect.x += 1200;
		BaseClass::render(renderer);
		mRect.x -= 1200;
	}
	else {
		BaseClass::render(renderer);
	}
}

void Game::loadImage(SDL_Renderer* renderer, const std::vector<std::string>& listName) {
	SDL_Texture* loadedTexture;
	for (std::string s : listName) {
		loadedTexture = loadTexture(renderer, s);
		mTextures.push_back(loadedTexture);
	}
}

void Game::handleState(SDL_Renderer* renderer, std::pair<int, int>& mouse, SDL_Event &event, Character* hero, GameType &oldState, std::vector<Bot*>& bots) {

	if (!(mState != START && mState != SHOP && mState != DEAD && mState != UPGRADE && mState != VICTORY)) {
		setRect(0, 0);
	}
	
	switch (mState) {

	case START:
		if (mouse.first >= 550 && mouse.first <= 650 && mouse.second >= 140 && mouse.second <= 190) {
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				mState = LEVEL_1;
				hero->reborn();
			}
			SDL_Rect rect = { 550, 140, 100, 50 };

			SDL_SetRenderDrawColor(gRenderer, 0, 253, 253, 150);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_RenderFillRect(renderer, &rect);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

		}
		if (mouse.first >= 550 && mouse.first <= 650 && mouse.second >= 220 && mouse.second <= 270) {
			if(event.type == SDL_MOUSEBUTTONDOWN)
				mState = SHOP;
			SDL_Rect rect = { 550, 220, 100, 50 };

			SDL_SetRenderDrawColor(renderer, 0, 253, 253, 150);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_RenderFillRect(renderer, &rect);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

		}
		if (mouse.first >= 500 && mouse.first <= 700 && mouse.second >= 300 && mouse.second <= 350) {
			if (event.type == SDL_MOUSEBUTTONDOWN)
				mState = UPGRADE;
			SDL_Rect rect = { 500, 300, 200, 50 };

			SDL_SetRenderDrawColor(renderer, 0, 253, 253, 150);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_RenderFillRect(renderer, &rect);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
		}
		break;
	case LEVEL_1:
	case LEVEL_2:
	case LEVEL_3:
	case LEVEL_4:
	case LEVEL_5:
		break;
	case DEAD:
		if (mouse.first >= 490 && mouse.first <= 710 && mouse.second >= 220 && mouse.second <= 270) {
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				mState = oldState;
			}

			SDL_Rect rect = { 490, 220, 220, 50 };

			SDL_SetRenderDrawColor(renderer, 0, 253, 253, 150);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_RenderFillRect(renderer, &rect);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
		}
		else if (mouse.first >= 550 && mouse.first <= 650 && mouse.second >= 300 && mouse.second <= 350) {
			
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				mState = START;
				for (int i = 0; i < int(bots.size()); i++) {
					if (i < 2) {
						bots[i]->setIsAppear(true);
					}
					else {
						bots[i]->setIsAppear(false);
					}
				}
			}
				
			SDL_Rect rect = { 550, 300, 100, 50 };

			SDL_SetRenderDrawColor(renderer, 0, 253, 253, 150);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_RenderFillRect(renderer, &rect);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
		}
		break;
	case SHOP:
		if (mouse.first >= 550 && mouse.first <= 650 && mouse.second >= 240 && mouse.second <= 290) {
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (hero->getCoin() >= 10) {
					hero->setCoin(hero->getCoin() - 10);
					hero->loadImage(renderer, HERO3_PATHS);
				}
			}
			SDL_Rect rect = { 550, 240, 100, 50 };
			SDL_SetRenderDrawColor(renderer, 0, 253, 253, 150);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_RenderFillRect(renderer, &rect);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
		}
		else if (mouse.first >= 230 && mouse.first <= 330 && mouse.second >= 240 && mouse.second <= 290) {
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (hero->getCoin() >= 10) {
					hero->setCoin(hero->getCoin() - 10);
					hero->loadImage(renderer, HERO1_PATHS);
				}
			}
			SDL_Rect rect = { 230, 240, 100, 50 };
			SDL_SetRenderDrawColor(renderer, 0, 253, 253, 150);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_RenderFillRect(renderer, &rect);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
		}
		else if (mouse.first >= 860 && mouse.first <= 960 && mouse.second >= 240 && mouse.second <= 290) {
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (hero->getCoin() >= 10) {
					hero->setCoin(hero->getCoin() - 10);
					hero->loadImage(renderer, HERO2_PATHS);
				}
			}
			SDL_Rect rect = { 860, 240, 100, 50 };
			SDL_SetRenderDrawColor(renderer, 0, 253, 253, 150);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_RenderFillRect(renderer, &rect);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
		}
		else if (mouse.first >= 550 && mouse.first <= 650 && mouse.second >= 380 && mouse.second <= 430) {
			if (event.type == SDL_MOUSEBUTTONDOWN)
				mState = START;
			
			SDL_Rect rect = { 550, 380, 100, 50 };
			SDL_SetRenderDrawColor(renderer, 0, 253, 253, 150);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_RenderFillRect(renderer, &rect);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
		}
		break;

	case VICTORY:
		if (mouse.first >= 490 && mouse.first <= 710 && mouse.second >= 140 && mouse.second <= 190) {
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (oldState == LEVEL_1) {
					mState = LEVEL_2;
					bots[2]->setIsAppear(true);
				}
				else if (oldState == LEVEL_2) {
					mState = LEVEL_3;
					bots[2]->setIsAppear(true);
				}
				else if (oldState == LEVEL_3) {
					mState = LEVEL_4;
					bots[3]->setIsAppear(true);
				}
				else if (oldState == LEVEL_4) {
					mState = LEVEL_5;
					bots[4]->setIsAppear(true);
				}
				else if (oldState == LEVEL_5) {
					mState = LEVEL_5;
					bots[5]->setIsAppear(true);
				}
			}
				
			SDL_Rect rect = { 490, 140, 220, 50 };

			SDL_SetRenderDrawColor(renderer, 0, 253, 253, 150);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_RenderFillRect(renderer, &rect);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
		}

		if (mouse.first >= 490 && mouse.first <= 710 && mouse.second >= 220 && mouse.second <= 270) {
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (oldState == LEVEL_1) {
					mState = LEVEL_1;
				}
				else if (oldState == LEVEL_2) {
					mState = LEVEL_2;
				}
				else if (oldState == LEVEL_3) {
					mState = LEVEL_3;
				}
				else if (oldState == LEVEL_4) {
					mState = LEVEL_4;
				}
				else if (oldState == LEVEL_5) {
					mState = LEVEL_5;
				}
			}
				
			SDL_Rect rect = { 490, 220, 220, 50 };

			SDL_SetRenderDrawColor(renderer, 0, 253, 253, 150);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_RenderFillRect(renderer, &rect);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
		}
		if (mouse.first >= 550 && mouse.first <= 650 && mouse.second >= 300 && mouse.second <= 350) {
			if (event.type == SDL_MOUSEBUTTONDOWN)
				mState = START;
			
			for (int i = 0; i < int(bots.size()); i++) {
				if (i < 2) {
					bots[i]->setIsAppear(true);
				}
				else {
					bots[i]->setIsAppear(false);
				}
			}
			SDL_Rect rect = { 550, 300, 100, 50 };

			SDL_SetRenderDrawColor(renderer, 0, 253, 253, 150);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_RenderFillRect(renderer, &rect);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
		}
		break;
	case UPGRADE:
		if (mouse.first >= 550 && mouse.first <= 650 && mouse.second >= 380 && mouse.second <= 430) {
			if (event.type == SDL_MOUSEBUTTONDOWN)
				mState = START;
			SDL_Rect rect = { 550, 380, 100, 50 };
			SDL_SetRenderDrawColor(renderer, 0, 253, 253, 150);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_RenderFillRect(renderer, &rect);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
		}
		else if (mouse.first >= 1030 && mouse.first <= 1090 && mouse.second >= 130 && mouse.second <= 180) {
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (hero->getCoin() >= 10 && hero->getMaxHeart() < 110) {
					hero->setCoin(hero->getCoin() - 10);
					hero->setMaxHeart(hero->getMaxHeart() + 10);
				}
			}
			SDL_Rect rect = { 1030, 130, 60, 50 };
			SDL_SetRenderDrawColor(renderer, 0, 253, 253, 150);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_RenderFillRect(renderer, &rect);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
		}
		else if (mouse.first >= 1030 && mouse.first <= 1090 && mouse.second >= 210 && mouse.second <= 260) {
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (hero->getCoin() >= 10 && hero->getAmor() < 6) {
					hero->setCoin(hero->getCoin() - 10);
					hero->setAmor(hero->getAmor() + 1);
				}
			}
			SDL_Rect rect = { 1030, 210, 60, 50 };
			SDL_SetRenderDrawColor(renderer, 0, 253, 253, 150);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_RenderFillRect(renderer, &rect);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
		}
		else if (mouse.first >= 1030 && mouse.first <= 1090 && mouse.second >= 290 && mouse.second <= 340) {
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (hero->getCoin() >= 10 && hero->getAttack() < 35) {
					hero->setCoin(hero->getCoin() - 10);
					hero->setAttack(hero->getAttack() + 5);
				}
			}
			SDL_Rect rect = { 1030, 290, 60, 50 };
			SDL_SetRenderDrawColor(renderer, 0, 253, 253, 150);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_RenderFillRect(renderer, &rect);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
		}
				
		SDL_Rect rectBg = {320, 140, 600, 10};
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
		SDL_RenderFillRect(renderer, &rectBg);
		rectBg.y += 90;
		SDL_RenderFillRect(renderer, &rectBg);
		rectBg.y += 90;
		SDL_RenderFillRect(renderer, &rectBg);

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
		SDL_Rect rect = { 320, 140, (hero->getMaxHeart() - 50) / 10 * 100, 10 };
		SDL_RenderFillRect(renderer, &rect);
		rect = { 320, 230, (hero->getAmor() - 0) * 100, 10 };
		SDL_RenderFillRect(renderer, &rect);
		rect = { 320, 320, (hero->getAttack() - 5) / 5 * 100, 10 };
		SDL_RenderFillRect(renderer, &rect);
		
		break;
	}

	mHeroCoin = hero->getCoin();
	mHeroScore = hero->getScore();
}


void Game::handleLogic(SDL_Renderer* renderer, Character* hero, std::vector<Bot*>& bots) {
	if (hero->checkIsDestroyed()) {
		this->setState(GameType::DEAD);
		hero->reborn();
		for (int j = 0; j < int(bots.size()); j++) {
			bots[j]->reborn(renderer);
		}
	}

	if (hero->getScore() >= 10) {
		this->setState(GameType::VICTORY);
		hero->reborn();
		for (int i = 0; i < int(bots.size()); i++) {
			bots[i]->reborn(renderer);
		}
	}
	this->handleCollision(hero, bots);
}


void Game::handleCollision(Character *hero, std::vector<Bot*> bots) {
	for (int j = 0; j < int(bots.size()); j++) {
		if (bots[j]->getIsAppear()) {

			for (int i = 0; i < int(hero->getBulletList().size()); i++) {
				if (checkConllision(bots[j], hero->getBulletList()[i])) {
					bots[j]->getDamage(hero->getAttack());
					hero->getBulletList()[i]->setIsAppear(false);
				}
			}

			for (int i = 0; i < int(bots[j]->getBulletList().size()); i++) {
				if (bots[j]->getHeart() != 0 && checkConllision(hero, bots[j]->getBulletList()[i])) {
					hero->getDamage(bots[j]->getAttack());
					bots[j]->getBulletList()[i]->setIsAppear(false);
				}
			}

			if (checkConllision(hero, bots[j]) && bots[j]->getHeart() != 0) {
				bots[j]->getDamage(1000);
				hero->getDamage(30);
			}
		}
		if (bots[j]->checkIsDestroyed()) {
			Mix_PlayChannel(-1, mBonkMusic, 0);
			hero->setScore(hero->getScore() + 2);
			hero->setCoin(hero->getCoin() + 3);
		}
	}
}

void Game::renderText(SDL_Renderer* renderer, TTF_Font* font) {
	if (mState != START && mState != SHOP && mState != DEAD && mState != UPGRADE && mState != VICTORY) {
		mScoreText.loadText(renderer, font, "Score : " + std::to_string(mHeroScore)); mScoreText.render(renderer);
		mCoinText.loadText(renderer, font, "Coin : " + std::to_string(mHeroCoin)); mCoinText.render(renderer);
	}
	else if (mState == SHOP || mState == UPGRADE) {
		mCoinText.loadText(renderer, font, "Coin : " + std::to_string(mHeroCoin)); mCoinText.render(renderer);
	}
}