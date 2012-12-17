#include <global_header.h>

namespace CloudberryKingdom
{

	CampaignChapterItem::CampaignLevelsLambda::CampaignLevelsLambda()
	{
	}

	int CampaignChapterItem::CampaignLevelsLambda::Apply( const boost::shared_ptr<PlayerData> &p )
	{
		return p->CampaignLevel;
	}

	CampaignChapterItem::CampaignChapterItem( const boost::shared_ptr<EzText> &Text, int Chapter ) : MenuItem( Text )
	{
		InitializeInstanceFields();
		this->Chapter = Chapter;

	#if !defined(DEBUG)
		if ( PlayerManager::PlayerMax( boost::make_shared<CampaignLevelsLambda>() ) < (Chapter - 1) * 100 )
		{
			this->GrayOutOnUnselectable = true;
			this->Selectable = false;
		}
	#endif
	}

	void CampaignChapterItem::InitializeInstanceFields()
	{
		Chapter = 0;
	}

	StartMenu_MW_Campaign::CampaignGoLambda::CampaignGoLambda( const boost::shared_ptr<StartMenu_MW_Campaign> &cine )
	{
		this->cine = cine;
	}

	void StartMenu_MW_Campaign::CampaignGoLambda::Apply( const boost::shared_ptr<MenuItem> &item )
	{
		cine->Go( item );
	}

	StartMenu_MW_Campaign::GoLambda::GoLambda( const boost::shared_ptr<StartMenu_MW_Campaign> &sm )
	{
		this->sm = sm;
	}

	void StartMenu_MW_Campaign::GoLambda::Apply()
	{
		sm->Active = true;
		sm->MyGame->FadeIn( .05f );
		CampaignSequence::getInstance()->Start(sm->_StartLevel);
	}

	StartMenu_MW_Campaign::StartMenu_MW_Campaign( const boost::shared_ptr<TitleGameData_MW> &Title ) : 
		StartMenu(),
		_StartLevel( 0 )
	{
	}
	boost::shared_ptr<StartMenu_MW_Campaign> StartMenu_MW_Campaign::StartMenu_MW_Campaign_Construct( const boost::shared_ptr<TitleGameData_MW> &Title )
	{
		StartMenu::StartMenu_Construct();
		this->Title = Title;

		return boost::static_pointer_cast<StartMenu_MW_Campaign>( shared_from_this() );
	}

	void StartMenu_MW_Campaign::SlideIn( int Frames )
	{
		Title->BackPanel->SetState( StartMenu_MW_Backpanel::State_SCENE_PRINCESS );

		StartMenu::SlideIn( 0 );
	}

	void StartMenu_MW_Campaign::SlideOut( const PresetPos &Preset, int Frames )
	{
		StartMenu::SlideOut( Preset, 0 );
	}

	void StartMenu_MW_Campaign::SetText( const boost::shared_ptr<EzText> &text )
	{
		text->MyFloatColor = ( bColor( 34, 214, 47 ) ).ToVector4();
		text->OutlineColor = ( bColor( 0, 0, 0, 0 ) ).ToVector4();
	}

	void StartMenu_MW_Campaign::SetItemProperties( const boost::shared_ptr<MenuItem> &item )
	{
		StartMenu::SetItemProperties( item );

		SetText( item->MyText );

		item->MySelectedText->Shadow = item->MyText->Shadow = false;
		item->MySelectedText->MyFloatColor = ( bColor( 73, 255, 86 ) ).ToVector4();
		item->MySelectedText->OutlineColor = ( bColor( 0, 0, 0, 0 ) ).ToVector4();

		//item.MyOscillateParams.Set(1f, 1.01f, .005f);
	}

	void StartMenu_MW_Campaign::OnAdd()
	{
		StartMenu::OnAdd();
	}

	void StartMenu_MW_Campaign::Init()
	{
		 StartMenu::Init();

		CallDelay = ReturnToCallerDelay = 0;
		MyMenu->OnB = boost::make_shared<MenuReturnToCallerLambdaFunc>( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) );

		MyMenu->ClearList();

		MakeHeader();

		CreateMenu();
	}

	void StartMenu_MW_Campaign::CreateMenu()
	{
		boost::shared_ptr<MenuItem> item;

		// Chapter 1
		item = boost::make_shared<CampaignChapterItem>( boost::make_shared<EzText>( Localization::Words_THE_BEGINNING, ItemFont ), 1 );
		item->Name = _T( "MainCampaign" );
		item->setGo( boost::make_shared<CampaignGoLambda>( boost::static_pointer_cast<StartMenu_MW_Campaign>( shared_from_this() ) ) );
		AddItem( item );

		// Chapter 2
		item = boost::make_shared<CampaignChapterItem>( boost::make_shared<EzText>( Localization::Words_THE_NEXT_NINETY_NINE, ItemFont ), 2 );
		item->Name = _T( "Easy" );
		item->setGo( boost::make_shared<CampaignGoLambda>( boost::static_pointer_cast<StartMenu_MW_Campaign>( shared_from_this() ) ) );
		AddItem( item );

		// Chapter 3
		item = boost::make_shared<CampaignChapterItem>( boost::make_shared<EzText>( Localization::Words_AGAUNTLET_OF_DOOM, ItemFont ), 3 );
		item->Name = _T( "Hard" );
		item->setGo( boost::make_shared<CampaignGoLambda>( boost::static_pointer_cast<StartMenu_MW_Campaign>( shared_from_this() ) ) );
		AddItem( item );

		// Chapter 4
		item = boost::make_shared<CampaignChapterItem>( boost::make_shared<EzText>( Localization::Words_ALMOST_HERO, ItemFont ), 4 );
		item->Name = _T( "Hardcore" );
		item->setGo( boost::make_shared<CampaignGoLambda>( boost::static_pointer_cast<StartMenu_MW_Campaign>( shared_from_this() ) ) );
		AddItem( item );

		// Chapter 5
		item = boost::make_shared<CampaignChapterItem>( boost::make_shared<EzText>( Localization::Words_THE_MASOCHIST, ItemFont ), 5 );
		item->Name = _T( "Maso" );
		item->setGo( boost::make_shared<CampaignGoLambda>( boost::static_pointer_cast<StartMenu_MW_Campaign>( shared_from_this() ) ) );
		AddItem( item );

		//// Cinematics
		//item = new MenuItem(new EzText("Cinematics", ItemFont));
		//item.Name = "Cine";
		//item.Go = null;
		//AddItem(item);
		//item.MyText.MyFloatColor = new Color(241, 32, 117).ToVector4();
		//item.MySelectedText.MyFloatColor = new Color(251, 52, 137).ToVector4();

		MyMenu->SelectItem( 0 );

		//SetPos_NoCinematic();
		SetPos_WithCinematic();
	}

	void StartMenu_MW_Campaign::MakeHeader()
	{
		boost::shared_ptr<EzText> Header = boost::make_shared<EzText>( Localization::Words_STORY_MODE, ItemFont );
		Header->Name = _T( "Header" );
		Header->setScale( Header->getScale() * 1.3f );
		SetText( Header );
		Header->OutlineColor = Color::Black.ToVector4();
		MyPile->Add( Header );

		Header->setPos( Vector2( -800.0029f, 863.8889f ) );
	}

	void StartMenu_MW_Campaign::Go( const boost::shared_ptr<MenuItem> &item )
	{
		boost::shared_ptr<CampaignChapterItem> c_item = boost::dynamic_pointer_cast<CampaignChapterItem>( item );
		if ( 0 == c_item )
			return;

		Go( c_item->Chapter );
	}

	void StartMenu_MW_Campaign::Go( int StartLevel )
	{
		Tools::SongWad->FadeOut();
		MyGame->FadeToBlack( .0225f, 20 );
		Active = false;

		_StartLevel = StartLevel;
		MyGame->WaitThenDo( 75, boost::make_shared<GoLambda>( boost::static_pointer_cast<StartMenu_MW_Campaign>( shared_from_this() ) ) );
	}

	void StartMenu_MW_Campaign::SetPos_NoCinematic()
	{
		boost::shared_ptr<MenuItem> _item;
		_item = MyMenu->FindItemByName( _T( "MainCampaign" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 686.4453f, 191.6667f ) );
			_item->MyText->setScale( 0.8f );
			_item->MySelectedText->setScale( 0.8f );
			_item->SelectIconOffset = Vector2( 0, 0 );
			_item->SetSelectedPos( Vector2( 622.5566f, 186.1112f ) );
		}
		_item = MyMenu->FindItemByName( _T( "Easy" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 708.665f, -36.44455f ) );
			_item->MyText->setScale( 0.8f );
			_item->MySelectedText->setScale( 0.8f );
			_item->SelectIconOffset = Vector2( 0, 0 );
			_item->SetSelectedPos( Vector2( 622.5566f, -1 ) );
		}
		_item = MyMenu->FindItemByName( _T( "Hard" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 711.4443f, -239.5557f ) );
			_item->MyText->setScale( 0.8f );
			_item->MySelectedText->setScale( 0.8f );
			_item->SelectIconOffset = Vector2( 0, 0 );
			_item->SetSelectedPos( Vector2( 622.5566f, -1 ) );
		}
		_item = MyMenu->FindItemByName( _T( "Hardcore" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 714.2227f, -437.111f ) );
			_item->MyText->setScale( 0.8f );
			_item->MySelectedText->setScale( 0.8f );
			_item->SelectIconOffset = Vector2( 0, 0 );
			_item->SetSelectedPos( Vector2( 622.5566f, -1 ) );
		}
		_item = MyMenu->FindItemByName( _T( "Maso" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 730.8906f, -656.889f ) );
			_item->MyText->setScale( 0.8f );
			_item->MySelectedText->setScale( 0.8f );
			_item->SelectIconOffset = Vector2( 0, 0 );
			_item->SetSelectedPos( Vector2( 622.5566f, -1 ) );
		}

		MyMenu->setPos( Vector2( -783.3339f, 227.7778f ) );
	}

	void StartMenu_MW_Campaign::SetPos_WithCinematic()
	{
		boost::shared_ptr<MenuItem> _item;
		_item = MyMenu->FindItemByName( _T( "MainCampaign" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 686.4453f, 191.6667f ) );
			_item->MyText->setScale( 0.8f );
			_item->MySelectedText->setScale( 0.8f );
			_item->SelectIconOffset = Vector2( 0, 0 );
			_item->SetSelectedPos( Vector2( 622.5566f, 186.1112f ) );
		}
		_item = MyMenu->FindItemByName( _T( "Easy" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 708.665f, -36.44455f ) );
			_item->MyText->setScale( 0.8f );
			_item->MySelectedText->setScale( 0.8f );
			_item->SelectIconOffset = Vector2( 0, 0 );
			_item->SetSelectedPos( Vector2( 622.5566f, -1 ) );
		}
		_item = MyMenu->FindItemByName( _T( "Hard" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 711.4443f, -239.5557f ) );
			_item->MyText->setScale( 0.8f );
			_item->MySelectedText->setScale( 0.8f );
			_item->SelectIconOffset = Vector2( 0, 0 );
			_item->SetSelectedPos( Vector2( 622.5566f, -1 ) );
		}
		_item = MyMenu->FindItemByName( _T( "Hardcore" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 714.2227f, -437.111f ) );
			_item->MyText->setScale( 0.8f );
			_item->MySelectedText->setScale( 0.8f );
			_item->SelectIconOffset = Vector2( 0, 0 );
			_item->SetSelectedPos( Vector2( 622.5566f, -1 ) );
		}
		_item = MyMenu->FindItemByName( _T( "Maso" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 730.8906f, -656.889f ) );
			_item->MyText->setScale( 0.8f );
			_item->MySelectedText->setScale( 0.8f );
			_item->SelectIconOffset = Vector2( 0, 0 );
			_item->SetSelectedPos( Vector2( 622.5566f, -1 ) );
		}
		_item = MyMenu->FindItemByName( _T( "Cine" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 733.6666f, -876.6666f ) );
			_item->MyText->setScale( 0.7373331f );
			_item->MySelectedText->setScale( 0.7373331f );
			_item->SetSelectedPos( Vector2( 622.5566f, -1 ) );
		}

		MyMenu->setPos( Vector2( -783.3339f, 227.7778f ) );

		boost::shared_ptr<EzText> _t;
		_t = MyPile->FindEzText( _T( "Header" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -800.0029f, 863.8889f ) );
			_t->setScale( 1.3f );
		}
		MyPile->setPos( Vector2( 0, 0 ) );
	}
}
