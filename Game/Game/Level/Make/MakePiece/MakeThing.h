#ifndef MAKETHING
#define MAKETHING

namespace CloudberryKingdom
{
	struct MakeThing
	{

		MakeThing() { }
		virtual ~MakeThing()
		{
#ifdef BOOST_BIN
			OnDestructor( "MakeThing" );
#endif
		}


		virtual void Phase1() { }
		virtual void Phase2() { }
		virtual void Phase3() { }
		virtual void Cleanup() { }
	};
}


#endif	//#ifndef MAKETHING
