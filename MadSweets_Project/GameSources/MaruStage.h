/*!
@file MaruStage.cpp
@brief MaruStageÀ‘Ì
’S“–ÒFŠÛR —TŠì
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	class MaruStage : public Stage {

		//ƒrƒ…[‚Ìì¬
		void CreateViewLight();
	public:
		//\’z‚Æ”jŠü
		MaruStage() :Stage() {}
		virtual ~MaruStage() {}
		//‰Šú‰»
		virtual void OnCreate()override;

	};

}

//endbasecross