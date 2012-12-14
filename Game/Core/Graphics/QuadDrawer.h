﻿#ifndef QUADDRAWER
#define QUADDRAWER

#include <global_header.h>

namespace CloudberryKingdom
{
	struct QuadDrawer
	{

	
		static void InitializeStatics();

	
		std::shared_ptr<GraphicsDevice> Device;

	
		std::shared_ptr<EzEffect> DefaultEffect;
		std::shared_ptr<EzTexture> DefaultTexture;

	
		std::shared_ptr<EzEffect> CurrentEffect;
		std::shared_ptr<EzTexture> CurrentTexture;

		/// <summary>
		/// Color rotation matrix.
		/// </summary>
		const Matrix &getCurrentMatrix() const;

		void setCurrentMatrix( const Matrix &value );
		Matrix _CurrentMatrix;
	
		float CurrentMatrixSignature;
	
		bool Current_U_Wrap, Current_V_Wrap;
	
		std::vector<MyOwnVertexFormat> Vertices;
		int N;
		int TrianglesInBuffer;
	
		int i;

		SimpleQuad LineQuad;

		std::shared_ptr<SamplerState> WrapWrap, ClampWrap, WrapClamp, ClampClamp;

	
		const float &getGlobalIllumination() const;
		void setGlobalIllumination( const float &value );
	
		float _GlobalIllumination;
		float Illumination;

		//float CurrentIllumination = 1f;
		//public void InvalidateIllumination() { CurrentIllumination = -1; }

	
		QuadDrawer( const std::shared_ptr<GraphicsDevice> &device, int n );

		void SetColorMatrix( Matrix m, float signature );

		void DrawQuad( const std::shared_ptr<Quad> &quad );

		void SetInitialState();

	
		void SetSamplerState();

	
		void SetAddressMode( bool U_Wrap, bool V_Wrap );

		void DrawQuad_Particle( SimpleQuad &quad );

		void DrawQuad( SimpleQuad &quad );

		void DrawFilledBox( Vector2 BL, Vector2 TR, Color color );

		void DrawLine( Vector2 x1, Vector2 x2, const std::shared_ptr<LineSpriteInfo> &info );
		void DrawLine( Vector2 x1, Vector2 x2, const std::shared_ptr<LineSpriteInfo> &info, Vector4 Tint, float Width );
		void DrawLine( Vector2 x1, Vector2 x2, const std::shared_ptr<LineSpriteInfo> &info, Vector4 Tint, float Width, float v_shift );
		void DrawLine( Vector2 x1, Vector2 x2, Color color, float width );
		void DrawLine( Vector2 x1, Vector2 x2, Color color, float width, const std::shared_ptr<EzTexture> &Tex, const std::shared_ptr<EzEffect> &fx, float RepeatWidth, int Dir, bool Illumination );
		void DrawLine( Vector2 x1, Vector2 x2, Color color, float width, const std::shared_ptr<EzTexture> &Tex, const std::shared_ptr<EzEffect> &fx, float RepeatWidth, int Dir, float BlendAddRatio );
		void DrawLine( Vector2 x1, Vector2 x2, Color color, float width, const std::shared_ptr<EzTexture> &Tex, const std::shared_ptr<EzEffect> &fx, float RepeatWidth, int Dir, float BlendAddRatio, float v_shift, bool Wrap );

		void DrawLineAndEndPoints( Vector2 x1, Vector2 x2, Color color, float width, const std::shared_ptr<EzTexture> &Tex1, const std::shared_ptr<EzTexture> &Tex2, const std::shared_ptr<EzTexture> &Tex3, const std::shared_ptr<EzEffect> &fx, float RepeatWidth, int Dir, float BlendAddRatio, float v_shift );

		void DrawCircle( Vector2 x, float r, Color color );

	
		static float CurLightSourceFade;
	
		void DrawLightSource( Vector2 x, float r, float Fade, Color color );

		void DrawSquareDot( Vector2 x, Color color, float width );
		void DrawSquareDot( Vector2 x, Color color, float width, const std::shared_ptr<EzTexture> &Tex, const std::shared_ptr<EzEffect> &fx );


		void DrawToScaleQuad( Vector2 x, Color color, float width );
		void DrawToScaleQuad( Vector2 x, Color color, float width, const std::shared_ptr<EzTexture> &Tex, const std::shared_ptr<EzEffect> &fx );

		void DrawBox( Vector2 BL, Vector2 TR, Color color, float width );

		void SetToDefaultTexture();

		/// <summary>
		/// Makes sure the current texture isn't set to any RenderTargets
		/// </summary>
		void WashTexture();

		void Flush();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef QUADDRAWER
