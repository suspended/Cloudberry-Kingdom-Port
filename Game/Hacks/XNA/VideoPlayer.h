#ifndef _VIDEOPLAYER_H_
#define _VIDEOPLAYER_H_

struct VideoPlayer
{

	bool IsLooped;

	VideoPlayer() : IsLooped( false ) { }

	void Play( const boost::shared_ptr<Video> &video )
	{
	}

	boost::shared_ptr<Texture2D> GetTexture()
	{
		return boost::shared_ptr<Texture2D>();
	}

};

#endif