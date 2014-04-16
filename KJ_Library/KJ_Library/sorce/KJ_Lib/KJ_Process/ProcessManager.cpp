#include "ProcessManager.h"

namespace Klibrary{

	//========--------========--------========--------========--------========
	//
	//			ProcessManager�N���X
	//
	//========--------========--------========--------========--------========
	
	//========--------========--------========--------========--------========
	//			�S�v���Z�X�X�V
	//========--------========--------========--------========--------========
	jUInt32 ProcessManager::UpdateProcesses(const jUInt32 deltaMs){
		jUInt16 successNum = 0;
		jUInt16 failNum = 0;


		ProcessList::iterator ite = m_processList.begin();
		ProcessList::iterator tempIte;
		ProcessSharedPtr pCurrentProcess;
		ProcessSharedPtr pChild;
		while (ite != m_processList.end()){
			pCurrentProcess = (*ite);
			tempIte = ite;
			++ite;       //�O�u�� += ��u�� x = x + 1�݂����Ȃ��̂��B���ɃN���X�B�@

			if (pCurrentProcess->GetState() == Process::UNINITIALIZED){
				pCurrentProcess->VInitialize();
			}

			if (pCurrentProcess->GetState() == Process::RUNNING){
				pCurrentProcess->VUpdate(deltaMs);
			}

			if (pCurrentProcess->IsDead()){
				switch (pCurrentProcess->GetState())
				{
				case Process::DEAD_SUCCEEDED:
					pCurrentProcess->VSuccess();
					pChild = pCurrentProcess->GetChild();
					if (pChild){
						AttachProcesses(pChild); //FIFO
					}
					else{
						successNum++; 
					}

					break;

				case Process::DEAD_FAILED:
					pCurrentProcess->VFail();
					failNum++;
					break;

				case Process::DEAD_ABORTED:
					pCurrentProcess->VAbort();
					failNum++;
					break;
				}
				m_processList.erase(tempIte);
			}
		}
		return ((successNum << 16 | failNum));
	}

	//========--------========--------========--------========--------========
	//		   Process��Attach
	//        weakPtr�ɂȂ����߂�l�̃v���Z�X���ʂɎ����Ƃ��ł���B 
	//========--------========--------========--------========--------========
	ProcessWeakPtr ProcessManager::AttachProcesses(ProcessSharedPtr pProcess){
		m_processList.push_front(pProcess);
		return ProcessWeakPtr(pProcess);
	}

	
	//========--------========--------========--------========--------========
	//		   �S���X�g�I�u�W�F�N�g�����I���X�e�[�^�X�Ɉȍ~
	//        ����erase��True�Ȃ烊�X�g�̃N���X��Abort����erase����B
	//========--------========--------========--------========--------========
	void ProcessManager::AbortAllProcesses(bool erase){
		ProcessList::iterator ite = m_processList.begin();
		ProcessList::iterator tempIte;
		ProcessSharedPtr pProcess;

		while (ite != m_processList.end()){
			tempIte = ite;
			++ite;

			pProcess = *tempIte;
			if (pProcess->IsAlive()){
				pProcess->SetState(Process::DEAD_ABORTED);
				if (erase){
					pProcess->VAbort();
					m_processList.erase(tempIte);
				}
			}
		}
	}

	//========--------========--------========--------========--------========
	//			�S�v���Z�X�N���A
	//========--------========--------========--------========--------========
	void ProcessManager::ClearAllProcesses(){
		m_processList.clear(); 
	}


}