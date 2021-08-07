/*!
@file SearchObject.cpp
@brief SearchObjectなど実体
*/

#include "stdafx.h"
#include "Project.h"

#include "SearchObject.h"
#include "DebugObject.h"

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
		m_objs.remove(removeObj);
	}

	bool SearchObject::IsSearchTarget(const std::shared_ptr<GameObject>& other) {
		//対象が親だったら検索対象外
		auto parent = GetGameObject()->GetParent();
		if (other == parent) {
			return false;
		}

		//検索対象が0なら親以外全てを対象にする。
		if (m_searchTypes.size() == 0) {
			return true;
		}

		//そうでないなら検索対象かどうか判断する。
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