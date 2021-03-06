#include <small_header.h>
#include "Game/Objects/Game Objects/GameObjects/GUI_Blobs.h"

#include "Core/Graphics/Draw/DrawPile.h"
#include "Core/Graphics/Draw/Quads/QuadClass.h"
#include "Core/Text/EzText.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Panel.h"
#include "Game/Player/PlayerManager.h"
#include "Game/Objects/Door/Door.h"
#include "Game/Tools/Resources.h"
#include "Game/Tools/Tools.h"

#include "Game/Games/GameType.h"
#include "Game/Player/PlayerData.h"
#include "Game/Player/Stats.h"
#include "Game/Level/Level.h"

namespace CloudberryKingdom
{

	GUI_BlobQuota::MyPhsxStepHelper::MyPhsxStepHelper( const boost::shared_ptr<GUI_BlobQuota> &blobQuota )
	{
		this->blobQuota = blobQuota;
	}

	void GUI_BlobQuota::MyPhsxStepHelper::Apply()
	{
		blobQuota->SlideOut( PresetPos_TOP, 26 );
	}

	GUI_BlobQuota::GUI_BlobQuota( int Quota )
	{
		InitializeInstanceFields();
		this->Quota = Quota;
	}

	int GUI_BlobQuota::OutOf()
	{
		return Quota;
	}

	void GUI_BlobQuota::OnAdd()
	{
		GUI_Blobs::OnAdd();

		//FinalDoor = MyGame.MyLevel.FinalDoor;
		//FinalDoor.SetLock(true, true, false);
	}

	void GUI_BlobQuota::Reset( bool BoxesOnly )
	{
		GUI_Blobs::Reset( BoxesOnly );
	}

	void GUI_BlobQuota::MyPhsxStep()
	{
		GUI_Blobs::MyPhsxStep();

		if ( Blobs >= Quota )
		{
			Blobs = Quota;
			UpdateCoinText();

			if ( !QuotaMet )
			{
				// On Quoate Met
				if ( OnQuotaMet != 0 )
					OnQuotaMet->Apply( boost::static_pointer_cast<GUI_Blobs>( shared_from_this() ) );

				// Emphasize
				MyPile->BubbleUp( true );

				// Hide
				MyGame->WaitThenDo( 28, boost::make_shared<MyPhsxStepHelper>( boost::static_pointer_cast<GUI_BlobQuota>( shared_from_this() ) ), std::wstring( L"" ), true, true );

				//FinalDoor.SetLock(false);

				QuotaMet = true;
			}
		}
		else
		{
			//FinalDoor.SetLock(true, true, false);

			QuotaMet = false;
		}
	}

	void GUI_BlobQuota::InitializeInstanceFields()
	{
		QuotaMet = false;
	}

	int GUI_Blobs::TempStatsLambda::Apply( const boost::shared_ptr<PlayerData> &p )
	{
		return p->TempStats->Blobs;
	}

	boost::shared_ptr<StringBuilder> GUI_Blobs::BuildString()
	{
		MyString->setLength( 0 );

		MyString->Add( Blobs, 1 );
		MyString->Append( L'/' );
		MyString->Add( OutOf(), 1 );

		return MyString;
	}

	int GUI_Blobs::OutOf()
	{
		return TotalBlobs;
	}

	void GUI_Blobs::OnAdd()
	{
		GUI_Panel::OnAdd();

		if ( !AddedOnce )
		{
			Hide();

			Show();
		}

		AddedOnce = true;

		if ( TotalBlobs == 0 )
			TotalBlobs = MyGame->MyLevel->NumBlobs;
		Blobs = 0;
	}

	void GUI_Blobs::Hide()
	{
		GUI_Panel::Hide();
		SlideOut( PresetPos_TOP, 0 );
	}

	void GUI_Blobs::Show()
	{
		GUI_Panel::Show();
		//SlideIn();
		//MyPile.BubbleUp(false, 10, .7f);
		SlideIn( 50 );
	}

	const Vector2 GUI_Blobs::getApparentPos() const
	{
		return Text->FancyPos->AbsVal + Text->GetWorldSize() / 2;
	}

	void GUI_Blobs::UpdateCoinText()
	{
		Text->SubstituteText( BuildString() );
	}

	GUI_Blobs::GUI_Blobs() :
		Blobs( 0 ), TotalBlobs( 0 ),
		AddedOnce( false )
	{
	}
	boost::shared_ptr<GUI_Blobs> GUI_Blobs::GUI_Blobs_Construct()
	{
		InitializeInstanceFields();
		GUI_Panel::GUI_Panel_Construct();

		return boost::static_pointer_cast<GUI_Blobs>( shared_from_this() );
	}

	void GUI_Blobs::Init()
	{
		GUI_Panel::Init();

		MyPile = boost::make_shared<DrawPile>();
		EnsureFancy();

		Vector2 shift = Vector2( -320, 0 );
		MyPile->setPos( Vector2( 836.1112f, 806.6667f ) - shift );
		SlideInLength = 0;

		// Object is carried over through multiple levels, so prevent it from being released.
		PreventRelease = true;

		PauseOnPause = true;

		MyPile->FancyPos->UpdateWithGame = true;

		boost::shared_ptr<QuadClass> cloud = boost::make_shared<QuadClass>( std::wstring( L"Cloud1" ), 150.f, true );
		cloud->setPos( Vector2( 193.0659f, -22.74048f ) );
		cloud->setSize( Vector2( 465.5865f, 259.2372f ) );
		MyPile->Add( cloud );

//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		Text = boost::make_shared<EzText>( BuildString()->ToString(), Resources::Font_Grobold42_2, 450.f, false, false );
		Text->setScale( .55f );
		Text->setPos( Vector2( 0.3707275f, 73.3901f ) );
		Text->MyFloatColor = ( bColor( 255, 255, 255 ) ).ToVector4();
		Text->OutlineColor = ( bColor( 0, 0, 0 ) ).ToVector4();
		MyPile->Add( Text );

		Blob = boost::make_shared<QuadClass>( std::wstring( L"Blob" ), 150.f, true );
		Blob->setPos( Vector2( -26.84131f, 11.98175f ) );
		Blob->setSize( Vector2( 122.2223f, 193.6508f ) );
		Blob->ScaleXToMatchRatio();
		//Blob.Angle = 0.1055556f;
		MyPile->Add( Blob );
	}

	void GUI_Blobs::MyDraw()
	{
		if ( !getCore()->Show || getCore()->MyLevel->SuppressCheckpoints )
			return;

		GUI_Panel::MyDraw();
	}

	void GUI_Blobs::MyPhsxStep()
	{
		GUI_Panel::MyPhsxStep();

		if ( MyGame->SoftPause )
			return;
		if ( Hid || !Active )
			return;

		if ( getCore()->MyLevel->Watching || getCore()->MyLevel->Finished )
			return;

		Blobs = PlayerManager::PlayerSum( boost::make_shared<TempStatsLambda>() );

		//CoinText.Pos = new Vector2(CoinText.GetWorldWidth(), CoinText.Pos.Y);
		UpdateCoinText();
	}

	void GUI_Blobs::Reset( bool BoxesOnly )
	{
		GUI_Panel::Reset( BoxesOnly );

		//SlideOut(PresetPos.Top, 0);
		SlideIn( 30 );
	}

	void GUI_Blobs::InitializeInstanceFields()
	{
		MyString = boost::make_shared<StringBuilder>( 50, 50 );
		TotalBlobs = 0;
		AddedOnce = false;
	}
}
