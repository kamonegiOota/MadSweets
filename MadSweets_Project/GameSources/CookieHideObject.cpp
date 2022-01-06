
/*!
@file CookieHideObject.cpp
@brief CookieHideObject�N���X����
�S���F�ێR�T��
*/

#include "stdafx.h"
#include "Project.h"

#include "CookieHideObject.h"
#include "PNTPointDraw.h"
#include "HiddenComponent.h"

namespace basecross {

	void CookieHideObject::OnCreate() {
		StageObject::OnCreate();

		//���b�V���̒����pMat
		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(1.0f),
			Vec3(0.0f),
			Vec3(0.0f, XM_PI, 0.0f),
			Vec3(0.0f, -1.0f, 0.0f)
		);

		AddComponent<HiddenComponent>(transform->GetPosition(), transform->GetForword());
		auto draw = AddComponent<BcPNTStaticModelDraw>();
		draw->SetMeshResource(m_mesh);
		draw->SetMeshToTransformMatrix(spanMat);

		auto col = AddComponent<CollisionObb>();
		col->SetFixed(true);
		//col->SetAfterCollision(AfterCollision::None);

		auto trans = GetComponent<Transform>();
		auto scale = trans->GetScale();
		scale /= 25.0f;
		trans->SetScale(scale);
	}

	

}

//endbasecross