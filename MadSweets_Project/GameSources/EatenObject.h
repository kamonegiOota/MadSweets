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

	class EatenObject : public StageObject
	{
		BuildeVertexPCTParam m_param;

	public:
		EatenObject(const std::shared_ptr<Stage>& stage,
			const std::wstring& name,
			const Vec3& scale,
			const Vec3& rotation,
			const Vec3& position,
			const wstring& texture
		) :
			StageObject(stage, name, scale, rotation, position),
				m_param(BuildeVertexPCTParam(texture, false))
		{}

		void OnCreate() override;

	};

}

//endbasecross