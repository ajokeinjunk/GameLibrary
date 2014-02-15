#ifndef __H_COLLISION_DATA_H__
#define __H_COLLISION_DATA_H__

#include "meshData.h"
#include "PhysicsMath.h"



namespace Kmath{
	
#define CONVEX_MESH_MAX_SHAPES  5

	//----------------------------------------------------------------------------------------------------------------------------
	//		���̂̎��̃f�[�^
	//----------------------------------------------------------------------------------------------------------------------------

	//�`��
	struct Shape{
		ConvexMesh m_mesh;
		Vector3 m_offsetPos;
		Quaternion m_offsetOri;
		void *userData;   //���[�U�[�f�[�^(�`��p���f�����Q�[���I�u�W�F�N�g�ւ̃����N)
	};

	//���̃f�[�^(���f��1�ɑ΂��Ẵf�[�^)
	struct CollidableMesh{
		int m_numShapes;
		Shape m_shapes[CONVEX_MESH_MAX_SHAPES];
		AABB m_aabb;
	};


	//����
	struct RigidBody{
		Matrix m_inertia;   //Matrix3�����e���\��
		float m_mass;       
		float m_restitution; //�����W��
		float m_friction;    //���C�W��
	};

	enum MotionType{
		Active,      //������
		Static       //�Œ�
	};
	//���
	struct State{
		Vector3 m_pos;   //�ʒu
		Quaternion m_orientation; //�p��
		Vector3 m_linearVelo;  //���i���x
		MotionType m_motionType;
	};

} //namespace Kmath

#endif