
/*!
@file EatenObject.cpp
@brief EatenObjectクラス実体
担当：丸山裕喜
*/

#include "stdafx.h"
#include "Project.h"

#include "EatenObject.h"
#include "EatenComponent.h"
#include "SoundHelper.h"

#include "BuildeVertexPCTSprite.h"
#include "BillBoard.h"

namespace basecross {

	void EatenObject::SetEatenParametor(const wstring& texture) {
		auto eaten = GetComponent<EatenComponent>();
		if (eaten) {
			eaten->SetEatenData(eaten->GetDefaultEatenData(texture));
		}
	}

	void EatenObject::OnCreate() {
		auto builde = BuildeVertexPCTSprite(m_param);

		auto draw = AddComponent<PCTStaticDraw>();
		draw->CreateOriginalMesh(builde.m_vertices, builde.m_indices);
		draw->SetOriginalMeshUse(true);
		SetAlphaActive(true);

		AddComponent<BillBoard>();

		auto col = AddComponent<CollisionObb>();
		col->SetAfterCollision(AfterCollision::None);

		AddComponent<EatenComponent>(EatenData(10, 10));
		AddComponent<SoundEmitter>();
	}

	void EatenObject::SetTexture(const wstring& name) {
		m_param = BuildeVertexPCTParam(name, false);
		auto builde = BuildeVertexPCTSprite(m_param);

		auto draw = GetComponent<PCTStaticDraw>();
		draw->UpdateVertices(builde.m_vertices);
		draw->SetTextureResource(name);

		SetEatenParametor(name);
	}

}

//endbasecross