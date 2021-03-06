#ifndef CLOUDBERRYKINGDOM_LEVELSEEDDATA
#define CLOUDBERRYKINGDOM_LEVELSEEDDATA

#include <small_header.h>

#include "Core/PhsxData.h"
//#include "Game/Localization.h"
//#include "Game/Objects/Game Objects/GameObjects/ChapterTitle.h"
//#include "Game/Tilesets/Backgrounds/Background.h"
//#include "Core/Particle Effects/ParticleEmitter.h"
//#include "Core/Song/EzSong.h"
//#include "Core/Tools/CoreMath.h"
//#include "Core/Tools/Random.h"
//#include "Game/Collision Detection/AABox.h"
//#include "Game/Tilesets/TileSet.h"
//#include "Game/Objects/In Game Objects/Blocks/Block.h"
//#include "Game/Objects/In Game Objects/Blocks/Wall.h"
#include "Game/Games/GameType.h"
//#include "Game/Games/ActionGame.h"
//#include "Game/Games/NormalGame.h"
//#include "Game/Games/Meta Games/StringWorlds/StringWorld.h"
//#include "Game/Games/Campaign/FadeIn.h"
//#include "Game/Games/Campaign/CampaignSequence.h"
//#include "Game/Games/Meta Games/StringWorlds/LevelConnector.h"
//#include "Game/Level/Make/PieceSeedData.h"
//#include "Game/Level/Make/Parameters/RandomDifficulty.h"
//#include "Game/Level/Make/Parameters/Upgrades.h"
//#include "Game/Level/Make/Parameters/StyleData/StyleData.h"
//#include "Game/Player/PlayerManager.h"
//#include "Game/Menus/Concrete Menus/InGameStartMenus/InGameStartMenu.h"
//#include "Game/Menus/Concrete Menus/Score Screens/ScoreScreen.h"
//#include "Game/Menus/Concrete Menus/Title Screen/Freeplay/CustomLevel_GUI.h"
//#include "Game/Player/Hero Physics/Base.h"
//#include "Game/Objects/AutoGen.h"
//#include "Game/Objects/Bob/Bob.h"
//#include "Game/Objects/Door/Door.h"
//#include "Game/Objects/Game Objects/GameObjects/LevelTitle.h"
//#include "Game/Objects/Game Objects/GameObjects/NewHero.h"
//#include "Game/Objects/Game Objects/GameObjects/PerfectScoreObject.h"
//#include "Game/Menus/Concrete Menus/Help/HelpMenu.h"
//#include "Game/Menus/Concrete Menus/Help/HintGiver.h"
//#include "Game/Objects/In Game Objects/Blocks/NormalBlock__Auto.h"
//#include "Game/Objects/In Game Objects/Grab/Checkpoint.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Player/ColorSchemeManager.h"
//#include "Game/Player/Stats.h"
//#include "Game/Player/Hero Physics/Normal.h"
//#include "Game/Player/Hero Physics/Double.h"
//#include "Game/Player/Hero Physics/Jetman.h"
//#include "Game/Player/Hero Physics/Meat.h"
//#include "Game/Player/Hero Physics/BobPhsxRandom.h"
//#include "Game/Player/Hero Physics/Rocketbox.h"
//#include "Game/Player/Hero Physics/Spaceship.h"
//#include "Game/Tools/Camera.h"
//#include "Game/Tools/Recycler.h"
//#include "Game/Tools/Tools.h"
//#include "Game/Tilesets/TileSetInfo.h"


namespace CloudberryKingdom
{

	struct LevelSeedData : public boost::enable_shared_from_this<LevelSeedData>
	{

		virtual ~LevelSeedData()
		{
#ifdef BOOST_BIN
			OnDestructor( "LevelSeedData" );
#endif
		}


		struct MakeScoreProxy : public LambdaFunc<boost::shared_ptr<GameObject> >
		{
			boost::shared_ptr<Level> level;

			MakeScoreProxy( boost::shared_ptr<Level> _level );

			boost::shared_ptr<GameObject> Apply();
		};

		struct WaitThenPlayProxy : public Lambda
		{
			boost::shared_ptr<EzSong> song;

			WaitThenPlayProxy( boost::shared_ptr<EzSong> _song );
			void Apply();
		};

		struct _NewHeroProxy : public Lambda_1<boost::shared_ptr<Level> >
		{
		
			boost::shared_ptr<LevelSeedData> lsd;
		
			_NewHeroProxy( const boost::shared_ptr<LevelSeedData> &lsd );

			void Apply( const boost::shared_ptr<Level> &level );
		};	

		struct _RepeatHeroProxy : public Lambda_1<boost::shared_ptr<Level> >
		{
			boost::shared_ptr<LevelSeedData> lsd;
		
			_RepeatHeroProxy( const boost::shared_ptr<LevelSeedData> &lsd );

			void Apply( const boost::shared_ptr<Level> &level );
		};	

		struct _ShowChapterNameProxy : public Lambda_1<boost::shared_ptr<Level> >
		{
		
			boost::shared_ptr<LevelSeedData> lsd;
		
			_ShowChapterNameProxy( const boost::shared_ptr<LevelSeedData> &lsd );

			void Apply( const boost::shared_ptr<Level> &level );
		};	

		struct _ScoreScreenProxy : public Lambda_1<boost::shared_ptr<Level> >
		{
		
			boost::shared_ptr<LevelSeedData> lsd;
		
			_ScoreScreenProxy( const boost::shared_ptr<LevelSeedData> &lsd );

			void Apply( const boost::shared_ptr<Level> &level );
		};	

		struct _StartSongProxy : public Lambda_1<boost::shared_ptr<Level> >
		{
		
			boost::shared_ptr<LevelSeedData> lsd;

		
			_StartSongProxy( const boost::shared_ptr<LevelSeedData> &lsd );

			void Apply( const boost::shared_ptr<Level> &level );
		};

	
		struct _HasWall_ProcessProxy : public Lambda_2<boost::shared_ptr<Level>, boost::shared_ptr<PieceSeedData> >
		{
		
			void Apply( const boost::shared_ptr<Level> &level, const boost::shared_ptr<PieceSeedData> &piece );
		};

	
		struct _SetWeather_ProcessProxy : public Lambda_1<boost::shared_ptr<Level> >
		{
		
			void Apply( const boost::shared_ptr<Level> &level );
		};

	
		struct _NoStartDoorProxy : public Lambda_1<boost::shared_ptr<Level> >
		{
		
			void Apply( const boost::shared_ptr<Level> &level );
		};

	
		struct _FadeIn_ProcessProxy : public Lambda_1<boost::shared_ptr<Level> >
		{
		
			void Apply( const boost::shared_ptr<Level> &level );
		};

	
		struct EOL_StringWorldDoorEndAction_WithFadeProxy : public Lambda_1<boost::shared_ptr<Door> >
		{
		
			boost::shared_ptr<StringWorldGameData> gameData;

		
			EOL_StringWorldDoorEndAction_WithFadeProxy( const boost::shared_ptr<StringWorldGameData> &gameData );

			void Apply( const boost::shared_ptr<Door> &door );
		};

	
		struct _FadeOut_ProcessProxy : public Lambda_1<boost::shared_ptr<Level> >
		{
		
			void Apply( const boost::shared_ptr<Level> &level );
		};

	
		struct ModPieceViaStringProxy : public Lambda_1<boost::shared_ptr<PieceSeedData> >
		{
		
			boost::shared_ptr<LevelSeedData> lsd;

		
			ModPieceViaStringProxy( const boost::shared_ptr<LevelSeedData> &lsd );

			void Apply( const boost::shared_ptr<PieceSeedData> &piece );
		};

	
		struct ModPieceViaHashProxy : public Lambda_1<boost::shared_ptr<PieceSeedData> >
		{
		
			boost::shared_ptr<LevelSeedData> lsd;

		
			ModPieceViaHashProxy( const boost::shared_ptr<LevelSeedData> &lsd );

			void Apply( const boost::shared_ptr<PieceSeedData> &piece );
		};

	
		struct SetToStartSongHelper : public Lambda
		{
		
			boost::shared_ptr<EzSong> song;

		
			SetToStartSongHelper( const boost::shared_ptr<EzSong> &song );

			void Apply();
		};

	
		struct SetToStartSongPostMakeHelper : public Lambda_1<boost::shared_ptr<Level> >
		{
		
			int delay;
			boost::shared_ptr<Lambda> songHelper;

		
			SetToStartSongPostMakeHelper( int delay, const boost::shared_ptr<Lambda> &songHelper );

			void Apply( const boost::shared_ptr<Level> &lvl );
		};

	
		struct BOL_StartMusicProxy : public Lambda
		{
		
			void Apply();
		};

	
		struct ScoreScreenLambda : public LambdaFunc<boost::shared_ptr<GameObject> >
		{
		
			StatGroup stats;
			boost::shared_ptr<Level> level;

		
			ScoreScreenLambda( StatGroup stats, const boost::shared_ptr<Level> &level );

			boost::shared_ptr<GameObject> Apply();
		};

	
		struct EOL_DoorActionProxy : public Lambda_1<boost::shared_ptr<Door> >
		{
			void Apply( const boost::shared_ptr<Door> &door );
		};

	
		struct PostMake_StringWorldStandardHelper : public Lambda
		{
		
			void Apply();
		};

	
		enum LavaMakeTypes
		{
			LavaMakeTypes_ALWAYS_MAKE,
			LavaMakeTypes_NEVER_MAKE,
			LavaMakeTypes_RANDOM
		};
	
		struct StandardInitHelper : public Lambda_1<boost::shared_ptr<PieceSeedData> >
		{
		
			boost::shared_ptr<Lambda_2<boost::shared_ptr<PieceSeedData>, boost::shared_ptr<Upgrades> > > CustomDiff;

		
			StandardInitHelper( const boost::shared_ptr<Lambda_2<boost::shared_ptr<PieceSeedData>, boost::shared_ptr<Upgrades> > > &CustomDiff );

			void Apply( const boost::shared_ptr<PieceSeedData> &p );
		};

	
		struct InitNormalMyModParamsHelper : public Lambda_2<boost::shared_ptr<Level>, boost::shared_ptr<PieceSeedData> >
		{
		
			void Apply( const boost::shared_ptr<Level> &level, const boost::shared_ptr<PieceSeedData> &p );
		};

	
		static bool NoDoublePaths;

		boost::shared_ptr<Level> MakeLevel( const boost::shared_ptr<GameData> &game );
		boost::shared_ptr<Level> MakeLevel( bool MakeBackground, const boost::shared_ptr<GameData> &game );

	
		void MakeTheBackground( const boost::shared_ptr<Level> &NewLevel, float Height );

	
		static int ForcedReturnEarly;
	
		int SetReturnEarly( const boost::shared_ptr<PieceSeedData> &Piece );


	
		bool Saveable;

		/// <summary>
		/// These special flags add additional properties to levels made by this seed.
		/// </summary>
		#pragma region Special flags
		bool HasWall;
	
		static const std::wstring WallFlag;
	
		bool FadeIn;
		float FadeInSpeed;
		static const std::wstring FadeInFlag;
	
		bool FadeOut;
		float FadeOutSpeed;
		static const std::wstring FadeOutFlag;
	
		float WeatherIntensity;
	
		static const std::wstring WeatherIntensityFlag;
	
		bool NoStartDoor;
	
		static const std::wstring NoStartDoorFlag;
	
		int LevelNum, LevelIndex;
	
		static const std::wstring LevelFlag, IndexFlag;

        bool NewHero; static const std::wstring NewHeroFlag;

		bool RepeatHero; static const std::wstring RepeatHeroFlag;
		int ChapterNameIndex; bool ShowChapterName; static const std::wstring ChapterNameFlag;
		bool GiveScoreScreen; static const std::wstring ScoreScreenFlag;;

        bool Darkness; static const std::wstring DarknessFlag;
        bool Masochistic; static const std::wstring MasochistFlag;

		/// <summary>
		/// How long to wait before opening the initial door.
		/// </summary>
	
		int WaitLengthToOpenDoor;
		bool AlwaysOverrideWaitDoorLength;
		static const std::wstring WaitLengthToOpenDoorString;
	
		bool OpenDoorSound;
	
		static const std::wstring OpenDoorSoundFlag;

		/// <summary>
		/// Song to play when this level starts. Regular sound track will resume on completion.
		/// </summary>
	
		boost::shared_ptr<EzSong> MySong;
	
		static const std::wstring SongString;

		MetaGameType MyMetaGameType;

		void ProcessSpecial();

		static void WaitThenPlay( boost::shared_ptr<GameData> game, int wait, boost::shared_ptr<EzSong> song );

		void _StartSong( const boost::shared_ptr<Level> &level );

		static void _HasWall_Process( const boost::shared_ptr<Level> &level, const boost::shared_ptr<PieceSeedData> &piece );

		static void _SetWeather_Process( const boost::shared_ptr<Level> &level );

		static void _NoStartDoor( const boost::shared_ptr<Level> &level );
		static void _NewHero( const boost::shared_ptr<Level> &level );
		static void _RepeatHero( const boost::shared_ptr<Level> &level );
		static void _ShowChapterName( const boost::shared_ptr<Level> &level );
		static void _ScoreScreen( const boost::shared_ptr<Level> &level );
		static void _FadeIn_Process( const boost::shared_ptr<Level> &level );

		static void _FadeOut_Process( const boost::shared_ptr<Level> &level );
		#pragma endregion

		/// <summary>
		/// Set default parameters for this LevelSeedData assuming we are about to read in parameters from a string.
		/// </summary>
	
		void DefaultRead( const std::wstring &str );

		/// <summary>
		/// Read in parameters from a string.
		/// </summary>
		void ReadString( std::wstring str );

		virtual std::wstring ToString();

		/// <summary>
		/// While reading in parameters from a string, the portion of the string storing upgrade data is stored in this string.
		/// </summary>
	
		std::vector<std::wstring> UpgradeStrs;

		/// <summary>
		/// Modify a PieceSeedData to conform to the upgrade data stored in UpgradeStr.
		/// </summary>
		void ModPieceViaString( const boost::shared_ptr<PieceSeedData> &piece );

		/// <summary>
		/// Modify a PieceSeedData to have random upgrades.
		/// </summary>
		void ModPieceViaHash( const boost::shared_ptr<PieceSeedData> &piece );
		int PieceHash;

		/// <summary>
		/// Make a random hero.
		/// </summary>
		void RandomHero( const boost::shared_ptr<BobPhsx> &Hero, int Hash );

	
		std::wstring SuggestedName();

		static std::wstring GetNameFromSeedStr( const std::wstring &seed );

		/// <summary>
		/// Called when the loading screen is created, just before the level creation algorithm starts.
		/// </summary>
		boost::shared_ptr<Lambda> OnBeginLoad;

		/// <summary>
		/// When true the campaign manager does not add a default PostMake action to this seed.
		/// </summary>
		bool NoDefaultMake;

		/// <summary>
		/// When true this game will not start any music, or stop any previously playing music.
		/// </summary>
		bool NoMusicStart;

		/// <summary>
		/// The created level will loop the given song, starting once the level loads.
		/// </summary>
		void SetToStartSong( const boost::shared_ptr<EzSong> &song );
		void SetToStartSong( const boost::shared_ptr<EzSong> &song, int delay );

		std::wstring Name;

		boost::shared_ptr<Multicaster_1<boost::shared_ptr<Level> > > PostMake;

		/// <summary>
		/// Adds the default GameObjects to a level.
		/// </summary>
		static void AddGameObjects_Default( const boost::shared_ptr<Level> &level, bool global, bool ShowMultiplier );

		/// <summary>
		/// Adds the bare bones GameObjects to a level. (Menu, Perfect)
		/// </summary>
		static void AddGameObjects_BareBones( const boost::shared_ptr<Level> &level, bool global );

		/// <summary>
		/// Standard beginning of level music start.
		/// Shuffles and starts the standard playlist.
		/// </summary>
		static void BOL_StartMusic();

		/// <summary>
		/// Allow the user to load different levels from the menu within this level.
		/// </summary>
		void PostMake_EnableLoad( const boost::shared_ptr<Level> &level );

		void PostMake_StandardLoad( const boost::shared_ptr<Level> &level );

		static void PostMake_Standard( const boost::shared_ptr<Level> &level, bool StartMusic, bool ShowMultiplier );

		static void PostMake_StringWorldStandard( const boost::shared_ptr<Level> &level );

		bool ReleaseWhenLoaded;

		boost::shared_ptr<LockableBool> Loaded;
		bool LoadingBegun;
		boost::shared_ptr<GameData> MyGame;

		LevelGeometry MyGeometry;

		int PieceLength;

		boost::shared_ptr<BobPhsx> DefaultHeroType;

		GameFlags MyGameFlags;

		LavaMakeTypes LavaMake;

		/// <summary>
		/// If true then seed used in the random number generator is never changed.
		/// The level will always be made the same way.
		/// </summary>
		bool LockedSeed;

		/// <summary>
		/// The seed fed into the random number generator.
		/// </summary>
		const int &getSeed() const;
		void setSeed( const int &value );
		boost::shared_ptr<Rand> Rnd;

		boost::shared_ptr<GameFactory> MyGameType;

		std::vector<boost::shared_ptr<PieceSeedData> > PieceSeeds;

		boost::shared_ptr<BackgroundTemplate> MyBackgroundType;
		boost::shared_ptr<TileSet> MyTileSet;

		void SetTileSet( const std::wstring &name );

		void SetTileSet( const boost::shared_ptr<TileSet> &tileset );

		/// <summary>
		/// Reset the seed so that it may be used again.
		/// </summary>
		void Reset();

		void Release();

		void ReleasePieces();

		LevelSeedData( const boost::shared_ptr<LevelSeedData> &data );

		LevelSeedData();

	
		void BaseInit();

	
		int Difficulty, NumPieces, Length;
	
		boost::shared_ptr<Lambda_1<boost::shared_ptr<PieceSeedData> > > MyCustomDifficulty;
	
		void PreInitialize( const boost::shared_ptr<GameFactory> &Type, int Difficulty, int NumPieces, int Length, const boost::shared_ptr<Lambda_1<boost::shared_ptr<PieceSeedData> > > &CustomDiff );

	
		bool Initialized;
	
		void Init();

		/// <summary>
		/// Prevent unreasonable or dangerous parameter combinations.
		/// </summary>
	
		void Sanitize();

	
		void StandardInit( const boost::shared_ptr<Lambda_2<boost::shared_ptr<PieceSeedData>, boost::shared_ptr<Upgrades> > > &CustomDiff );
		void Initialize( const boost::shared_ptr<Lambda_1<boost::shared_ptr<PieceSeedData> > > &CustomDiff );
		void Initialize( const boost::shared_ptr<GameFactory> &factory, LevelGeometry geometry, int NumPieces, int Length, const boost::shared_ptr<Lambda_1<boost::shared_ptr<PieceSeedData> > > &CustomDiff );

		float CalcPieceLength( const boost::shared_ptr<PieceSeedData> &data );

		void InitNormal( bool Place, const boost::shared_ptr<Lambda_1<boost::shared_ptr<PieceSeedData> > > &CustomDiff );

		void InitPlace( const boost::shared_ptr<Lambda_1<boost::shared_ptr<PieceSeedData> > > &CustomDiff );

	
		boost::shared_ptr<Level> MakeNewLevel( const boost::shared_ptr<GameData> &game );

	
		boost::shared_ptr<GameData> Create();
		boost::shared_ptr<GameData> Create( bool MakeInBackground );

	
		void InitializeInstanceFields();

	};

}

#endif	//#ifndef CLOUDBERRYKINGDOM_LEVELSEEDDATA
