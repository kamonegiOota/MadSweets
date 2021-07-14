/*!
@file BaseEnemy.cpp
@brief BaseEnemyÀ‘Ì
’S“–ÒFŠÛR —TŠì
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	class DebugObject : public GameObject
	{
	public:
		static wstringstream m_wss;

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
	};

}