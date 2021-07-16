/*!
@file SearchObject.h
@brief SearchObjectなど
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	class SearchObject : Component 
	{
		std::list<std::shared_ptr<GameObject>> m_objs;

		void AddObject(const std::shared_ptr<GameObject>& addObj);
		void RemoveObject(const std::shared_ptr<GameObject>& removeObj);

	public:
		SearchObject(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override;
		void OnUpdate() override {};
		void OnDraw() override {}

		void OnCollisionEnter(std::shared_ptr<GameObject>& other) override;
		void OnCollisionExit(std::shared_ptr<GameObject>& other) override;

		//アクセッサ-------------------------------------------------------------------
		

	};

}

//endbasecross