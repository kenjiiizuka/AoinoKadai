 
// ���_�V�F�[�_�[�̃��C���֐�
//�����@�e���_�ɑ΂��čs�������ړ��@��]�@�k���Ȃǂ����s����
// �߂�l�F���̃V�F�[�_�[�̏����̌��ʂ��A���_�̃f�[�^�Ƃ��Ė߂�
// ���� inputPos�FVRAM�ɓ]�����ꂽ���_�f�[�^�i�̂����P�j���n�����

//return�p�̍\����

struct VS_OUTPUT
{
	float4 pos : SV_Position; //�V�X�e���Ō��߂��Ă閼�O
	float2 uv : TEXCOORD; //�V�X�e���Ō��߂��Ă閼�O
};

VS_OUTPUT vs_main(float4 inputPos : POSITION,/*xy*/ float2 uv:TEX /*uv*/)
{
	VS_OUTPUT output;

	output.pos = inputPos;  // �n���ꂽ���_�����̂܂�return����B�i���̂܂܎g���j
	output.uv = uv;
	//�ړ�
	//outputPos.x += 0.2f;
	//outputPos.y += 0.3f;
	//�g��k��
	output.pos.x *= (480.0f/640.0f);
	output.pos.y *= 1.0f;

    return output;
}