#pragma once
#include "../dxlib_ext/dxlib_ext.h"


namespace wta
{
	// ���z�x�N�g���̃Z�b�g���`
	static const int grad3[12][3] =
	{
		{1,1,0}, {-1,1,0}, {1,-1,0}, {-1,-1,0},
		{1,0,1}, {-1,0,1}, {1,0,-1}, {-1,0,-1},
		{0,1,1}, {0,-1,1}, {0,1,-1}, {0,-1,-1}
	};

	// �t�F�[�h�֐�(�C���[�W : �R�X�̎R�Ԃ̌q����̊��炩��)
	// args ... 1�����̍��W
	// return ... 0.0f ~ 1.0f �̒l
	// ex ... float fade = wta::SimplexNoise::fade(x);
	inline float fade(float t)
	{
		// ���w�I�ɓ����ꂽ�v�Z���łȂ��A�]�܂������ʂ𓾂邽�ߎ����I�Ɍ���
		// �e���l�̓m�C�Y�����̂��߂̒萔�Ƃ��čl���Ă���
		// �ύX����ΐ����̓x�����ς��
		return t * t * t * (t * (t * 6 - 15) + 10);
	}

	// ��Ԋ֐��i�C���[�W : �ЂƂ̎R�̎Ζʂ̊��炩���j
	// args1 ... ��Ԃ̎n�_
	// args2 ... ��Ԃ̏I�_ 
	// args3 ... ��ԌW��
	// return ... -1.0f ~ 1.0f �̒l
	// ex ... float lerp = wta::SimplexNoise::lerp(x, y);
	inline float lerp(float a, float b, float t)
	{
		// ��Ԃ̂��߂ɒ��Ԃ̒l���v�Z
		// ���`��ԁi�m�C�Y�����̈�Ƃ��Ēl�Ԃ̊��炩�ȑJ�ځj
		// b - a : �n�_�ƏI�_�̍���
		// t * (b - a) : ��ԌW������Z���ĕ�ԋ������v�Z
		// a + t * (b - a) : �n�_�ɕ�ԋ��������Z���ĕ�Ԍ��ʂ��v�Z
		return a + t * (b - a);
	}

	// 3�����̍��W�ɑ΂���n�b�V���֐�
	// �m�C�Y�����̂��߁i�����_���l�j
	// �n�b�V�� : �C�ӂ̐��l���A���̃��[���Ɋ�Â��ČŒ蒷�̒l�ɕϊ�
	// ����́A3�����̍��W���n�b�V���֐��ɓ���āA�����_���Ȓl�𐶐�
	// args ... 3�����̍��W
	// return ... 0 ~ 255 �̒l
	// ex ... int hash =�@wta::SimplexNoise::hash(x, y, z);
	inline int hash(float x, float y, float z)
	{
		// 57 : 1�����̃n�b�V���֐��̑f��
		// 3623 : 2�����̃n�b�V���֐��̑f��
		// 160621 : 3�����̃n�b�V���֐��̑f��
		// �����̐��l�́A�����_���Ȓl�𐶐����邽�߂̑f��
		int n = static_cast<int>(x + y * 57 + z * 3623);
		// �r�b�g�V�t�g���Z
		// ����ɂ��A�����_���Ȓl�𐶐�
		// 13 : 1�����̃n�b�V���֐��̃V�t�g��
		// 7 : 2�����̃n�b�V���֐��̃V�t�g��
		// 11 : 3�����̃n�b�V���֐��̃V�t�g��
		// n �̃r�b�g������11�r�b�g�V�t�g
		// �����I�ɐ��l��2�̃V�t�g�񐔕��̗ݏ�ŏ�Z���邱�ƂƓ���
		// ���̏ꍇ�� 2 ^ 11(2�i���ł̃V�t�g���Z�̂���)
		// ���̐��l n �̃r�b�g�p�^�[�����ω����A�n�b�V���֐��̃����_����������
		n = (n << 11) ^ n;
		// ����ɂ��A�����_���Ȓl�𐶐�
		// 15731 : 1�����̃n�b�V���֐��̑f��
		// 789221 : 2�����̃n�b�V���֐��̑f��
		// 1376312589 : 3�����̃n�b�V���֐��̑f��
		// & : �r�b�g���Z��AND
		// 0x7fffffff : 32bit�̍ő�l
		// �����̐��l�́A�����_���Ȓl�𐶐����邽�߂̑f��
		// �����Ȃ������ɂ��邽�߂ɁA�r�b�g���Z���s��
		return (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff;
	}

	// �m�C�Y�����̂��߂̌��z�x�N�g���𐶐�����֐�(3�����p)
	// �n�b�V���l����Ɍ��z�x�N�g���𐶐�
	// �m�C�Y�̊e�_�ɂ����ĕ���������������
	// args1 ... �n�b�V���l(�m�C�Y�����̂��߂Ɏg�p)
	// args2~4 ... 3�����̍��W
	// return ... -1.0f ~ 1.0f �̒l
	// ex ... float grad = wta::SimplexNoise::grad(hash,x,y,z);
	inline float grad(int hash, float x, float y, float z)
	{
		// �n�b�V���l�ɑ΂��ăr�b�gAND���Z���s��
		// 15 : 2�i���� 1111
		// �n�b�V���l�̉�4�����擾�i0~15�͈̔͂ɐ����j
		// AND���Z�ɂ��A�n�b�V���l�̉�4���ȊO�̃r�b�g��0�ɂȂ�
		// ���ɂǂ̌��z�x�N�g�����g���������肷�邽�߂ɁA�n�b�V���l�̉�4�����擾
		// ex ) 101101110011(�n�b�V���l)
		// AND  000000000111(15)
		// ------------------
		//      000000000011(3) : ��4���̂ݎc��
		// ��4���̒l�́A���z�x�N�g���I���Ō��肳�ꂽ�͈͂̃C���f�b�N�X�𓾂邽��
		// ���z�x�N�g���̃Z�b�g��12�ł��邽�߁A��4���̒l�����͈̔͂Ɏ��߂���
		// ��4�����g�p����ƁA������l��0~15�͈̔͂ɐ����ł���
		// ��3�����V���v���b�N�X�̎����ł�12�̌��z�x�N�g�����g�p����̂���ʓI
		// 12�̌��z�x�N�g���́A3������Ԃ𐳎l�ʑ̂̌`��i5�j�ɕ��������Ƃ�
		// �e���l�ʑ̂̒��_��12�̈قȂ���z�x�N�g�������蓖�Ă�
		// ����ɂ��A���������m�C�Y����ԑS�̂ɋψ�ɕ��z
		// �e���_�̌��z�x�N�g���́A���̓_�ł̃m�C�Y�ɕ������Ƌ��x������
		// �O�����i�q : �݂��ɗאڂ���i�q�_�i�O���b�h�|�C���g�j�ō\��
		// �e���_����o�����A���̎��͂̋�Ԃ��J�o�[���邽�߂ɐ��l�ʑ̂�z�u
		// 1�̊i�q�_�ɑ΂��āA���̓_���܂ސ��l�ʑ͍̂��v5���݂���
		// ���̊i�q�_�Ƃ��̋ߗׂ̓_����\��������Ԃ��J�o�[���邽��
		int h = hash & 15;
		// u < 8�@�Ȃ�x���g�p���A�����łȂ����y���g�p
		// h : ��L�Ŏ擾������4���̒l�i0~15�͈̔́j
		// 8 ; 0~15�̒����l�i�����_�����A�ϓ��ȕ��z�A�ȈՂȌv�Z�������j
		// �n�b�V���l�Ɋ�Â��Č��z�x�N�g���̈ꕔ��I��
		// �n�b�V���l�ɂ���āAx�܂���y�̂ǂ�����g�p���邩�����肷��
		// 3�����m�C�Y�ɂ�������z�x�N�g���̕������������_�������A
		// �m�C�Y�p�^�[���ɑ��l������������
		// �����_�ł� z���W���܂��l�����Ȃ�
		// z���W���l������ƁA�m�C�Y�p�^�[�����c�����ɐL�тĂ��܂�����
		// u�͌��z�x�N�g���̈ꕔ�Ƃ��āAxy�����ꂩ����̕������𑨂��邽�߂Ɏg�p
		float u = h < 8 ? x : y;
		// �����̂�
		// if (h < 4) {v = y;}
		// else 
		// {
		//		if (h == 12 || h == 14) { v = x;}
		//		else { v = z;}
		//	}
		// �����Ɋ�Â��āAx,y,z�̂ǂ���g�p���邩������
		// 3�����m�C�Y�ɂ�������z�x�N�g���̕������������_�������邽�߂Ɏg�p
		// 4 : �n�b�V���l��0~15(16�̗v�f)�̏ꍇ�A4�ŕ�������@�����ʓI(�ꍇ�ɂ��)
		// 4�ŕ����邱�ƂŁA�m�C�Y�p�^�[���ɑ��l������������
		// 12 : 3�����ł�12�̌��z�x�N�g������ʓI�Ɏg�p����
		// 12�̌��z�x�N�g���́A3������Ԃ𐳎l�ʑ̂̌`��i5�j�ɕ��������Ƃ�
		// �e���l�ʑ̂̒��_��12�̈قȂ���z�x�N�g�������蓖�Ă�
		// 14 : �����_�����A�ϓ��ȕ��z�A�ȈՂȌv�Z���������邽�߂̔C�ӂ̐���
		// �K������14�łȂ��Ă��悢�i�K���ĂȂ���ΓK�X�ύX���Ă��悢�j
		// ��ʓI�ɂ́A����̏����ł�14���œK�Ȃ����ŁA�őP�ł͂Ȃ�
		// ����Ɠ��������ł����̎���p���邱�ƂŁA�p�^�[����ω����邱�Ƃ��\
		// ex ) h < 5 ? x : h < 10 : y : z;
		//		(h % 3 == 0) ? x : (h % 3 == 1) ? y : z;
		//		(h % 6 < 2 ) ? x : (h % 6 < 4) ? y : z;
		// ���̎���p�����̂́A�����_�����A�ϓ��ȕ��z�A�ȈՂȌv�Z���������邽��
		// ����������r�I�V���v���ŁA�v�Z�������ێ��ł���(�œK�ł���őP�ł͂Ȃ�)
		float v = h < 4 ? y : h == 12 || h == 14 ? x : z;
		// ����̓_�ł̌��z�x�N�g�����Z�o
		// h & 1 : �r�b�gAND���Z(&)�ɂ��A�ŉ��ʃr�b�g��0��1���𔻒�(00001)
		// h & 2 : �r�b�gAND���Z(&)�ɂ��A������2�Ԗڂ̃r�b�g�𔻒�(00010)
		// �����̃r�b�g�̒l�ɂ���āA���z�x�N�g���̐���������
		// ���̒l�Ȃ畁�ʂ̎R�A���̒l�Ȃ�t���R
		// �����u��v�̓�̗v�f�̉��Z�����A��萸�I�ɂ��邽��w�����Z���邱�Ƃ�
		// �����܂ŊȈՓI�Ȍv�Z�Ŏ������邽�߁A�����u��v�̓�̗v�f�����Z
		// �������O�����̏ꍇ�A�ő�v�f����3�܂�
		return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
	}
	// 3�����̃V���v���b�N�X�m�C�Y���v�Z����֐�
	float Calculate3DSimplexNoise(tnl::Vector3 pos)
	{
		// 3�����̃V���v���b�N�X�m�C�Y�̌v�Z�́A2�����̌v�Z�Ɠ���
		// 3�����̏ꍇ�́A3�̒��_�̌��z�x�N�g�����v�Z

		// ���z�x�N�g���̌v�Z
		// floor : �^����ꂽ�����̒l�ȉ��̍ő�̐�����Ԃ�(�����_�؂�̂�)
		// ����̓_�̍��W�𐮐��̊i�q�_�Ƀ}�b�s���O���邽��
		// �i�q�_ : ������ԓ��ɂ����Ĉ��Ԋu�Ŕz�u���ꂽ�_
		// �m�C�Y�����ɂ����ċ�Ԃ��\�������A�e�_�̃m�C�Y�l���v�Z���邽�߂Ɏg�p
		// �m�C�Y�l�̎Z�o�ŁA���͂̊i�q�_�Ɋ��蓖�Ă�ꂽ���z�x�N�g�����g�p���邽��
		int ix = (int)floor(pos.x);
		int iy = (int)floor(pos.y);
		int iz = (int)floor(pos.z);
		// �����_�ȉ��̒l�̂ݎ擾
		// �i�q�_����ǂ̈ʗ���Ă��邩��\��
		// �m�C�Y�l�Z�o�ŁA�֘A����i�q�_�Ɋ��蓖�Ă�ꂽ���z�x�N�g�����g�p���邽��
		float fx = pos.x - ix;
		float fy = pos.y - iy;
		float fz = pos.z - iz;

		// �t�F�[�h�֐���K�p
		// �אڂ���i�q�_�Ԃ̃m�C�Y�l�̑J�ڂ����炩�ɂ���
		// �m�C�Y�p�^�[���S�̂ɑ΂��Ă�芊�炩�ŘA���I�ȊO�ς�����
		float u = fade(fx);
		float v = fade(fy);
		float w = fade(fz);

		// �n�b�V���֐����g���Č��z�x�N�g���𐶐�
		// ����̓_�̎��͂ɂ���אڂ���i�q�_�̃n�b�V���l���Z�o
		// +1 : ���̓_�ɍł��߂��אڂ���i�q�_�̍��W���Z�o�ł���
		// ����ɂ��A���̓_�̎��͂ɂ���אڂ���i�q�_�̃n�b�V���l���Z�o
		// +1�ɂ���ĎZ�o�����i�q�_�́A���̓_�̒��ړI�ȗאڋ�Ԃ��J�o�[����B
		// ����ɂ��A��Ԃ̘A�����ƃm�C�Y�̊��炩����ێ�
		// -1��+2�Ȃǂ̒l���g�p����ƁA�m�C�Y�̊��炩����������
		// ����-1���ƁA�w�肳�ꂽ�_�ƈقȂ��ԓI�֌W�����i�q�_���Z�o�����
		float h0 = hash(ix, iy, iz);
		float h1 = hash(ix + 1, iy, iz);
		float h2 = hash(ix, iy + 1, iz);
		float h3 = hash(ix + 1, iy + 1, iz);
		float h4 = hash(ix, iy, iz + 1);
		float h5 = hash(ix + 1, iy, iz + 1);
		float h6 = hash(ix, iy + 1, iz + 1);
		float h7 = hash(ix + 1, iy + 1, iz + 1);

		// ���ꂼ��̒��_�̌��z�x�N�g�����v�Z
		// +1 : ����̓_�̎��͂ɂ���i�q�_��I�����邽��
		// -1 : �����̊i�q�_�ƌ��̓_�̑��Έʒu���v�Z���邽��
		tnl::Vector3 g0 = { grad(h0, fx, fy, fz)
							, grad(h0, fx, fy, fz)
							, grad(h0, fx, fy, fz) };

		tnl::Vector3 g1 = { grad(h1, fx - 1, fy, fz)
							, grad(h1, fx - 1, fy, fz)
							, grad(h1, fx - 1, fy, fz) };

		tnl::Vector3 g2 = { grad(h2, fx, fy - 1, fz)
							, grad(h2, fx, fy - 1, fz)
							, grad(h2, fx, fy - 1, fz) };

		tnl::Vector3 g3 = { grad(h3, fx - 1, fy - 1, fz)
							, grad(h3, fx - 1, fy - 1, fz)
							, grad(h3, fx - 1, fy - 1, fz) };

		tnl::Vector3 g4 = { grad(h4, fx, fy, fz - 1)
							, grad(h4, fx, fy, fz - 1)
							, grad(h4, fx, fy, fz - 1) };

		tnl::Vector3 g5 = { grad(h5, fx - 1, fy, fz - 1)
							, grad(h5, fx - 1, fy, fz - 1)
							, grad(h5, fx - 1, fy, fz - 1) };

		tnl::Vector3 g6 = { grad(h6, fx, fy - 1, fz - 1)
							, grad(h6, fx, fy - 1, fz - 1)
							, grad(h6, fx, fy - 1, fz - 1) };

		tnl::Vector3 g7 = { grad(h7, fx - 1, fy - 1, fz - 1)
							, grad(h7, fx - 1, fy - 1, fz - 1)
							, grad(h7, fx - 1, fy - 1, fz - 1) };

		// �d�݂��v�Z�i����̓_���e�i�q�_����ǂ̒��x����Ă��邩�l���j
		// �m�C�Y�̊��炩�ȑJ�ڂ��������邽�߂Ɏg�p
		// ����̓_�̎��͂ɗאڂ���i�q�_�Ԃ���̊�^�i�d�݁j���Z�o�i�R�Ԃ̔g�j
		// w0 : �_��ix,iy,iz�ɍł��߂��ꍇ�ɍł��傫���Ȃ�	
		// �_�� ix �ɔ��ɋ߂��ꍇ�Au �͏������Ȃ�A1 - u �͑傫���Ȃ�
		// ����́A�_�����̊i�q�_����̉e���������󂯂邱�Ƃ��Ӗ�����
		float w0 = (1 - u) * (1 - v) * (1 - w);
		// w1 : �_��ix+1,iy,iz�ɍł��߂��ꍇ�ɍł��傫���Ȃ�
		float w1 = u * (1 - v) * (1 - w);
		float w2 = (1 - u) * v * (1 - w);
		float w3 = u * v * (1 - w);
		float w4 = (1 - u) * (1 - v) * w;
		float w5 = u * (1 - v) * w;
		float w6 = (1 - u) * v * w;
		float w7 = u * v * w;

		// ���ꂼ��̒��_�̒l���v�Z
		// ���ρi�h�b�g�ρj�́A2�̃x�N�g���Ԃ̕������̊֌W�𐔒l������
		// ����̓_�̌��z�x�N�g���̕����ƁA���̓_�̊i�q�_����̑��Έʒu��]��
		// �_�� g0 �����������ɂǂꂾ����^���邩���Z�o
		// �l���傫���قǁA���z�x�N�g���Ƒ��Έʒu�x�N�g���̕�������v���e��������
		// �m�C�Y�p�^�[���ɕ������Ƌ��x���^�����A���A���Ŋ��炩�ȃe�N�X�`���𐶐�
		float n0 = tnl::Vector3::Dot(g0, { fx, fy, fz });
		float n1 = tnl::Vector3::Dot(g1, { fx - 1, fy, fz });
		float n2 = tnl::Vector3::Dot(g2, { fx, fy - 1, fz });
		float n3 = tnl::Vector3::Dot(g3, { fx - 1, fy - 1, fz });
		float n4 = tnl::Vector3::Dot(g4, { fx, fy, fz - 1 });
		float n5 = tnl::Vector3::Dot(g5, { fx - 1, fy, fz - 1 });
		float n6 = tnl::Vector3::Dot(g6, { fx, fy - 1, fz - 1 });
		float n7 = tnl::Vector3::Dot(g7, { fx - 1, fy - 1, fz - 1 });

		// ��Ԋ֐���K�p���āA�ŏI�I�ȃm�C�Y�l���v�Z
		// �ŏI�I�ȃm�C�Y�l�Z�o�ŁA�����̐��`��Ԃ�g�ݍ��킹�Ďg�p
		// ������� : �אڂ���i�q�_���瓾��ꂽ�m�C�Y�l�in0,n1,n2,n3�Ȃǁj��
		//			�@��ԌW�� u, v, w ��p���Đ��`���
		// ���ԕ�� : ������Ԍ��ʂ��X�ɑg�ݍ��킹�āA���̎����ɉ����ĕ��
		// �ŏI��� : ���ԕ�Ԍ��ʂ� w ��p���ĕ�Ԃ�
		//			�@����̓_�ɂ�����ŏI�I�ȃm�C�Y�l�𐶐�
		float noise = lerp(lerp(lerp(n0, n1, u)
					, lerp(n2, n3, u), v)
					, lerp(lerp(n4, n5, u)
					, lerp(n6, n7, u), v), w);

		return noise;
	}

	// 3����
	// arg1 ... 3�����̍��W(���̓_�ɑ΂��ăm�C�Y�l���v�Z)
	// arg2 ... ���g��(�m�C�Y�p�^�[���ׂ̍�����e���𒲐�)
	// arg3 ... �U��(�m�C�Y�ɕ����̎��g��������ǉ����A��蕡�G�ȃp�^�[���𐶐�)
	// arg4 ... �e�I�N�^�[�u�̐U���̌�����(�����Ȃ�x�A���g���͂��̌W���ɂ���Č���)
	// arg5 ... �e�I�N�^�[�u�̎��g���̑�����(�����Ȃ�x�A���g���͂��̌W���ɂ���đ���)
	// arg6 ... �I�t�Z�b�g(�m�C�Y�l�͈̔͂𒲐�)
	// return ... -1.0f ~ 1.0f �̒l
	float SimplexNoise3D(tnl::Vector3 pos
						, float scale = 1.0f
						, int octaves = 1
						, float persistence = 0.5f
						, float lacunarity = 2.0f
						, float offset = 0.0f)
	{
		// �ݐς����m�C�Y�l
		float total = 0.0f;
		// ���g��
		float frequency = scale;
		// �U��
		float amplitude = 1.0f;
		// �ő�l(���K���̂��߂Ɏg�p�����ő�l��ݐ�)
		float max_value = 0.0f;

		for (int i = 0; i < octaves; i++)
		{
			// �X�P�[�����O���ꂽ���W���Z�o
			// �X�P�[�����O : ���W��ϊ����邱�ƂŁA�m�C�Y�ׂ̍�����e���𒲐�
			float nx = pos.x * frequency / 100.0f;
			float ny = pos.y * frequency / 100.0f;
			float nz = pos.z * frequency / 100.0f;

			// ������3D�V���v���b�N�X�m�C�Y�̌v�Z���s��
			float noise_value = Calculate3DSimplexNoise({ nx, ny, nz });
			// �I�N�^�[�u�̃m�C�Y�l�ɑΉ�����U������Z���A�ݐσm�C�Y�l�ɉ��Z
			// �U�� : �m�C�Y�ɕ����̎��g��������ǉ����A��蕡�G�ȃp�^�[���𐶐�
			total += noise_value * amplitude;
			// ���K���̂��߂Ɏg�p�����ő�l��U���̍��v�ōX�V
			// �ŏI�I�ȃm�C�Y�l������͈͓̔�(-1.0f ~ 1.0f)�Ɏ��܂�悤�ɂ��邽��
			max_value += amplitude;
			// �U���͊e�I�N�^�[�u�Ō���
			// ��荂���I�N�^�[�u�ł̓m�C�Y�̉e�����������Ȃ�A�ׂ����ڍׂ�����
			amplitude *= persistence;
			// ���g�������́A��荂���I�N�^�[�u�ł̃m�C�Y�����̃X�P�[��������������
			// ��荂���I�N�^�[�u�ł̓m�C�Y�̉e�����������Ȃ�A�ׂ����ڍׂ�����
			frequency *= lacunarity;
		}
		// �ݐς��ꂽ�m�C�Y�l���ő�l�Ŋ����Đ��K��
		// ����ɂ��A�m�C�Y�l�͈̔͂� -1.0f ~ 1.0f �ɂȂ�
		return total / max_value + offset;
	}
}

