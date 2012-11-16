#include "LoadSeedAs.h"
#include "Game/Menus/Concrete Menus/Title Screen/Freeplay/SavedSeedsGUI.h"
#include "Game/Menus/Menu Components/MenuItem.h"
#include "Game/Player/PlayerData.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_TextBox.h"
#include "Core/Text/EzText.h"
#include "Game/Localization.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Panel.h"
#include "Core/Graphics/Draw/Quads/QuadClass.h"

using namespace Microsoft::Xna::Framework;
using namespace Microsoft::Xna::Framework::Graphics;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Linq;

namespace CloudberryKingdom
{

	LoadSeedAs::LoadSeedAsOnEnterLambda::LoadSeedAsOnEnterLambda( const std::shared_ptr<LoadSeedAs> &lsa )
	{
		this->lsa = lsa;
	}

	void LoadSeedAs::LoadSeedAsOnEnterLambda::Apply()
	{
		SavedSeedsGUI::LoadSeed( lsa->TextBox->Text, lsa );
		lsa->Active = false;
		lsa->ReturnToCaller();
	}

	LoadSeedAs::LoadSeedAsBackLambda::LoadSeedAsBackLambda( const std::shared_ptr<LoadSeedAs> &lsa )
	{
		this->lsa = lsa;
	}

	void LoadSeedAs::LoadSeedAsBackLambda::Apply()
	{
		lsa->TextBox->Active = false;
		lsa->ReturnToCaller();
	}

	LoadSeedAs::LoadProxy1::LoadProxy1( const std::shared_ptr<LoadSeedAs> &lsa )
	{
		this->lsa = lsa;
	}

	void LoadSeedAs::LoadProxy1::Apply( const std::shared_ptr<MenuItem> &_item )
	{
		lsa->Load( _item );
	}

	LoadSeedAs::LoadSeedAs( int Control, const std::shared_ptr<PlayerData> &Player ) : VerifyBaseMenu( false )
	{
		this->setControl( Control );
		this->Player = Player;
		FixedToCamera = true;

		Constructor();
	}

	void LoadSeedAs::Init()
	{
		VerifyBaseMenu::Init();

		this->FontScale *= .9f;

		// Header
		std::wstring Text = _T( "Load the following Seed...?" );
		HeaderText = std::make_shared<EzText>( Text, ItemFont );
		HeaderText->Name = _T( "Header" );
		SetHeaderProperties( HeaderText );
		MyPile->Add( HeaderText );
		HeaderText->setPos( HeaderPos );

		// Question
		//HeaderText = new EzText("?", ItemFont);
		//HeaderText.Name = "Question";
		//SetHeaderProperties(HeaderText);
		//MyPile.Add(HeaderText);
		//HeaderText.Pos = HeaderPos;

		std::shared_ptr<MenuItem> item;

		// Load seed
		item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_LOAD_SEED, ItemFont ) );
		item->Name = _T( "Load" );
		item->setGo( std::make_shared<LoadProxy1>( this ) );
		AddItem( item );


		MakeBackButton();

		MyMenu->OnX = MyMenu->OnB = std::make_shared<MenuReturnToCallerLambdaFunc>( this );

		SetPosition();
		MyMenu->SortByHeight();
		MyMenu->SelectItem( 0 );
	}

	void LoadSeedAs::Release()
	{
		VerifyBaseMenu::Release();

		TextBox->Release();
	}

	void LoadSeedAs::SetPosition()
	{
		std::shared_ptr<MenuItem> _item;
		_item = MyMenu->FindItemByName( _T( "Load" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 1269.445f, 161 ) );
		}
		_item = MyMenu->FindItemByName( _T( "Back" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 1338.89f, -52.8888f ) );
		}

		MyMenu->setPos( Vector2( -1125.001f, -319.4444f ) );

		MyPile->FindEzText( _T( "Header" ) )->setPos( Vector2( 61.11098f, 821.8887f ) );

		std::shared_ptr<QuadClass> _q;
		_q = MyPile->FindQuad( _T( "Backdrop" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( 1175.696f, 233.3334f ) );
			_q->setSize( Vector2( 1500, 803.2258f ) );
		}

		MyPile->setPos( Vector2( -1125.001f, -319.4444f ) );
	}

	void LoadSeedAs::OnAdd()
	{
		VerifyBaseMenu::OnAdd();

		std::wstring clipboard = _T( "" );

	#if defined(WINDOWS)
		try
		{
			clipboard = System::Windows::Forms::Clipboard::GetText();
		}
		catch ( ... )
		{
			clipboard = _T( "<Error>" );
		}
	#endif

		if ( clipboard == _T( "" ) || clipboard.length() == 0 )
			clipboard = _T( "Type in a seed!" );

		TextBox = std::make_shared<GUI_TextBox>( clipboard, Vector2::Zero, Vector2( 1.85f,.65f ),.95f );
		TextBox->MaxLength = 80;
		TextBox->FixedToCamera = false;
		TextBox->Pos->SetCenter( MyPile->FancyPos );
		TextBox->Pos->RelVal = Vector2( 1175.001f, 277.7778f );
		TextBox->OnEnter->Add( std::make_shared<LoadSeedAsOnEnterLambda>( this ) );
		TextBox->OnEscape->Add( std::make_shared<LoadSeedAsBackLambda>( this ) );
		MyGame->AddGameObject( TextBox );

		SetPosition();
	}

	void LoadSeedAs::Load( const std::shared_ptr<MenuItem> &_item )
	{
		if ( TextBox != 0 )
		{
			TextBox->Enter();
			return;
		}

		SavedSeedsGUI::LoadSeed( TextBox->getText(), this );
	}
}