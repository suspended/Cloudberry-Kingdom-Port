#include <small_header.h>
#include "Game/Level/Make/Parameters/StyleData/DownData.h"

#include "Core/Tools/Random.h"
#include "Game/Level/Make/Parameters/StyleData/UpData.h"


namespace CloudberryKingdom
{

	void DownData::CalculateKeepUnused( float JumpLevel )
	{
		{
			float MaxChance = .05f;
			float chance = MaxChance - .1f * ( MaxChance - 0 ) * JumpLevel;
			ChanceToKeepUnused = Rnd->RndFloat( 0, chance );
		}
	}

	DownData::DownData( const boost::shared_ptr<Rand> &Rnd ) : VerticalData( Rnd )
	{
		VisualStyle = VisualStyles_CASTLE;
	}

	void DownData::Randomize()
	{
		VerticalData::Randomize();
	}

}
