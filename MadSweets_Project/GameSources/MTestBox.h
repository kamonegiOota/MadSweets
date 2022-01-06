
/*!
@file MTestBox.h
@brief MTestBox�N���X
�S���F�ێR�T��
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class MTestBox : public GameObject
	{

	public:
		MTestBox(const std::shared_ptr<Stage>& stage):
			GameObject(stage)
		{}

		void OnCreate() override;


		void SetColor(const Col4& color) {
			auto draw = AddComponent<BcPNTStaticDraw>();
			draw->SetDiffuse(color);
		}
	};

}

//endbasecross