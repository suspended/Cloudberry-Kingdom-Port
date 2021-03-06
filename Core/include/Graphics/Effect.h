#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "EffectParameter.h"
#include "EffectTechnique.h"

#include <memory>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <string>

class Effect
{

	boost::shared_ptr<EffectTechnique> DefaultTechnique;

	struct EffectInternal *internal_;
	
	friend class EffectPass;
	friend class EffectParameter;

	void Apply();

public:

	boost::shared_ptr<EffectTechnique> CurrentTechnique;

	Effect();
	~Effect();

	void Load( const std::string &name );

	boost::shared_ptr<EffectParameter> Parameters( const std::string &name );
	boost::shared_ptr<EffectTechnique> Techniques( const std::string &name );
	unsigned int Attributes( const std::string &name );

};

#endif
