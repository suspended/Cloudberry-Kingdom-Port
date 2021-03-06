#ifndef FIRESNAKE__AUTO
#define FIRESNAKE__AUTO

#include <small_header.h>

//#include "Game/Objects/ObjectBase.h"
//#include "Game/Level/Make/DifficultyHelper.h"
//#include "Game/Level/Make/PieceSeedData.h"
#include "Game/Level/Make/Parameters/Param.h"
#include "Game/Objects/AutoGen.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Objects/In Game Objects/Obstacles/CloudberryKingdom.Firesnake.h"
//#include "Game/Tools/Recycler.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{

	struct Firesnake_Parameters : public AutoGen_Parameters
	{
	
		virtual ~Firesnake_Parameters()
		{
#ifdef BOOST_BIN
			OnDestructor( "Firesnake_Parameters" );
#endif
		}


		struct _Special
		{
		};
	
		Param Step, Period;
		VectorParam RadiiX, RadiiY;

		bool Make;

		_Special Special;

		std::vector<std::vector<unsigned long long> > Snakes;

		virtual void SetParameters( const boost::shared_ptr<PieceSeedData> &PieceSeed, const boost::shared_ptr<Level> &level );

	
		void InitializeInstanceFields();


		Firesnake_Parameters() :
			Make( false )
		{
			InitializeInstanceFields();
		}
	};

	struct Firesnake_AutoGen : public AutoGen
	{
	
		static boost::shared_ptr<Firesnake_AutoGen> instance;
	
		const static boost::shared_ptr<Firesnake_AutoGen> &getInstance();

	
		Firesnake_AutoGen();

	
		boost::shared_ptr<AutoGen_Parameters> SetParameters( const boost::shared_ptr<PieceSeedData> &data, const boost::shared_ptr<Level> &level );

		boost::shared_ptr<Firesnake_Parameters> GetParams( const boost::shared_ptr<Level> &level );

		void Cleanup_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void CreateLine( const boost::shared_ptr<Level> &level, Vector2 pos );

		boost::shared_ptr<ObjectBase> CreateAt( const boost::shared_ptr<Level> &level, Vector2 pos );

		void PreFill_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );
	};
}


#endif	//#ifndef FIRESNAKE__AUTO
