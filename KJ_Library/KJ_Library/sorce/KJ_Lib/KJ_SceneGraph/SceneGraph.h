#pragma once 

#include "SceneNode\KJ_SceneNode.h"
#include "../KJ_Renderer/KJ_Renderer.h"
#include <memory>

namespace Klibrary{
	/** ===================================================================================
	* @class Scene3DGraph
	* @brief 3DSceneNodeを管理しSceneを構成するクラス。
	* 3DSceneNodeの更新、描画、追加、削除等の管理を行う最上位のエントリーポイント。
	* アクターの可視状態のコンポーネントがどの3DSceneNodeかも管理している。
	==================================================================================== */
	class Scene3DGraph{
	protected:
		//!< @brief　可視状態のScene3DNodeのみで構成されるシーンのルートノード。
		std::shared_ptr<Scene3DNode> m_RootNode;
		//!< @brief  Scene内のカメラ。Managerを持ってきてもいけそう。
		std::shared_ptr<CameraNode>  m_Camera;

	public:
		Scene3DGraph();
		virtual ~Scene3DGraph(){}

		/**
		* @brief 更新
		*/
		void Update(jUInt32 deltaMs);
		/**
		* @brief 描画
		*/
		void Render();
	};
}