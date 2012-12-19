#include <global_header.h>

#include <Hacks\List.h>

namespace CloudberryKingdom
{

	HeroItem::HeroItem( const boost::shared_ptr<BobPhsx> &Hero ) : MenuItem( boost::make_shared<EzText>( Hero->Name, Resources::Font_Grobold42_2 ) )
	{
		this->Hero = Hero;

		Locked = false;
	}

	StartMenu_MW_HeroSelect::OnSelectProxy::OnSelectProxy( const boost::shared_ptr<StartMenu_MW_HeroSelect> &smmwhs )
	{
		this->smmwhs = smmwhs;
	}

	void StartMenu_MW_HeroSelect::OnSelectProxy::Apply()
	{
		smmwhs->OnSelect();
	}

	StartMenu_MW_HeroSelect::UpdateScoreProxy::UpdateScoreProxy( const boost::shared_ptr<StartMenu_MW_HeroSelect> &smmwhs )
	{
		this->smmwhs = smmwhs;
	}

	void StartMenu_MW_HeroSelect::UpdateScoreProxy::Apply()
	{
		smmwhs->UpdateScore();
	}

	StartMenu_MW_HeroSelect::StartMenuGoLambda::StartMenuGoLambda( const boost::shared_ptr<StartMenu_MW_HeroSelect> &hs )
	{
		this->hs = hs;
	}

	void StartMenu_MW_HeroSelect::StartMenuGoLambda::Apply( const boost::shared_ptr<MenuItem> &item )
	{
		hs->Go( item );
	}

	StartMenu_MW_HeroSelect::StartMenu_MW_HeroSelect( const boost::shared_ptr<TitleGameData_MW> &Title, const boost::shared_ptr<ArcadeMenu> &Arcade, const boost::shared_ptr<ArcadeItem> &MyArcadeItem ) : ArcadeBaseMenu() { }
	boost::shared_ptr<StartMenu_MW_HeroSelect> StartMenu_MW_HeroSelect::StartMenu_MW_HeroSelect_Construct( const boost::shared_ptr<TitleGameData_MW> &Title, const boost::shared_ptr<ArcadeMenu> &Arcade, const boost::shared_ptr<ArcadeItem> &MyArcadeItem )
	{
		ArcadeBaseMenu::ArcadeBaseMenu_Construct();

		this->Title = Title;
		this->Arcade = Arcade;
		this->MyArcadeItem = MyArcadeItem;

		return boost::static_pointer_cast<StartMenu_MW_HeroSelect>( shared_from_this() );
	}

	void StartMenu_MW_HeroSelect::Release()
	{
		ArcadeBaseMenu::Release();

		if ( MyHeroDoll != 0 )
			MyHeroDoll->Release();
		if ( Options != 0 )
			Options->Release();

		Title.reset();
		Arcade.reset();
	}

	void StartMenu_MW_HeroSelect::OnSelect()
	{
		boost::shared_ptr<HeroItem> item = boost::dynamic_pointer_cast<HeroItem>( MyMenu->getCurItem() );
		if ( 0 == item )
			return;

		Challenge::ChosenHero = item->Hero;
		MyHeroDoll->MakeHeroDoll( item->Hero );

		UpdateScore();
	}

	void StartMenu_MW_HeroSelect::SlideIn( int Frames )
	{
		Title->BackPanel->SetState( StartMenu_MW_Backpanel::State_SCENE_KOBBLER_BLUR );
		ArcadeBaseMenu::SlideIn( 0 );

		if ( MyHeroDoll != 0 )
		{
			MyHeroDoll->SlideIn( 0 );
			MyHeroDoll->Hid = false;
		}
		if ( Options != 0 )
			Options->SlideIn( 0 );
	}

	void StartMenu_MW_HeroSelect::SlideOut( PresetPos Preset, int Frames )
	{
		ArcadeBaseMenu::SlideOut( Preset, 0 );

		if ( MyHeroDoll != 0 )
			MyHeroDoll->SlideOut( Preset, 0 );
		if ( Options != 0 )
			Options->SlideOut( Preset, 0 );
	}

	void StartMenu_MW_HeroSelect::SetItemProperties( const boost::shared_ptr<MenuItem> &item )
	{
		ArcadeBaseMenu::SetItemProperties( item );

		SetItemProperties_FadedOnUnselect( item );
	}

	void StartMenu_MW_HeroSelect::SetItemProperties_FadedOnUnselect( const boost::shared_ptr<MenuItem> &item )
	{
		item->MySelectedText->Shadow = item->MyText->Shadow = false;

		StartMenu::SetItemProperties_Green( item, true );

		item->MyText->OutlineColor.W *= .4f;
		item->MySelectedText->OutlineColor.W *= .7f;
	}

	void StartMenu_MW_HeroSelect::OnAdd()
	{
		ArcadeBaseMenu::OnAdd();

		// Hero Doll
		MyHeroDoll = MakeMagic( HeroDoll, ( getControl() ) );
		MyGame->AddGameObject( MyHeroDoll );

		// Options. Menu for PC, graphics only for consoles.
		Options = MakeMagic( HeroSelectOptions, ( boost::static_pointer_cast<StartMenu_MW_HeroSelect>( shared_from_this() ) ) );
		MyGame->AddGameObject( Options );
	}

	void StartMenu_MW_HeroSelect::Init()
	{
		 ArcadeBaseMenu::Init();

		MyPile = boost::make_shared<DrawPile>();

		CallDelay = ReturnToCallerDelay = 0;

		Score = boost::make_shared<EzText>( _T( "0" ), Resources::Font_Grobold42_2 );
		Level_Renamed = boost::make_shared<EzText>( _T( "0" ), Resources::Font_Grobold42_2 );

		// Heroes
		BobPhsxNormal::getInstance()->Id = 0;
		BobPhsxBig::getInstance()->Id = 1;
		BobPhsxInvert::getInstance()->Id = 2;
		BobPhsxDouble::getInstance()->Id = 3;
		BobPhsxJetman::getInstance()->Id = 4;
		BobPhsxBouncy::getInstance()->Id = 5;
		BobPhsxBox::getInstance()->Id = 6;
		BobPhsxScale::getInstance()->Id = 7;
		BobPhsxTime::getInstance()->Id = 8;
		BobPhsxSmall::getInstance()->Id = 9;
		BobPhsxSpaceship::getInstance()->Id = 10;
		BobPhsxWheel::getInstance()->Id = 11;

		boost::shared_ptr<BobPhsx> JetpackWheelie = BobPhsx::MakeCustom( Hero_BaseType_WHEEL, Hero_Shape_CLASSIC, Hero_MoveMod_JETPACK );
		JetpackWheelie->Name = Localization::Words_JETPACK_WHEELIE;
		JetpackWheelie->Id = 12;

		//BobPhsxMeat.Instance =
		//BobPhsxRocketbox.Instance =

		boost::shared_ptr<BobPhsx>  tempVector[] = { BobPhsxNormal::getInstance(), BobPhsxBig::getInstance(), BobPhsxInvert::getInstance(), BobPhsxDouble::getInstance(), BobPhsxJetman::getInstance(), BobPhsxBouncy::getInstance(), BobPhsxBox::getInstance(), BobPhsxScale::getInstance(), BobPhsxTime::getInstance(), BobPhsxSmall::getInstance(), BobPhsxSpaceship::getInstance(), BobPhsxWheel::getInstance(), JetpackWheelie };
		std::vector<boost::shared_ptr<BobPhsx> > list = VecFromArray( tempVector );

		// Menu
		boost::shared_ptr<MiniMenu> mini = boost::make_shared<MiniMenu>();
		MyMenu = mini;

		MyMenu->OnSelect = boost::make_shared<UpdateScoreProxy>( boost::static_pointer_cast<StartMenu_MW_HeroSelect>( shared_from_this() ) );

		mini->WrapSelect = false;
		mini->Shift = Vector2( 0, -135 );
		mini->ItemsToShow = 6;
		FontScale *= .75f;

		for ( std::vector<boost::shared_ptr<BobPhsx> >::const_iterator phsx = list.begin(); phsx != list.end(); ++phsx )
		{
			boost::shared_ptr<HeroItem> item = boost::make_shared<HeroItem>( *phsx );
			item->AdditionalOnSelect = boost::make_shared<OnSelectProxy>( boost::static_pointer_cast<StartMenu_MW_HeroSelect>( shared_from_this() ) );
			AddItem( item );
			item->setGo( boost::make_shared<StartMenuGoLambda>( boost::static_pointer_cast<StartMenu_MW_HeroSelect>( shared_from_this() ) ) );
		}

		MyMenu->OnB = boost::make_shared<MenuReturnToCallerLambdaFunc>( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) );
		EnsureFancy();

		/// <summary>
		/// Left Side
		/// </summary>
		#pragma region
		// Black box, left side
		boost::shared_ptr<QuadClass> BackBoxLeft = boost::make_shared<QuadClass>( _T( "Arcade_BoxLeft" ) );
		BackBoxLeft->setAlpha( 1 );
		MyPile->Add( BackBoxLeft, _T( "BoxLeft" ) );
		#pragma endregion

		/// <summary>
		/// Right Side
		/// </summary>
		#pragma region
		// Black box, right side
		boost::shared_ptr<QuadClass> BackBox = boost::make_shared<QuadClass>( _T( "Arcade_Box" ) );
		BackBox->setAlpha( 1 );
		MyPile->Add( BackBox, _T( "BoxRight" ) );

		// Score, level
		boost::shared_ptr<EzText> ScoreHeader = boost::make_shared<EzText>( Localization::Words_HIGH_SCORE, Resources::Font_Grobold42_2 );
		StartMenu::SetText_Green( ScoreHeader, true );
		MyPile->Add( ScoreHeader, _T( "ScoreHeader" ) );

		MyPile->Add( Score, _T( "Score" ) );

		boost::shared_ptr<EzText> LevelHeader = boost::make_shared<EzText>( Localization::Words_BEST_LEVEL, Resources::Font_Grobold42_2 );
		StartMenu::SetText_Green( LevelHeader, true );
		MyPile->Add( LevelHeader, _T( "LevelHeader" ) );

		MyPile->Add( Level_Renamed, _T( "Level" ) );
		#pragma endregion

		/// <summary>
		/// Back
		/// </summary>
		MyPile->Add( boost::make_shared<QuadClass>( ButtonTexture::getBack() ), _T("Back") );
		MyPile->Add( boost::make_shared<QuadClass>( _T( "BackArrow2" ), _T( "BackArrow" ) ) );

		MyPile->FadeIn( .33f );

		SetPos();
	}

	void StartMenu_MW_HeroSelect::OnReturnTo()
	{
		ArcadeBaseMenu::OnReturnTo();

		UpdateScore();
	}

	void StartMenu_MW_HeroSelect::UpdateScore()
	{
		boost::shared_ptr<HeroItem> item = boost::dynamic_pointer_cast<HeroItem>( MyMenu->getCurItem() );
		if ( 0 == item )
			return;

		int TopScore = MyArcadeItem->MyChallenge->TopScore();
		int TopLevel = MyArcadeItem->MyChallenge->TopLevel();

		Score->RightJustify = Level_Renamed->RightJustify = true;
		Score->SubstituteText( StringConverterHelper::toString( TopScore ) );
		Level_Renamed->SubstituteText( StringConverterHelper::toString( TopLevel ) );
	}

	void StartMenu_MW_HeroSelect::SetPos()
	{
		MyMenu->setPos( Vector2( -1340.222f, 104.4444f ) );

		boost::shared_ptr<EzText> _t;
		_t = MyPile->FindEzText( _T( "ScoreHeader" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -22.22266f, 636.1111f ) );
			_t->setScale( 1 );
		}
		_t = MyPile->FindEzText( _T( "Score" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( 1161.11f, 366.6667f ) );
			_t->setScale( 1 );
		}
		_t = MyPile->FindEzText( _T( "LevelHeader" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -2.779297f, 105.5556f ) );
			_t->setScale( 1 );
		}
		_t = MyPile->FindEzText( _T( "Level" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( 1163.887f, -155.5555f ) );
			_t->setScale( 1 );
		}

		boost::shared_ptr<QuadClass> _q;
		_q = MyPile->FindQuad( _T( "BoxLeft" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( -972.2227f, -127.7778f ) );
			_q->setSize( Vector2( 616.5467f, 1004.329f ) );
		}
		_q = MyPile->FindQuad( _T( "BoxRight" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( 666.6641f, -88.88879f ) );
			_q->setSize( Vector2( 776.5515f, 846.666f ) );
		}
		_q = MyPile->FindQuad( _T( "Back" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( -1269.443f, -1011.111f ) );
			_q->setSize( Vector2( 64.49973f, 64.49973f ) );
		}
		_q = MyPile->FindQuad( _T( "BackArrow" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( -1416.666f, -1016.667f ) );
			_q->setSize( Vector2( 71.89921f, 61.83332f ) );
		}

		MyPile->setPos( Vector2( 83.33417f, 130.9524f ) );

	}

	void StartMenu_MW_HeroSelect::Go( const boost::shared_ptr<MenuItem> &item )
	{
		boost::shared_ptr<StartLevelMenu> levelmenu = MakeMagic( StartLevelMenu, ( MyArcadeItem->MyChallenge->TopLevel() ) );

		levelmenu->MyMenu->SelectItem( StartLevelMenu::PreviousMenuIndex );
		levelmenu->StartFunc = boost::make_shared<StartFuncProxy>( boost::static_pointer_cast<ArcadeBaseMenu>( shared_from_this() ) );
		levelmenu->ReturnFunc.reset();

		Call( levelmenu );
		Hide();
	}
}
