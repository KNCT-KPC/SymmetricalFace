#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

const char mainWin[] = "Symmetrical Face";
const char rightWin[] = "RightWindow";
const char leftWin[] = "LeftWindow";

int main(int argc, char *argv[])
{
	Mat maskImg, frame, grayframe;

	//�E�B���h�E����
	namedWindow(mainWin, WINDOW_AUTOSIZE);
	namedWindow(rightWin, WINDOW_AUTOSIZE);
	namedWindow(leftWin, WINDOW_AUTOSIZE);

	// �J�X�P�[�h���ފ�̎擾
	CascadeClassifier cascade;
	if (!cascade.load("haarcascade_frontalface_alt.xml")) return -1;

	// �J�����̃L���v�`��
	VideoCapture cap(0);
	if (!cap.isOpened()) return -1;

	vector<Rect> faces;
	while (1) {
		// �J�����f���̎擾	
		cap >> frame;

		// �O���[�X�P�[���ϊ�
		cvtColor(frame, grayframe, CV_RGB2GRAY);

		// �q�X�g�O�����̕��R��
		equalizeHist(grayframe, grayframe);

		// �J�X�P�[�h���ފ�Ŋ�̒T��
		cascade.detectMultiScale(grayframe, faces, 1.2, 2, CV_HAAR_SCALE_IMAGE, Size(30, 30));

		for (vector<Rect>::const_iterator r = faces.begin(); r != faces.end(); ++r) {
			Mat cutImg(frame, Rect(r->x, r->y, r->width, r->height));
			Mat reverseImg = cutImg.clone();
			Mat dstImg = cutImg.clone();
			flip(cutImg, reverseImg, 1);
			cutImg.copyTo(dstImg);

			for (int x = 0; x < r->width/2; x++) {
				for (int y = 0; y < r->height; y++) {
					// �獶���ʂ̉�f
					int z1 = y*reverseImg.step + x*reverseImg.channels();
					int r = reverseImg.data[z1 + 2];
					int g = reverseImg.data[z1 + 1];
					int b = reverseImg.data[z1];
					int a = reverseImg.data[z1 + 3];
					// ��������
					int z2 = y *dstImg.step + x * dstImg.channels();
					dstImg.data[z2 + 2] = r;
					dstImg.data[z2 + 1] = g;
					dstImg.data[z2] = b;

					// ��E���ʂ̉�f
					z1 = y*cutImg.step + x*cutImg.channels();
					r = cutImg.data[z1 + 2];
					g = cutImg.data[z1 + 1];
					b = cutImg.data[z1];
					a = cutImg.data[z1 + 3];
					// ��������
					z2 = y *reverseImg.step + x * reverseImg.channels();
					reverseImg.data[z2 + 2] = r;
					reverseImg.data[z2 + 1] = g;
					reverseImg.data[z2] = b;
					
				}
			}
			imshow(rightWin, reverseImg);
			imshow(leftWin, dstImg);
		}

		// �f���̕\��
		imshow(mainWin, frame);

		int key = waitKey(1);
		if (key == 113) { // q�������ꂽ�Ƃ�
			break; // while���[�v���甲����D
		}
		else if (key == 115) { // s�������ꂽ�Ƃ�
			imwrite("img.png", frame); // �t���[���摜��ۑ�����D
		}
	}
	return 1;
}