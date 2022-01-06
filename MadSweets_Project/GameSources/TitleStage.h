/*!
@file TitleStage.h
@brief TitleStage
’S“–ÒFŠÛR —TŠì
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	class TitleStage : public Stage {

		//ƒrƒ…[‚Ìì¬
		void CreateViewLight();

		void CreateTitle();
		void CreateFadeCtrl(std::shared_ptr<Button>& startButton, std::shared_ptr<Button>& goOptionButton);

	public:
		//\’z‚Æ”jŠü
		TitleStage() :Stage() {}
		virtual ~TitleStage() {}
		//‰Šú‰»
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void GoOption();
	};

}

//endbasecross