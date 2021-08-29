/*!
@file MyUtility.cpp
@brief MyUtility�N���X����
�S���F�ێR�T��
*/

#include "stdafx.h"
#include "Project.h"

#include "TableObject.h"
#include "EatenComponent.h"
#include "SoundHelper.h"

#include "PNTPointDraw.h"

namespace basecross {

	void TableObject::OnCreate() {
		StageObject::OnCreate();

		//���b�V���̒����pMat
		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(1.0f),
			Vec3(0.0f),
			Vec3(0.0f, XM_PI, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		auto draw = AddComponent<PNTPointDraw>();
		draw->SetMeshResource(m_mesh);
		draw->SetMeshToTransformMatrix(spanMat);
		
		auto scale = GetComponent<Transform>()->GetScale();
		//���}���u
		if (m_mesh == L"Chair") {
			scale /= 50.0f;
		}
		else {
			scale /= 25.0f;
		}
		scale.y *= 0.8f;
		GetComponent<Transform>()->SetScale(scale);
	}

}

//endbasecross