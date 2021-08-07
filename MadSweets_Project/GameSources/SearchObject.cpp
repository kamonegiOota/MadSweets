/*!
@file SearchObject.cpp
@brief SearchObject�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

#include "SearchObject.h"
#include "DebugObject.h"

namespace basecross {

	void SearchObject::AddObject(const std::shared_ptr<GameObject>& addObj) {
		bool isNew = true;  //�ǉ������I�u�W�F�N�g���V�K���ǂ����𔻒f����
		for (auto obj : m_objs) {
			if (obj == addObj) {
				isNew = false;
			}
		}

		if (isNew) { //�V����������ǉ�
			m_objs.push_back(addObj);
		}
	}

	void SearchObject::RemoveObject(const std::shared_ptr<GameObject>& removeObj) {
		m_objs.remove(removeObj);
	}

	bool SearchObject::IsSearchTarget(const std::shared_ptr<GameObject>& other) {
		//�Ώۂ��e�������猟���ΏۊO
		auto parent = GetGameObject()->GetParent();
		if (other == parent) {
			return false;
		}

		//�����Ώۂ�0�Ȃ�e�ȊO�S�Ă�Ώۂɂ���B
		if (m_searchTypes.size() == 0) {
			return true;
		}

		//�����łȂ��Ȃ猟���Ώۂ��ǂ������f����B
		auto otherObjType = type_index(typeid(other));
		for (auto& type : m_searchTypes) {
			if (type == otherObjType) {
				return true;
			}
		}

		return false;
	}

	void SearchObject::OnCreate() {
		auto col = GetGameObject()->AddComponent<CollisionObb>();
		col->SetAfterCollision(AfterCollision::None);
	}

	void SearchObject::OnCollisionEnter(std::shared_ptr<GameObject>& other) {
		if (IsSearchTarget(other)) {
			AddObject(other);
			DebugObject::sm_wss << "Enter";
		}
	}

	void SearchObject::OnCollisionExit(std::shared_ptr<GameObject>& other) {
		if (IsSearchTarget(other)) {
			DebugObject::sm_wss << "Exit";
			RemoveObject(other);
		}
	}

}

//endbasecross