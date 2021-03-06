#include <small_header.h>
#include "Game/Menus/Concrete Menus/Help/HelpMenu.h"

#include "Core/Graphics/Draw/DrawPile.h"
#include "Core/Graphics/Draw/Quads/QuadClass.h"
#include "Game/Localization.h"
#include "Core/Input/ButtonCheck.h"
#include "Core/Text/EzText.h"
#include "Game/Objects/Game Objects/GameObject.h"
#include "Game/Menus/CkBaseMenu.h"
#include "Game/Games/GameType.h"
#include "Game/Games/Meta Games/Challenges/Challenge_Base.h"
#include "Game/Menus/Menu.h"
#include "Game/Menus/Concrete Menus/Help/HelpBlurb.h"
#include "Game/Player/PlayerManager.h"
#include "Game/Menus/Concrete Menus/InGameStartMenus/InGameStartMenu.h"
#include "Game/Menus/Menu Components/MenuItem.h"
#include "Game/Menus/Menu Components/MenuToggle.h"
#include "Game/Objects/Icon.h"
#include "Game/Objects/Game Objects/GameObjects/Guide.h"
#include "Game/Objects/Game Objects/GameObjects/Listener.h"
#include "Game/Objects/Game Objects/GameObjects/SlowMo.h"
#include "Game/Menus/Concrete Menus/Help/HintGiver.h"
#include "Game/Objects/In Game Objects/Grab/MakeData.h"
#include "Game/Level/Level.h"
#include "Game/Objects/In Game Objects/Grab/Coin.h"
#include "Game/Player/Awardments/Awardment.h"
#include "Game/Tools/Resources.h"
#include "Game/Tools/Tools.h"

#include "Game/Player/PlayerData.h"

namespace CloudberryKingdom
{

	int HelpMenu::CostMultiplier = 1;

	HelpMenu::MakeListenerHelper::MakeListenerHelper( const boost::shared_ptr<Listener> &listener )
	{
		this->listener = listener;
	}

	void HelpMenu::MakeListenerHelper::Apply()
	{
		if ( Tools::StepControl )
			return;

		boost::shared_ptr<Level> level = Tools::CurLevel;
		if ( !level->Replay && !level->Watching && !level->Finished && !level->PreventHelp )
			listener->Call( MakeMagic( HelpMenu, () ) );
	}

	HelpMenu::ReturnToCallerProxy::ReturnToCallerProxy( const boost::shared_ptr<HelpMenu> &hm )
	{
		this->hm = hm;
	}

	void HelpMenu::ReturnToCallerProxy::Apply()
	{
		hm->ReturnToCaller();
	}

	HelpMenu::WatchComputerHelper::WatchComputerHelper( const boost::shared_ptr<HelpMenu> &hm )
	{
		this->hm = hm;
	}

	void HelpMenu::WatchComputerHelper::Apply()
	{
		hm->MyGame->MyLevel->WatchComputer();
	}

	HelpMenu::WatchComputerProxy::WatchComputerProxy( const boost::shared_ptr<HelpMenu> &hm )
	{
		this->hm = hm;
	}

	void HelpMenu::WatchComputerProxy::Apply()
	{
		hm->WatchComputer();
	}

	HelpMenu::IsShowGuidLambda::IsShowGuidLambda()
	{
	}

	bool HelpMenu::IsShowGuidLambda::Apply( const boost::shared_ptr<GameObject> &obj )
	{
		return boost::dynamic_pointer_cast<ShowGuide>( obj ) != 0;
	}

	HelpMenu::IsSlowMoLambda::IsSlowMoLambda()
	{
	}

	bool HelpMenu::IsSlowMoLambda::Apply( const boost::shared_ptr<GameObject> &obj )
	{
		return boost::dynamic_pointer_cast<CloudberryKingdom::SlowMo>( obj ) != 0;
	}

	HelpMenu::Toggle_ShowPathHelper::Toggle_ShowPathHelper( const boost::shared_ptr<HelpMenu> &hm )
	{
		this->hm = hm;
	}

	void HelpMenu::Toggle_ShowPathHelper::Apply()
	{
		for ( GameObjVec::const_iterator go = hm->MyGame->MyGameObjects.begin(); go != hm->MyGame->MyGameObjects.end(); ++go )
		{
			if ( boost::dynamic_pointer_cast<ShowGuide>( *go ) != 0 )
				( *go )->Release();
		}
	}

	HelpMenu::Toggle_ShowPathSetter::Toggle_ShowPathSetter( const boost::shared_ptr<HelpMenu> &hm, bool state )
	{
		this->hm = hm;
		this->state = state;
	}

	void HelpMenu::Toggle_ShowPathSetter::Apply()
	{
		hm->Toggle_ShowPath( state );
	}

	HelpMenu::Toggle_ShowPathProxy::Toggle_ShowPathProxy( const boost::shared_ptr<HelpMenu> &hm )
	{
		this->hm = hm;
	}

	void HelpMenu::Toggle_ShowPathProxy::Apply( const bool &state )
	{
		hm->Toggle_ShowPath( state );
	}

	HelpMenu::ShowPathProxy::ShowPathProxy( const boost::shared_ptr<HelpMenu> &hm )
	{
		this->hm = hm;
	}

	void HelpMenu::ShowPathProxy::Apply()
	{
		hm->ShowPath();
	}

	bool HelpMenu::Toggle_SloMoHelperPredicate::Apply( const boost::shared_ptr<GameObject> &match )
	{
		return boost::dynamic_pointer_cast<CloudberryKingdom::SlowMo>( match ) != 0;
	}

	HelpMenu::Toggle_SloMoHelper::Toggle_SloMoHelper( const boost::shared_ptr<HelpMenu> &hm )
	{
		this->hm = hm;
	}

	void HelpMenu::Toggle_SloMoHelper::Apply()
	{
		Tools::RemoveAll<boost::shared_ptr<GameObject> >( hm->MyGame->MyGameObjects, boost::make_shared<Toggle_SloMoHelperPredicate>() );
	}

	HelpMenu::Toggle_SlowMoProxy::Toggle_SlowMoProxy( const boost::shared_ptr<HelpMenu> &hm )
	{
		this->hm = hm;
	}

	void HelpMenu::Toggle_SlowMoProxy::Apply( const bool &state )
	{
		hm->Toggle_SlowMo( state );
	}

	HelpMenu::SlowMoProxy::SlowMoProxy( const boost::shared_ptr<HelpMenu> &hm )
	{
		this->hm = hm;
	}

	void HelpMenu::SlowMoProxy::Apply()
	{
		hm->DoSlowMo();
	}

	int HelpMenu::CampaignCoinsLambda::Apply( const boost::shared_ptr<PlayerData> &p )
	{
		return p->CampaignCoins;
	}

	int HelpMenu::Bank()
	{
		switch ( MyGame->MyBankType )
		{
			case GameData::BankType_INFINITE:
				return 999;

			case GameData::BankType_ESCALATION:
                return Challenge::Coins;

			case GameData::BankType_CAMPAIGN:
				return PlayerManager::PlayerMax( boost::make_shared<CampaignCoinsLambda>() );
		}

		return 0;
	}

	void HelpMenu::Buy( int Cost )
	{
		std::vector<boost::shared_ptr<PlayerData> > vec;

		switch ( MyGame->MyBankType )
		{
			case GameData::BankType_ESCALATION:
                Challenge::Coins -= Cost;
                break;

			case GameData::BankType_CAMPAIGN:
				vec = PlayerManager::getExistingPlayers();
				for ( std::vector<boost::shared_ptr<PlayerData> >::const_iterator p = vec.begin(); p != vec.end(); ++p )
					( *p )->CampaignCoins = __max( ( *p )->CampaignCoins - Cost, 0 );
				break;

			case GameData::BankType_INFINITE:
				break;
		}

		Awardments::CheckForAward_Buy();
		//PlayerManager::CoinsSpent += Cost;

		SetCoins( Bank() );
	}

	void HelpMenu::SetCoins( int Coins )
	{
		//if ( Coins > 99 ) Coins = 99;
		CoinsText->SubstituteText( std::wstring( L"x" ) + StringConverterHelper::toString( Coins ) );
	}

	void HelpMenu::SetItemProperties( const boost::shared_ptr<MenuItem> &item )
	{
		CkBaseMenu::SetItemProperties( item );

		item->MyText->Shadow = item->MySelectedText->Shadow = false;
		item->MyText->PicShadow = item->MySelectedText->PicShadow = false;
	}

	HelpMenu::HelpMenu() :
		DelayExit( 0 )
	{
	}

	boost::shared_ptr<HelpMenu> HelpMenu::HelpMenu_Construct()
	{
		InitializeInstanceFields();

		CkBaseMenu::CkBaseMenu_Construct();

		// Note that help was used, so that no hint is given about it
		Hints::SetYForHelpNum( 999 );

		return boost::static_pointer_cast<HelpMenu>( shared_from_this() );
	}

	boost::shared_ptr<GameObject> HelpMenu::MakeListener()
	{
		boost::shared_ptr<Listener> listener = MakeMagic( Listener, () );
		listener->setControl( -1 );
		listener->MyButton = ControllerButtons_Y;
		listener->MyButton2 = ButtonCheck::Help_KeyboardKey;
		listener->MyAction = boost::make_shared<MakeListenerHelper>( listener );

		return listener;
	}

	void HelpMenu::ReturnToCaller()
	{
		InGameStartMenu::PreventMenu = false;

		if ( Active )
		{
			Active = false;
			MyGame->WaitThenDo( DelayExit, boost::make_shared<ReturnToCallerProxy>( boost::static_pointer_cast<HelpMenu>( shared_from_this() ) ) );
		}
		else
			CkBaseMenu::ReturnToCaller();
	}

	bool HelpMenu::MenuReturnToCaller( const boost::shared_ptr<Menu> &menu )
	{
		DelayExit = 0;

		return CkBaseMenu::MenuReturnToCaller( menu );
	}





		CostGrowthTypes HelpMenu::CostGrowthType = CostGrowthTypes_None;
		int HelpMenu::Cost_Multiplier_Watch = 1, HelpMenu::Cost_Multiplier_Path = 1, HelpMenu::Cost_Multiplier_Slow = 1;

		void HelpMenu::SetCostGrowthType(CostGrowthTypes type)
		{
			CostGrowthType = type;

			Cost_Multiplier_Watch = 1;
			Cost_Multiplier_Path = 1;
			Cost_Multiplier_Slow = 1;
		}

		int HelpMenu::CurrentCostTo_Watch()
		{
			return Cost_Watch * CostMultiplier * Cost_Multiplier_Watch;
		}

		int HelpMenu::CurrentCostTo_Slow()
		{
			return Cost_Slow * CostMultiplier * Cost_Multiplier_Slow;
		}

		int HelpMenu::CurrentCostTo_Path()
		{
			return Cost_Path * CostMultiplier * Cost_Multiplier_Path;
		}


		int HelpMenu::Cost_Watch = 5, HelpMenu::Cost_Path = 40, HelpMenu::Cost_Slow = 20;



	bool HelpMenu::Allowed_WatchComputer()
	{
		return MyGame->MyLevel->WatchComputerEnabled() && Bank() >= CurrentCostTo_Watch();
	}

	void HelpMenu::WatchComputer()
	{
		if ( !Allowed_WatchComputer() )
			return;

		Buy( CurrentCostTo_Watch() );

		if ( CostGrowthType == CostGrowthTypes_DoublePerBuy )
			Cost_Multiplier_Watch *= 2;

		ReturnToCaller();
		MyGame->WaitThenDo( DelayExit - 10, boost::make_shared<WatchComputerHelper>( boost::static_pointer_cast<HelpMenu>( shared_from_this() ) ) );
	}

	bool HelpMenu::On_ShowPath()
	{
		return Tools::Any<boost::shared_ptr<GameObject> >( Tools::CurGameData->MyGameObjects, boost::make_shared<IsShowGuidLambda>() );
	}

	bool HelpMenu::Allowed_ShowPath()
	{
	#if defined(DEBUG)
		return MyGame->MyLevel->WatchComputerEnabled();
	#else
		return MyGame->MyLevel->CanWatchComputer && Bank() >= CurrentCostTo_Path();
	#endif
	}

	void HelpMenu::Toggle_ShowPath( bool state )
	{
		if ( state )
		{
			boost::shared_ptr<ShowGuide> guide = MakeMagic( ShowGuide, () );

			MyGame->AddGameObject( guide );
		}
		else
		{
			for ( GameObjVec::const_iterator obj = MyGame->MyGameObjects.begin(); obj != MyGame->MyGameObjects.end(); ++obj )
				if ( boost::dynamic_pointer_cast<ShowGuide>( *obj ) != 0 )
					( *obj )->Release();
			MyGame->AddToDo( boost::make_shared<Toggle_ShowPathHelper>( boost::static_pointer_cast<HelpMenu>( shared_from_this() ) ) );
		}
	}

	void HelpMenu::ShowPath()
	{
		if ( !Allowed_ShowPath() )
			return;

		Buy( CurrentCostTo_Path() );

		if ( CostGrowthType == CostGrowthTypes_DoublePerBuy )
			Cost_Multiplier_Path *= 2;

		ReturnToCaller();
		MyGame->WaitThenDo( DelayExit - 10, boost::make_shared<Toggle_ShowPathSetter>( boost::static_pointer_cast<HelpMenu>( shared_from_this() ), true ) );
	}

	bool HelpMenu::On_SlowMo()
	{
		return Tools::Any<boost::shared_ptr<GameObject> >( Tools::CurGameData->MyGameObjects, boost::make_shared<IsSlowMoLambda>() );
	}

	bool HelpMenu::Allowed_SlowMo()
	{
		return true && Bank() >= CurrentCostTo_Slow();
	}

	void HelpMenu::Toggle_SlowMo( bool state )
	{
		if ( state )
		{
			boost::shared_ptr<SlowMo> slowmo = MakeMagic( SlowMo, () );
			slowmo->setControl( getControl() );

			MyGame->AddGameObject( slowmo );
		}
		else
		{
			MyGame->AddToDo( boost::make_shared<Toggle_SloMoHelper>( boost::static_pointer_cast<HelpMenu>( shared_from_this() ) ) );
		}
	}

	void HelpMenu::DoSlowMo()
	{
		if ( !Allowed_SlowMo() )
			return;

		Buy( CurrentCostTo_Slow() );

		if ( CostGrowthType == CostGrowthTypes_DoublePerBuy )
			Cost_Multiplier_Slow *= 2;

		Toggle_SlowMo( true );
		ReturnToCaller();
	}

	void HelpMenu::OnAdd()
	{
		Initialization();

		CkBaseMenu::OnAdd();

		InGameStartMenu::PreventMenu = true;

		Item_WatchComputer->Icon->Fade( !Allowed_WatchComputer() );
		Item_SlowMo->Icon->Fade( !Allowed_SlowMo() );
		Item_ShowPath->Icon->Fade( !Allowed_ShowPath() );

		ReturnToCallerDelay = 30;
	}

	void HelpMenu::SetHeaderProperties( const boost::shared_ptr<EzText> &text )
	{
		CkBaseMenu::SetHeaderProperties( text );

		text->setScale( FontScale * 1.2f );
	}

	void HelpMenu::Initialization()
	{
		boost::shared_ptr<GameData> game = Tools::CurGameData;

		setPauseGame( true );

		//FontScale = .73f;
		FontScale = .8f;

		MyPile = boost::make_shared<DrawPile>();

		setRightPanel( Blurb = MakeMagic( HelpBlurb, () ) );

		this->CallDelay = 3;
		this->setSlideLength( 14 );
		this->SelectedItemShift = Vector2( 0, 0 );
		//this.SlideInFrom = PresetPos.Right;

		MakeDarkBack();

		// Make the left backdrop
		boost::shared_ptr<QuadClass> backdrop = boost::make_shared<QuadClass>( std::wstring( L"Backplate_1500x900" ), 1500.f );
		MyPile->Add( backdrop, std::wstring( L"Backdrop" ) );
		backdrop->setPos( Vector2( -1777.778f, 30.55557f ) );

		// Coin
		boost::shared_ptr<QuadClass> Coin_Renamed = boost::make_shared<QuadClass>( std::wstring( L"Coin_Blue" ), 90.f, true );
		Coin_Renamed->setPos( Vector2( -873.1558f, 770.5778f ) );
		MyPile->Add( Coin_Renamed, std::wstring( L"Coin" ) );

		CoinsText = boost::make_shared<EzText>( std::wstring( L"x" ), Resources::Font_Grobold42, 450.f, false, true );
		CoinsText->Name = std::wstring( L"Coins" );
		CoinsText->setScale( .8f );
		CoinsText->setPos( Vector2( -910.2224f, 717.3333f ) );
		CoinsText->MyFloatColor = ( bColor( 255, 255, 255 ) ).ToVector4();
		CoinsText->OutlineColor = ( bColor( 0, 0, 0 ) ).ToVector4();

		CoinsText->ShadowOffset = Vector2( -11, 11 );
		CoinsText->ShadowColor = bColor( 65, 65, 65, 160 );
		CoinsText->PicShadow = false;
		MyPile->Add( CoinsText );
		SetCoins( Bank() );


		// Make the menu
		MyMenu = boost::make_shared<Menu>( false );

		setControl( -1 );

		MyMenu->OnB.reset();

		boost::shared_ptr<MenuItem> item;
		boost::shared_ptr<MenuToggle> toggle;

		// Header
		boost::shared_ptr<EzText> HeaderText = boost::make_shared<EzText>( Localization::Words_Coins, ItemFont );
		SetHeaderProperties( HeaderText );
		MyPile->Add( HeaderText, std::wstring( L"Header" ) );
		HeaderText->setPos( Vector2( -1663.889f, 971.8889f ) );


		Vector2 IconOffset = Vector2( -150, 0 );

		std::wstring CoinPrefix = std::wstring( L"{pCoin_Blue,100,?}" );

		// Watch the computer
		boost::shared_ptr<MenuItem> WatchItem = item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( CoinPrefix + std::wstring( L"x" ) + StringConverterHelper::toString( CurrentCostTo_Watch() ), ItemFont ) ) );
		item->Name = std::wstring( L"WatchComputer" );
		Item_WatchComputer = item;
		item->SetIcon( ObjectIcon::RobotIcon->Clone() );
		item->Icon->setPos( IconOffset + Vector2( -10, 0 ) );
		item->setGo( Cast::ToItem( boost::make_shared<WatchComputerProxy>( boost::static_pointer_cast<HelpMenu>( shared_from_this() ) ) ) );
		ItemPos = Vector2( -1033.333f, 429.4446f );
		PosAdd = Vector2( 0, -520 );
		AddItem( item );
		item->AdditionalOnSelect = Blurb->SetText_Action( Localization::Words_WatchComputer );

		// Show path
		boost::shared_ptr<MenuItem> PathItem;
		if ( On_ShowPath() )
		{
			item = toggle = MakeMagic( MenuToggle, ( ItemFont ) );
			toggle->OnToggle = boost::make_shared<Toggle_ShowPathProxy>( boost::static_pointer_cast<HelpMenu>( shared_from_this() ) );
			toggle->Toggle( true );
		}
		else
		{
            PathItem = item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( CoinPrefix + std::wstring( L"x" ) + StringConverterHelper::toString( CurrentCostTo_Path() ), ItemFont ) ) );
            if ( Bank() >= CurrentCostTo_Path() )
                item->setGo( Cast::ToItem( boost::make_shared<ShowPathProxy>( boost::static_pointer_cast<HelpMenu>( shared_from_this() ) ) ) );
            else
                item->setGo( 0 );
		}
		item->Name = std::wstring( L"ShowPath" );
		item->SetIcon( ObjectIcon::PathIcon->Clone() );
		item->Icon->setPos( IconOffset + Vector2( -20, -75 ) );
		AddItem( item );
		item->AdditionalOnSelect = Blurb->SetText_Action( Localization::Words_ShowPath );
		Item_ShowPath = item;

		// Slow mo
		boost::shared_ptr<MenuItem> SlowItem;
		if ( On_SlowMo() )
		{
			item = toggle = MakeMagic( MenuToggle, ( ItemFont ) );
			toggle->OnToggle = boost::make_shared<Toggle_SlowMoProxy>( boost::static_pointer_cast<HelpMenu>( shared_from_this() ));
			toggle->Toggle( true );
		}
		else
		{
            SlowItem = item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( CoinPrefix + std::wstring( L"x" ) + StringConverterHelper::toString( CurrentCostTo_Slow() ), ItemFont ) ) );
            if (Bank() >= CurrentCostTo_Slow() )
                item->setGo( Cast::ToItem( boost::make_shared<SlowMoProxy>( boost::static_pointer_cast<HelpMenu>( shared_from_this() ) ) ) );
            else
                item->setGo( 0 );
		}
		item->Name = std::wstring( L"SlowMo" );
		item->SetIcon( ObjectIcon::SlowMoIcon->Clone() );
		item->Icon->setPos( IconOffset + Vector2( -20, -55 ) );
		AddItem( item );
		item->AdditionalOnSelect = Blurb->SetText_Action( Localization::Words_ActivateSlowMo );
		Item_SlowMo = item;

        // Fade if not usable
		if ( WatchItem != 0 && Bank() < CurrentCostTo_Watch() )
		{
			WatchItem->setGo( 0 );
			WatchItem->MyText->Alpha = .6f;
			WatchItem->MySelectedText->Alpha = .6f;
		}

        if ( PathItem != 0 && PathItem->getGo() == 0 )
        {
            PathItem->MyText->Alpha = .6f;
            PathItem->MySelectedText->Alpha = .6f;
        }

        if ( SlowItem != 0 && SlowItem->getGo() == 0 )
        {
            SlowItem->MyText->Alpha = .6f;
            SlowItem->MySelectedText->Alpha = .6f;
        }

		MyMenu->OnStart = MyMenu->OnX = MyMenu->OnB = boost::make_shared<MenuReturnToCallerLambdaFunc>( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) );
		MyMenu->OnY = Cast::ToAction( boost::make_shared<MenuReturnToCallerProxy>( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) ) );

		// Select the first item in the menu to start
		MyMenu->SelectItem( 0 );

		EnsureFancy();
		SetPos();

		EpilepsySafe( .75f );
	}

	void HelpMenu::SetPos()
	{
            boost::shared_ptr<MenuItem> _item;
            _item = MyMenu->FindItemByName( L"WatchComputer" ); if (_item != 0 ) { _item->setSetPos( Vector2(-1050.f, 285.0002f ) ); _item->MyText->setScale( 0.8f ); _item->MySelectedText->setScale( 0.8f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
            _item = MyMenu->FindItemByName( L"ShowPath" ); if (_item != 0 ) { _item->setSetPos( Vector2(-1047.222f, -98.8887f ) ); _item->MyText->setScale( 0.8f ); _item->MySelectedText->setScale( 0.8f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
            _item = MyMenu->FindItemByName( L"SlowMo" ); if (_item != 0 ) { _item->setSetPos( Vector2(-1052.777f, -499.4443f ) ); _item->MyText->setScale( 0.8f ); _item->MySelectedText->setScale( 0.8f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

            MyMenu->setPos( Vector2( 0.f, 0.f ) );

            boost::shared_ptr<EzText> _t;
			_t = MyPile->FindEzText( L"Coins" ); if (_t != 0 ) { _t->setPos( Vector2(-1497.222f, 615.889f ) ); _t->setScale( 0.6593335f ); }
            _t = MyPile->FindEzText( L"Header" ); if (_t != 0 ) { _t->setPos( Vector2(-1497.222f, 816.3335f ) ); _t->setScale( 0.9640832f ); }

            boost::shared_ptr<QuadClass> _q;
            _q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 22.22229f, -33.33333f ) ); _q->setSize( Vector2( 1740.553f, 1044.332f ) ); }
            _q = MyPile->FindQuad( L"Coin" ); if (_q != 0 ) { _q->setPos( Vector2(-798.1558f, 634.4669f ) ); _q->setSize( Vector2( 110.5714f, 110.5714f ) ); }

            MyPile->setPos( Vector2( 0.f, 0.f ) );


			// Position coins
			float x = 0;
			_t = MyPile->FindEzText( L"Header" ); if (_t != 0 ) { _t->CalcBounds(); x = CoinsText->getPos().X + _t->GetWorldWidth(); }
			CoinsText->setPos( Vector2( x, CoinsText->getPos().Y ) );
			_q = MyPile->FindQuad( L"Coin" ); if (_q != 0 ) { _q->setPos( Vector2( x + 10, _q->getPos().Y ) ); }
	}

	void HelpMenu::AddItem( const boost::shared_ptr<MenuItem> &item )
	{
		CkBaseMenu::AddItem( item );

	#if defined(PC_VERSION)
		item->Padding += Vector2( 20, 40 );
	#endif
	}

	void HelpMenu::ReturnToCaller( bool PlaySound )
	{
		CkBaseMenu::ReturnToCaller( PlaySound );
	}

	void HelpMenu::SlideIn( int Frames )
	{
		CkBaseMenu::SlideIn( Frames );
	}

	void HelpMenu::SlideOut_RightPanel( GUI_Panel::PresetPos Preset, int Frames )
	{
		CkBaseMenu::SlideOut_RightPanel( Preset, Frames );
	}

	void HelpMenu::InitializeInstanceFields()
	{
		DelayExit = 29;
		Cost_Watch = 5;
		Cost_Path = 40;
		Cost_Slow = 20;
	}
}
