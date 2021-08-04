
/*!
@file GameManager.cpp
@brief GameManagerクラス実体
担当：丸山裕喜
*/

#include "stdafx.h"
#include "Project.h"
#include "MyRandom.h"

namespace basecross {

	namespace maru {
		std::mt19937 MyRandom::m_mt(std::random_device{}());
	}

	//int MyRandom::RandomInt(const int min,const int max)
	//{
	//	std::uniform_real_distribution<> dist(1, 2);

	//	return static_cast<int>(dist(m_mt));
	//}
}

//endbasecross