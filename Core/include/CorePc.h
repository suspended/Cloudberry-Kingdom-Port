#ifndef _CORE_PC_H_
#define _CORE_PC_H_

#include "ForwardDeclarations.h"

/**
 * PC Core.
 */
class CorePc
{

	/// Is the game currently running?
	bool running_;

	/// The game.
	GameLoop &game_;

	// Components.

	QuadDrawer *qd_;

private:

	/// No copyig.
	CorePc( const CorePc & );

	/// No assignment.
	CorePc &operator = ( const CorePc & );

public:

	CorePc( GameLoop &game );
	~CorePc();

	/**
	 * @see Core::Run()
	 */
	int Run();

	/**
	 * @see Core::Exit()
	 */
	void Exit();

	// Accessors to components.
	QuadDrawer *GetQuadDrawer()
	{
		assert( qd_ );
		return qd_;
	}

};

#endif
