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
		static wstringstream m_wss;
		static bool sm_isResetDelta;  //���t���[���e�N�X�g�����Z�b�g���邩�ǂ����𔻒f

		DebugObject(const std::shared_ptr<Stage>& stage):
			GameObject(stage)
		{}

		void OnCreate() override;
		void OnUpdate() override;

		static void AddVector(const Vec3& vec) {
			m_wss << L"x: " << vec.x << L", "
				<< L"y: " << vec.y << L", "
				<< L"z: " << vec.z << endl;
		}

		void OnUpdate2() override;

		//�A�N�Z�b�T----------------------------------------------------

	};

}