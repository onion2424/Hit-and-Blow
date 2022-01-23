// ConsoleApplication1.cpp : ���̃t�@�C���ɂ� 'main' �֐����܂܂�Ă��܂��B�v���O�������s�̊J�n�ƏI���������ōs���܂��B
//

#include<string>
#include <iostream>
#include <emmintrin.h>
#include <intrin.h>
#include <vector>
#include <algorithm>
#include <functional>
#include <cctype>

//����
#include "Next.h"
#include "GameInfo.h"
#include "Common.h"


//�֐��錾
bool isValidCall(std::string input, int call[3]);
bool isValidHB(std::string input, int hb[2]);

int main()
{
	int turn = 1; //���^�[���ڂ�
	int count = 0;

	std::string input = "";
	int call[3] = {}; //�R�[���𕪉����Ċi�[����
	int hb[2] = {}; //H&B�𕪉����Ċi�[����

	//Target�C���X�^���X�쐬
	std::vector<Next> nexts;
	//���̎��I�Ԃ��߂̊��Ҍ�␔�ŏ��l�A�ő�l�i�[�p
	int min = 0;
	int max = 0;

	std::cout << "�I������ꍇ�� 'q' ����͂��Ă��������B" << std::endl;
	std::cout << "�܂��A�r���ł�蒼���ꍇ�� 'r' ����͂��Ă��������B" << std::endl << std::endl;

	GameInfo gi; //�Q�[�����N���X�̃C���X�^���X
	gi.init();  //�����ݒ�
	//static�����o�̃A�h���X��ݒ�
	Next::field = gi.getField();
	MiniMax::bitY = gi.getBitY();
	MiniMax::notY = gi.getNotY();
	MiniMax::bitZ = gi.getBitZ();
	MiniMax::notZ = gi.getNotZ();

Game:
	while (true) {
		std::cout << turn << "�^�[����" << std::endl;
		if (turn == 1) { //1�^�[���ڂȂ�Q�[���̏�������������
			gi.setField();
		}

		//�������R�[�������͂����܂ŌJ��Ԃ�(�ϐ� : call�Ɋi�[�����)
		//call���Q�[�����ɃZ�b�g����
		while (std::cout << "�R�[�����������͂��Ă������� : ", std::cin >> input, !isValidCall(input, call)) {
			turn = input == "r" ? 1 : turn; //reset����turn���P�ɂ���΂���
			if (input == "q") {
				return 0; //�Q�[���I��
			}
			else if (input == "r") {
				std::cout << "���X�^�[�g" << std::endl << std::endl;
				goto Game; //���x���t��continue�̑���
			}
		}
		gi.setTarget(call);


		//������H&B�����͂����܂ŌJ��Ԃ� (�ϐ� : hb�Ɋi�[�����)
		//hb���Q�[�����ɃZ�b�g����
		while (std::cout << "Hit&Blow�� '-' �q���œ��͂��Ă������� : ", std::cin >> input, !isValidHB(input, hb)) {
			turn = input == "r" ? 1 : turn; //reset����turn���P�ɂ���΂���
			if (input == "q") {
				return 0; //�Q�[���I��
			}
			else if (input == "r") {
				std::cout << "���X�^�[�g" << std::endl << std::endl;
				goto Game; //���x���t��continue�̑���
			}
		}
		if (input[0] == '3') { //3-0�������ꍇ�̓��Z�b�g
			std::cout << "���萬��!!���̎�����" << std::endl << std::endl;
			turn = 1;
			continue;
		}
		gi.setHitBlow(hb);


		//�Q�[�����̎c��̌�␔���X�V����
		std::cout << "�c�� : " << (count = gi.updateField()) << "�p�^�[��" << std::endl;
		if (!count) { //�c�肪0�ɂȂ��Ă��܂������蒼������
			std::cout << "�����������݂��܂���B������x��蒼���Ă��������B" << std::endl << std::endl;
		}

		//720��̔z����쐬����i���̃R�s�[�ł��ǂ��j
		//���̌�S��̊��Ҍ�␔�𒲂ׂ��̂����̍ő�l���Z�b�g����
		nexts = makeVector();
		setMaxNum(nexts);

		//�ŏ��l�ȊO���폜����
		min = (*min_element(nexts.begin(), nexts.end())).maxNum;
		nexts.erase(remove_if(nexts.begin(), nexts.end(), [min](Next elm) { return elm.maxNum > min; }), nexts.end());
		//�ő�l�����Ƃ��͎��̎���݂�
		while (nexts[0].maxNum > 1) {
			for (int i = 0; i < nexts.size(); i++) {
				//���i�߂�
				nexts[i].setNext();

			}
			//	�ŏ��l�ȊO���폜����
			min = (*min_element(nexts.begin(), nexts.end())).maxNum;
			max = (*max_element(nexts.begin(), nexts.end())).maxNum;
			if (min == max) break; //�ŏ��l�ƍő�l���ς��Ȃ��Ƃ��͂���ȏ㌩�Ă����Ӗ��Ȃ̂Ŕ�����
			nexts.erase(remove_if(nexts.begin(), nexts.end(), [min](Next elm) { return elm.maxNum > min; }), nexts.end());
		}
		//�����o�͂���
		std::cout << "�R�[����̌��(�Z�͐����̉\�����c���Ă���R�[��) : ";
		setIsArrive(gi.getField(), nexts);
		for (int i = 0; i < nexts.size(); i++) { //�ʓ|�Ȃ̂�size��ϐ��ɓ��ꂸ�Ɏg��
			if (i % 10 == 0) std::cout << std::endl; //10�����ɉ��s
			std::cout << nexts[i].target[0] << nexts[i].target[1] << nexts[i].target[2] << (nexts[i].isArrive ? "�Z" : "�@") << " ";

		}

		//���������
		nexts.shrink_to_fit();

		//�^�[����i�߂�
		turn++;
		std::cout << std::endl << std::endl;
	}
	return 0;
}

bool isValidCall(std::string input, int call[3]) {
	bool ret = false;
	//���l���ǂ������`�F�b�N����
	if (input.length() == 3 && std::all_of(input.cbegin(), input.cend(), isdigit))
	{
		//vector�ɓ���ďd���`�F�b�N
		std::vector<int> numbers = { input[0] - '0', input[1] - '0' , input[2] - '0' };
		std::sort(numbers.begin(), numbers.end());
		numbers.erase(std::unique(numbers.begin(), numbers.end()), numbers.end());

		//size���ς��Ȃ���Ώd���Ȃ��Ɣ��f
		if (numbers.size() == 3) {
			call[0] = input[0] - '0';
			call[1] = input[1] - '0';
			call[2] = input[2] - '0';
			ret = true;
		}
		else {
			std::cout << "���������d�����Ă��܂��B" << std::endl;
		}
	}
	else {
		std::cout << "��3�����Ȃ��̐��l����͂��Ă��������B" << std::endl;
	}

	return ret;
}

bool isValidHB(std::string input, int hb[2]) {
	bool ret = false;
	//2�����ڂ�0�ɂ��Đ��l���ǂ����`�F�b�N��������3�ȉ��ł��邱�Ƃ��m�F
	input[1] = '0';
	if (input.length() == 3 && std::all_of(input.cbegin(), input.cend(), isdigit) && input[0] - '0' + input[2] - '0' <= 3)
	{
		hb[0] = input[0] - '0';
		hb[1] = input[2] - '0';
		ret = true;
	}
	else {
		std::cout << "��������Hit Blow������͂��Ă��������B" << std::endl;
	}
	return ret;
}
