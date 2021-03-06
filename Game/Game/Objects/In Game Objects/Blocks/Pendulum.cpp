#include <small_header.h>
#include "Game/Objects/In Game Objects/Blocks/Pendulum.h"

#include "Core/Graphics/Draw/Quads/PieceQuad.h"
#include "Core/Tools/CoreMath.h"
#include "Game/Collision Detection/AABox.h"
#include "Game/Objects/ObjectBase.h"
#include "Game/Tilesets/TileSet.h"
#include "Game/Objects/In Game Objects/Blocks/Block.h"
#include "Game/Objects/IBounded.h"
#include "Game/Objects/Bob/Bob.h"
#include "Game/Objects/In Game Objects/Blocks/NormalBlockDraw.h"
#include "Game/Objects/In Game Objects/Grab/MakeData.h"
#include "Game/Level/Level.h"
#include "Game/Objects/In Game Objects/Obstacles/BlockEmitter__Auto.h"
#include "Game/Tilesets/BlockGroup.h"
#include "Game/Tools/Recycler.h"
#include "Game/Tools/Tools.h"
#include "Game/Tilesets/TileSetInfo.h"

#include "Game/Collision Detection/FloatRectangle.h"
#include "Game/Tools/Camera.h"

namespace CloudberryKingdom
{

	void Pendulum::PendulumTileInfo::InitializeInstanceFields()
	{
		Group = PieceQuad::ElevatorGroup;
	}

	void Pendulum::LandedOn( const boost::shared_ptr<Bob> &bob )
	{
		BlockBase::LandedOn( bob );
	}

	void Pendulum::MakeNew()
	{
		getBlockCore()->Init();
		getBlockCore()->MyType = ObjectType_PENDULUM;
		getCore()->DrawLayer = 3;

		MyBox->TopOnly = true;

		Angle = 0;
		MaxAngle = 0;
		Period = 150;
		Offset = 0;
		PivotPoint = Vector2();

		Active = false;

		getBlockCore()->Layer = .7f;

		getCore()->RemoveOnReset = false;
		getBlockCore()->HitHead = true;

		getCore()->EditHoldable = getCore()->Holdable = true;
	}

	Pendulum::Pendulum( bool BoxesOnly ) :
		MoveType( PendulumMoveType_LINE ),
		Angle( 0 ),
		MaxAngle( 0 ),
		Length( 0 ),
		Period( 0 ),
		Offset( 0 ),
		AddAngle( 0 ),
		CorrespondingAngle( 0 ),
		MyTime( 0 )
	{
		InitializeInstanceFields();
		MyBox = boost::make_shared<AABox>();
		MyDraw = boost::make_shared<NormalBlockDraw>();

		MakeNew();

		getCore()->BoxesOnly = BoxesOnly;
	}

	Vector2 Pendulum::TR_Bound()
	{
		Vector2 max = Vector2::Max( Vector2::Max( CalcPosition( 0 ), CalcPosition( .5f ) ), Vector2::Max( CalcPosition( 0.25f ), CalcPosition( .75f ) ) );
		return max;
	}

	Vector2 Pendulum::BL_Bound()
	{
		Vector2 min = Vector2::Min( Vector2::Min( CalcPosition( 0 ), CalcPosition( .5f ) ), Vector2::Min( CalcPosition( 0.25f ), CalcPosition( .75f ) ) );

		return min;
	}

	void Pendulum::Init( Vector2 center, Vector2 size, const boost::shared_ptr<Level> &level, BoxStyle _MyBoxStyle )
	{
        this->MyBoxStyle = _MyBoxStyle;

        if ( MyBoxStyle == BoxStyle_NO_SIDES )
        {
            getBox()->TopOnly = false;
            getBox()->NoSides = true;
        }
        else if ( MyBoxStyle == BoxStyle_FULL_BOX )
        {
            getBox()->TopOnly = false;
        }

		BlockBase::Init( center, size, level, level->getInfo()->Pendulums->Group );

		getCore()->Data.Position = getCore()->StartData.Position = PivotPoint = center;
	}

	void Pendulum::MoveToBounded( Vector2 shift )
	{
		Move( shift );
	}

	void Pendulum::CalculateLength()
	{
		Length = ( getCore()->StartData.Position - PivotPoint ).Length();
	}

	void Pendulum::Move( Vector2 shift )
	{
		BlockBase::Move( shift );

		getBox()->Move(shift);
	}

	void Pendulum::Reset( bool BoxesOnly )
	{
		BlockBase::Reset( BoxesOnly );

		getCore()->Data = getBlockCore()->Data = getBlockCore()->StartData;

		MyBox->Current->Center = getBlockCore()->StartData.Position;
		MyBox->SetTarget( MyBox->Current->Center, MyBox->Current->Size );
		MyBox->SwapToCurrent();

		Active = false;
	}

	Vector2 Pendulum::CalcPosition( float t )
	{
		//switch ( MoveType )
		{
			//default:
				CorrespondingAngle = MaxAngle * static_cast<float>( cos( 2 * M_PI * t ) );

				// Horizontal
				//Vector2 Dir = new Vector2((float)Math.Cos(AddAngle + CorrespondingAngle - Math.PI / 2),
				//                          (float)-1);

				// Normal
				Vector2 Dir = Vector2( static_cast<float>( cos( AddAngle + CorrespondingAngle - M_PI / 2 ) ), static_cast<float>( sin( AddAngle + CorrespondingAngle - M_PI / 2 ) ) );

				// Upside-down
				//Vector2 Dir = new Vector2((float)Math.Cos(AddAngle + CorrespondingAngle - Math.PI / 2),
				//                          (float)Math.Sin(AddAngle + CorrespondingAngle + Math.PI / 2));

				// Vertical
				//Vector2 Dir = new Vector2((float)0,
				//                          (float)Math.Sin(AddAngle + CorrespondingAngle - Math.PI / 2));

				return PivotPoint + Length * Dir;
		}

		//return BlockCore.StartData.Position;
	}

	void Pendulum::PhsxStep()
	{
		if ( !getCore()->Held )
		{
			float Step = CoreMath::Modulo( getCore()->GetIndependentPhsxStep() + Offset, static_cast<float>(Period) );
			setPos( CalcPosition( static_cast<float>( Step ) / Period ) );
		}

		Vector2 PhsxCutoff = Vector2( 900 + Length );
		if ( getCore()->MyLevel->BoxesOnly )
			PhsxCutoff = Vector2( 500, 500 );
		if ( !getCore()->MyLevel->getMainCamera()->OnScreen(getCore()->Data.Position, PhsxCutoff) )
		{
			Active = false;
			getCore()->SkippedPhsx = true;
			getCore()->WakeUpRequirements = true;
			return;
		}
		getCore()->SkippedPhsx = false;

		MyBox->Target->Center = getCore()->Data.Position;

		MyBox->SetTarget( MyBox->Target->Center, MyBox->Current->Size );
		if ( !Active )
			MyBox->SwapToCurrent();

		Active = true;
	}

	void Pendulum::PhsxStep2()
	{
		if ( !Active )
			return;

		MyBox->SwapToCurrent();
	}

	void Pendulum::Draw()
	{
		bool DrawSelf = true;

		if ( !getCore()->Held )
		{
			if ( !Active )
				return;

			if ( MyBox->Current->BL.X > getBlockCore()->MyLevel->getMainCamera()->TR.X || MyBox->Current->BL.Y > getBlockCore()->MyLevel->getMainCamera()->TR.Y )
				DrawSelf = false;
			if ( MyBox->Current->TR.X < getBlockCore()->MyLevel->getMainCamera()->BL.X || MyBox->Current->TR.Y < getBlockCore()->MyLevel->getMainCamera()->BL.Y )
				DrawSelf = false;

			if ( getCore()->MyLevel->CurrentDrawLayer == getCore()->DrawLayer )
			{
				//if (PivotLocationType == PivotLocationTypes.TopBottom)
			{
					if ( PivotPoint.X < getCore()->MyLevel->getMainCamera()->TR.X && PivotPoint.X > getCore()->MyLevel->getMainCamera()->BL.X )
						DrawSelf = true;
				}
				//else
				//{
				//    if (PivotPoint.Y < Core.MyLevel.MainCamera.TR.Y && PivotPoint.Y > Core.MyLevel.MainCamera.BL.Y)
				//        DrawSelf = true;
				//}
			}
		}

		if ( DrawSelf )
		{
			if ( Tools::DrawBoxes )
				MyBox->Draw( Tools::QDrawer, Color::Olive, 15 );
		}

		if ( Tools::DrawGraphics )
		{
			if ( DrawSelf && !getBlockCore()->BoxesOnly )
			{
				//Vector2 add = new Vector2(Box.Current.Size.X, 0);
				//Tools::QDrawer.DrawLine(Core.Data.Position + add, PivotPoint + add, Info.SpikeyGuys.Chain);
				//Tools::QDrawer.DrawLine(Core.Data.Position - add, PivotPoint - add, Info.SpikeyGuys.Chain);

				int RepeatWidth = 1900;
				if ( CoreData->Data.Position.Y < -1200 ) RepeatWidth = 2150;
				Tools::QDrawer->DrawLine( getCore()->Data.Position, PivotPoint, getInfo()->Boulders->Chain, RepeatWidth );

				MyDraw->Update();
				MyDraw->Draw();
			}

			getBlockCore()->Draw();
		}
	}

	void Pendulum::ResetPieces()
	{
		if ( getInfo()->Pendulums->Group != 0 )
			if ( MyDraw->MyTemplate != 0 )
			{
				MyDraw->MyTemplate = getCore()->getMyTileSet()->GetPieceTemplate( boost::static_pointer_cast<BlockBase>( shared_from_this() ), getRnd(), getInfo()->Pendulums->Group);
				MyDraw->Init( boost::static_pointer_cast<BlockBase>( shared_from_this() ), MyDraw->MyTemplate, false );
			}
	}

	void Pendulum::Extend( Side side, float pos )
	{
		MyBox->Invalidated = true;

		MyBox->Extend( side, pos );

		if ( !getCore()->BoxesOnly )
			ResetPieces();

		getBlockCore()->StartData.Position = MyBox->Current->Center;

		ResetPieces();
	}

	void Pendulum::Clone( const boost::shared_ptr<ObjectBase> &A )
	{
		boost::shared_ptr<Pendulum> BlockA = boost::dynamic_pointer_cast<Pendulum>( A );

		Init( BlockA->getBox()->Current->Center, BlockA->getBox()->Current->Size, BlockA->getMyLevel(), MyBoxStyle );

		getCore()->Clone(A->getCore());

		MoveType = BlockA->MoveType;

		Angle = BlockA->Angle;
		MaxAngle = BlockA->MaxAngle;
		Period = BlockA->Period;
		Offset = BlockA->Offset;
		PivotPoint = BlockA->PivotPoint;
		Length = BlockA->Length;

		AddAngle = BlockA->AddAngle;
		//PivotLocationType = BlockA.PivotLocationType;
	}

	void Pendulum::InitializeInstanceFields()
	{
		MyTime = 0;
		MyBoxStyle = static_cast<BoxStyle>( 0 );
	}
}
