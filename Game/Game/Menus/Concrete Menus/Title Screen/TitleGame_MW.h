#ifndef TITLEGAME_MW
#define TITLEGAME_MW

#include <small_header.h>

#include "Game/Games/GameType.h"
//#include "Game/Menus/Concrete Menus/Title Screen/StartMenu_MW_Backpanel.h"
//#include "Game/Menus/Concrete Menus/Title Screen/StartMenu_MW_PressStart.h"
#include "Game/Menus/Concrete Menus/Title Screen/TitleGameBase.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Objects/Special/CameraZone.h"
//#include "Game/Tools/Camera.h"
//#include "Game/Tools/Recycler.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{
	struct TitleGameData_MW_Factory : public SimpleGameFactory
	{

	
		virtual ~TitleGameData_MW_Factory()
		{
#ifdef BOOST_BIN
			OnDestructor( "TitleGameData_MW_Factory" );
#endif
		}


		virtual boost::shared_ptr<GameData> Make();

	};

	struct TitleGameData_MW : public TitleGameData
	{
	
		virtual ~TitleGameData_MW()
		{
#ifdef BOOST_BIN
			OnDestructor( "TitleGameData_MW" );
#endif
		}

	
		static void InitializeStatics();
	
		struct _InitProxy : public Lambda
		{
		
			boost::shared_ptr<TitleGameData_MW> tgdmw;

		
			_InitProxy( const boost::shared_ptr<TitleGameData_MW> &tgdmw );

			void Apply();
		};

	
		static boost::shared_ptr<SimpleGameFactory> Factory;

		virtual void Release();

		TitleGameData_MW();

		virtual void SetToReturnTo( int code );

		virtual void ReturnTo( int code );

	
		virtual boost::shared_ptr<Level> MakeLevel();

	
		boost::shared_ptr<StartMenu_MW_Backpanel> BackPanel;
		boost::shared_ptr<StartMenu_MW_PressStart> PressStart;
		virtual void Init();

	
		void _Init();

	
		virtual void AdditionalReset();

		virtual void PhsxStep();

		virtual void PostDraw();
	};
}


#endif	//#ifndef TITLEGAME_MW
