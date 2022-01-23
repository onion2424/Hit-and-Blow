//// ConsoleApplication1.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
////
//
//#include <iostream>
//#include <emmintrin.h>
//#include <intrin.h>
//#include <vector>
//#include <algorithm>
//#include <functional>
//
////自作
//#include "Target.h"
//#include "Target2.h"
//#include "GameInfo.h"
//#include "Common.h"
//
//using namespace std;
//
//void makeTargetArray(vector<Target>& target); //720個のTargetインスタンスを作成する
//void setMaxNum(vector<Target>& target);
//bool operator<(const Target& left, const Target& right);  //sort用
//bool operator>(const Target& left, const Target& right);  //sort用
//
//
//int main()
//{
//	//カウント用
//	int cnt;
//
//
//	//インスタンス化と同時に初期設定を行う
//	GameInfo gi;
//
//	//初期設定
//	gi.init();
//
//	//Targetにフィールドのアドレスを持たせる
//	Target::field = gi.getField();
//	Target::bitY = gi.getBitY();
//	Target::notY = gi.getNotY();
//	Target::bitZ = gi.getBitZ();
//	Target::notZ = gi.getNotZ();
//
//	//Targetインスタンス作成
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
//	//************ゲーム開始***************　複数回の場合はここからループすればいい
//
//	for (int n = 0; n < gi.LOOP; n++) { //n回の統計を取る
//#pragma region init
//		//フィールドをセットする
//		gi.setField();
//
//		//答えをランダムに選ぶ
//		gi.setAnswer();
//		//gi.showAnswer(); //表示する
//
//		//1手目をランダムで選ぶ
//		gi.setFirstTarget();
//		//gi.showTarget();
//
//		//カウントを初期化
//		cnt = 1;
//
//#pragma endregion 
//
//		//++++++++++ループ部分++++++++++
//		while (!gi.isEnd()) { //ここでhitBlowがセットされる
//			gi.showHitBlow();
//
//			// 1. フィールドを更新する(残りの数を保存する)
//			//gi.optionArray[cnt - 1] += gi.updateField();
//			cout << "残り : " << gi.updateField() << endl;
//
//			//2. それぞれの最大値を求める
//			setMaxNum(target);
//
//			//並び変え
//			sort(target.begin(), target.end());
//
//			//上位n件だけもう一手考える(最上位が1の場合は見ない)
//			if (target[0].maxNum > 1) {
//				for (int i = 0; i < gi.RANGE; i++)
//				{
//					target[i].nextTarget();
//				}
//				sort(target.begin(), target.begin() + gi.RANGE - 1); //上位n件のみ並び変え?
//
//			}
//			//else {
//			//	//残っているのを優先したい?
//			//	//cout << "特定？" << endl;
//			//}
//
//
//
//			//最上位を次の手にセットする
//			gi.setTarget(target[0].target);
//
//			std::cout << "次の予想残り" << target[0].maxNum << std::endl;
//
//			//表示する
//			gi.showTarget();
//
//			if (cnt++ > 10) break;
//
//		}
//
//
//		//何回目かを格納する
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
//	//ゲーム終了時処理
//	//gi.gameEnd();
//	return 0;
//}
//
////*************関数************:
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
////vectorの中身全てに最大値をセットさせる
//void setMaxNum(vector<Target>& target)
//{
//	for (auto& elm : target) {
//		elm.getMaxNum();
//	}
//}
//
////ソート用に関数を定義
//bool operator<(const Target& left, const Target& right)
//{
//	return left.maxNum < right.maxNum;
//}
//bool operator>(const Target& left, const Target& right)
//{
//	return left.maxNum > right.maxNum;
//}
//
//// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
//// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー
//
//// 作業を開始するためのヒント: 
////    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
////   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
////   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
////   4. エラー一覧ウィンドウを使用してエラーを表示します
////   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
////   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
