#ifndef MULTIPLIERUP
#define MULTIPLIERUP

#include <small_header.h>

//#include "Core/Graphics/Draw/DrawPile.h"
//#include "Game/Localization.h"
//#include "Core/Text/EzText.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Panel.h"
//#include "Game/Tools/CkColorHelper.h"
//#include "Game/Tools/Resources.h"


namespace CloudberryKingdom
{

	struct MultiplierUp : public GUI_Panel
	{

		virtual ~MultiplierUp()
		{
#ifdef BOOST_BIN
			OnDestructor( "MultiplierUp" );
#endif
		}

	
		virtual void OnAdd();

		boost::shared_ptr<EzText> text;
	
		MultiplierUp();
		boost::shared_ptr<MultiplierUp> MultiplierUp_Construct();
		MultiplierUp( Vector2 shift, float scale, bool perma );
		boost::shared_ptr<MultiplierUp> MultiplierUp_Construct( Vector2 shift, float scale, bool perma );

	
		bool Perma;
		void Init( Vector2 shift, float scale, bool perma );

		int Count;
	
		virtual void MyPhsxStep();

	
		void InitializeInstanceFields();
	};

}


#endif	//#ifndef MULTIPLIERUP
