#ifndef ANIMATIONDATA_VECTOR
#define ANIMATIONDATA_VECTOR

#include <small_header.h>

//#include "Core/WriteReadTools.h"


#include "Hacks/NET/BinaryWriter.h"
#include "Hacks/NET/BinaryReader.h"

namespace CloudberryKingdom
{

	struct OneAnim
	{
	
		std::vector<Vector2> Data;

	};

	struct AnimationData
	{
		/// <summary>
		/// If false, only changing values are recorded
		/// </summary>
	
		static bool RecordAll;

		std::vector<OneAnim> Anims;

		bool Linear;

		Vector2 Hold;

		void Release();

		void Write( const boost::shared_ptr<BinaryWriter> &writer );

		void Read( const boost::shared_ptr<BinaryReader> &reader );

		AnimationData();

		AnimationData( const AnimationData &data );

		void CopyAnim( const AnimationData &data, int Anim );

		//public AnimationData()
		void Init();

		void InsertFrame( int anim, int frame );

		void DeleteFrame( int anim, int frame );

		void AddFrame( Vector2 val, int anim );
		void Set( Vector2 val, int anim, int frame );

		Vector2 Get( int anim, int frame );

		Vector2 Transfer( int DestAnim, float DestT, int DestLength, bool DestLoop, bool DestLinear, float t );

		Vector2 Calc( int anim, float t, int Length, bool Loop, bool Linear );

	
		Vector3 VecAndLength( Vector2 v );
	
		Vector2 CalcAxis( int anim, float t, int Length, bool Loop, bool Linear );
	};
}


#endif	//#ifndef ANIMATIONDATA_VECTOR
