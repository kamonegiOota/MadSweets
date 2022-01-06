/*!
@file Heuristic.cpp
@brief Heuristic�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

#include "Heuristic.h"

namespace basecross {

	float Heuristic::CalucHeuristicRange(const std::shared_ptr<const NavGraphNode>& node) {
		auto pos = node->GetPosition();
		auto targetPos = m_targetNode->GetPosition();

		auto toVec = targetPos - pos;
		return toVec.length();
	}

}

//endbasecross