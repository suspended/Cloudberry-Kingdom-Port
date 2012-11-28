#ifndef _LIST_H_
#define _LIST_H_

#include <algorithm>
#include <cstring>
#include <vector>

template<class T>
inline int IndexOf( const std::vector<T> &v, const T &o )
{
	using namespace std;

	vector<T>::iterator i = find( v.begin(), v.end(), o );
	return i - v.begin();
}

template<class T>
inline void CopyFromTo( const std::vector<T> &v1, std::vector<T> &v2 )
{
	v2.assign( v1.begin(), v1.end() );
}

template<class T>
inline void AddRange( std::vector<T> destination, const std::vector<T> source )
{
	for ( std::vector<T>::const_iterator item = source.begin(); item != source.end(); ++item )
		destination.push_back( item );
}

#endif
