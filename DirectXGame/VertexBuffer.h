#pragma once

#include <d3dx12.h>

class VertexBuffer {

public:
	// VertexBufferの生成
	void Create(const UINT size, const UINT stride);

	// ゲッター
	ID3D12Resource* Get();               // 頂点バッファー
	D3D12_VERTEX_BUFFER_VIEW* GetView(); // 頂点バッファービュー

	// コンストラクタ
	VertexBuffer();

	// デストラクタ
	~VertexBuffer();

private:
	ID3D12Resource* vertexBuffer_ = nullptr;    // 頂点バッファー
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView_{}; // 頂点バッファービュー
};
