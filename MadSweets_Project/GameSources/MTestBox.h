
/*!
@file MTestBox.h
@brief MTestBoxクラス
担当：丸山裕喜
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