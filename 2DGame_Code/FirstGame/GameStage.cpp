#include "GameStage.h"
#include "Hero.h"
#include "LiterMonster.h"
#include "SDL_ttf.h"
#include "TextureManager.h"
#include <string>
#include "Creature.h"
#include "SDL_main.h"
#include <list>
#include "EndingStage.h"
#include "Missile.h"
#include "Item.h"
#include "FirstStage.h"
#include "SecondStage.h"
#include "ThirdStage.h"
#include "SoundManager.h"

extern Stage *stage;
extern SDL_Renderer *g_renderer;
extern int ground_height;
extern int g_window_width;
extern int g_window_height;
extern int g_flag_running;
extern TTF_Font* game_font;

GameStage::GameStage() {
	
	//변수들 초기화
	xpos = 0;

}

GameStage::~GameStage() {
	TextureManager* tm = TextureManager::GetSingleton();
	tm->DestroyInstance();
	tm->CreateInstance();
}

Creature* GameStage::GetHero() {
	return hero;
}
void GameStage::SetHero(Hero* h) {
	hero = h;
}
int GameStage::GetClearTime() {
	return clearTime;
}
void GameStage::SetClearTime(int c) {
	clearTime = c;
}
int GameStage::GetKillCount() {
	return killCount;
}
void GameStage::SetKillCount(int c) {
	killCount = c;
}


void GameStage::DrawBackGround() {
	TextureManager* tm = TextureManager::GetSingleton();
	SDL_Rect bg_src_rect;
	bg_src_rect.x = xpos;
	bg_src_rect.y = 0;
	bg_src_rect.w = 640;
	bg_src_rect.h = 720;

	SDL_Rect bg_des_rect;
	bg_des_rect.w = g_window_width;
	bg_des_rect.h = g_window_height;
	bg_des_rect.x = 0;
	bg_des_rect.y = 0;
	SDL_RenderCopy(g_renderer, tm->GetTexture("bg"), &bg_src_rect, &bg_des_rect);

}

void GameStage::DrawScoreA() {
	
}

void GameStage::DrawHeader() {
	TextureManager* tm = TextureManager::GetSingleton();

	//아이템 타입 그리기
	std::string spriteId = "item_face0";

	if (hero->GetItemType() == 1) {
		spriteId = "item_math0";
	}
	else if (hero->GetItemType() == 2) {
		spriteId = "item_comp0";
	}
	tm->DrawSprite("item", spriteId, 20, 20, 50, 50);

	//하트 갯수 그리기.
	for (int i = 0; i < hero->GetHealth(); i++) {
		tm->DrawSprite("item", "item_heart0", 100 + i * 20, 20, 50, 50);
	}

	//스코어 그리기.
	tm->DrawSprite("item", "item_aplus0", 1000, 20, 50, 50);

	std::string score_image = "item_aplus0";
	int Ascore = hero->GetAplus();
	std::string score_string = "X" + std::to_string(Ascore / 10) + std::to_string(Ascore % 10);

	SDL_Color black = { 0, 0, 0, 0 };
	SDL_Surface *score_surface = TTF_RenderText_Blended(game_font, score_string.c_str(), black);

	SDL_Rect score_rect;
	score_rect.x = 0;
	score_rect.w = score_surface->w;
	score_rect.y = 0;
	score_rect.h = score_surface->h;

	SDL_Texture* score_texture = SDL_CreateTextureFromSurface(g_renderer, score_surface);
	SDL_FreeSurface(score_surface);

	SDL_Rect score_dest;
	score_dest.x = 1050;
	score_dest.w = 150;
	score_dest.y = 20;
	score_dest.h = 50;

	SDL_RenderCopy(g_renderer, score_texture, &score_rect, &score_dest);
}

void GameStage::Update() {

	//hero상태변화 앞뒤 움직임.
	if (hero->GetStatus() == 2) {
		if (hero->GetXpos() > g_window_width / 10 * 3 || xpos == 0) {
			hero->Move_Xpos();
		}
		else {
			Scroll(1);
		}
	}

	else if (hero->GetStatus() == 3) {
		if (hero->GetXpos() < g_window_width / 10 * 5 || xpos == bg_width - 640) {
			hero->Move_Xpos();
		}
		else {
			Scroll(2);
		}
	}

	//hero 상태변화 높이.
	hero->Move_Ypos();
	if (hero->GetYpos() + hero->GetHeight() >= ground_height) {
		hero->SetYpos(ground_height - hero->GetHeight());
		hero->SetYvel(0);
	}

	//히어로가 아이템을 먹었는지 확인
	if (!item.empty()) {
		for (std::list<Item*>::iterator iter = item.begin(); iter != item.end(); ++iter) {
			Item* i = (*iter);
			if (hero->isIn(i->GetXpos() + i->GetWidth() / 5 * 1, i->GetYpos(), i->GetWidth() / 5 * 3, i->GetHeight())) {
				SoundManager* sm = SoundManager::GetSingleton();
				sm->PlayChunk("hero_get_item");
				i->Effect(hero);
				item.erase(iter);
				break;
			}
		}
	}

	//몬스터 움직임.
	for (std::list<Monster*>::iterator iter = monster.begin(); iter != monster.end(); ++iter) {
		(*iter)->Move_Xpos();
	}

	//미사일 움직임.
	for (std::list<Missile*>::iterator iter = missile.begin(); iter != missile.end(); ++iter) {
		(*iter)->Move();
	}

	//몬스터 미사일 생성.
	for (std::list<Monster*>::iterator iter = monster.begin(); iter != monster.end(); ++iter) {
		if ((*iter)->AttackableStatus()) {
			if ((*iter)->isDistance(hero)) {
				(*iter)->Attack(hero);
				(*iter)->throwMissile(&missile);
			}
		}
	}

	//미사일 제거.
	for (std::list<Missile*>::iterator iter = missile.begin(); iter != missile.end(); ++iter) {
		if ((*iter)->GetLen() < 0 || (*iter)->GetXpos() < 0 || (*iter)->GetXpos() > g_window_width || (*iter)->GetYpos() > ground_height - Missile::MISSILE_SIZE) {
			missile.erase(iter);
			break;
		}
	}

	//캐릭터가 몬스터, 미사일과 부딫혔는지 확인. 맞은 상태가 아니었을 때 부딫혔다면 공격받음.
	if (hero->GetInvinceTime() >= 1800) {
		for (std::list<Monster*>::iterator iter = monster.begin(); iter != monster.end(); ++iter) {
			Creature* c = (*iter);
			if (hero->isIn(c->GetXpos()  + c->GetWidth() / 5 * 1, c->GetYpos(), c->GetWidth() / 5 * 3, c->GetHeight())) {
				hero->Attacked(c);
			}
		}
		for (std::list<Missile*>::iterator iter = missile.begin(); iter != missile.end(); ++iter) {
			Missile* m = (*iter);
			if (hero->isIn(m->GetXpos() + m->GetWidth() / 4 * 3, m->GetYpos(), m->GetWidth() / 2 * 1, m->GetHeight())) {
				hero->Attacked(m);
				missile.erase(iter);
				break;
			}
		}
	}

	//캐릭터가 몬스터를 근접 공격 했는지 확인.
	if (hero->GetStatus() == 8 || hero->GetStatus() == 9) {
		SDL_Rect hand;
		if (hero->GetItemType() == 2) {
			hand.w = 90;
		}
		else {
			hand.w = 40;
		}
		hand.h = 40;

		if (hero->GetStatus() == 8) {
			if (hero->GetItemType() == 2) {
				hand.x = hero->GetXpos() - 85;
			}
			else {
				hand.x = hero->GetXpos() - 40;
			}
			hand.y = hero->GetYpos();
		}
		else if(hero->GetStatus() == 9){
			hand.x = hero->GetXpos() + 80;
			hand.y = hero->GetYpos();
		}

		for (std::list<Monster*> ::iterator iter = monster.begin(); iter != monster.end(); ++iter) {
			if ((*iter)->isIn(hand.x, hand.y, hand.w, hand.h) && (*iter)->GetInvinceTime() >= 300) {
				(*iter)->Attacked(hero);

				if ((*iter)->isDead()) {
					monster.erase(iter);
					killCount++;
					break;
				}
			}
		}
	}

	//프레임타임 업데이트
	hero->SetInvinceTime(hero->GetInvinceTime() + 30);
	hero->FrameControl();
	for (std::list<Monster*>::iterator iter = monster.begin(); iter != monster.end(); ++iter) {
		(*iter)->SetInvinceTime((*iter)->GetInvinceTime() + 30);
		(*iter)->FrameControl();
		clearTime += 30;
	}

	//스테이지 클리어 확인
	if (typeid(*stage) == typeid(FirstStage)) {
		FirstStage* s = dynamic_cast<FirstStage*>(stage);
		if (s->isClear()) {
			s->NextStage();
		}
	}
	
	else if (typeid(*stage) == typeid(SecondStage)) {
		SecondStage* s = dynamic_cast<SecondStage*>(stage);
		if (s->isClear()) {
			s->NextStage();
		}
	}

	else if (typeid(*stage) == typeid(ThirdStage)) {
		ThirdStage* s = dynamic_cast<ThirdStage*>(stage);
		if (s->isClear()) {
			s->NextStage();
		}
	}

	//히어로 죽음.
	if (hero->isDead()) {
		stage = new EndingStage(1, (TotalScore() >= 0) ? TotalScore() : 0);
		return;
	}
}

void GameStage::Render() {
	SDL_RenderClear(g_renderer);

	stage->DrawBackGround();
	DrawScoreA();
	DrawHeader();
	for (std::list<Missile*>::iterator iter = missile.begin(); iter != missile.end(); ++iter) {
		(*iter)->Draw();
	}
	for (std::list<Monster*>::iterator iter = monster.begin(); iter != monster.end(); ++iter) {
		(*iter)->Draw();
	}

	for (std::list<Item*>::iterator iter = item.begin(); iter != item.end(); ++iter) {
		(*iter)->Draw();
	}
	hero->Draw();
	SDL_RenderPresent(g_renderer);
}

void GameStage::HandleEvents() {
	Hero* h = dynamic_cast<Hero*> (hero);

	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			g_flag_running = 0;
			break;

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_LEFT)
			{
				if (h->isMoveable()) {
					hero->SetStatus(2);
				}
			}
			else if (event.key.keysym.sym == SDLK_RIGHT)
			{
				if (h->isMoveable()) {
					hero->SetStatus(3);
				}
			}
			else if (event.key.keysym.sym == SDLK_UP) {
				if(hero->GetXpos() <= 1 && xpos == 0)
					hero->SetInvinceTime(-30000000);
			}
			else if (event.key.keysym.sym == SDLK_DOWN) {
				
			}

			else if (event.key.keysym.sym == SDLK_1) {
				hero->SetAttackPower(1);
				hero->SetItemType(0);
			}

			else if (event.key.keysym.sym == SDLK_2) {
				hero->SetAttackPower(2);
				hero->SetItemType(1);
			}

			else if (event.key.keysym.sym == SDLK_3) {
				hero->SetAttackPower(1);
				hero->SetItemType(2);
			}

			else if (event.key.keysym.sym == SDLK_4) {
				hero->SetHealth(hero->GetHealth() + 3);
			}

			else if (event.key.keysym.sym == SDLK_SPACE) {
				if (h->isMoveable()) {
					if (h->GetYvel() == 0) {
						h->Jump();
					}
				}
			}

			else if (event.key.keysym.sym == SDLK_TAB) {

			}

			else if (event.key.keysym.sym == SDLK_LCTRL) {
				if (h->isMoveable()) {
					if (h->GetStatus() < 6) {
						h->Attack();
					}
				}
			}

			break;

		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_LEFT) {
				if (h->isMoveable()) {
					if (hero->GetStatus() == 2) {
						hero->SetStatus(0);
					}
				}
			}
			else if (event.key.keysym.sym == SDLK_RIGHT) {
				if (h->isMoveable()) {
					if (hero->GetStatus() == 3) {
						hero->SetStatus(1);
					}
				}
			}
			else if (event.key.keysym.sym == SDLK_UP) {
				
			}
			else if (event.key.keysym.sym == SDLK_DOWN) {
				
			}


			if (event.key.keysym.sym == SDLK_SPACE) {
				
			}
			break;

		case SDL_MOUSEBUTTONDOWN:

			// If the mouse left button is pressed. 
			if (event.button.button == SDL_BUTTON_LEFT)
			{
			}
			break;

		default:
			break;
		}
	}
}

void GameStage::Scroll(int dir) {
	if (dir == 1) {
		//왼쪽 스크롤링
		if (xpos > 0) {
			xpos -= 2;

			for (std::list<Monster*>::iterator iter = monster.begin(); iter != monster.end(); ++iter) {
				(*iter)->SetXpos((*iter)->GetXpos() + 4);
			}

			for (std::list<Missile*>::iterator iter = missile.begin(); iter != missile.end(); ++iter) {
				(*iter)->SetXpos((*iter)->GetXpos() + 4);
			}

			for (std::list<Item*>::iterator iter = item.begin(); iter != item.end(); ++iter) {
				(*iter)->SetXpos((*iter)->GetXpos() + 4);
			}

		}
		if (xpos < 0) {
			xpos = 0;
		}
	}

	else {
		//오른쪽 스크롤링
		if (xpos < bg_width - 640) {
			xpos += 2;

			for (std::list<Monster*>::iterator iter = monster.begin(); iter != monster.end(); ++iter) {
				(*iter)->SetXpos((*iter)->GetXpos() - 4);
			}
			for (std::list<Missile*>::iterator iter = missile.begin(); iter != missile.end(); ++iter) {
				(*iter)->SetXpos((*iter)->GetXpos() - 4);
			}
			for (std::list<Item*>::iterator iter = item.begin(); iter != item.end(); ++iter) {
				(*iter)->SetXpos((*iter)->GetXpos() - 4);
			}

		}
		if (xpos > bg_width - 640) {
			xpos = bg_width - 640;
		}
	}
}

int GameStage::TotalScore() {
	return(hero->GetHealth() * 3000 + killCount * 1000 + hero->GetAplus() * 500
		- clearTime / 500);
}