#ifndef __H_COLLISION_DATA_H__
#define __H_COLLISION_DATA_H__

#include "meshData.h"
#include "PhysicsMath.h"



namespace Kmath{
	
#define CONVEX_MESH_MAX_SHAPES  5

	//----------------------------------------------------------------------------------------------------------------------------
	//		剛体の実体データ
	//----------------------------------------------------------------------------------------------------------------------------

	//形状
	struct Shape{
		ConvexMesh m_mesh;
		Vector3 m_offsetPos;
		Quaternion m_offsetOri;
		void *userData;   //ユーザーデータ(描画用モデルがゲームオブジェクトへのリンク)
	};

	//剛体データ(モデル1つに対してのデータ)
	struct CollidableMesh{
		int m_numShapes;
		Shape m_shapes[CONVEX_MESH_MAX_SHAPES];
		AABB m_aabb;
	};


	//属性
	struct RigidBody{
		Matrix m_inertia;   //Matrix3慣性テンソル
		float m_mass;       
		float m_restitution; //反発係数
		float m_friction;    //摩擦係数
	};

	enum MotionType{
		Active,      //活動可
		Static       //固定
	};
	//状態
	struct State{
		Vector3 m_pos;   //位置
		Quaternion m_orientation; //姿勢
		Vector3 m_linearVelo;  //並進速度
		MotionType m_motionType;
	};

} //namespace Kmath

#endif