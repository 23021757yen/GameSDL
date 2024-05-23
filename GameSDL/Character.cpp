
#include "Character.h"


Character :: Character()
{
	x_pos = 15 * TILE_SIZE;
	y_pos = 12 * TILE_SIZE;

	x_val = 0;
	y_val = 0;

	map_x_ = 0;
	map_y_ = 0;

	collision.x = getX() + 32;
	collision.y = getY() + 16;
	collision.w = PLAYER_WIDTH;
	collision.h = PLAYER_HEIGHT;

	for (int i = 0; i < FRAME_RUN; i++)
	{
		run_clip[i] = { i * FRAME_WIDTH, FRAME_HEIGHT, FRAME_WIDTH, FRAME_HEIGHT };
	}

	for (int i = 0; i < FRAME_JUMP; i++)
	{
		jump_clip[i] = { i * FRAME_WIDTH, 2 * FRAME_HEIGHT, FRAME_WIDTH, FRAME_HEIGHT };
	}


	for (int i = 0; i < FRAME_DEATH; i++)
	{
		death_clip[i] = { i * FRAME_WIDTH, 3 * FRAME_HEIGHT, FRAME_WIDTH, FRAME_HEIGHT };
	}


	for (int i = 0; i < FRAME_IDLE; i++)
	{
		idle_clip[i] = { i * FRAME_WIDTH, 0, FRAME_WIDTH, FRAME_HEIGHT };
	}
}

Character::~Character()
{

}


bool Character::Load_Img(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::Load_Img(path, screen);
	return ret;
    
}

void Character::KeyBoard(SDL_Event& event, Mix_Chunk* p_sfx[], Menu menu)
{
		if (event.type == SDL_KEYDOWN && event.key.repeat==0)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_RIGHT:
				
				x_val += PLAYER_VAL;
				break;
			case SDLK_LEFT:
				
				x_val -= PLAYER_VAL;
				break;
			case SDLK_UP:
				if (on_ground_)
				{
					if (menu.isOnsound() && !menu.isMute())
					{
						Mix_PlayChannel(-1, p_sfx[jumpSFX], 0);
					}
					Jump();
				}
				break;
			case SDLK_SPACE:
			{
				if (menu.isOnsound() && !menu.isMute())
				{
					Mix_PlayChannel(-1, p_sfx[shootSFX], 0);
				}
				Item* bullet = new Item(getX() + 80, getY() + 32, flip_type_);
				bullet->SetMove(true);
				bullet->SetPosition(getX() + 16, getY() + 32);
				bulletList.push_back(bullet);
			}
				break;
			default:
				break;
			}

		}
		else if (event.type == SDL_KEYUP && event.key.repeat==0)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_RIGHT:
				x_val -= PLAYER_VAL;
				break;
			case SDLK_LEFT:
				x_val += PLAYER_VAL;
				break;
			case SDLK_UP:
				//Jump();
				if (!on_ground_ && jump_)
				{
					y_val *= 0.5;
				}
				break;
			default:
				break;
			}
		}
}

void Character::HandleCamera(SDL_Rect& camera, int& cam_val)
{
	if (!isDeath()) camera.x += cam_val;
	float acc = 0.1;
	if (cam_val > 7) acc = 0.03;
	if (cam_val > 10) acc = 0.001;
	cam_val += acc;

	//camera.x = (getX() + PLAYER_WIDTH / 2) - SCREEN_WIDTH / 2;

	if (getX() + PLAYER_WIDTH / 2 - camera.x >= SCREEN_WIDTH * 2 / 3) {
		camera.x = (getX() + PLAYER_WIDTH / 2) - SCREEN_WIDTH * 2 / 3;
	}

	
	if (camera.x < 0)
	{
		camera.x = 0;
	}
	if (camera.x > LEVEL_WIDTH - SCREEN_WIDTH)
	{
		//camera.x = LEVEL_WIDTH - SCREEN_WIDTH;
	}
}

void Character::Jump()
{
	if (on_ground_)
	{
		y_val -= 15;
		on_ground_ = false;
	}
	
}

void Character::Gravity()
{
	if (!on_ground_ && !death_)
	{
		y_val += GRAVITY;
		if (y_val >= MAX_GRAVITY) y_val = MAX_GRAVITY;
	}
	else
	{
		y_val = 0;
	}
}

void Character::Update(std::vector<map>& map_data, std::vector<Monster*>& monsterList ,Mix_Chunk* p_sfx[], Menu menu,SDL_Rect& camera)
{
	Gravity();
	GetHit(monsterList,p_sfx,menu,camera);
	if (!death_ && x_val == 0 && on_ground_)
	{
		idle_ = true;
	}
	else
	{
		idle_ = false;
	}
	if (!death_ && x_val != 0 && on_ground_)
	{
		run_ = true;
	}
	else
	{
		run_ = false;
	}

	if ( !death_ && y_val < 0 && !on_ground_)
	{
		jump_ = true;
	}
	else
	{
		jump_ = false;
	}
	if (!death_ && y_val >= 0 && !on_ground_)
	{
		fall_ = true;
	}
	else
	{
		fall_ = false;
	}


	if (x_val > 0)
	{
		flip_type_ = SDL_FLIP_NONE;
	}
	if (x_val < 0)
	{
		flip_type_ = SDL_FLIP_HORIZONTAL;
	}

	if (!death_) 
	{
		x_pos += x_val;
	
		collision.x = getX() + 32;
		if (CommonFunc_SDL2::checkToMap(collision, map_data))
		{
			x_pos -= x_val;
			collision.x = getX() + 32;
		}
	}
	y_pos += y_val;
	collision.y = getY() + 16;
	if (CommonFunc_SDL2::checkToMap(collision, map_data, on_ground_, ground[0], ground[1], levelSTT))
	{
		if (y_val > 0)
		{
			y_pos = ground[1] * TILE_SIZE - 96 + 16;
			
			if (fall_)
			{
				on_ground_ = true;
			}
		}
		
		if (y_val < 0)
		{
			y_pos -= y_val;
			y_val = 0;

		}
		
		collision.y = getY() + 16;
	}

	if (collision.y + collision.h >= 640)
	{
		on_ground_ = false;
		death_ = true;
	}
	//std::cout << ground[0] << " " << ground[1] << std::endl;
	//std::cout << on_ground_ << std::endl;
}

void Character::GetHit(std::vector<Monster*>& monsterList, Mix_Chunk* p_sfx[], Menu menu, SDL_Rect& camera)
{
	for (int i = 0; i < monsterList.size(); i++)
	{
		if (monsterList.at(i) != NULL)
		{
			if (monsterList.at(i)->isAttacking() && monsterList.at(i)->getFlip() == SDL_FLIP_NONE)
			{
				SDL_Rect a = { monsterList.at(i)->getCollision().x + 32, monsterList.at(i)->getCollision().y, 32, 64 };
				//printf("1");
				if (CommonFunc_SDL2::checkCollision(a, getCollision()))
				{
					//printf("2");
					if (menu.isOnsound() && !menu.isMute())
					{
						Mix_PlayChannel(-1, p_sfx[hitSFX], 0);
					}
					if (SDL_GetTicks() - lastTakenDmg >= 500)
					{
						MARK_CHA--;
						if (MARK_CHA <= 0)
						{
							death_ = true;
						}
						lastTakenDmg = SDL_GetTicks();
						std::cout << MARK_CHA << std::endl;
					}

				}
			}
			if (monsterList.at(i)->isAttacking() && monsterList.at(i)->getFlip() == SDL_FLIP_HORIZONTAL)
			{
				//printf("3");
				SDL_Rect a = { monsterList.at(i)->getCollision().x - 32, monsterList.at(i)->getCollision().y, 32, 64 };
				if (CommonFunc_SDL2::checkCollision(a, getCollision()))
				{
				//	printf("%d\n",MARK_CHA);
					if (menu.isOnsound() && !menu.isMute())
					{
						Mix_PlayChannel(-1, p_sfx[hitSFX], 0);
					}
					if (SDL_GetTicks() -lastTakenDmg>=500)
					{
						MARK_CHA--;
						if (MARK_CHA <= 0)
						{
							death_ = true;
						}
						lastTakenDmg = SDL_GetTicks();
						std::cout << MARK_CHA << std::endl;
					}
				}
			}
		}
	}
	if ((camera.x + 380 >= getCollision().x))
	{
		death_ = true;
	} // you ngựa
}

void Character::Show_Frames(SDL_Renderer* des, SDL_Rect& camera)
{

	if (idle_ && !death_) 
	{
		CommonFunc_SDL2::RenderAnimation(des,p_object, x_pos, y_pos, &idle_clip[idleCounter / delay_], &camera, 0, NULL, flip_type_);
		idleCounter++;
		if (idleCounter / delay_ >= FRAME_IDLE)
		{
			idleCounter = 0;
		}
	}
	else idleCounter = 0;

	if (run_ && !death_)
	{
		CommonFunc_SDL2::RenderAnimation(des,p_object, x_pos, y_pos, &run_clip[runCounter / delay_], &camera, 0, NULL, flip_type_);
		runCounter++;
		if (runCounter / delay_ >= FRAME_RUN)
		{
			runCounter = 0;
		}
	}
	else runCounter = 0;

	if (jump_ && !death_)
	{
		CommonFunc_SDL2::RenderAnimation(des,p_object, x_pos, y_pos, &jump_clip[jumpCounter], &camera, 0, NULL, flip_type_);
	}

	if (fall_ && !death_)
	{
		CommonFunc_SDL2::RenderAnimation(des,p_object, x_pos, y_pos, &jump_clip[fallCounter], &camera, 0, NULL, flip_type_);
	}

	if (death_)
	{
		CommonFunc_SDL2::RenderAnimation(des,p_object, x_pos, y_pos, &death_clip[deathCounter / delay_], &camera, 0, NULL, flip_type_);
		deathCounter++;
		if (deathCounter / delay_ >= FRAME_DEATH)
		{
			deathCounter = 23;
		}

	}
	else deathCounter = 0;
}


