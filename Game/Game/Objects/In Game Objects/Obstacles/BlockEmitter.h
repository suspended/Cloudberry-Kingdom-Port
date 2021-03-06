#ifndef BLOCKEMITTER
#define BLOCKEMITTER

#include <small_header.h>

#include "Core/PhsxData.h"
//#include "Core/Tools/CoreMath.h"
#include "Game/Objects/ObjectBase.h"
//#include "Game/Level/Make/PieceSeedData.h"
#include "Game/Objects/In Game Objects/Blocks/MovingPlatform.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Objects/In Game Objects/Obstacles/BlockEmitter__Auto.h"
//#include "Game/Tools/Recycler.h"


namespace CloudberryKingdom
{
	struct BlockEmitter : public ObjectBase
	{
	
		virtual ~BlockEmitter()
		{
#ifdef BOOST_BIN
			OnDestructor( "BlockEmitter" );
#endif
		}


		MovingPlatform::MoveType MyMoveType;
		float Amp;

	
		std::vector<boost::shared_ptr<MovingPlatform> > Platforms;

	
		virtual void Release();

		bool AlwaysOn, Active;
		Vector2 Range;

		PhsxData EmitData;
		int Delay, Offset;
		Vector2 Size;

		virtual void OnUsed();

		virtual void OnMarkedForDeletion();

		virtual void MakeNew();

		BlockEmitter( bool BoxesOnly );

		/// <summary>
		/// If true the emitter emits multiple blocks prior to the level starting.
		/// This simulates the behavior of the level having been running before starting.
		/// </summary>
		bool DoPreEmit;

		/// <summary>
		/// When true the emitter will PreEmit on the next phsx step
		/// </summary>
	
		bool SetToPreEmit;

	
		virtual void Reset( bool BoxesOnly );

	
		void PreEmit();

	
		bool GiveCustomRange;
		bool GiveLayer;
	
		void Emit( int offset );

	
		void AddPlatform( const boost::shared_ptr<MovingPlatform> &platform );

		void RemovePlatform( const boost::shared_ptr<MovingPlatform> &platform );

		virtual void PhsxStep();

		virtual void Move( Vector2 shift );

	
		BoxStyle MyBoxStyle;
	
		void Init( Vector2 pos, const boost::shared_ptr<Level> &level, BoxStyle MyBoxStyle );

		virtual void Clone( const boost::shared_ptr<ObjectBase> &A );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef BLOCKEMITTER
