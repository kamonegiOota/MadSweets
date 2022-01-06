/*!
@file SearchHidden.h
@brief SearchHidden�Ȃ�
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

		//�߂���hideObject�̒����烉���_���Ɉ�I��
		//excuteObj == �ΏۊO����I�u�W�F�N�g
		static std::shared_ptr<GameObject> SearchRandomHiddenObject(const std::shared_ptr<GameObject>& self, const float& nearRange,
			const std::shared_ptr<GameObject>& excluteObj = nullptr);

	};

}

//endbasecross