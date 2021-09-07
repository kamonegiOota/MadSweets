/*!
@file PositionDrawComp.h
@brief PositionDrawComp
担当者：丸山 裕喜
*/

#include "PositionDrawComp.h"
#include "GraphAstar.h"
#include "AstarEdgeDraw.h"
#include "DebugObject.h"
#include "ArrowObject.h"

namespace basecross {

	void AstarEdgeDraw::CreateDrawBox(const Vec3& startPosition, const Vec3& endPosition) {
		auto toVec = endPosition - startPosition;
		auto halfToVec = toVec * 0.5f;
		auto createPosition = startPosition + halfToVec;

		auto obj = GetStage()->Instantiate<ArrowObject>(createPosition, Quat::Identity());
		auto trans = obj->GetComponent<Transform>();

		//スケールのセット
		auto scale = Vec3(toVec.length() * 0.9f, 1.0f, 1.0f);
		trans->SetScale(scale);

		trans->SetForward(toVec.GetNormalized());
		trans->Rotate(Vec3(0.0f,-XM_PIDIV2, 0.0f));
	}

	void AstarEdgeDraw::OnCreate() {
		auto graph = m_astar.GetGraph();
		auto numNode = graph.GetNumNodes();

		DebugObject::AddValue(numNode);

		for (int i = 0; i < numNode; i++) {
			auto edges = graph.GetEdges(i);
			for (const auto& edge : edges) {
				auto startPosition = graph.GetNode(edge.GetFrom()).GetPosition();
				auto endPosition = graph.GetNode(edge.GetTo()).GetPosition();

				CreateDrawBox(startPosition, endPosition);
			}
		}
	}

}

//endbasecross