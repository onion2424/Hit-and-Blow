//// ConsoleApplication1.cpp : ���̃t�@�C���ɂ� 'main' �֐����܂܂�Ă��܂��B�v���O�������s�̊J�n�ƏI���������ōs���܂��B
////
//
//#include <iostream>
//#include <emmintrin.h>
//#include <intrin.h>
//#include <vector>
//#include <algorithm>
//#include <functional>
//
////����
//#include "Target.h"
//#include "Target2.h"
//#include "GameInfo.h"
//#include "Common.h"
//
//using namespace std;
//
//void makeTargetArray(vector<Target>& target); //720��Target�C���X�^���X���쐬����
//void setMaxNum(vector<Target>& target);
//bool operator<(const Target& left, const Target& right);  //sort�p
//bool operator>(const Target& left, const Target& right);  //sort�p
//
//
//int main()
//{
//	//�J�E���g�p
//	int cnt;
//
//
//	//�C���X�^���X���Ɠ����ɏ����ݒ���s��
//	GameInfo gi;
//
//	//�����ݒ�
//	gi.init();
//
//	//Target�Ƀt�B�[���h�̃A�h���X����������
//	Target::field = gi.getField();
//	Target::bitY = gi.getBitY();
//	Target::notY = gi.getNotY();
//	Target::bitZ = gi.getBitZ();
//	Target::notZ = gi.getNotZ();
//
//	//Target�C���X�^���X�쐬
//	vector<Target> target(720);
//	//makeTargetArray(target);
//	int i = 0;
//	for (int x = 0; x < 10; x++) {
//		for (int y = 0; y < 10; y++) {
//			if (x == y) continue;
//			for (int z = 0; z < 10; z++) {
//				if (x == z || y == z) continue;
//				target[i++] = *new Target(x, y, z);
//			}
//		}
//	}
//	//************�Q�[���J�n***************�@������̏ꍇ�͂������烋�[�v����΂���
//
//	for (int n = 0; n < gi.LOOP; n++) { //n��̓��v�����
//#pragma region init
//		//�t�B�[���h���Z�b�g����
//		gi.setField();
//
//		//�����������_���ɑI��
//		gi.setAnswer();
//		//gi.showAnswer(); //�\������
//
//		//1��ڂ������_���őI��
//		gi.setFirstTarget();
//		//gi.showTarget();
//
//		//�J�E���g��������
//		cnt = 1;
//
//#pragma endregion 
//
//		//++++++++++���[�v����++++++++++
//		while (!gi.isEnd()) { //������hitBlow���Z�b�g�����
//			gi.showHitBlow();
//
//			// 1. �t�B�[���h���X�V����(�c��̐���ۑ�����)
//			//gi.optionArray[cnt - 1] += gi.updateField();
//			cout << "�c�� : " << gi.updateField() << endl;
//
//			//2. ���ꂼ��̍ő�l�����߂�
//			setMaxNum(target);
//
//			//���ѕς�
//			sort(target.begin(), target.end());
//
//			//���n�������������l����(�ŏ�ʂ�1�̏ꍇ�͌��Ȃ�)
//			if (target[0].maxNum > 1) {
//				for (int i = 0; i < gi.RANGE; i++)
//				{
//					target[i].nextTarget();
//				}
//				sort(target.begin(), target.begin() + gi.RANGE - 1); //���n���̂ݕ��ѕς�?
//
//			}
//			//else {
//			//	//�c���Ă���̂�D�悵����?
//			//	//cout << "����H" << endl;
//			//}
//
//
//
//			//�ŏ�ʂ����̎�ɃZ�b�g����
//			gi.setTarget(target[0].target);
//
//			std::cout << "���̗\�z�c��" << target[0].maxNum << std::endl;
//
//			//�\������
//			gi.showTarget();
//
//			if (cnt++ > 10) break;
//
//		}
//
//
//		//����ڂ����i�[����
//		gi.turnArray[cnt - 1]++;
//
//
//		//if (cnt == 7) {
//		//	cout << "oh" << endl;
//		//	cout << "ans" << endl;
//		//	cout << gi.ans[0] << gi.ans[1] << gi.ans[2] << endl;
//		//	cout << "first" << endl;
//		//	cout << gi.first[0] << gi.first[1] << gi.first[2] << endl;
//		//	cout << "6 : " << six << "/" << cnt;
//		//	return 0;
//		//}
//		//else { 
//		//	cout << cnt << endl;
//		//	if (cnt == 6) six++;
//		//}
//	}
//	//�Q�[���I��������
//	//gi.gameEnd();
//	return 0;
//}
//
////*************�֐�************:
//void makeTargetArray(vector<Target>& target)
//{
//	int i = 0;
//	for (int x = 0; x < 10; x++) {
//		for (int y = 0; y < 10; y++) {
//			if (x == y) continue;
//			for (int z = 0; z < 10; z++) {
//				if (x == z || y == z) continue;
//				target[i++] = *new Target(x, y, z);
//			}
//		}
//	}
//	return;
//}
//
////vector�̒��g�S�Ăɍő�l���Z�b�g������
//void setMaxNum(vector<Target>& target)
//{
//	for (auto& elm : target) {
//		elm.getMaxNum();
//	}
//}
//
////�\�[�g�p�Ɋ֐����`
//bool operator<(const Target& left, const Target& right)
//{
//	return left.maxNum < right.maxNum;
//}
//bool operator>(const Target& left, const Target& right)
//{
//	return left.maxNum > right.maxNum;
//}
//
//// �v���O�����̎��s: Ctrl + F5 �܂��� [�f�o�b�O] > [�f�o�b�O�Ȃ��ŊJ�n] ���j���[
//// �v���O�����̃f�o�b�O: F5 �܂��� [�f�o�b�O] > [�f�o�b�O�̊J�n] ���j���[
//
//// ��Ƃ��J�n���邽�߂̃q���g: 
////    1. �\�����[�V���� �G�N�X�v���[���[ �E�B���h�E���g�p���ăt�@�C����ǉ�/�Ǘ����܂� 
////   2. �`�[�� �G�N�X�v���[���[ �E�B���h�E���g�p���ă\�[�X�Ǘ��ɐڑ����܂�
////   3. �o�̓E�B���h�E���g�p���āA�r���h�o�͂Ƃ��̑��̃��b�Z�[�W��\�����܂�
////   4. �G���[�ꗗ�E�B���h�E���g�p���ăG���[��\�����܂�
////   5. [�v���W�F�N�g] > [�V�������ڂ̒ǉ�] �ƈړ����ĐV�����R�[�h �t�@�C�����쐬���邩�A[�v���W�F�N�g] > [�����̍��ڂ̒ǉ�] �ƈړ����Ċ����̃R�[�h �t�@�C�����v���W�F�N�g�ɒǉ����܂�
////   6. ��قǂ��̃v���W�F�N�g���ĂъJ���ꍇ�A[�t�@�C��] > [�J��] > [�v���W�F�N�g] �ƈړ����� .sln �t�@�C����I�����܂�
