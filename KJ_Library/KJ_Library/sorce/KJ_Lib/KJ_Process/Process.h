#ifndef H_KLIB_PROCESS_H
#define H_KLIB_PROCESS_H

#include "../KJ_Defines/KJ_Defines.h"
#include <cassert>

//lol�����R�����g�͏�������

#include <memory>

using namespace std;

namespace Klibrary{
	//========--------========--------========--------========--------========
	//
	//			Process�N���X
	//
	//========--------========--------========--------========--------========
	class Process;
	typedef shared_ptr<Process> ProcessSharedPtr;
	typedef weak_ptr<Process> ProcessWeakPtr;
	
	class Process
	{
		friend class ProcessManager;

	public:
	enum ProcessState
	{
		UNINITIALIZED = 0,  //��������
		REMOVED,    //���X�g�����菜���ꂽ��������Ă͂��Ȃ�

		RUNNING,  //���쒆
		PAUSED,   //�ꎞ��~��

		DEAD_SUCCEEDED,  //���슮��
		DEAD_FAILED,     //���쎸�s
		DEAD_ABORTED,    //���s�����ꂸ�����I��������ꂽ

	};


	private:
		ProcessState m_state;
		ProcessSharedPtr m_pChild;

	protected:
		virtual void VInitialize(){ m_state = RUNNING; }
		virtual void VUpdate(jUInt32 deltaMs) = 0;
		virtual void VSuccess(){}      //�����������ɌĂяo������
		virtual void VFail(){}         
		virtual void VAbort(){}

	public:
		Process(){ m_state = UNINITIALIZED; }
		~Process(){ if (m_pChild)m_pChild->VAbort(); } //lol���̃A�N�Z�X�ł���H

		//�I��������
		inline void Succeed();
		inline void Fail();

		//�|�[�Y����
		inline void Pause();
		inline void UnPause();
		
		//�q�֐�
		inline void AttchChiled(ProcessSharedPtr pChiled);
		ProcessSharedPtr RemoveChild();  //���������菜�������B�j�󂵂Ȃ��B

		//�A�N�Z�T
		ProcessSharedPtr GetChild(){ return m_pChild; }
		ProcessState     GetState()const{ return m_state; }
		bool IsAlive()const{ return (m_state == RUNNING || m_state || PAUSED); }
		bool IsDead()const{ return (m_state == DEAD_SUCCEEDED || m_state == DEAD_FAILED || m_state == DEAD_ABORTED); }
		bool IsRemoved()const{ return (m_state == REMOVED); }
		bool IsPaused()const{ return (m_state == PAUSED); }

	private:
		void SetState(ProcessState newState){ m_state = newState; }

	};

	//========--------========--------========--------========--------========
	//			Process�N���XInline����
	//========--------========--------========--------========--------========
	//lol�A�T�[�g�͕ʏ����ɒu�������邱��
	
	inline void Process::Succeed(){
		assert(m_state == RUNNING || m_state == PAUSED);
		m_state = DEAD_SUCCEEDED;
	}

	inline void Process::Fail(){
		assert(m_state == RUNNING || m_state == PAUSED);
		m_state = DEAD_FAILED;
	}

	inline void Process::Pause(){
		if (m_state == RUNNING){
			m_state = PAUSED;
		}
		else{
			assert(0);  
		}
	}

	inline void Process::UnPause(){
		if (m_state == PAUSED){
			m_state = RUNNING;
		}
		else{
			assert(0);
		}
	}

	inline void Process::AttchChiled(ProcessSharedPtr pChild){
		if (m_pChild){
			m_pChild->AttchChiled(pChild);
		}
		else{
			m_pChild = pChild;
		}
	}

}

#endif