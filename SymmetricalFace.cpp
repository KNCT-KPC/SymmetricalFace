#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

const char mainWin[] = "Symmetrical Face";
const char rightWin[] = "RightWindow";
const char leftWin[] = "LeftWindow";

int main(int argc, char *argv[])
{
	Mat maskImg, frame, grayframe;

	//ウィンドウ生成
	namedWindow(mainWin, WINDOW_AUTOSIZE);
	namedWindow(rightWin, WINDOW_AUTOSIZE);
	namedWindow(leftWin, WINDOW_AUTOSIZE);

	// カスケード分類器の取得
	CascadeClassifier cascade;
	if (!cascade.load("haarcascade_frontalface_alt.xml")) return -1;

	// カメラのキャプチャ
	VideoCapture cap(0);
	if (!cap.isOpened()) return -1;

	vector<Rect> faces;
	while (1) {
		// カメラ映像の取得	
		cap >> frame;

		// グレースケール変換
		cvtColor(frame, grayframe, CV_RGB2GRAY);

		// ヒストグラムの平坦化
		equalizeHist(grayframe, grayframe);

		// カスケード分類器で顔の探索
		cascade.detectMultiScale(grayframe, faces, 1.2, 2, CV_HAAR_SCALE_IMAGE, Size(30, 30));

		for (vector<Rect>::const_iterator r = faces.begin(); r != faces.end(); ++r) {
			Mat cutImg(frame, Rect(r->x, r->y, r->width, r->height));
			Mat reverseImg = cutImg.clone();
			Mat dstImg = cutImg.clone();
			flip(cutImg, reverseImg, 1);
			cutImg.copyTo(dstImg);

			for (int x = 0; x < r->width/2; x++) {
				for (int y = 0; y < r->height; y++) {
					// 顔左半面の画素
					int z1 = y*reverseImg.step + x*reverseImg.channels();
					int r = reverseImg.data[z1 + 2];
					int g = reverseImg.data[z1 + 1];
					int b = reverseImg.data[z1];
					int a = reverseImg.data[z1 + 3];
					// 書き換え
					int z2 = y *dstImg.step + x * dstImg.channels();
					dstImg.data[z2 + 2] = r;
					dstImg.data[z2 + 1] = g;
					dstImg.data[z2] = b;

					// 顔右半面の画素
					z1 = y*cutImg.step + x*cutImg.channels();
					r = cutImg.data[z1 + 2];
					g = cutImg.data[z1 + 1];
					b = cutImg.data[z1];
					a = cutImg.data[z1 + 3];
					// 書き換え
					z2 = y *reverseImg.step + x * reverseImg.channels();
					reverseImg.data[z2 + 2] = r;
					reverseImg.data[z2 + 1] = g;
					reverseImg.data[z2] = b;
					
				}
			}
			imshow(rightWin, reverseImg);
			imshow(leftWin, dstImg);
		}

		// 映像の表示
		imshow(mainWin, frame);

		int key = waitKey(1);
		if (key == 113) { // qが押されたとき
			break; // whileループから抜ける．
		}
		else if (key == 115) { // sが押されたとき
			imwrite("img.png", frame); // フレーム画像を保存する．
		}
	}
	return 1;
}
