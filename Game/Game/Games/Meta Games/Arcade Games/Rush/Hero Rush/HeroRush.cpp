#include <small_header.h>
#include "Game/Games/Meta Games/Arcade Games/Rush/Hero Rush/HeroRush.h"

#include "Game/Localization.h"
#include "Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h"
#include "Core/Tools/CoreMath.h"
#include "Game/Objects/ObjectBase.h"
#include "Game/Tilesets/TileSet.h"
#include "Game/Games/GameType.h"
#include "Game/Games/Meta Games/Arcade Games/Rush/CoinMod.h"
#include "Game/Games/Meta Games/Arcade Games/Rush/Rush.h"
#include "Game/Games/Meta Games/Arcade Games/Rush/Hero Rush/HeroRush_Tutorial.h"
#include "Game/Games/Meta Games/Challenges/_Regular.h"
#include "Game/Level/Make/LockableBool.h"
#include "Game/Level/Make/LevelSeedData.h"
#include "Game/Level/Make/PieceSeedData.h"
#include "Game/Menus/Concrete Menus/Title Screen/Arcade/ArcadeMenu.h"
#include "Game/Player/Hero Physics/Base.h"
#include "Game/Objects/Game Objects/GameObjects/DoorIcon.h"
#include "Game/Objects/Game Objects/GameObjects/MultiplierUp.h"
#include "Game/Objects/Game Objects/GameObjects/SuperCheer.h"
#include "Game/Player/Hero Physics/Normal.h"
#include "Game/Player/Hero Physics/Big.h"
#include "Game/Player/Hero Physics/Bouncy.h"
#include "Game/Player/Hero Physics/Box.h"
#include "Game/Player/Hero Physics/Double.h"
#include "Game/Player/Hero Physics/Jetman.h"
#include "Game/Player/Hero Physics/Rocketbox.h"
#include "Game/Player/Hero Physics/Small.h"
#include "Game/Player/Hero Physics/Spaceship.h"
#include "Game/Player/Hero Physics/Wheel.h"
#include "Game/Tools/Tools.h"
#include "Game/Tilesets/TileSetInfo.h"

#include "Game/Level/Make/Parameters/StyleData/StyleData.h"
#include "Game/Objects/In Game Objects/Grab/Coin__Auto.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Timer.h"
#include "Game/Games/Meta Games/StringWorlds/StringWorld_Timed.h"
#include "Game/Level/Level.h"
#include "Core/Tools/Random.h"

#include "Hacks/List.h"

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>

namespace CloudberryKingdom
{

	void Challenge_HeroRush::InitializeStatics()
	{
		Challenge_HeroRush::instance = boost::make_shared<Challenge_HeroRush>();

		int tempVector[] = { 20, 15, 10, 10, 10 };
		Challenge_HeroRush::MaxTime_ByDifficulty = VecFromArray( tempVector );
		int tempVector2[] = { 15, 12, 10, 10, 10 };
		Challenge_HeroRush::StartTime_ByDifficulty = VecFromArray( tempVector2 );

		boost::shared_ptr<BobPhsx> tempVector3[] = { BobPhsxNormal::getInstance(), BobPhsxJetman::getInstance(), BobPhsxDouble::getInstance(), BobPhsxSmall::getInstance(), BobPhsxWheel::getInstance(), BobPhsxSpaceship::getInstance(), BobPhsxBouncy::getInstance(), BobPhsxBig::getInstance() };
		Challenge_HeroRush::_HeroTypes = VecFromArray( tempVector3 );

		std::wstring tempVector4[] = { std::wstring( L"sea" ), std::wstring( L"hills" ), std::wstring( L"forest" ), std::wstring( L"cloud" ), std::wstring( L"cave" ), std::wstring( L"castle" ) };
		Challenge_HeroRush::tilesets = VecFromArray( tempVector4 );
	}

	// Statics
	boost::shared_ptr<Challenge_HeroRush> Challenge_HeroRush::instance;

	std::vector<int> Challenge_HeroRush::MaxTime_ByDifficulty;
	std::vector<int> Challenge_HeroRush::StartTime_ByDifficulty;

	std::vector<boost::shared_ptr<BobPhsx> > Challenge_HeroRush::_HeroTypes, Challenge_HeroRush::HeroTypes;
	std::vector<std::wstring> Challenge_HeroRush::tilesets;



	Challenge_HeroRush::OnSwapLambda::OnSwapLambda( const boost::shared_ptr<Challenge_HeroRush> &ch )
	{
		this->ch = ch;
	}

	void Challenge_HeroRush::OnSwapLambda::Apply( const boost::shared_ptr<LevelSeedData> &data )
	{
		data->MyGame->AddGameObject( boost::make_shared<HeroRush_Tutorial>( ch ) );
	}

	Challenge_HeroRush::ScoreMultiplierHelper::ScoreMultiplierHelper( float multiplier )
	{
		this->multiplier = multiplier;
	}

	void Challenge_HeroRush::ScoreMultiplierHelper::Apply( const boost::shared_ptr<GameData> &game )
	{
		game->ScoreMultiplier *= multiplier;
	}

	Challenge_HeroRush::AdditionalPreStartOnSwapToLevelHelper::AdditionalPreStartOnSwapToLevelHelper( const boost::shared_ptr<Challenge_HeroRush> &chr )
	{
		this->chr = chr;
	}

	void Challenge_HeroRush::AdditionalPreStartOnSwapToLevelHelper::Apply( const int &levelindex )
	{
		chr->AdditionalSwap( levelindex );

		ArcadeMenu::CheckForArcadeUnlocks_OnSwapIn( levelindex );

		// Add hero icon to exit door
		chr->MakeExitDoorIcon( levelindex );

		// Score multiplier, x1, x1.5, x2, ... for levels 0, 20, 40, ...
		float multiplier = 1 + ( ( levelindex + 1 ) / chr->LevelsPerDifficulty ) *.5f;
		Tools::CurGameData->OnCalculateScoreMultiplier->Add( boost::make_shared<ScoreMultiplierHelper>( multiplier ) );

		// Mod number of coins
		boost::shared_ptr<CoinMod> mod = boost::make_shared<CoinMod>( chr->Timer );
		mod->LevelMax = 17;
		mod->ParMultiplier_Start = 1.6f;
		mod->ParMultiplier_End = 1;
		mod->CoinControl( Tools::CurGameData->MyLevel, ( levelindex + 1 ) % chr->LevelsPerDifficulty );

		// Reset sooner after death
		Tools::CurGameData->SetDeathTime( GameData::DeathTime_FAST );

		// Modify the timer
		chr->SetTimerProperties( levelindex / chr->LevelsPerDifficulty );

		chr->OnSwapTo_GUI( levelindex );
	}

	void Challenge_HeroRush::MakeMyModParamsHelper::Apply( const boost::shared_ptr<Level> &level, const boost::shared_ptr<PieceSeedData> &p )
	{
		boost::shared_ptr<Coin_Parameters> Params = boost::dynamic_pointer_cast<Coin_Parameters>( p->Style->FindParams( Coin_AutoGen::getInstance() ) );
		Params->FillType = Coin_Parameters::FillTypes_RUSH;
	}

	const boost::shared_ptr<Challenge_HeroRush> &Challenge_HeroRush::getInstance()
	{
		return instance;
	}

	Challenge_HeroRush::Challenge_HeroRush()
	{
		InitializeInstanceFields();

		GameTypeId = 2;
		MenuName = Name = Localization::Words_HeroRush;

		SetGameId();
	}

	void Challenge_HeroRush::SetTimerProperties( int Difficulty )
	{
		Difficulty = __min( Difficulty, static_cast<int>( MaxTime_ByDifficulty.size() ) - 1 );

		Timer->CoinTimeValue = static_cast<int>( 62 * 1.75f );

		if ( Difficulty >= static_cast<int>( MaxTime_ByDifficulty.size() ) )
			Timer->MaxTime = MaxTime_ByDifficulty[ MaxTime_ByDifficulty.size() - 1 ];
		else
			Timer->MaxTime = 62 * ( MaxTime_ByDifficulty[ Difficulty ] + 0 ) - 1;
	}

	void Challenge_HeroRush::PreStart_Tutorial( bool TemporarySkip )
	{
		HeroRush_Tutorial::TemporarySkip = TemporarySkip;
		MyStringWorld->OnSwapToFirstLevel->Add( boost::make_shared<OnSwapLambda>( boost::static_pointer_cast<Challenge_HeroRush>( shared_from_this() ) ) );
	}

	void Challenge_HeroRush::MakeExitDoorIcon( int levelindex )
	{
		Vector2 shift = Vector2( 0, 470 );

		Tools::CurGameData->AddGameObject( MakeMagic( DoorIcon, ( GetHero( levelindex + 1 - StartIndex ), Tools::CurLevel->getFinalDoor()->getPos() + shift, 1.f ) ) );
	}

    void Challenge_HeroRush::AdditionalSwap(int levelindex)
    {
    }

	void Challenge_HeroRush::AdditionalPreStart()
	{
		Rush::AdditionalPreStart();

		// Set timer values
		int Difficulty = ( StartIndex + 1 ) / LevelsPerDifficulty;
		SetTimerProperties( Difficulty );

		if ( Difficulty >= static_cast<int>( StartTime_ByDifficulty.size() ) )
			Timer->setTime( 62 * StartTime_ByDifficulty[ StartTime_ByDifficulty.size() - 1 ] );
		else
			Timer->setTime( 62 * StartTime_ByDifficulty[ Difficulty ] );

		// Tutorial
		PreStart_Tutorial( StartIndex > 0 );

		// When a new level is swapped to...
		MyStringWorld->OnSwapToLevel->Add( boost::make_shared<AdditionalPreStartOnSwapToLevelHelper>( boost::static_pointer_cast<Challenge_HeroRush>( shared_from_this() ) ) );
	}

	void Challenge_HeroRush::OnSwapTo_GUI( int levelindex )
	{
		// Multiplier increase text
		if ( ( levelindex + 1 ) % LevelsPerDifficulty == 0 )
			Tools::CurGameData->AddGameObject( MakeMagic( MultiplierUp, () ) );

		// Cheering berries (20, 40, 60, ...)
		if ( ( levelindex + 1 ) % LevelsPerDifficulty == 0 && levelindex != StartIndex )
			Tools::CurGameData->AddGameObject( boost::make_shared<SuperCheer>( 1 ) );
	}

	boost::shared_ptr<LevelSeedData> Challenge_HeroRush::GetSeed( int Index )
	{
		std::vector<float> lerp_vec;

		lerp_vec.push_back(-.5f);
		lerp_vec.push_back(0);
		lerp_vec.push_back(1);
		lerp_vec.push_back(2);
		lerp_vec.push_back(2.5f);
		lerp_vec.push_back(3);
		lerp_vec.push_back(3.5f);
		lerp_vec.push_back(4);
		lerp_vec.push_back(4.5f);
		lerp_vec.push_back(5.0f);
		lerp_vec.push_back(6.0f);

		float difficulty = CoreMath::MultiLerpRestrict( Index / static_cast<float>( LevelsPerDifficulty ), lerp_vec );
		boost::shared_ptr<CloudberryKingdom::LevelSeedData> seed = Make( Index, difficulty );

		return seed;
	}

        void Challenge_HeroRush::ShuffleHeros()
        {
            HeroTypes.clear();

            for (int i = 0; i < 5; i++)
            {
                HeroTypes.push_back(BobPhsxNormal::getInstance());
                
                _HeroTypes = Tools::GlobalRnd->Shuffle(_HeroTypes);
				AddRange( HeroTypes, _HeroTypes );

                HeroTypes.push_back(BobPhsxBox::getInstance());

                _HeroTypes = Tools::GlobalRnd->Shuffle(_HeroTypes);
                AddRange( HeroTypes, _HeroTypes );

                HeroTypes.push_back(BobPhsxRocketbox::getInstance());

                _HeroTypes = Tools::GlobalRnd->Shuffle(_HeroTypes);
                AddRange( HeroTypes, _HeroTypes );
            }
        }

        void Challenge_HeroRush::Start(int StartLevel)
        {
			CloudberryKingdomGame::SetPresence( Presence_HeroRush );

            ShuffleHeros();

            Rush::Start(StartLevel);
        }

	boost::shared_ptr<BobPhsx> Challenge_HeroRush::GetHero( int i )
	{
		return HeroTypes[ i % HeroTypes.size() ];
	}

	boost::shared_ptr<TileSet> Challenge_HeroRush::GetTileSet( int i )
	{
		return TileSet::Get( tilesets[ ( i / LevelsPerTileset ) % tilesets.size() ] );
	}

	int Challenge_HeroRush::GetLength( int Index, float Difficulty )
	{
		int Length;
		if ( Index == 0 || ( Index + 1 ) % LevelsPerDifficulty == 0 )
			Length = LevelLength_Short;
		else
		{
			float t = static_cast<float>( ( ( ( Index + 1 ) % LevelsPerDifficulty ) / 5 + 1 ) / 5.f );
			Length = CoreMath::LerpRestrict( LevelLength_Short, LevelLength_Long, t );
		}

		return Length;
	}
	boost::shared_ptr<LevelSeedData> Challenge_HeroRush::Make( int Index, float Difficulty )
	{
		boost::shared_ptr<BobPhsx> hero = GetHero( Index - StartIndex );

		// Adjust the length. Longer for higher levels.
		int Length = GetLength(Index, Difficulty);

		// Create the LevelSeedData
		boost::shared_ptr<LevelSeedData> data = RegularLevel::HeroLevel( Difficulty, hero, Length, false );
		data->SetTileSet( GetTileSet( Index - StartIndex ) );

		// Adjust the piece seed data
		for ( std::vector<boost::shared_ptr<PieceSeedData> >::const_iterator piece = data->PieceSeeds.begin(); piece != data->PieceSeeds.end(); ++piece )
		{
			( *piece )->MyMetaGameType = MetaGameType_TIME_CRISIS;
		}

		return data;
	}

	void Challenge_HeroRush::InitializeInstanceFields()
	{
		LevelsPerDifficulty = 20;
		LevelsPerTileset = 4;
		LevelLength_Short = 2150;
		LevelLength_Long = 3900;
	}
}
