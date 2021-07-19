/*!
@file SearchObject.h
@brief SearchObject�Ȃ�
�S���ҁF�ێR �T��
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//����Enter��Exit�̗��p�����ꍇ�ɃG���[��f�����߁A��߂�B
	class SearchObject : public Component 
	{
		std::list<std::shared_ptr<GameObject>> m_objs;
		std::list<type_index> m_searchTypes;

		void AddObject(const std::shared_ptr<GameObject>& addObj);
		void RemoveObject(const std::shared_ptr<GameObject>& removeObj);

		bool IsSearchTarget(const std::shared_ptr<GameObject>& other);  //�����Ώۂ�������true

	public:
		SearchObject(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override;
		void OnUpdate() override {}
		void OnDraw() override {}

		void OnCollisionEnter(std::shared_ptr<GameObject>& other) override;
		void OnCollisionExit(std::shared_ptr<GameObject>& other) override;

		//�A�N�Z�b�T-------------------------------------------------------------------
		template<class T>
		void AddSearchType() {  //�����Ώۂ��i��
			m_searchTypes.push_back(type_index(typeid(T)));
		}

		std::list<std::shared_ptr<GameObject>> GetObjects() {
			return m_objs;
		}

		template<class T,
			enable_if_t<is_base_of_v<GameObject, T>, std::nullptr_t> = nullptr >  //GameObject���p���������̂̂ݎw��ł���
		std::shared_ptr<T> GetSearchObject() const
		{
			for (auto obj : m_objs) {
				auto target = dynamic_pointer_cast<T>(obj);
				if (target) {
					return target;
				}
			}

			return nullptr;
		}

		template<class T,
			enable_if_t<is_base_of_v<GameObject, T>, std::nullptr_t> = nullptr >  //GameObject���p���������̂̂ݎw��ł���
		std::vector<std::shared_ptr<T>> GetSearchObjects() const 
		{
			std::vector<std::shared_ptr<T>> reObjs;

			for (auto obj : m_objs) {
				auto target = dynamic_pointer_cast<T>(obj);
				if (target) {
					reObjs.push_back(target);
				}
			}

			return reObjs;
		}

		template<class T,
			enable_if_t<is_base_of_v<Component, T>, std::nullptr_t> = nullptr > //Component���p���������̂̂ݎw��ł���
		std::shared_ptr<T> GetSearchComponent() const
		{
			for (auto obj : m_objs) {
				auto target = obj->GetComponent<T>(false);
				if (target) {
					return target;
				}
			}

			return nullptr;
		}

		template<class T,
			enable_if_t<is_base_of_v<Component, T>, std::nullptr_t> = nullptr > //Component���p���������̂̂ݎw��ł���
		std::vector<std::shared_ptr<T>> GetSearchComponents() const 
		{
			std::vector<std::shared_ptr<T>> reComps;

			for (auto obj : m_objs) {
				auto target = obj->GetComponent<T>(false);
				if (target) {
					reComps.push_back(target);
				}
			}

			return reComps;
		}

	};

}

//endbasecross