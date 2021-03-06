#ifndef _FILESYSTEM_H_
#define _FILESYSTEM_H_

#include <Architecture/Singleton.h>
#include <ForwardDeclarations.h>

#include <memory>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/enable_shared_from_this.hpp>

#ifdef CAFE
	#include "FilesystemWiiU.h"
#elif PS3
	#include "FilesystemPS3.h"
#elif VITA
	#include "FilesystemVita.h"
#else
	#include "FilesystemPc.h"
#endif

// Forward declarations.
class File;

/**
 * Base filesystem.
 */
class Filesystem : public Singleton< Filesystem >
{

#ifdef CAFE
	FilesystemWiiU impl_;
#elif PS3
	FilesystemPS3 impl_;
#elif VITA
	FilesystemVita impl_;
#else
	FilesystemPc impl_;
#endif

private:

	/// No copying.
	Filesystem( const Filesystem & ) { }

	/// No assignment.
	Filesystem &operator = ( const Filesystem & ) {	return *this; }

public:

	Filesystem();
	~Filesystem();

	/// Open a file for reading.
	/**
	 * @param path Path to file.
	 * @param write Should the file be open to writing?
	 * @return File interface.
	 */
	boost::shared_ptr<File> Open( const std::string &path, bool write = false )
	{
		return impl_.Open( path, write );
	}

	/// Get core singleton.
	static Filesystem &GetSingleton();
};

#define FILESYSTEM Filesystem::GetSingleton()

#endif
