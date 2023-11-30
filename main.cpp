#include <opencv2/opencv.hpp>
#include <mjpeg_streamer.hpp>
#include <net.h>
#include <pthread.h>

using namespace std;
using namespace cv;

using MJPEGStreamer = nadjieb::MJPEGStreamer;

int main(int argc, char **argv) {

    int VideoPort = 0;
    bool low_quality_mode = true;

    if(argc >= 2) {
        VideoPort = atoi(argv[1]);
    }

    VideoCapture cap(VideoPort);

    if(!cap.isOpened()) {
        std::cout << "Cannot open cam" << std::endl;
        return -1;
    }

    cap.set(cv::CAP_PROP_FOURCC, cv::CAP_OPENCV_MJPEG);
    if(!cap.set(cv::CAP_PROP_FRAME_WIDTH, 640))
        std::cout << "camera set width error" << std::endl;
    if(!cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480))
        std::cout << "camera set height error" << std::endl;
    
    MJPEGStreamer streamer;
    std::vector<int> params = {cv::IMWRITE_JPEG_QUALITY, 90};
    streamer.start(7778);

    std::chrono::steady_clock::time_point Tbegin, Tend;

    
    while(cap.isOpened()) {
        Mat frame;
        Tbegin = std::chrono::steady_clock::now();
        cap >> frame;

        if(low_quality_mode == true)
            resize(frame, frame, Size(), 1.0f / 2.0f, 1.0f / 2.0f, INTER_AREA);

        Tend = std::chrono::steady_clock::now();
        float fps = std::chrono::duration_cast<std::chrono::milliseconds>(Tend - Tbegin).count();
      
        putText(frame, cv::format("FPS %0.2f", 1000.0/fps), cv::Point(10, 20), cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(0, 0, 255));
#ifdef __x86_64__
        imshow("frame", frame);
        const int key = cv::waitKey(1);
#endif
        std::vector<uchar> buff_bgr;
        cv::imencode(".jpg", frame, buff_bgr, params);
        streamer.publish("/frame", std::string(buff_bgr.begin(), buff_bgr.end()));
    }
    streamer.stop();
    return 0;
}




