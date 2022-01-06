
/*!
@file ThrowHandyObject.cpp
@brief ThrowHandyObject�N���X����
�S���F�ێR�T��
*/

#include "stdafx.h"
#include "Project.h"

#include "ThrowHandyObject.h"
#include "Velocity.h"
#include "ThrowObjectCtrl.h"

namespace basecross {

	void ThrowHandyObject::OnCreate() {
		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(1.0f),
			Vec3(0.0f),
			Vec3(0.0f, XM_PI, 0.0f),
			Vec3(0.0f, -1.0f, 0.0f)
		);

		//�����I�ɂ͌����ڂ̂ݏ���
		auto draw = AddComponent<PNTStaticModelDraw>();
		draw->SetMeshResource(L"Stick");
		draw->SetMeshToTransformMatrix(spanMat);
		transform->SetScale(Vec3(0.5f));
		
		auto col = AddComponent<CollisionSphere>();
		col->SetAfterCollision(AfterCollision::None);

		AddComponent<Velocity>();
		AddComponent<ThrowObjectCtrl>();
	}

}

//endbasecross