#include "IntroStage.h"
#include "GameStage.h"
#include "TextureManager.h"
#include "GameFunc.h"
#include "FirstStage.h"
#include "SoundManager.h"

extern Stage *stage;
extern SDL_Renderer *g_renderer;
extern int g_flag_running;
extern int g_window_width;
extern int g_window_height;

SDL_Rect start_rect;
SDL_Rect end_rect;
SDL_Rect skip_rect;
SDL_Rect next_rect;

//0 : 보통, 1 : 스타트 불들어옴, 2 : 엔딩 불들어옴
static int click_mode;

IntroStage::IntroStage()
{
	phase = 0;
	TextureManager* tm = TextureManager::GetSingleton();
	tm->LoadTexture("bg", "../res/intro_bg_image.png");
	tm->LoadTexture("bg_how1", "../res/how_bg_image1.png", 255, 255, 255);
	tm->LoadTexture("bg_how2", "../res/how_bg_image2.png", 255, 255, 255);
	tm->LoadTexture("intro_text", "../res/intro_text_image.png", 255, 255, 255);

	tm->AddSpriteRect("intro_text_start0", 0, 0, 400, 94);
	tm->AddSpriteRect("intro_text_start1", 0, 94, 400, 94);
	tm->AddSpriteRect("intro_text_end0", 0, 188, 400, 94);
	tm->AddSpriteRect("intro_text_end1", 0, 282, 400, 94);

	start_rect.w = 400;
	start_rect.h = 94;
	start_rect.x = g_window_width / 2 - 200;
	start_rect.y = 398;

	end_rect.w = 400;
	end_rect.h = 94;
	end_rect.x = g_window_width / 2 - 200;
	end_rect.y = 500;

	//skip버튼
	skip_rect.x = 1135;
	skip_rect.y = 38;
	skip_rect.w = 100;
	skip_rect.h = 52;


	//다음 이동 버튼
	next_rect.x = 1022;
	next_rect.y = 552;
	next_rect.w = 216;
	next_rect.h = 83;

	click_mode = 0;

	//사운드 매니저
	SoundManager* sm = sm->GetSingleton();
	{
		sm->LoadMusic("bgm_music", "../music/second_stage.mp3");
		sm->PlayMusic("bgm_music");

		sm->LoadChunk("button", "../music/button.wav");
	}

}

IntroStage::~IntroStage()
{
	TextureManager* tm = TextureManager::GetSingleton();
	tm->DestroyInstance();
	tm->CreateInstance();
	
	SoundManager* sm = SoundManager::GetSingleton();
	sm->DestroyInstance();
	sm->CreateInstance();
}

void IntroStage::Render() {
	SDL_RenderClear(g_renderer);

	TextureManager* tm = TextureManager::GetSingleton();
	DrawBackGround();

	if (phase == 0) {
		if (click_mode == 1) {
			tm->DrawSprite("intro_text", "intro_text_start1", start_rect);
			tm->DrawSprite("intro_text", "intro_text_end0", end_rect);

		}
		else if (click_mode == 2) {
			tm->DrawSprite("intro_text", "intro_text_start0", start_rect);
			tm->DrawSprite("intro_text", "intro_text_end1", end_rect);
		}
		else {
			tm->DrawSprite("intro_text", "intro_text_start0", start_rect);
			tm->DrawSprite("intro_text", "intro_text_end0", end_rect);
		}
	}

	SDL_RenderPresent(g_renderer);
}

void IntroStage::HandleEvents() {
	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			g_flag_running = 0;
			break;

		case SDL_MOUSEBUTTONDOWN:

			if (event.button.button == SDL_BUTTON_LEFT)
			{
				int mouse_x = event.button.x;
				int mouse_y = event.button.y;

				if (phase == 0) {
					if (mouse_x > start_rect.x &&
						mouse_y > start_rect.y &&
						mouse_x < start_rect.x + start_rect.w &&
						mouse_y < start_rect.y + start_rect.h)
						click_mode = 1;

					else if (mouse_x > end_rect.x &&
						mouse_y > end_rect.y &&
						mouse_x < end_rect.x + end_rect.w &&
						mouse_y < end_rect.y + end_rect.h)
						click_mode = 2;
					else
						click_mode = 0;
				}

			}
			break;

		case SDL_MOUSEBUTTONUP:

			if (event.button.button == SDL_BUTTON_LEFT) {

				int mouse_x = event.button.x;
				int mouse_y = event.button.y;

				if (phase == 0) {
					click_mode = 0;

					if (mouse_x > start_rect.x &&
						mouse_y > start_rect.y &&
						mouse_x < start_rect.x + start_rect.w &&
						mouse_y < start_rect.y + start_rect.h) {
						SoundManager* sm = SoundManager::GetSingleton();
						sm->PlayChunk("button");
						phase = 1;
					}
						

					else if (mouse_x > end_rect.x &&
						mouse_y > end_rect.y &&
						mouse_x < end_rect.x + end_rect.w &&
						mouse_y < end_rect.y + end_rect.h) {
						SoundManager* sm = SoundManager::GetSingleton();
						sm->PlayChunk("button");
						g_flag_running = 0;
					}
				}

				else {
					if (mouse_x > skip_rect.x &&
						mouse_y > skip_rect.y &&
						mouse_x < skip_rect.x + skip_rect.w &&
						mouse_y < skip_rect.y + skip_rect.h) {
						//게임 실행
						delete this;
						SoundManager* sm = SoundManager::GetSingleton();
						sm->PlayChunk("button");
						stage = new  FirstStage();
					}


					else if (mouse_x > next_rect.x &&
						mouse_y > next_rect.y &&
						mouse_x < next_rect.x + next_rect.w &&
						mouse_y < next_rect.y + next_rect.h) {

						if (phase == 1) {
							SoundManager* sm = SoundManager::GetSingleton();
							sm->PlayChunk("button");
							phase = 2;
						}
						else if (phase == 2) {
							delete this;
							SoundManager* sm = SoundManager::GetSingleton();
							sm->PlayChunk("button");
							stage = new FirstStage();
						}
					}
						
				}

			}
			break;


		default:
			break;
		}
	}
}


void IntroStage::Update() {

}

void IntroStage::DrawBackGround() {
	TextureManager* tm = TextureManager::GetSingleton();
	SDL_Rect bg_des_rect;
	bg_des_rect.x = 0;
	bg_des_rect.y = 0;
	bg_des_rect.w = g_window_width;
	bg_des_rect.h = g_window_height;
	if (phase == 0) {
		SDL_RenderCopy(g_renderer, tm->GetTexture("bg"), 0, &bg_des_rect);
	}

	if (phase == 1) {
		SDL_RenderCopy(g_renderer, tm->GetTexture("bg_how1"), 0, &bg_des_rect);
	}

	if (phase == 2) {
		SDL_RenderCopy(g_renderer, tm->GetTexture("bg_how2"), 0, &bg_des_rect);
	}
}