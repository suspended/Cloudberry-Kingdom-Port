#ifndef _NETWORK_PS3_H_
#define _NETWORK_PS3_H_

/// Get current NP score context id.
/**
 * @param[out] id Current NP id.
 * @return True if the id is valid, false otherwise.
 */
bool GetNPScoreContext( int &id );

/// Are the networking features available?
/**
 * @return True if networking features are available, false otherwise.
 */
bool IsNPAvailable();

#endif
