/*!
@file OriginalMeshObject.cpp
@brief OriginalMeshObjectクラス実体
担当：丸山裕喜
*/

#include "stdafx.h"
#include "Project.h"

#include "OriginalMeshObject.h"
#include "EatenComponent.h"
#include "SoundHelper.h"

#include "PNTPointDraw.h"

namespace basecross {

	void OriginalMeshObject::OnCreate() {
		StageObject::OnCreate();

		//メッシュの調整用Mat
		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(1.0f),
			Vec3(0.0f),
			Vec3(0.0f, XM_PI, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		auto draw = AddComponent<BcPNTStaticModelDraw>();
		draw->SetMeshResource(m_mesh);
		//draw->SetTextureResource(L"");
		draw->SetMeshToTransformMatrix(spanMat);
		
		auto scale = GetComponent<Transform>()->GetScale();
		//応急処置
		if (m_mesh == L"Chair") {
			scale /= 50.0f;
		}
		else {
			scale /= 25.0f;
		}
		scale.y *= 0.8f;
		GetComponent<Transform>()->SetScale(scale);

		auto col = AddComponent<CollisionObb>();
		col->SetFixed(true);
		col->SetMakedSize(1.2f);
	}

}

//endbasecross