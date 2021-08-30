#pragma once

/*!
@file MyUtility.h
@brief MyUtilityクラス
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"
#include "StageObject.h"
#include "BuildeVertexPCTSprite.h"

namespace basecross {

	class EatenObject : public GameObject
	{
		BuildeVertexPCTParam m_param;

	public:

		EatenObject(const std::shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}

		void OnCreate() override;

		void SetTexture(const wstring& name) {
			m_param = BuildeVertexPCTParam(name, false);
			auto builde = BuildeVertexPCTSprite(m_param);

			auto draw = GetComponent<PCTStaticDraw>();
			draw->UpdateVertices(builde.m_vertices);
			draw->SetTextureResource(name);
		}
	};

}

//endbasecross