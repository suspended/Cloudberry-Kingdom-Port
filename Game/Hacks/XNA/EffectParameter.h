#ifndef _EFFECTPARAMETERS_H_
#define _EFFECTPARAMETERS_H_

struct EffectParameter
{



	// FIXME: Implement everything.
	void SetValue( const Vector4 &v )
	{
	}

	void SetValue( const Matrix &m )
	{
	}

	void SetValue( const std::shared_ptr<struct Texture2D> &t )
	{
	}

	void SetValue( const Vector2 &v )
	{
	}

	void SetValue( float v )
	{
	}

	float GetValueSingle()
	{
		return 0.f;
	}

};

#endif