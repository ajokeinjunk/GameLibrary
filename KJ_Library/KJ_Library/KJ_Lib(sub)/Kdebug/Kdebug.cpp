#include "Kdebug.h"


void Kdebug::EnableWire(){
	iexSystem::Device->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME);
}

void Kdebug::DisableWire(){
	iexSystem::Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

