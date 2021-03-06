#ifndef CLOUDBERRYKINGDOM_CLOUDBERRYKINGDOMGAME
#define CLOUDBERRYKINGDOM_CLOUDBERRYKINGDOMGAME

#define MEM_DEBUG

#if defined( MEM_DEBUG ) && defined( WINDOWS )
	#include <stdlib.h>
	#include <crtdbg.h>
	#include <errno.h>
#endif


#include <small_header.h>

//#include "Core/ResolutionGroup.h"
//#include "Core/Graphics/MainRender.h"
//#include "Core/Graphics/QuadDrawer.h"
//#include "Core/Graphics/Draw/Quads/QuadClass.h"
#include "Game/Localization.h"
//#include "Game/Tilesets/Backgrounds/Background.h"
//#include "Game/Tools/IntVector2.h"
//#include "Core/Input/ButtonCheck.h"
//#include "Core/Particle Effects/Specific Effects/CloudberryKingdom.ParticleEffects.h"
//#include "Core/Sound/EzSoundWad.h"
//#include "Core/Text/EzText.h"
//#include "Core/Texture/EzTexture.h"
//#include "Game/Objects/ObjectBase.h"
//#include "Game/Objects/In Game Objects/Blocks/Block.h"
//#include "Game/Games/GameType.h"
//#include "Game/Games/NormalGame.h"
//#include "Game/Games/ScreenSaver.h"
//#include "Game/Games/Meta Games/StringWorlds/LevelConnector.h"
//#include "Game/Level/Make/LockableBool.h"
//#include "Game/Level/Make/ComputerRecording.h"
//#include "Game/Level/Make/LevelSeedData.h"
//#include "Game/Level/Make/PieceSeedData.h"
//#include "Game/Level/Make/Parameters/RandomDifficulty.h"
//#include "Game/Level/Make/Parameters/StyleData/StyleData.h"
//#include "Game/Menus/Menu.h"
//#include "Game/Menus/Concrete Menus/CharacterSelect/CharSelectManager.h"
//#include "Game/Tools/EzStorage.h"
//#include "Game/Player/PlayerManager.h"
//#include "Game/Menus/Concrete Menus/InGameStartMenus/InGameStartMenu.h"
//#include "Game/Menus/Menu Components/MenuItem.h"
//#include "Game/Menus/Concrete Menus/Loading Screen/Loading.h"
//#include "Game/Menus/Concrete Menus/Loading Screen/LoadingScreen.h"
//#include "Game/Menus/Concrete Menus/Score Screens/ScoreEntry.h"
//#include "Game/Menus/Concrete Menus/Title Screen/StartMenu.h"
//#include "Game/Menus/Concrete Menus/Title Screen/TitleGame_MW.h"
//#include "Game/Player/Hero Physics/Base.h"
//#include "Game/Objects/AutoGen.h"
//#include "Game/Objects/Bob/Bob.h"
//#include "Game/Objects/Door/Door.h"
//#include "Game/Menus/Concrete Menus/Help/HelpMenu.h"
//#include "Game/Menus/Concrete Menus/Help/HintGiver.h"
//#include "Game/Objects/In Game Objects/Blocks/BouncyBlock__Auto.h"
//#include "Game/Objects/In Game Objects/Blocks/FallingBlock__Auto.h"
//#include "Game/Objects/In Game Objects/Blocks/MovingBlock.h"
//#include "Game/Objects/In Game Objects/Blocks/MovingBlock__Auto.h"
//#include "Game/Objects/In Game Objects/Blocks/NormalBlock.h"
//#include "Game/Objects/In Game Objects/Blocks/NormalBlock__Auto.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Objects/In Game Objects/Grab/Coin.h"
//#include "Game/Objects/In Game Objects/Obstacles/CloudberryKingdom.Fireball.h"
//#include "Game/Objects/In Game Objects/Obstacles/FlyingBlob__Auto.h"
//#include "Game/Objects/Special/CameraZone.h"
//#include "Game/Player/PlayerData.h"
//#include "Game/Player/Hero Physics/Normal.h"
//#include "Game/Tools/Camera.h"
//#include "Game/Tools/Globals.h"
//#include "Game/Tools/Resources.h"
#include "Game/Tools/Tools.h"


#include "Hacks/XNA/GraphicsDevice.h"
#include "Hacks/XNA/GraphicsDeviceManager.h"
#include "Hacks/XNA/PreparingDeviceSettingsEventArgs.h"
#include "Hacks/XNA/GameTime.h"
#include "Hacks/NET/Stopwatch.h"
#include "Hacks/NET/StringBuilder.h"

struct SmallErrorMenu;

namespace CloudberryKingdom
{


	enum Presence { Presence_TitleScreen, Presence_Escalation, Presence_TimeCrisis, Presence_HeroRush, Presence_HeroRush2, Presence_Freeplay, Presence_Campaign, Presence_Arcade };
	enum MainMenuTypes { MainMenuTypes_PC, MainMenuTypes_Xbox, MainMenuTypes_PS3, MainMenuTypes_WiiU, MainMenuTypes_Vita };

	struct CloudberryKingdomGame : public boost::enable_shared_from_this<CloudberryKingdomGame>
	{

		static bool CampaignProgressMade;
		
#if PS3
		static bool CaveDoneLoading;
#endif

#if defined(DEBUG)
		static int _count;
		static int address;
#endif

        static boost::shared_ptr<EzText> SavingText;
        static int ShowSavingDuration;

		static void ShowSaving();
        void DrawSavingText();

		static void memdebug_DumpStart();
		static void memdebug_DumpEnd();

	
		static void StaticIntializer_NoDependence();
		static void StaticIntializer_AfterResourcesLoad();


		static bool DigitalDayBuild;

		static bool ChoseNotToSave;
		static bool PastPressStart;
		static bool CanSave();

		static bool CanSave( PlayerIndex index );

        static void ChangeSaveGoFunc( boost::shared_ptr<MenuItem> item );
        static void ShowError_CanNotSaveLevel_NoSpace();

		static void ShowError_CanNotSaveNoDevice();

		static bool ProfilesAvailable();

		static bool OnlineFunctionalityAvailable();

		static void BeginShowMarketplace();

		static Presence CurrentPresence;
		static void SetPresence(Presence presence);

		static int Freeplay_Count;
		static int Freeplay_Max;



































	
		struct ExitProxy : public Lambda
		{
		
			boost::shared_ptr<CloudberryKingdomGame> ckg;

		
			ExitProxy( const boost::shared_ptr<CloudberryKingdomGame> &ckg );

			void Apply();
		};

	
		struct UpdateVolumeProxy : public Lambda
		{
		
			void Apply();
		};

	
		struct MakeTestLevelInitializeHelper : public Lambda_1<boost::shared_ptr<PieceSeedData> >
		{
		
			boost::shared_ptr<CloudberryKingdomGame> ckg;

		
			MakeTestLevelInitializeHelper( const boost::shared_ptr<CloudberryKingdomGame> &ckg );

			void Apply( const boost::shared_ptr<PieceSeedData> &piece );
		};

	
		struct TestLevelPostMakeProxy : public Lambda_1<boost::shared_ptr<Level> >
		{
		
			boost::shared_ptr<CloudberryKingdomGame> ckg;
		
			TestLevelPostMakeProxy( const boost::shared_ptr<CloudberryKingdomGame> &ckg );

			void Apply( const boost::shared_ptr<Level> &level );
		};

		/// <summary>
		/// The version of the game we are working on now (+1 over the last version uploaded to Steam).
		/// MajorVersion is 0 for beta, 1 for release.
		/// MinorVersion increases with substantial change.
		/// SubVersion increases with any pushed change.
		/// </summary>
	
		static Version GameVersion;




		// Flags
		static bool GodMode;
		static bool HideLogos;
		static bool LockCampaign;
		static bool SimpleMainMenu;
		static MainMenuTypes MainMenuType;
		static bool SimpleLeaderboards;
		static bool AsianButtonSwitch;
		static bool FakeAwardments;
		static float GuiSqueeze;



        static bool ForFrapsRecording;

        static bool AlwaysGiveTutorials;
        static bool Unlock_Customization;
        static bool Unlock_Levels;

        static bool getIsDemo();

        static void OfferToBuy();










		/// <summary>
		/// The command line arguments.
		/// </summary>
		static std::vector<std::wstring> args;

		static bool StartAsBackgroundEditor;
		static bool StartAsTestLevel;
		static bool StartAsBobAnimationTest;
		static bool StartAsFreeplay;
#if defined(INCLUDE_EDITOR)
		static bool LoadDynamic;
#else
		static bool LoadDynamic;
#endif
		static bool ShowSongInfo;

		static std::wstring TileSetToTest;
		static std::wstring ModRoot;
		static bool AlwaysSkipDynamicArt;

		static bool HideGui;
		static bool HideForeground;
		static bool UseNewBob;

		//public static SimpleGameFactory TitleGameFactory = TitleGameData_Intense.Factory;
		static boost::shared_ptr<SimpleGameFactory> TitleGameFactory;
		//public static SimpleGameFactory TitleGameFactory = TitleGameData_Forest.Factory;

		static float fps;

		int DrawCount, PhsxCount;

		ResolutionGroup Resolution;
		std::vector<ResolutionGroup> Resolutions;

#if defined(WINDOWS)
		boost::shared_ptr<QuadClass> MousePointer, MouseBack;
	
		bool _DrawMouseBackIcon;
	
		const bool &getDrawMouseBackIcon() const;
		void setDrawMouseBackIcon( const bool &value );
#endif

		bool LogoScreenUp;

		/// <summary>
		/// When true the initial loading screen is drawn even after loading is finished
		/// </summary>
	
		bool LogoScreenPropUp;

		/// <summary>
		/// The game's initial loading screen. Different than the in-game loading screens seen before levels.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The variable LoadingScreen was renamed since it is named the same as a user-defined type:
		boost::shared_ptr<InitialLoadingScreen> LoadingScreen_Renamed;

		boost::shared_ptr<GraphicsDevice> MyGraphicsDevice;
		boost::shared_ptr<GraphicsDeviceManager> MyGraphicsDeviceManager;

	
		int ScreenWidth, ScreenHeight;

		boost::shared_ptr<Camera> MainCamera;

//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//		public event EventHandler<EventArgs> Exiting
//		{
//			add
//			{
//				Tools::GameClass.Exiting += value;
//			}
//			remove
//			{
//				Tools::GameClass.Exiting -= value;
//			}
//		}

	
		void Exit();

		/// <summary>
		/// Process the command line arguments.
		/// This is used to load different tools, such as the background editor, instead of the main game.
		/// </summary>
		/// <param name="args"></param>
		static void ProcessArgs( std::vector<std::wstring> &args );

		CloudberryKingdomGame();

	
		void graphics_PreparingDeviceSettings( const boost::shared_ptr<Object> &sender, const boost::shared_ptr<PreparingDeviceSettingsEventArgs> &e );

	
		void Initialize();

		void InitialResolution();

#if defined(NOT_PC) && (defined(XBOX) || defined(XBOX_SIGNIN))
	
		void SignedInGamer_SignedOut( const boost::shared_ptr<Object> &sender, const boost::shared_ptr<SignedOutEventArgs> &e );

		void SignedInGamer_SignedIn( const boost::shared_ptr<Object> &sender, const boost::shared_ptr<SignedInEventArgs> &e );
#endif

	
		void LoadContent();

	
		void UnloadContent();

	
		void DoQuickSpawn();

		/// <summary>
		/// The current game being played.
		/// </summary>
		const boost::shared_ptr<GameData> &getGame() const;

		/// <summary>
		/// Update the current game.
		/// </summary>
		void DoGameDataPhsx();

		/// <summary>
		/// A list of actions to perform. Each time an action is peformed it is removed from the list.
		/// </summary>
	
		boost::shared_ptr<Multicaster> ToDo;

	
		void DoToDoList();

		void GodModePhxs();

		void PhsxStep();

#if defined(WINDOWS)
	
		void CheckForQuickSpawn_PC();
#endif

		void CheckForQuickSpawn_Xbox();

#if defined(WINDOWS)
		/// <summary>
		/// Whether the mouse should be allowed to be shown, usually only when a menu is active.
		/// </summary>
	
		bool ShowMouse;

		/// <summary>
		/// Draw the mouse cursor.
		/// </summary>
	
		void MouseDraw();
#endif

		/// <summary>
		/// Whether a song was playing prior to the game window going inactive
		/// </summary>
	
		bool MediaPlaying_HoldState;

		/// <summary>
		/// Whether this is the first frame the window has been inactive
		/// </summary>
		bool FirstInactiveFrame;

		/// <summary>
		/// Whether this is the first frame the window has been active
		/// </summary>
		bool FirstActiveFrame;

		double DeltaT;

		void Update();















		static bool ShowMarketplace;
        static bool ShowErrorMessage;


		static void ShowError_LoadError();

		static void ShowError_MustBeSignedIn(Localization::Words word);

        static void ShowError_MustBeSignedInToLive(Localization::Words word);

        static void ShowError_MustBeSignedInToLiveForLeaderboard();

        static bool IsNetworkCableUnplugged();

        static void ShowError(Localization::Words Header, Localization::Words Text, Localization::Words Option1/*, AsyncCallback callback*/);

        static Localization::Words Err_Header, Err_Text;
        static std::vector<std::wstring> Err_Options;
        //AsyncCallback Err_Callback;

        static void _ShowError();

		bool DisconnectedController();

		static bool getSuperPause();

        static boost::shared_ptr<SmallErrorMenu> SmallErrorMessage;
        static void ShowSmallError();

        static bool CustomMusicPlaying;
        void UpdateCustomMusic();

        /// <summary>
        /// If a gamer has no save device selected, ask them to select one.
        /// </summary>
        static void PromptForDeviceIfNoneSelected();













		/// <summary>
		/// The main draw loop.
		/// Sets all the rendering up and determines which sub-function to call (game, loading screen, nothing, etc).
		/// Also updates the game logic. TODO: Seperate this from the draw function?
		/// </summary>
		/// <param name="gameTime"></param>
		void Draw( const boost::shared_ptr<GameTime> &gameTime );

		/// <summary>
		/// Non-game drawing, such as debug info and tool drawing.
		/// </summary>
	
		void DrawExtra();

		/// <summary>
		/// Draws the load screen, assuming the game should not be drawn this frame.
		/// </summary>
		void DrawLoading();

		/// <summary>
		/// Draws nothing (black). Called when the game shouldn't be shown, nor anything else, such as load screens.
		/// </summary>
		void DrawNothing();

		/// <summary>
		/// Draws the actual the game, not any loading screens or other non-game graphics.
		/// </summary>
		void DrawGame();

		/// <summary>
		/// The update function called for the actual game, not for loading screens or other non-game functions.
		/// </summary>
		/// <param name="gameTime"></param>
		void GameUpdate( const boost::shared_ptr<GameTime> &gameTime );

		void UpdateFps( const boost::shared_ptr<GameTime> &gameTime );

		/// <summary>
		/// Sets up the renderer. Returns true if no additional drawing should be done, because the game does not have focus.
		/// </summary>
		/// <returns></returns>
		bool SetupToRender();

		/// <summary>
		/// Draw the fireball textures to memory.
		/// </summary>
		void ComputeFire();

#if defined(WINDOWS)
		/// <summary>
		/// Decide if the game should be active or not.
		/// </summary>
		/// <returns>Returns true if the game is active.</returns>
		bool ActiveInactive();
#endif


		void BenchmarkAll();

		static boost::shared_ptr<Stopwatch> stopwatch;
		static void Start();
		static long long Stop();

		static boost::shared_ptr<Stopwatch> stopwatch2;
		static void Start2();
		static long long Stop2();


		static void BenchmarkLoadSize();
		bool ShowFPS;

#if defined(DEBUG)
		/// <summary>
		/// Extra functions that allow a user to better debug/test/
		/// </summary>
		/// <returns>Return true if the calling method should return.</returns>
		bool DebugModePhsx();
#endif

	
		static std::wstring debugstring;
	
		boost::shared_ptr<StringBuilder> MainString;

		/// <summary>
		/// Method for drawing various debug information to the screen.
		/// </summary>
		void DrawDebugInfo();


		void MakeEmptyLevel();

		void MakeTestLevel();

		void TestLevelPostMake( const boost::shared_ptr<Level> &level );

		void TestLevelInit( const boost::shared_ptr<PieceSeedData> &piece );

		static void __Roughly_Maso( const boost::shared_ptr<PieceSeedData> &piece );

		static void __Roughly_Abusive( const boost::shared_ptr<PieceSeedData> &piece );

		void TestLevelModParams( const boost::shared_ptr<Level> &level, const boost::shared_ptr<PieceSeedData> &p );


		bool DoInnerLogoPhsx;
		void LogoPhsx();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef CLOUDBERRYKINGDOM_CLOUDBERRYKINGDOMGAME
