// �s�N�Z���V�F�[�_�[�̃��C���֐��@���@�|���S����`�悷��̂ɕK�v�ȃs�N�Z���������Ăяo�����
// �e�s�N�Z���̐F���w�肷��̂����
// �߂�l�F�@���̃s�N�Z�������F�ɂ��������ARGBA�Ŏw�肷��
// ����inputPos�F�@���_�̍��W�B�E�C���h�E�̍�������_�Ƃ���s�N�Z�����W

//�e�N�X�`�����󂯓����O���[�o���ϐ�
Texture2D gTexture : register(t0);


//�T���v���[�̃O���[�o���ϐ�
SamplerState gSampler : register(s0);
/*
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};*/

float4 ps_main( float4 inputPos : SV_POSITION,float2 uv : TEXCOORD ) : SV_Target
{
	
	//�O���f�[�V�����@�Z�s�A����Ƃ����o����
	float color = inputPos.x/640.0f;// ���W�������ł���Ă�����Ƃ���
	float4 pixelColor = float4(color+0.2f, color, color+0.3f, 1.0f); // RGBA  0.0f-1.0f
	

	//�e�N�X�`���̐F���o�̓s�N�Z���F�ɂ���
	pixelColor = gTexture.Sample(gSampler, uv);

	return pixelColor;
}
