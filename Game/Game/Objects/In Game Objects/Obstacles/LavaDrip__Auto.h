#ifndef LAVADRIP__AUTO
#define LAVADRIP__AUTO

#include <small_header.h>

//#include "Game/Level/Make/DifficultyHelper.h"
//#include "Game/Level/Make/PieceSeedData.h"
#include "Game/Level/Make/Parameters/Param.h"
#include "Game/Objects/AutoGen.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Objects/In Game Objects/Obstacles/LavaDrip.h"
//#include "Game/Tools/Recycler.h"


namespace CloudberryKingdom
{
	struct PieceSeedData;
}

namespace CloudberryKingdom
{
	struct Level;
}

namespace CloudberryKingdom
{
	struct AutoGen_Parameters;
}

namespace CloudberryKingdom
{
	struct LavaDrip_Parameters : public AutoGen_Parameters
	{
	
		virtual ~LavaDrip_Parameters()
		{
#ifdef BOOST_BIN
			OnDestructor( "LavaDrip_Parameters" );
#endif
		}


		float LavaDripStepCutoff;
		Param LavaDripStep, Speed;
		VectorParam Length;

		virtual void SetParameters( const boost::shared_ptr<PieceSeedData> &PieceSeed, const boost::shared_ptr<Level> &level );

	
		void InitializeInstanceFields();


		LavaDrip_Parameters()
		{
			InitializeInstanceFields();
		}
	};

	struct LavaDrip_AutoGen : public AutoGen
	{
	
		static boost::shared_ptr<LavaDrip_AutoGen> instance;
	
		const static boost::shared_ptr<LavaDrip_AutoGen> &getInstance();

	
		LavaDrip_AutoGen();

	
		boost::shared_ptr<AutoGen_Parameters> SetParameters( const boost::shared_ptr<PieceSeedData> &data, const boost::shared_ptr<Level> &level );

		void PreFill_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void Cleanup_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );
	};
}


#endif	//#ifndef LAVADRIP__AUTO
