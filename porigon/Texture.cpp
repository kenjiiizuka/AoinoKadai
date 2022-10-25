#include "Texture.h"
#include "WICTextureLoader.h"

void LoadTexture(const wchar_t * _fileName, ID3D11ShaderResourceView ** _outTexture)
{
	HRESULT hr;
	DIRECT3D *d3d = Direct3D_Get();

	// �K�E�Z�̃G�t�F�N�g�O�Q
	hr = DirectX::CreateWICTextureFromFile(d3d->device, _fileName, NULL, _outTexture);
	//�Q�o�C�g�������n���Ȃ��Ƃ����Ȃ��@L�@������ƂQ�o�C�g������ɂȂ�

	//�G���[����
	if (FAILED(hr)) //���s�����ꍇ
	{
		MessageBox(NULL, L"�e�N�X�`���ǂݍ��ݎ��s", L"�G���[����", MB_OK);
	}
}
