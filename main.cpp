#include <sys/stat.h>
#include <iostream>
#include <iomanip>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main(int argc, char** argv)
{
    std::cout << std::endl;

    if (argc != 4){
        std::cerr << "Invalid parameters! [./extract_image video_path video_name skips]" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::string video_path(argv[1]);
    std::string video_name(argv[2]);
    if (atoi(argv[3]) <= 0){
        std::cerr << "skips <= 0" << std::endl;
        exit(EXIT_FAILURE);
    }
    const unsigned int skips = atoi(argv[3]);

    std::string image_full_name = video_path+"/"+video_name;
    std::string save_path = image_full_name.substr(0, image_full_name.length() - 4);
    const int flag_mkdir = mkdir(save_path.c_str(), S_IRWXU);
    if (flag_mkdir != 0) {
        std::cerr << "Failure to creat folder, maybe Folder already exists!" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Start extract images" << std::endl;
    VideoCapture cap(image_full_name);
    long totalFrameNum = cap.get(CV_CAP_PROP_FRAME_COUNT);
    cout << "Total frame: " << totalFrameNum << endl;
    Mat frame;
    bool flags = true;
    long currentFrame = 1;

    while (flags)
    {
        cap.read(frame);
        stringstream str;
        str << currentFrame << ".jpg";
        cout << "dealing " << currentFrame << " frame";
        cout  << " [ " << (unsigned int) (static_cast<float>(currentFrame) / static_cast<float>(totalFrameNum) * 100) << "% ]" << endl;

        if (currentFrame % skips == 0) {
            imwrite(save_path + "/" + str.str(), frame);
        }

        if (currentFrame >= totalFrameNum) {
            flags = false;
        }

        currentFrame++;

    }

    cap.release();
    waitKey(0);
    return 0;
}