#include "PipelineState.h"
#include <KamataEngine.h>

using namespace KamataEngine;

// PipelineStateを生成する
void PipelineState::Create(D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDesc) {

	// クラス内で取得するために追加
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// 準備は整った。PSOを生成する
	ID3D12PipelineState* graphicsPipelineState = nullptr;
	HRESULT hr = dxCommon->GetDevice()->CreateGraphicsPipelineState(&graphicsPipelineStateDesc, IID_PPV_ARGS(&graphicsPipelineState));
	assert(SUCCEEDED(hr));

	// 生成したPipelineStateは取っておく
	pipelineState_ = graphicsPipelineState;
}

// 生成したPipelineStateを変えす
ID3D12PipelineState* PipelineState::Get() { return pipelineState_; }

PipelineState::PipelineState() {}

PipelineState::~PipelineState() {
	if (pipelineState_) {
		pipelineState_->Release();
		pipelineState_ = nullptr;
	}
}
