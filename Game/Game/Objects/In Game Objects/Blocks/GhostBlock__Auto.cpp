#include <small_header.h>
#include "Game/Objects/In Game Objects/Blocks/GhostBlock__Auto.h"

#include "Game/Objects/ObjectBase.h"
#include "Game/Level/Make/DifficultyHelper.h"
#include "Game/Level/Make/PieceSeedData.h"
#include "Game/Level/Make/Parameters/LevelGenData.h"
#include "Game/Level/Make/Parameters/Param.h"
#include "Game/Level/Make/Parameters/StyleData/StyleData.h"
#include "Game/Objects/AutoGen.h"
#include "Game/Objects/In Game Objects/Blocks/GhostBlock.h"
#include "Game/Objects/In Game Objects/Grab/MakeData.h"
#include "Game/Level/Level.h"
#include "Game/Player/Hero Physics/Spaceship.h"
#include "Game/Tools/Recycler.h"

#include "Game/Level/Make/Parameters/Upgrades.h"
#include "Core/Tools/Random.h"
#include "Game/Collision Detection/AABox.h"

namespace CloudberryKingdom
{

	void GhostBlock_Parameters::SetParameters( const boost::shared_ptr<PieceSeedData> &PieceSeed, const boost::shared_ptr<Level> &level )
	{
		AutoGen_Parameters::SetParameters( PieceSeed, level );

		boost::shared_ptr<CloudberryKingdom::Upgrades> u = PieceSeed->getu();

		BoxType = BoxTypes_TOP_ONLY;

		KeepUnused = Param( PieceSeed );
		if ( boost::dynamic_pointer_cast<BobPhsxSpaceship>( level->DefaultHeroType ) != 0 )
		{
			KeepUnused.SetVal( BobPhsxSpaceship::KeepUnused( u->Get( Upgrade_GHOST_BLOCK ) ) );
		}

		FillWeight = Param( PieceSeed, u->Get( Upgrade_GHOST_BLOCK ) );

		InLength = Param( PieceSeed, DifficultyHelper::Interp( 147, 75, u->Get( Upgrade_SPEED ) ) * DifficultyHelper::Interp( 1.275f,.275f, u->Get( Upgrade_GHOST_BLOCK ) ) );

		OutLength = Param( PieceSeed, __max( 60, 110 - 4 * u->Get( Upgrade_SPEED ) ) );

		Width = Param( PieceSeed, __max( 40, 93 - 2 * u->Get( Upgrade_GHOST_BLOCK ) ) );

		TimeSafety = Param( PieceSeed );
		TimeSafety.SetVal( __max( 0, DifficultyHelper::Interp( 1, 0, u->Get( Upgrade_GHOST_BLOCK ) ) ) );

		// Masochistic
		if ( PieceSeed->getu()->Get( Upgrade_GHOST_BLOCK ) == 10 )
			Masochistic = true;
	}

	GhostBlock_AutoGen::OnGhostUsedLambda::OnGhostUsedLambda( const boost::shared_ptr<GhostBlock> &block, const boost::shared_ptr<Level> &level )
	{
		this->block = block;
		this->level = level;
	}

	void GhostBlock_AutoGen::OnGhostUsedLambda::Apply()
	{
		if ( block->getCore()->GenData.Used )
			return;

		int max = block->InLength - GhostBlock::LengthOfPhaseChange;
		block->ModOffset( level->getRnd()->RndInt(static_cast<int>(.25f * max), static_cast<int>(.75f * max)) );
	}

boost::shared_ptr<GhostBlock_AutoGen> GhostBlock_AutoGen::instance = boost::make_shared<GhostBlock_AutoGen>();

	const boost::shared_ptr<GhostBlock_AutoGen> &GhostBlock_AutoGen::getInstance()
	{
		return instance;
	}

	GhostBlock_AutoGen::GhostBlock_AutoGen()
	{
		Do_WeightedPreFill_1 = true;
		//Generators.AddGenerator(this);
	}

	boost::shared_ptr<AutoGen_Parameters> GhostBlock_AutoGen::SetParameters( const boost::shared_ptr<PieceSeedData> &data, const boost::shared_ptr<Level> &level )
	{
		boost::shared_ptr<GhostBlock_Parameters> Params = boost::make_shared<GhostBlock_Parameters>();
		Params->SetParameters( data, level );

		return boost::static_pointer_cast<AutoGen_Parameters>( Params );
	}

	void GhostBlock_AutoGen::PreFill_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::PreFill_2( level, BL, TR );
	}

	void GhostBlock_AutoGen::Cleanup_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::Cleanup_2( level, BL, TR );
	}

	boost::shared_ptr<ObjectBase> GhostBlock_AutoGen::CreateAt( const boost::shared_ptr<Level> &level, Vector2 pos, Vector2 BL, Vector2 TR )
	{
		AutoGen::CreateAt( level, pos, BL, TR );

		boost::shared_ptr<StyleData> Style = level->getStyle();
		boost::shared_ptr<RichLevelGenData> GenData = level->CurMakeData->GenData;
		boost::shared_ptr<PieceSeedData> piece = level->CurMakeData->PieceSeed;

		// Get GhostBlock parameters
		boost::shared_ptr<GhostBlock_Parameters> Params = boost::static_pointer_cast<GhostBlock_Parameters>( level->getStyle()->FindParams( GhostBlock_AutoGen::getInstance() ) );

		int InLength = static_cast<int>( Params->InLength.GetVal( pos ) );
		int OutLength = static_cast<int>( Params->OutLength.GetVal( pos ) );
		int Period = InLength + OutLength;
		int Offset = level->getRnd()->Rnd->Next( Period );

		boost::shared_ptr<GhostBlock> gblock = 0;
		int NumGhosts = 1; // Number of ghosts to create
		for ( int i = 0; i < NumGhosts; i++ )
		{
			// Stagger the offsets.
			// NOTE: THIS IS DEPRECATED. We are setting the Offset when the ghost is used.
			Offset = ( Offset + i * Period / NumGhosts ) % Period;

			int Width = static_cast<int>( Params->Width.GetVal( pos ) );
			Vector2 size = Vector2( static_cast<float>( Width ), static_cast<float>( Width ) );
			//Vector2 offset = new Vector2(MyLevel.Rnd.Rnd.Next(-60, 0), MyLevel.Rnd.Rnd.Next(-60, 0) - size.Y);
			Vector2 offset = Vector2();
			if ( i == 1 )
				offset = Vector2( 50, 0 );

			gblock = boost::static_pointer_cast<GhostBlock>( level->getRecycle()->GetObject(ObjectType_GHOST_BLOCK, false) );

            // Box type
            if ( Params->BoxType == GhostBlock_Parameters::BoxTypes_TOP_ONLY )
                gblock->TallBox = false;
            else if ( Params->BoxType == GhostBlock_Parameters::BoxTypes_FULL )
                gblock->TallBox = true;
            else if ( Params->BoxType == GhostBlock_Parameters::BoxTypes_LONG )
                gblock->TallInvertBox = true;
				
			gblock->Init( pos + offset, size, level );

			gblock->getBlockCore()->BlobsOnTop = false;

			gblock->getBlockCore()->Decide_RemoveIfUnused(Params->KeepUnused.GetVal(pos), level->getRnd());
			gblock->getBlockCore()->GenData.EdgeSafety = static_cast<float>( GenData->Get(DifficultyParam_EDGE_SAFETY, pos) );
			gblock->TimeSafety = Params->TimeSafety.GetVal( pos );

			if ( level->getStyle()->RemoveBlockOnOverlap )
				gblock->getBlockCore()->GenData.RemoveIfOverlap = true;


			gblock->InLength = InLength;
			gblock->OutLength = OutLength;
			gblock->Offset = Offset;
			//if (i == 1) gblock.Offset = Offset + (int)((InLength + OutLength) * .5f);
			//if (i == 2) gblock.Offset = Offset + (int)((InLength + OutLength) * .666f);

			boost::shared_ptr<GhostBlock> block = gblock;
			block->getCore()->GenData.OnUsed = boost::make_shared<OnGhostUsedLambda>(block, level);

			// Box type
			if ( Params->BoxType == GhostBlock_Parameters::BoxTypes_TOP_ONLY )
			{
				gblock->getBox()->TopOnly = true;
				gblock->TallBox = false;
			}
			else if ( Params->BoxType == GhostBlock_Parameters::BoxTypes_FULL )
			{
				gblock->getBox()->TopOnly = false;
				gblock->TallBox = true;
			}
			else if ( Params->BoxType == GhostBlock_Parameters::BoxTypes_LONG )
			{
				gblock->getBox()->TopOnly = false;
				gblock->TallInvertBox = true;
			}

			level->AddBlock( gblock );
		}

		return gblock;
	}
}
