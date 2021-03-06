#include <small_header.h>
#include "Game/Objects/Game Objects/GameObjects/PerfectScoreObject.h"

#include "Core/Graphics/Draw/DrawPile.h"
#include "Core/Graphics/Draw/Quads/QuadClass.h"
#include "Game/Localization.h"
#include "Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h"
#include "Core/Particle Effects/Specific Effects/CloudberryKingdom.ParticleEffects.h"
#include "Core/Text/EzFont.h"
#include "Core/Text/EzText.h"
#include "Core/Texture/EzTexture.h"
#include "Core/Tools/CoreMath.h"
#include "Game/Objects/ObjectBase.h"
#include "Game/Objects/Game Objects/GameObject.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Panel.h"
#include "Game/Player/PlayerManager.h"
#include "Game/Objects/Game Objects/GameObjects/Cheer.h"
#include "Game/Objects/In Game Objects/Grab/MakeData.h"
#include "Game/Level/Level.h"
#include "Game/Objects/Special/TextFloat.h"
#include "Game/Player/PlayerData.h"
#include "Game/Tools/Resources.h"
#include "Game/Tools/Tools.h"

#include "Game/Games/GameType.h"
#include "Game/Player/Stats.h"
#include "Core/Sound/EzSound.h"
#include "Core/Sound/EzSoundWad.h"

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>
#include <Hacks/String.h>

namespace CloudberryKingdom
{

	PerfectScoreObject::TextEffectProxy::TextEffectProxy( const boost::shared_ptr<PerfectScoreObject> &pso )
	{
		this->pso = pso;
	}

	void PerfectScoreObject::TextEffectProxy::Apply()
	{
		pso->TextEffect();
	}

	PerfectScoreObject::OnCoinGrabProxy::OnCoinGrabProxy( const boost::shared_ptr<PerfectScoreObject> &pso )
	{
		this->pso = pso;
	}

	void PerfectScoreObject::OnCoinGrabProxy::Apply( const boost::shared_ptr<ObjectBase> &obj )
	{
		pso->OnCoinGrab( obj );
	}

	PerfectScoreObject::OnLevelRetryProxy::OnLevelRetryProxy( const boost::shared_ptr<PerfectScoreObject> &pso )
	{
		this->pso = pso;
	}

	void PerfectScoreObject::OnLevelRetryProxy::Apply()
	{
		pso->OnLevelRetry();
	}

	const bool &PerfectScoreObject::getObtained() const
	{
		return _Obtained;
	}

	void PerfectScoreObject::setObtained( const bool &value )
	{
		_Obtained = value;
		if ( Global )
			GlobalObtained = _Obtained;
	}

	void PerfectScoreObject::OnAdd()
	{
		GUI_Panel::OnAdd();

		// Remove other perfect score objects
		for ( GameObjVec::const_iterator obj = MyGame->MyGameObjects.begin(); obj != MyGame->MyGameObjects.end(); ++obj )
		{
			if ( ( *obj ).get() == this )
				continue;
			if ( boost::dynamic_pointer_cast<PerfectScoreObject>( *obj ) != 0 )
				( *obj )->Release();
		}

		// If the player didn't get the bonus last level, reset the multiplier
		if ( !getObtained() )
			ResetMultiplier();
		setObtained( false );

		Eligible = true;

		MyGame->OnCoinGrab->Add( boost::make_shared<OnCoinGrabProxy>( boost::static_pointer_cast<PerfectScoreObject>( shared_from_this() ) ) );
		MyGame->OnLevelRetry->Add( boost::make_shared<OnLevelRetryProxy>( boost::static_pointer_cast<PerfectScoreObject>( shared_from_this() ) ) );
		MyGame->OnWatchComputer->Add( boost::make_shared<OnLevelRetryProxy>( boost::static_pointer_cast<PerfectScoreObject>( shared_from_this() ) ) );

		OnAdd_GUI();
	}

	void PerfectScoreObject::ReleaseBody()
	{
		GUI_Panel::ReleaseBody();

		Dots.clear();

		//MyGame.OnCoinGrab -= OnCoinGrab;
		//MyGame.OnLevelRetry -= OnLevelRetry;
	}

	const int &PerfectScoreObject::getBaseBonus() const
	{
		return _BaseBonus;
	}

	void PerfectScoreObject::setBaseBonus( const int &value )
	{
		_BaseBonus = value;
		if ( getNextBonus() < getBaseBonus() )
			setNextBonus( getBaseBonus() );
	}

	const int &PerfectScoreObject::getNextBonus() const
	{
		return _NextBonus;
	}

	void PerfectScoreObject::setNextBonus( const int &value )
	{
		_NextBonus = __min( value, MaxBonus );
		if ( Global )
			GlobalBonus = _NextBonus;
	}

	void PerfectScoreObject::OnCoinGrab( const boost::shared_ptr<ObjectBase> &obj )
	{
		if ( !Eligible )
			return;

		// Give the bonus?
		if ( PlayerManager::GetLevelCoins() == MyGame->MyLevel->NumCoins )
		{
			setObtained( true );
			BonusCount++;

			boost::shared_ptr<PlayerData> player = obj->getCore()->InteractingPlayer;

			if ( player != 0 )
			{
				if ( Campaign )
				{
					player->CampaignCoins += BonusValue();
				}
				else
				{
					player->LevelStats->Score += BonusValue();
				}
			}
				

			// Remove last coin score text
			MyGame->RemoveLastCoinText();

			// Add the visual effect
			Effect( obj->getCore()->Data.Position );

			// Increase the bonus
			MyGame->WaitThenDo( 2, boost::make_shared<TextEffectProxy>( boost::static_pointer_cast<PerfectScoreObject>( shared_from_this() ) ) );
			//setNextBonus( getNextBonus() + BonusIncrement );
		}

		UpdateScoreText();
	}

	int PerfectScoreObject::BonusValue()
	{
		return static_cast<int>( getNextBonus() * MyGame->ScoreMultiplier );
	}

	void PerfectScoreObject::Effect( Vector2 pos )
	{
		// Berries
		if ( BonusCount % 5 == 0 )
		{
			Tools::CurGameData->AddGameObject( boost::make_shared<Cheer>() );
		}

		pos += Vector2( 110, 70 );

		// Text float
		boost::shared_ptr<TextFloat> text = boost::make_shared<TextFloat>( Localization::Words_Perfect, pos + Vector2( 21, 76.5f ) );

		std::wstring s = StringConverterHelper::toString( BonusValue() );
		if ( Campaign ) s = L"+" + s;
		boost::shared_ptr<TextFloat> text2 = boost::make_shared<TextFloat>( s, pos + Vector2( 21, -93.5f ) );

		text->MyText->setScale( text->MyText->getScale() * 1.5f );
		MyGame->AddGameObject( text );

		text2->MyText->setScale( text2->MyText->getScale() * 1.5f );
		MyGame->AddGameObject( text2 );

        ParticleEffects::CoinDie_Perfect( MyGame->MyLevel, pos );
        ParticleEffects::CoinDie_Spritely( MyGame->MyLevel, pos );

		//Vector2 TextPos = MyGame.CamPos + MyPile.Pos;
		////ParticleEffects.CoinDie_Perfect(MyGame.MyLevel, TextPos + new Vector2(-260, 0));
		////ParticleEffects.CoinDie_Perfect(MyGame.MyLevel, TextPos + new Vector2(60, 0));
		//ParticleEffects.CoinDie_Spritely(MyGame.MyLevel, TextPos + new Vector2(-260, 0));
		//ParticleEffects.CoinDie_Spritely(MyGame.MyLevel, TextPos + new Vector2(-160, 0));
		//ParticleEffects.CoinDie_Spritely(MyGame.MyLevel, TextPos + new Vector2(-60, 0));
		//ParticleEffects.CoinDie_Spritely(MyGame.MyLevel, TextPos + new Vector2(40, 0));

		//MyGame.OnCompleteLevel += new Action<Levels.Level>(MyGame_OnCompleteLevel);
		//MyGame.WaitThenDo(1, TextEffect);
		//TextEffect();

		boost::shared_ptr<EzSound> sound = Tools::SoundWad->FindByName( L"PerfectSound" );
		if ( sound != 0 ) sound->Play();
	}

    void PerfectScoreObject::MyGame_OnCompleteLevel( boost::shared_ptr<Level> obj )
    {
        TextEffect();
    }

    void PerfectScoreObject::TextEffect()
    {
        setNextBonus( getNextBonus() + BonusIncrement );
        UpdateScoreText();

        if ( MyGame->ScoreMultiplier <= 2 )
        {
            Text->MyFloatColor = .77f * Color::White.ToVector4() + .23f * bColor( 228, 0, 69 ).ToVector4();
            Text->setScale( 1.18f );
        }
        else
        {
            Text->MyFloatColor = .6f * Color::White.ToVector4() + .4f * bColor( 228, 0, 69 ).ToVector4();
            Text->setScale( 1.115f );
        }
    }

	void PerfectScoreObject::OnLevelRetry()
	{
		if ( Count == 0 )
			return;
		if ( MyGame->FreeReset )
			return;

		if ( IneligibleOnDeath )
			Eligible = false;

		ResetMultiplier();
	}

	void PerfectScoreObject::ResetMultiplier()
	{
		bool LostStreak = BonusCount > 0;

		setNextBonus( getBaseBonus() );
		BonusCount = 0;

        if ( LostStreak )
        {
            Text->MyFloatColor = .8f * Color::Black.ToVector4() + .2f * bColor( 228, 0, 69 ).ToVector4();
            Text->setScale( 1.185f );
            Text->Angle = -1;
        }

		UpdateScoreText();
	}

bool PerfectScoreObject::GlobalObtained = false;
int PerfectScoreObject::GlobalBonus = 0;

	PerfectScoreObject::PerfectScoreObject( bool Global, bool ShowMultiplier, bool Campaign ) :
		Campaign( Campaign ),
		Eligible( false ),
		_Obtained( false ),
		_BaseBonus( 0 ),
		BonusIncrement( 0 ),
		MaxBonus( 0 ),
		_NextBonus( 0 ),
		BonusCount( 0 ),
		IneligibleOnDeath( false ),
		Count( 0 ),
		Global( false ),
		ShowMultiplier( false ),
		AddedOnce( false )
	{
	}

	boost::shared_ptr<PerfectScoreObject> PerfectScoreObject::PerfectScoreObject_Construct( bool Global, bool ShowMultiplier, bool Campaign )
	{
		InitializeInstanceFields();
		GUI_Panel::GUI_Panel_Construct();

		this->Campaign = Campaign;

		// Object is carried over through multiple levels, so prevent it from being released.
		PreventRelease = true;

		PauseOnPause = true;

			if (Campaign)
			{
				setBaseBonus( 10 );
				BonusIncrement = 10;
				MaxBonus = 10;
			}
			else
			{
				setBaseBonus( 1000 );
				BonusIncrement = 1000;
				MaxBonus = 8000;
			}

		// Global modifer, keep track of multiplier across levels/games
		if ( Global )
		{
			this->Global = true;
			setObtained( GlobalObtained );
			setNextBonus( GlobalBonus );
		}

		this->ShowMultiplier = ShowMultiplier;

		Init_GUI();

		return boost::static_pointer_cast<PerfectScoreObject>( shared_from_this() );
	}

	const float PerfectScoreObject::getMultiplier() const
	{
		if ( MyGame == 0 )
			return static_cast<float>( getNextBonus() / getBaseBonus() );
		else
			return static_cast<float>( MyGame->ScoreMultiplier * getNextBonus() / getBaseBonus() );
	}

	void PerfectScoreObject::MyPhsxStep()
	{
		GUI_Panel::MyPhsxStep();

		Count++;
	}

	std::wstring PerfectScoreObject::ToString()
	{
        //return "Streak x" + string.Format("{0:0.0}", Multiplier);
        //return "Perfect +" + ((int)(Multiplier * 1000)).ToString();
        //return "Next Bonus x " + string.Format("{0:0.0}", Multiplier);
        //return "Perfect x " + string.Format("{0:0}", Multiplier);
        //return "Bonus x " + string.Format("{0:0}", Multiplier);
        //return std::wstring( L"x" ) + Format( _T( "%01.1f" ), getMultiplier() );

		//return "x " + string.Format("{0:0}", Multiplier);
		return std::wstring( L"x" ) + Format( _T( "%i" ), static_cast<int>( getMultiplier() ) );
	}

	void PerfectScoreObject::OnAdd_GUI()
	{
		GUI_Panel::OnAdd();

		if ( !AddedOnce )
		{
			//SlideOut(PresetPos.Top, 0);
			//SlideIn();
			//Show();
			SlideIn( 0 );
			Show();
		}

		AddedOnce = true;

		if ( getMyLevel()->NumCoins == 0 ) setObtained( true );
	}

	void PerfectScoreObject::UpdateScoreText()
	{
		float Hold = getMultiplier();
		Text->SubstituteText( ToString() );

		if ( Hold != getMultiplier() )
			MyPile->BubbleUp( false );

		// Update dots
		int NumDots = getNextBonus() / getBaseBonus();
		Dots[0]->setSize( Vector2(19.9642f, 21.49991f) * CoreMath::Periodic(.96f, 1.03f, 1.0f, Tools::t) );
		for (int i = 0; i < 8; i++)
		{
			Dots[i]->Quad_Renamed.setMyTexture( i < NumDots ? Full : Empty );
			Dots[i]->setPos( Dots[0]->getPos() + static_cast<float>( i ) * Vector2(34.0f, 0.0f) );
			Dots[i]->setSize( Dots[0]->getSize() );
		}
	}

	void PerfectScoreObject::Init_GUI()
	{
		MyPile = boost::make_shared<DrawPile>();
		EnsureFancy();

		MyPile->setPos( Vector2( 1350, -800 ) );

		// Object is carried over through multiple levels, so prevent it from being released.
		PreventRelease = true;

		PauseOnPause = true;

		MyPile->FancyPos->UpdateWithGame = true;

		boost::shared_ptr<EzFont> font;
		float scale;
		Color c, o;

        font = Resources::Font_Grobold42;
        //scale = .666f;
        scale = .5f;
        //c = new Color(228, 0, 69);
        c = bColor( 228, 0, 69 );
        o = Color::White;

		Text = boost::make_shared<EzText>( ToString(), font, 950.f, false, true );
		Text->Name = L"Text";
		Text->setScale( scale );
		Text->setPos( Vector2( 0, 0 ) );
		Text->MyFloatColor = c.ToVector4();
		Text->OutlineColor = o.ToVector4();

		Text->RightJustify = true;

		MyPile->Add( Text );

			Full = Tools::Texture( std::wstring( L"Dot_Full" ) );
			Empty = Tools::Texture( std::wstring( L"Dot_Empty" ) );
			Dots = std::vector<boost::shared_ptr<QuadClass> >();
			for ( int i = 0; i < 8; i++)
			{
				boost::shared_ptr<QuadClass> dot = boost::make_shared<QuadClass>( L"White" );
				dot->setSize( Vector2( 13.54166f, 14.58333f ) );

				MyPile->Add( dot, std::wstring( L"Dot" ) + ::ToString( i ) );
				Dots.push_back( dot );
			}

			boost::shared_ptr<QuadClass> _q;
			_q = MyPile->FindQuad( L"Dot0" ); if (_q != 0 ) { _q->setPos( Vector2(-302.7778f, -91.66668f ) ); _q->setSize( Vector2( 19.2969f, 20.78128f ) ); }

		SetPos();
	}

    void PerfectScoreObject::SetPos()
    {
			boost::shared_ptr<EzText> _t;
			_t = MyPile->FindEzText( L"Text" ); if (_t != 0 ) { _t->setPos( Vector2( 0.f, 0.f ) ); _t->setScale( 0.8000005f ); }
			MyPile->setPos( Vector2( 1569.445f, -772.2226f ) );

			// Extra squeeze
			Vector2 squeeze = Vector2(-15, 15 ) * CloudberryKingdomGame::GuiSqueeze;

			MyPile->setPos( MyPile->getPos() + squeeze );
    }

    void PerfectScoreObject::Release()
    {
        GUI_Panel::Release();
    }

	void PerfectScoreObject::MyDraw()
	{
		if ( Campaign ) return;

        Text->MyFloatColor += .05f * ( bColor(228, 0, 69).ToVector4() - Text->MyFloatColor );
        Text->setScale( Text->getScale() + .05f * ( .8f - Text->getScale() ) );
        Text->Angle += .2f * ( 0 - Text->Angle );

        //Text.Scale = 1.285f; // Jordan likes
        //Text.Scale = 0.8f; // TJ is a faggot

		if ( !getCore()->Show || getCore()->MyLevel->SuppressCheckpoints || !ShowMultiplier )
			return;

		GUI_Panel::MyDraw();
	}

	void PerfectScoreObject::InitializeInstanceFields()
	{
		Eligible = false;
		_Obtained = false;
		BonusCount = 0;
		IneligibleOnDeath = false;
		Count = 0;
		Global = false;
		ShowMultiplier = true;
		AddedOnce = false;
	}
}
