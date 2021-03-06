#ifndef GUI_LEVEL
#define GUI_LEVEL

#include <small_header.h>

//#include "Core/Graphics/Draw/DrawPile.h"
#include "Game/Localization.h"
//#include "Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h"
//#include "Core/Text/EzFont.h"
//#include "Core/Text/EzText.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Panel.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Tools/Resources.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{

	struct GUI_Level : public GUI_Panel
	{
	
		virtual ~GUI_Level()
		{
#ifdef BOOST_BIN
			OnDestructor( "GUI_Level" );
#endif
		}


		Localization::Words Prefix;

		/// <summary>
		/// Return a string representation of the Level
		/// </summary>
		virtual std::wstring ToString();

	
		bool DoSlideIn;

		bool AddedOnce;
	
		virtual void OnAdd();

		virtual void ReleaseBody();
	
		int Level_Renamed;
	
		void SetLevel( int Level_Renamed );

		boost::shared_ptr<EzText> LevelText;
	
		void UpdateLevelText();

	

		GUI_Level( bool TimeCrisis );
		boost::shared_ptr<GUI_Level> GUI_Level_Construct( bool TimeCrisis );

		GUI_Level( int LevelNum );
		boost::shared_ptr<GUI_Level> GUI_Level_Construct( int LevelNum );

	
		void DoInit( bool SlideIn, bool TimeCrisis );

	
		virtual void MyDraw();

		virtual void MyPhsxStep();

	
		void InitializeInstanceFields();
	};

	struct GUI_CampaignLevel : public GUI_Level
	{

		virtual ~GUI_CampaignLevel()
		{
#ifdef BOOST_BIN
			OnDestructor( "GUI_CampaignLevel" );
#endif
		}

	
		GUI_CampaignLevel();
		boost::shared_ptr<GUI_CampaignLevel> GUI_CampaignLevel_Construct();

		virtual void OnAdd();

		virtual std::wstring ToString();
	};
}


#endif	//#ifndef GUI_LEVEL
