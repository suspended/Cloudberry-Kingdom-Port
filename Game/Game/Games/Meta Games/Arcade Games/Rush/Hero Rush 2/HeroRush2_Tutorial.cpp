#include "HeroRush2_Tutorial.h"
#include "Game/Games/Meta Games/Arcade Games/Rush/Hero Rush 2/HeroRush2.h"
#include "Game/Localization.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Text.h"

using namespace Microsoft::Xna::Framework;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;

namespace CloudberryKingdom
{

	HeroRush2_Tutorial::HeroRush2_Tutorial( const std::shared_ptr<Challenge_HeroRush2> &HeroRush2 ) : HeroRush_Tutorial( HeroRush2 )
	{
		this->HeroRush2 = HeroRush2;
	}

	void HeroRush2_Tutorial::Title()
	{
		ShowTitle = false;

		std::shared_ptr<GUI_Text> text = GUI_Text::SimpleTitle( Localization::Words_HYBRID_RUSH );
		text->MyText->setPos( text->MyText->getPos() + Vector2(0, -110) );

		MyGame->AddGameObject( text );
		MyGame->WaitThenDo( 0, std::make_shared<AddGameObjectHelper>( this, text ) );
	}
}