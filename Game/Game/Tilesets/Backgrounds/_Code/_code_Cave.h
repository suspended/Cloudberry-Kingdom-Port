﻿#ifndef _CODE_CAVE
#define _CODE_CAVE

#include "../Game/Tilesets/Backgrounds/Background.h"
#include <string>

namespace CloudberryKingdom
{
	class Background;
}


using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class Background_Cave : public BackgroundTemplate
	{
	public:
		Background_Cave( const std::wstring &Name );

		virtual void Code( const std::shared_ptr<Background> &b );
	};

}


#endif	//#ifndef _CODE_CAVE