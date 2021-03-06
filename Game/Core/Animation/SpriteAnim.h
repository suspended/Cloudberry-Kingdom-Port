#ifndef SPRITEANIM
#define SPRITEANIM

#include <small_header.h>

//#include "Core/Graphics/Draw/Object/ObjectClass.h"


#include "Core/Lambdas/Lambda_2.h"

#include <Graphics/Texture2D.h>

namespace CloudberryKingdom
{

	struct SpriteAnim
	{
	
		float dt;
		std::vector<boost::shared_ptr<Texture2D> > Frames;
		Vector2 Padding;

		void Release();

	};

	/// <summary>
	/// Should be replaced. Right now this is used for drawing the players in the replays, but replays should instead be reusing the same draw code for the player as the normal draw code.
	/// </summary>
	struct SpriteAnimGroup
	{
	
		std::map<int, boost::shared_ptr<SpriteAnim> > SpriteAnims;

		void Release();

		SpriteAnimGroup();

		void Init( const boost::shared_ptr<ObjectClass> &Obj, Vector2 ExtraPadding,
			boost::shared_ptr<Lambda_2<std::map<int, boost::shared_ptr<SpriteAnim> >, Vector2> > SpriteFunc );

		boost::shared_ptr<Texture2D> Get( int anim, float t, Vector2 &padding );
	};

}


#endif	//#ifndef SPRITEANIM
