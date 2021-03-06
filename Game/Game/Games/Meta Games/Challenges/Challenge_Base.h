#ifndef CHALLENGE_BASE
#define CHALLENGE_BASE

#include <small_header.h>

#include "Game/Localization.h"
//#include "Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h"
//#include "Game/Objects/ObjectBase.h"
//#include "Game/Games/GameType.h"
//#include "Game/Games/Meta Games/StringWorlds/StringWorld.h"
//#include "Game/Level/Make/LockableBool.h"
//#include "Game/Level/Make/LevelSeedData.h"
//#include "Game/Player/PlayerManager.h"
//#include "Game/Menus/Concrete Menus/Score Screens/ScoreDatabase.h"
//#include "Game/Player/Hero Physics/Base.h"
//#include "Game/Menus/Concrete Menus/Help/HelpMenu.h"
//#include "Game/Objects/Game Objects/GameObjects/End/GameOverPanel.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{
	struct AftermathData
	{
	
		bool Success;
		bool EarlyExit;
		bool Retry;
	
		void InitializeInstanceFields();

		AftermathData()
		{
			InitializeInstanceFields();
		}
	};

	struct Challenge : public boost::enable_shared_from_this<Challenge>
	{

		virtual ~Challenge()
		{
#ifdef BOOST_BIN
			OnDestructor( "Challenge" );
#endif
		}


		static int Coins;
		static int CurrentScore;
		static int CurrentId;
		static int LeaderboardIndex;

		struct OnCoinGrabProxy : public Lambda_1<boost::shared_ptr<ObjectBase> >
		{
		
			void Apply( const boost::shared_ptr<ObjectBase> &obj );

		};

	
		struct PassGetSeedAsLambda : public LambdaFunc_1<int, boost::shared_ptr<LevelSeedData> >
		{

		
			boost::shared_ptr<Challenge> challenge;

		
			PassGetSeedAsLambda( const boost::shared_ptr<Challenge> &challenge );

			boost::shared_ptr<LevelSeedData> Apply( const int &index );

		};

		struct ShowEndScreenProxy : public Lambda
		{
		
			boost::shared_ptr<Challenge> challenge;

		
			ShowEndScreenProxy( const boost::shared_ptr<Challenge> &challenge );

			void Apply();
		};

	
		static boost::shared_ptr<BobPhsx> ChosenHero;
	
		static const int LevelMask = 10000;

	
		std::vector<int> StartLevels;

		Localization::Words Name, MenuName;

		int GameId_Score, GameId_Level;
	
		int GameTypeId;

		int CalcTopGameLevel( boost::shared_ptr<BobPhsx> hero );
		int CalcGameId_Score( boost::shared_ptr<BobPhsx> hero );
		int CalcGameId_Level( boost::shared_ptr<BobPhsx> hero );
		int SetGameId();

	
		const boost::shared_ptr<StringWorldGameData> getStringWorld() const;

		/// <summary>
		/// Get the top score that anyone on this machine has ever gotten.
		/// </summary>
		int TopScore();

		/// <summary>
		/// Get the highest level that anyone on this machine has ever gotten.
		/// </summary>
		int TopLevel();

		/// <summary>
		/// Get the top score that anyone playing has ever gotten.
		/// </summary>
		int TopPlayerScore();
		int TopPlayerScore( boost::shared_ptr<BobPhsx> hero );

		/// <summary>
		/// Get the highest level that anyone playing has ever gotten.
		/// </summary>
		int TopPlayerLevel();

        /// <summary>
        /// Get the top score that anyone playing has ever gotten.
        /// </summary>
        int TopPlayerScore(BobPhsx hero);
	
		virtual void ShowEndScreen();

		/// <summary>
		/// If true then this meta-game is not part of the campaign.
		/// </summary>
	
		bool NonCampaign;
		virtual void Start( int Difficulty );

		/// <summary>
		/// The difficulty selected for this challenge.
		/// </summary>
		int DifficultySelected;

		/// <summary>
		/// Called immediately after the end of the challenge.
		/// </summary>
		void Aftermath();

	
		virtual void SetGameParent( const boost::shared_ptr<GameData> &game );

	
		virtual boost::shared_ptr<LevelSeedData> GetSeed( int Index ) = 0;

	
		void InitializeInstanceFields();


		Challenge()
		{
			InitializeInstanceFields();
		}
	};
}


#endif	//#ifndef CHALLENGE_BASE
