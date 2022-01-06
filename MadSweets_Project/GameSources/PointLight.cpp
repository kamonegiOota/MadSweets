/*!
@file PointLight.cpp
@brief PointLight‚È‚ÇŽÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"

#include "PointLight.h"

namespace basecross {

	PointLight::PointLight(const std::shared_ptr<GameObject>& objPtr)
		:PointLight(objPtr, PointLightParam())
	{}

	PointLight::PointLight(const std::shared_ptr<GameObject>& objPtr,
		const PointLightParam& param
	):
		Component(objPtr),
		m_param(param)
	{}


	void PointLight::OnUpdate() {
		m_param.position = transform->GetPosition();
	}

}

//endbasecross