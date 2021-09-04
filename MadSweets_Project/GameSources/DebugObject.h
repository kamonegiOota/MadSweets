/*!
@file DebugObject.h
@brief DebugObject
�S���ҁF�ێR �T��
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	class DebugObject : public GameObject
	{
	public:
		static wstringstream sm_wss;
		static bool sm_isResetDelta;  //���t���[���e�N�X�g�����Z�b�g���邩�ǂ����𔻒f

		DebugObject(const std::shared_ptr<Stage>& stage):
			GameObject(stage)
		{}

		void OnCreate() override;
		void OnUpdate() override;
		void OnUpdate2() override;

		static void AddVector(const Vec3& vec) {
			sm_wss << L"x: " << vec.x << L", "
				<< L"y: " << vec.y << L", "
				<< L"z: " << vec.z << endl;
		}

		template<class T>
		static void AddValue(const T& value , const bool isEndl = true) {
			sm_wss << to_wstring(value);
			if (isEndl) {
				sm_wss << endl;
			}
		}

		//�A�N�Z�b�T----------------------------------------------------

	};

}