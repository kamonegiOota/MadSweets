
/*!
@file BoardObj.cpp
@brief BoardObjクラス実体
担当：丸山裕喜
*/

#include "stdafx.h"
#include "Project.h"
#include "BoardObj.h"

namespace basecross {

	void BoardObj::OnCreate()
	{
		auto builde = BuildeVertexPCTSprite(m_param);

		auto drawComp = AddComponent<BcPCTStaticDraw>();
		drawComp->CreateOriginalMesh(builde.m_vertices, builde.m_indices);
		drawComp->SetOriginalMeshUse(true);
		if (m_param.texture != L"") {
			drawComp->SetTextureResource(m_param.texture);
		}

		SetAlphaActive(true);

		SetDrawLayer(5);
	}

}

//endbasecross