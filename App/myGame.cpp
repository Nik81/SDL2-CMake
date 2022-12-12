/*=========================================================================
Program: myApp (Base SDL2 Applications)
Module:  App
Authors: Nicola Vanella nicola.vanella@gmail.com

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notice for more information.
=========================================================================*/

#include "myGame.h"

//------------------------------------------------------------------------
myGame::myGame()
{
	m_Texture = NULL;
	m_Cross = NULL;
	m_Font = NULL;

	m_Sound = NULL;
	m_Music = NULL;
}
//------------------------------------------------------------------------
myGame::~myGame()
{

}

//------------------------------------------------------------------------
bool myGame::OnUserCreate()
{
	m_Texture = Assets()->LoadTexture("path.png");
	m_Cross = Assets()->LoadTexture("cross.png");
	m_Font = Assets()->LoadFont("arial.ttf", 16);

	m_Sound = Audio()->LoadSound("Attack1.wav");
	m_Music = Audio()->LoadMusic("music1.wav");
	//Audio()->PlayMusic(m_Music, 1);

	SDL_QueryTexture(m_Texture, NULL, NULL, &m_Dest.w, &m_Dest.h);

	// Adjust height and width of our image box.
	m_Dest.w /= 6;
	m_Dest.h /= 6;

	m_CrossDest.w = m_Dest.w;
	m_CrossDest.h = m_Dest.h;

	// Sets initial x-position of object
	m_Dest.x = m_CrossDest.x = (Settings()->ScreenWidth - m_Dest.w) / 2;

	// Sets initial y-position of object
	m_Dest.y = m_CrossDest.y = (Settings()->ScreenHeight - m_Dest.h) / 2;

	SDL_Color gray = { 50,50,50,255 };
	Graphics()->SetDrawColor(gray);

	root = new GameEntity(m_CrossDest.x, m_CrossDest.y);
	child1 = new GameEntity();
	child2 = new GameEntity();
	child3 = new GameEntity();
	child1->SetParent(root);
	child2->SetParent(root);
	child3->SetParent(child2);

	child1->SetPosition({ 0, 150 });
	child2->SetPosition({ 200, 250 });
	child3->SetPosition({ 50, 50 });

	return true;
}
//------------------------------------------------------------------------
bool myGame::OnUserUpdate(float elapsedTime)
{
	UpdateInput_Debug();
	//UpdateInput2_Debug();

	// Right boundary
	if (m_Dest.x + m_Dest.w > Settings()->ScreenWidth)
		m_Dest.x = Settings()->ScreenWidth - m_Dest.w;

	// Left boundary
	if (m_Dest.x < 0)
		m_Dest.x = 0;

	// Bottom boundary
	if (m_Dest.y + m_Dest.h > Settings()->ScreenHeight)
		m_Dest.y = Settings()->ScreenHeight - m_Dest.h;

	// Upper boundary
	if (m_Dest.y < 0)
		m_Dest.y = 0;

	Draw();

	return true;
}
//------------------------------------------------------------------------
bool myGame::OnUserDestroy()
{
	// Destroy textures
	SDL_DestroyTexture(m_Texture);
	SDL_DestroyTexture(m_Cross);
	
	TTF_CloseFont(m_Font);
	
	Mix_FreeChunk(m_Sound);
	Mix_FreeMusic(m_Music);

	delete(root);
	delete(child1);
	delete(child2);

	return true;
}

//------------------------------------------------------------------------
void myGame::UpdateInput_Debug()
{
	//NOTE, disable InputUpdate in GameEngine 
	SDL_Event event;

	// Events management
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			// handling of close button
			Exit();
			break;

			// Mouse Events
		case SDL_MOUSEMOTION: break;
		case SDL_MOUSEBUTTONDOWN: break;
		case SDL_MOUSEBUTTONUP:
		{
			int mousePosX, mousePosY;
			SDL_GetMouseState(&mousePosX, &mousePosY);
			m_CrossDest.x = mousePosX - m_CrossDest.w / 2;
			m_CrossDest.y = mousePosY - m_CrossDest.h / 2;

			root->SetPosition({ (float)m_CrossDest.x, (float)m_CrossDest.y });

			Audio()->PlaySound(m_Sound);
		}
			break;
		case SDL_MOUSEWHEEL: break;

		// Key Events
		case SDL_KEYUP: break;
		case SDL_KEYDOWN:
			// keyboard API for key pressed
			switch (event.key.keysym.scancode)
			{
			case SDL_SCANCODE_ESCAPE:
				Exit();
				break;

			case SDL_SCANCODE_W:
			case SDL_SCANCODE_UP:
				m_Dest.y -= m_Speed / 30;
				break;
			case SDL_SCANCODE_A:
			case SDL_SCANCODE_LEFT:
				m_Dest.x -= m_Speed / 30;
				break;
			case SDL_SCANCODE_S:
			case SDL_SCANCODE_DOWN:
				m_Dest.y += m_Speed / 30;
				break;
			case SDL_SCANCODE_D:
			case SDL_SCANCODE_RIGHT:
				m_Dest.x += m_Speed / 30;
				break;
				
			case SDL_SCANCODE_PRINTSCREEN:
			{
				std::string file = APP_BINARY_DIR;
				file += "/snapshot.png";
				SaveSnapshot(file.c_str());
			}
				break;

			case SDL_SCANCODE_M:
			{
				Audio()->PlayMusic(m_Music);
			}
			break;
			case SDL_SCANCODE_N:
			{
				Audio()->StopMusic();
			}
			break;
			case SDL_SCANCODE_KP_MINUS:
			{
				int volume = Audio()->GetMusicVolume() -1;
				Audio()->SetMusicVolume(volume);
			}
			break;
			case SDL_SCANCODE_KP_PLUS:
			{
				int volume = Audio()->GetMusicVolume() +1;
				Audio()->SetMusicVolume(volume);
			}
			break;

			default:
				break;
			}
		}
	}
}

void myGame::UpdateInput2_Debug()
{
	if (Input()->MouseButtonDown(MOUSE_BUTTON::LEFT))
	{
		m_CrossDest.x = Input()->GetMouseX() - m_CrossDest.w / 2;
		m_CrossDest.y = Input()->GetMouseY() - m_CrossDest.h / 2;
	}

	if (Input()->KeyButtonDown(SDL_SCANCODE_RIGHT) || Input()->KeyButtonDown(100))
	{
		m_Dest.x += m_Speed / 30;
	}

	if (Input()->KeyButtonDown(SDL_SCANCODE_LEFT) || Input()->KeyButtonDown(97))
	{
		m_Dest.x -= m_Speed / 30;
	}

	if (Input()->KeyButtonDown(SDL_SCANCODE_DOWN) || Input()->KeyButtonDown(115))
	{
		m_Dest.y += m_Speed / 30;
	}

	if (Input()->KeyButtonDown(SDL_SCANCODE_UP) || Input()->KeyButtonDown(119))
	{
		m_Dest.y -= m_Speed / 30;
	}

	if (Input()->KeyButtonPressed(SDL_SCANCODE_PRINTSCREEN))
	{
		std::string file = "C:/DEV_64/myAppSDL3/snapshot.png";
		SaveSnapshot(file.c_str());
	}
}

//------------------------------------------------------------------------
void myGame::Draw()
{
	// Draw
	Graphics()->Clear();
	
	// Colors
	SDL_Color white = { 255,255,255 };
	SDL_Color red = { 255,0,0,255 };
	SDL_Color green = { 0,255,0,255 };
	SDL_Color blue = { 0,0,255,255 };

	// Draw Text
	Graphics()->DrawText("0xABCEDFGHIJKLMNOPQRSTUVWXYZ", 1, Settings()->ScreenHeight - 20, m_Font, &white);

	// Draw Point
	Graphics()->DrawPoint(100, 100, green);
	Graphics()->DrawPoint({ 102, 100 }, red);

	// Draw Line
	Graphics()->DrawLine(120, 100, 180, 200, red);
	Graphics()->DrawLine({ 122, 100 }, { 182, 200 }, blue);

	// Draw Rect
	Graphics()->DrawRect({ 200, 100 }, { 300, 200 }, blue);
	Graphics()->DrawRect({ 202, 100 }, { 302, 200 }, green);

	// Draw Fill Rect
	Graphics()->DrawFillRect(320, 100, 420, 200, red);
	Graphics()->DrawFillRect({ 322, 100 }, { 422, 200 }, green);

	// Draw Textures
	Graphics()->DrawTexture(m_Texture, &m_Dest);
	Graphics()->DrawTexture(m_Cross, &m_CrossDest);

	DrawAudioStatus_Debug();
	//PrintInputStatus_Debug();

	root->SetRotation(root->GetRotation(GameEntity::SPACE::local) + 0.1f);

	float rX = root->GetPosition(GameEntity::SPACE::world).x;
	float rY = root->GetPosition(GameEntity::SPACE::world).y;

	float c1X = child1->GetPosition(GameEntity::SPACE::world).x;
	float c1Y = child1->GetPosition(GameEntity::SPACE::world).y;


	child2->SetRotation(child2->GetRotation(GameEntity::SPACE::local) + 0.5f);

	float c2X = child2->GetPosition(GameEntity::SPACE::world).x;
	float c2Y = child2->GetPosition(GameEntity::SPACE::world).y;

	float c3X = child3->GetPosition(GameEntity::SPACE::world).x;
	float c3Y = child3->GetPosition(GameEntity::SPACE::world).y;

	Graphics()->DrawLine(rX, rY, c1X, c1Y, red);
	Graphics()->DrawLine(rX, rY, c2X, c2Y, blue);
	Graphics()->DrawLine(c2X, c2Y, c3X, c3Y, green);

	//Graphics()->DrawText("R", rX, rY, m_Font, &white);
	Graphics()->DrawText("C1", c1X, c1Y, m_Font, &white);
	Graphics()->DrawText("C2", c2X, c2Y, m_Font, &white);
	Graphics()->DrawText("C3", c3X, c3Y, m_Font, &white);
}

//------------------------------------------------------------------------
void myGame::DrawInputStatus_Debug()
{
	SDL_Color white = { 255,255,255 };

	// Print Mouse Status
	for (int i = 0; i < 5; i++)
	{
		Graphics()->DrawText(Input()->MouseStatus[i], 1, 20 * i, m_Font, &white);
	}

	char mouseInfo[256];
	sprintf(mouseInfo, "Mouse Pos: (%d, %d) Move: %d", Input()->GetMouseX(), Input()->GetMouseY(), Input()->MouseMove());
	Graphics()->DrawText(mouseInfo, 1, 20 + 20 * 5, m_Font, &white);

	// Print Key Status
	// 	for (int i = 0; i < 512; i++)
	// 	{
	// 		Graphics()->DrawText(Input()->KeyStatus[i], 1, 20 * i, m_Font, &white);
	// 	}
}

void myGame::DrawAudioStatus_Debug()
{
	SDL_Color white = { 255,255,255 };

	if (Audio()->IsPlayingMusic())
	{
		Graphics()->DrawText("PLAY MUSIC", 1, 1, m_Font, &white);

		if (Audio()->IsPausedMusic())
		{
			Graphics()->DrawText("PAUSED", 100, 1, m_Font, &white);
		}

		char audioInfo[256];
		sprintf(audioInfo, "Volume: %d (+/-)", Audio()->GetMusicVolume());

		Graphics()->DrawText(audioInfo, 1, 50, m_Font, &white);
	}

	if (Audio()->IsPlayngSound())
	{
		Graphics()->DrawText("PLAY SOUND", Settings()->ScreenWidth-110, 1, m_Font, &white);
	}
}
