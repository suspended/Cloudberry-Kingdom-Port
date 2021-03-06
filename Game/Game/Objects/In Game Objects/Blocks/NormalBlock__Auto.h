#ifndef NORMALBLOCK__AUTO
#define NORMALBLOCK__AUTO

#include <small_header.h>

//#include "Core/Graphics/Draw/Quads/PieceQuad.h"
//#include "Game/Collision Detection/AABox.h"
//#include "Game/Objects/ObjectBase.h"
//#include "Game/Objects/In Game Objects/Blocks/Block.h"
//#include "Game/Objects/In Game Objects/Blocks/Wall.h"
//#include "Game/Level/Make/PieceSeedData.h"
//#include "Game/Level/Make/Parameters/LevelGenData.h"
#include "Game/Level/Make/Parameters/Param.h"
//#include "Game/Level/Make/Parameters/StyleData/StyleData.h"
#include "Game/Objects/AutoGen.h"
//#include "Game/Objects/In Game Objects/Blocks/NormalBlock.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Player/Hero Physics/Spaceship.h"
//#include "Game/Tools/Recycler.h"


namespace CloudberryKingdom
{
	
	struct NormalBlock_Parameters : public AutoGen_Parameters
	{
	
		virtual ~NormalBlock_Parameters()
		{
#ifdef BOOST_BIN
			OnDestructor( "NormalBlock_Parameters" );
#endif
		}


		Param KeepUnused;

		/// <summary>
		/// Whether to make normal blocks or not. Doesn't affect other fill weights.
		/// </summary>
		bool Make;

		bool CustomWeight;

		boost::shared_ptr<Wall> MyWall;
		boost::shared_ptr<Wall> SetWall( LevelGeometry geometry );

		/// <summary>
		/// Whether to do the standard Stage1Fill. False when certain special fills are set.
		/// </summary>
		bool DoStage1Fill, DoInitialPlats, DoFinalPlats;

		virtual void SetParameters( const boost::shared_ptr<PieceSeedData> &PieceSeed, const boost::shared_ptr<Level> &level );

	
		void InitializeInstanceFields();


		NormalBlock_Parameters()
		{
			InitializeInstanceFields();
		}
	};

	struct NormalBlock_AutoGen : public AutoGen
	{
	
		static boost::shared_ptr<NormalBlock_AutoGen> instance;
	
		const static boost::shared_ptr<NormalBlock_AutoGen> &getInstance();

	
		NormalBlock_AutoGen();

	
		boost::shared_ptr<AutoGen_Parameters> SetParameters( const boost::shared_ptr<PieceSeedData> &data, const boost::shared_ptr<Level> &level );

	
		void MakeWall( const boost::shared_ptr<Level> &level );

		boost::shared_ptr<NormalBlock_Parameters> GetParams( const boost::shared_ptr<Level> &level );

	
		void PreFill_1( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void PreFill_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void Cleanup_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		boost::shared_ptr<ObjectBase> CreateAt( const boost::shared_ptr<Level> &level, Vector2 pos );
		boost::shared_ptr<ObjectBase> CreateAt( const boost::shared_ptr<Level> &level, Vector2 pos, Vector2 BL, Vector2 TR );
	};
}


#endif	//#ifndef NORMALBLOCK__AUTO
