
/*!
@file TargetChase.h
@brief TargetChase
�S���ҁF�ێR �T��
*/

#pragma once

namespace basecross {

	//�ݒ肳�ꂽ�^�[�Q�b�g��Ǐ]���鏈��
	class TargetChase : public Component
	{

	public:
		TargetChase(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override;
		void OnUpdate() override;
		void OnDraw() override {}


		//�A�N�Z�b�T-----------------------------------------------------------------------

	};

}

//endbasecross