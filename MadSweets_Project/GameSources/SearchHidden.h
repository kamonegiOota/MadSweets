/*!
@file EnemyRotationCtrl.h
@brief EnemyRotationCtrl�Ȃ�
�S���ҁF�ێR �T��
*/

#pragma once

#include "stdafx.h"
#include "Project.h"


namespace basecross {

	class SearchHidden
	{
	public:

		//�w�肵����������HiddenObject���擾
		static vector<std::shared_ptr<GameObject>> SearchNearHiddenObjects(const std::shared_ptr<GameObject>& self, const float& nearRange = 10.0f);

		//SearchHidden(const std::shared_ptr<GameObject>& objPtr)
		//	:Component(objPtr)
		//{}

		//void OnCreate() override {}
		//void OnUpdate() override {}

		//�߂���hideObject�̒����烉���_���Ɉ�I��
		static std::shared_ptr<GameObject> SearchRandomHiddenObject(const std::shared_ptr<GameObject>& self, const float& nearRange = 10.0f);

	};

}

//endbasecross