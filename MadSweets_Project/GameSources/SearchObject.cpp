/*!
@file SearchObject.cpp
@brief SearchObject�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

#include "SearchObject.h"

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
		auto iter = m_objs.begin();

		while (iter != m_objs.end()) {
			if (*iter == removeObj) {
				m_objs.erase(iter);
				return;
			}
		}
	}

	void SearchObject::OnCreate() {
		auto col = GetGameObject()->AddComponent<CollisionObb>();
		col->SetAfterCollision(AfterCollision::None);
	}

	void SearchObject::OnCollisionEnter(std::shared_ptr<GameObject>& other) {
		AddObject(other);
	}

	void SearchObject::OnCollisionExit(std::shared_ptr<GameObject>& other) {
		RemoveObject(other);
	}

}

//endbasecross