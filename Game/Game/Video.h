﻿#ifndef VIDEO
#define VIDEO

#include <global_header.h>

#include <Graphics/Video.h>
#include <Graphics/VideoPlayer.h>
#include "Hacks/NET/DateTime.h"

namespace CloudberryKingdom
{

	struct MainVideo
	{
	
		static void InitializeStatics();

	
		static boost::shared_ptr<ContentManager> Content;

	
		static bool Playing;

	
		static boost::shared_ptr<Video> CurrentVideo;
		static boost::shared_ptr<VideoPlayer> VPlayer;

		static boost::shared_ptr<EzTexture> VEZTexture;

		static double Duration, Elapsed;

		static bool CanSkip;
		static float LengthUntilUserCanSkip;

		static std::vector<boost::shared_ptr<SubtitleAction> > Subtitles;
		static int SubtitleIndex;
		static boost::shared_ptr<EzText> SubtitleText;

	
		static void StartVideo_CanSkipIfWatched( const std::wstring &MovieName );

		static void StartVideo_CanSkipIfWatched_OrCanSkipAfterXseconds( const std::wstring &MovieName, float LengthUntilCanSkip );

	
		static void StartVideo( const std::wstring &MovieName, bool CanSkipVideo, float LengthUntilCanSkip );


		static void UpdateElapsedTime();

		static bool Paused;
		static void UserInput();

		static void Subtitle();

	
		static bool Draw();

	
		static bool Cleaned;
	
		static void Finish();
	};
}


#endif	//#ifndef VIDEO
