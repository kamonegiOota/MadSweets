
/*!
@file GameManager.cpp
@brief GameManager�N���X����
�S���F�ێR�T��
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