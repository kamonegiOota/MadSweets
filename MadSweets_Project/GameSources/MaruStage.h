/*!
@file MaruStage.cpp
@brief MaruStageÀÌ
SÒFÛR Tì
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	class MaruStage : Stage {

		//r[Ìì¬
		void CreateViewLight();
	public:
		//\zÆjü
		MaruStage() :Stage() {}
		virtual ~MaruStage() {}
		//ú»
		virtual void OnCreate()override;

	};

}

//endbasecross