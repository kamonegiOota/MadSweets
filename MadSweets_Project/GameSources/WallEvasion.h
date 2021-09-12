/*!
@file PlowlingMove.h
@brief PlowlingMove
�S���ҁF�ێR �T��
*/

#pragma once

#include "stdafx.h"
#include "Project.h"
#include "AstarCtrl.h"
#include "TactileCtrl.h"

namespace basecross {

	struct ObstacleRangePair
	{
		ex_weak_ptr<GameObject> object;
		float range;

		ObstacleRangePair()
			:ObstacleRangePair(nullptr, 0.0f)
		{}

		ObstacleRangePair(const std::shared_ptr<GameObject>& objPtr, const float& range)
			:object(objPtr), range(range)
		{}
	};

	class WallEvasion : public Component
	{
		//��Q���̑Ώ�
		vector<ex_weak_ptr<GameObject>> m_obstacleObjs;
		float m_maxSpeed = 30.0f;

		/// <summary>
		/// �ǂƂ̋����𑪒肵�āA���������ɕ��ׂĔz���Ԃ�
		/// </summary>
		/// <returns>�ǂƂ̋����𑪒肵���z��</returns>
		vector<ObstacleRangePair> CalucWallRangeSort();
		/// <summary>
		/// ������͂��v�Z����B
		/// </summary>
		/// <param name="tactile">�G�o�I�u�W�F�N�g</param>
		/// <returns>�v�Z������</returns>
		Vec3 CalucForce(const std::shared_ptr<GameObject>& tactile);

		/// <summary>
		/// �ǉ������
		/// </summary>
		/// <param name="tactile">�G�o�I�u�W�F�N�g</param>
		/// <param name="other">�ڐG�����I�u�W�F�N�g</param>
		void EvasionUpdate(const std::shared_ptr<TactileCtrl>& tactile, const std::shared_ptr<GameObject>& other);

	public:
		WallEvasion(const std::shared_ptr<GameObject>& objPtr
		)
			:Component(objPtr)
		{}
		
		void OnCreate() override {}
		void OnUpdate() override {}


		//�A�N�Z�b�T----------------------------------------------------

		void AddObstacleObjs(const std::shared_ptr<GameObject>& obj) {
			m_obstacleObjs.push_back(obj);
		}

		/// <summary>
		/// �G�o�̃Z�b�g
		/// </summary>
		/// <param name="tactile">�G�o�̃I�u�W�F�N�g</param>
		void SetTactile(const std::shared_ptr<TactileCtrl>& tactile);

		void SetMaxSpeed(const float& speed) {
			m_maxSpeed = speed;
		}
		float GetMaxSpeed() const {
			return m_maxSpeed;
		}

	};

}

//endbasecross