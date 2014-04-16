#include "ProcessManager.h"

namespace Klibrary{

	//========--------========--------========--------========--------========
	//
	//			ProcessManagerクラス
	//
	//========--------========--------========--------========--------========
	
	//========--------========--------========--------========--------========
	//			全プロセス更新
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
			++ite;       //前置は += 後置は x = x + 1みたいなものか。特にクラス。　

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
	//		   ProcessをAttach
	//        weakPtrになった戻り値のプロセスを個別に持つこともできる。 
	//========--------========--------========--------========--------========
	ProcessWeakPtr ProcessManager::AttachProcesses(ProcessSharedPtr pProcess){
		m_processList.push_front(pProcess);
		return ProcessWeakPtr(pProcess);
	}

	
	//========--------========--------========--------========--------========
	//		   全リストオブジェクト強制終了ステータスに以降
	//        もしeraseがTrueならリストのクラスをAbortさせeraseする。
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
	//			全プロセスクリア
	//========--------========--------========--------========--------========
	void ProcessManager::ClearAllProcesses(){
		m_processList.clear(); 
	}


}