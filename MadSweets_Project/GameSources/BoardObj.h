
/*!
@file BoardObj.h
@brief BoardObjクラス
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"
#include "BuildeVertexPCTSprite.h"

namespace basecross {

	class BoardObj : public GameObject
	{
		BuildeVertexPCTParam m_param;

	public:

		BoardObj(const std::shared_ptr<Stage>& stage,
			const BuildeVertexPCTParam& param
		):
			GameObject(stage),
			m_param(param)
		{

		}

		void OnCreate() override;
		//void OnUpdate() override;

	};

}

//basecross