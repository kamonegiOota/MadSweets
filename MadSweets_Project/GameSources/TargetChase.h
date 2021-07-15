
/*!
@file TargetChase.h
@brief TargetChase
担当者：丸山 裕喜
*/

#pragma once

namespace basecross {

	//設定されたターゲットを追従する処理
	class TargetChase : public Component
	{

	public:
		TargetChase(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override;
		void OnUpdate() override;
		void OnDraw() override {}


		//アクセッサ-----------------------------------------------------------------------

	};

}

//endbasecross