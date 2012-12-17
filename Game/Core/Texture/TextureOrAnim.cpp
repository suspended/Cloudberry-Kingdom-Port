﻿#include <global_header.h>

namespace CloudberryKingdom
{

	TextureOrAnim::TextureOrAnim()
	{
		InitializeInstanceFields();
	}

	TextureOrAnim::TextureOrAnim( const std::wstring &name )
	{
		InitializeInstanceFields();
		Set( name );
	}

	void TextureOrAnim::Set( const std::wstring &name )
	{
		if ( Tools::TextureWad->AnimationDict.find( name ) != Tools::TextureWad->AnimationDict.end() )
		{
			MyAnim = Tools::TextureWad->AnimationDict[ name ];
			IsAnim = true;
		}
		else
		{
			MyTexture = Tools::Texture( name );
			IsAnim = false;
		}
	}

	boost::shared_ptr<TextureOrAnim> TextureOrAnim::Get( const boost::shared_ptr<EzTexture> &texture )
	{
		boost::shared_ptr<TextureOrAnim> t_or_a = boost::make_shared<TextureOrAnim>();
		t_or_a->MyTexture = texture;
		return t_or_a;
	}

	boost::shared_ptr<TextureOrAnim> TextureOrAnim::Get( const std::wstring &name )
	{
		boost::shared_ptr<TextureOrAnim> t_or_a = boost::make_shared<TextureOrAnim>();
		t_or_a->Set( name );
		return t_or_a;
	}

	void TextureOrAnim::InitializeInstanceFields()
	{
		IsAnim = false;
	}
}
