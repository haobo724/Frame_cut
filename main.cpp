
#include <opencv2/opencv.hpp>
#include <math.h>
#include<vector>
#include <io.h>
#include <string>
#include <vector>
#include <fstream>
#include <direct.h>

using namespace cv;
using namespace std;


/// <summary>
/// split Frame from video ,the output frame from each video will automatic save in folder where has same name as video file

vector <string> getAllFiles(string path, vector<String> &src_name) {

	glob(path, src_name, false);
	return src_name;
}

void video_spliit(string &videoname) {


	VideoCapture capture(videoname);
	cout << capture.get(CAP_PROP_FRAME_COUNT) << endl;
	vector <Mat> skin_frame;
	double ratio;
	while (capture.isOpened())
	{
		Mat frame;
		capture >> frame;
		if (frame.empty()) {
			break;
		}
		skin_frame.push_back(frame);
		//Mat detectImg;
		//ratio = 0;
		//ratio = ellipse_detect(frame);
		//if (ratio > 0) { skin_frame.push_back(frame); }
		//imshow("视频", detectImg);
		//waitKey(1);
	}
	std::cout << skin_frame.size() << endl;
	destroyAllWindows();

	vector<Mat>::iterator i;  
	const String img_path = "F:/opencv/tracing/output/";

	int index = videoname.find_last_of("\\");

	string filename = videoname.substr(index + 1, -1);

	index = filename.find_last_of(".");
	string save_path_name = filename.substr(0, index);

	save_path_name = img_path + save_path_name;

	if (0 != access(save_path_name.c_str(), 0))
	{
		// if this folder not exist, create a new one.
		mkdir(save_path_name.c_str());   // 返回 0 表示创建成功，-1 表示失败
	}

	const String suffix = ".jpg";
	int timer = 0;

	for (i = skin_frame.begin(); i != skin_frame.end(); ++i) {  
		Mat frame;
		frame = *i;
		String nr = to_string(timer);
		String name = save_path_name +'\\' + nr + suffix;
		imwrite(name, frame);
		//imshow("视频", frame);
		//waitKey(10);
		timer++;
	}
	destroyAllWindows();

}



void do_video_split() {
	const string videopath = "F:/opencv/tracing/Training_videos/*.mp4";//path to video
	string write_path = "F:/opencv/tracing/output";//path to save

	if (0 != access(write_path.c_str(), 0))
	{
		// if this folder not exist, create a new one.
		mkdir(write_path.c_str());   
	}


	vector<String> src_name;

	getAllFiles(videopath, src_name);
	vector<String>::iterator i;
	for (i = src_name.begin(); i != src_name.end(); ++i) { 
		video_spliit(*i);
	}
}
int main(int argc, char* argv[]) {
	do_video_split();
	return 0;
}

