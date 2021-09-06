
/*!
@file MyUtility.cpp
@brief MyUtilityクラス実体
担当：丸山裕喜
*/

#include "stdafx.h"
#include "Project.h"

#include "ArrowObject.h"
#include "BuildeVertexPCTSprite.h"

namespace basecross {

	void ArrowObject::OnCreate() {
		auto texture = L"Arrow_Tx";
		auto build = BuildeVertexPCTSprite(BuildeVertexPCTParam(texture, false));

		auto draw = AddComponent<PCTStaticDraw>();
		draw->CreateOriginalMesh(build.m_vertices, build.m_indices);
		draw->SetTextureResource(texture);
		draw->SetOriginalMeshUse(true);
		draw->SetDepthStencilState(DepthStencilState::Read);
		SetAlphaActive(true);
	}

}

//endbasecross