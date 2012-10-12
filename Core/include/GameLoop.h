#ifndef _GAME_LOOP_H_
#define _GAME_LOOP_H_

/**
 * Application entry point.
 */
class GameLoop
{

public:

	virtual ~GameLoop() { }

	/// Update a single frame.
	virtual void Update() = 0;

};

#endif
