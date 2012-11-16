﻿#ifndef MENUTOGGLE
#define MENUTOGGLE

#include "MenuItem.h"
#include <tchar.h>

namespace CloudberryKingdom
{
	class EzFont;
}

namespace CloudberryKingdom
{
	class Lambda_1;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

namespace CloudberryKingdom
{
	class MenuToggle : public MenuItem
	{
	public:
		MenuToggle( const std::shared_ptr<EzFont> &Font );

	private:
		bool MyState;
	public:
		void Toggle( bool state );

		std::shared_ptr<Lambda_1<bool> > OnToggle;
		virtual void PhsxStep( bool Selected );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef MENUTOGGLE