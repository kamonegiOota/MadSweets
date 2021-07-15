/*!
@file SearchObject.cpp
@brief SearchObjectなど実体
*/

#include "stdafx.h"
#include "Project.h"

#include "SearchObject.h"

namespace basecross {

	void SearchObject::AddObject(const std::shared_ptr<GameObject>& addObj) {
		bool isNew = true;  //追加されるオブジェクトが新規かどうかを判断する
		for (auto obj : m_objs) {
			if (obj == addObj) {
				isNew = false;
			}
		}

		if (isNew) { //新しかったら追加
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