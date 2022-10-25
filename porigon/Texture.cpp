#include "Texture.h"
#include "WICTextureLoader.h"

void LoadTexture(const wchar_t * _fileName, ID3D11ShaderResourceView ** _outTexture)
{
	HRESULT hr;
	DIRECT3D *d3d = Direct3D_Get();

	// 必殺技のエフェクト０２
	hr = DirectX::CreateWICTextureFromFile(d3d->device, _fileName, NULL, _outTexture);
	//２バイト文字列を渡さないといけない　L　をつけると２バイト文字列になる

	//エラー処理
	if (FAILED(hr)) //失敗した場合
	{
		MessageBox(NULL, L"テクスチャ読み込み失敗", L"エラー発生", MB_OK);
	}
}
