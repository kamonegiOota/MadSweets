
/*!
@file NodeBase.h
@brief NodeBase
íSìñé“ÅFä€éR óTäÏ
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	template<class NodeType>
	class NodeBase
	{
        std::weak_ptr<NodeType> m_owner;

	public:
 
        NodeBase(const std::shared_ptr<NodeType>& owner)
            :m_owner(owner)
        {}

        virtual void OnStart() = 0;
        virtual void OnUpdate() = 0;
        virtual void OnExit() = 0;

    protected:

        std::shared_ptr<NodeType> GetOwner() const {
            auto owner = m_owner.lock();
            return owner ? owner : nullptr;
        }

	};

}

//endbasecross