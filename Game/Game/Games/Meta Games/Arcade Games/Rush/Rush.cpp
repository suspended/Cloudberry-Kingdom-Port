﻿#include "Rush.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Timer_Base.h"
#include "Game/Games/GameType.h"
#include "Game/Objects/In Game Objects/Grab/CloudberryKingdom.Level.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Panel.h"
#include "Game/Menus/Concrete Menus/InGameStartMenus/InGameStartMenu.h"
#include "Game/Objects/Bob/Bob.h"
#include "Core/Particle Effects/Specific Effects/CloudberryKingdom.ParticleEffects.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Timer.h"
#include "Game/Games/Meta Games/StringWorlds/StringWorld_Timed.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{

	Rush::RushOnTimeExpiredLambda::RushOnTimeExpiredLambda( const std::shared_ptr<Rush> &rush )
	{
		this->rush = rush;
	}

	void Rush::RushOnTimeExpiredLambda::Apply( const std::shared_ptr<GUI_Timer_Base> &Timer )
	{
		std::shared_ptr<GameData> game = Timer->MyGame;
		std::shared_ptr<Level> level = game->MyLevel;

		// Remove the timer
		Timer->SlideOut( GUI_Panel::PresetPos_TOP );
		Timer->Active = false;

		// End the level
		level->EndLevel();

		// Void the final door
		if ( level->getFinalDoor() != 0 )
			level->getFinalDoor()->getOnOpen().reset();

		game->AddToDo( std::make_shared<KillAllPlayersHelper>( rush, game ) );
	}

	Rush::OnLevelBeginLambda::OnLevelBeginLambda()
	{
	}

	bool Rush::OnLevelBeginLambda::Apply( const std::shared_ptr<Level> &level )
	{
		level->MyGame->AddGameObject( InGameStartMenu::MakeListener() );
		return false;
	}

	Rush::KillAllPlayersHelper::KillAllPlayersHelper( const std::shared_ptr<Rush> &rush, const std::shared_ptr<GameData> &game )
	{
		this->rush = rush;
		this->game = game;
	}

	bool Rush::KillAllPlayersHelper::Apply()
	{
		std::shared_ptr<Level> level = game->MyLevel;

		// Kill all the players
		for ( std::vector<Bob*>::const_iterator bob = level->Bobs.begin(); bob != level->Bobs.end(); ++bob )
		{
			if ( ( *bob )->IsVisible() )
			{
				ParticleEffects::PiecePopFart( level, ( *bob )->getCore()->Data->Position );
				( *bob )->getCore()->Show = false;
			}

			if ( !( *bob )->Dead && !( *bob )->Dying )
				( *bob )->Die( Bob::BobDeathType_NONE, true, false );
		}

		// Add the Game Over panel, check for Awardments
		game->WaitThenDo( 105, std::make_shared<ShowEndScreenProxy>( rush ) );

		return true;
	}

	void Rush::OnTimeExpired( const std::shared_ptr<GUI_Timer_Base> &Timer )
	{
	}

	void Rush::Start( int StartLevel )
	{
		Challenge::Start( StartLevel );
		StartIndex = StartLevel;

		// Create the timer
		Timer = std::make_shared<GUI_Timer>();

		// Set the time expired function
		Timer->OnTimeExpired->Add( std::make_shared<RushOnTimeExpiredLambda>( this ) );

		// Create the string world, and add the relevant game objects
		MyStringWorld = std::make_shared<StringWorldTimed>( getGetSeed(), Timer );
		MyStringWorld->StartLevelMusic.reset();

		// Start menu
		MyStringWorld->OnLevelBegin = std::make_shared<OnLevelBeginLambda>();


		// Invert level

		// Additional preprocessing
		SetGameParent( MyStringWorld );
		AdditionalPreStart();

		// Start
		MyStringWorld->Init( StartLevel );
	}

	void Rush::AdditionalPreStart()
	{
	}

	void Rush::InitializeInstanceFields()
	{
		StartIndex = 0;
	}
}