#include "class_timer.hpp"
#include "class_detector.h"
#include <fstream>

// helper function to parse all the classnames
std::vector<std::string> parseClassnames(std::string filename) {
    std::vector<std::string> classnames;
    std::ifstream fin(filename);
    std::string classname;
    while (fin >> classname)
    {
        classnames.push_back(classname);
    }
    return classnames;
}

int main(int argc, char* argv[]){
    if(argc < 5){
        std::cerr << "Proper use of script " << argv[0] << " <config file path> <weights file path> <classnames file path> <video file path>" << std::endl;
        return 1;
    }

    // loading classes names
    std::vector<std::string> classnames = parseClassnames(argv[3]);
    
    // loading yolov3 config
    Config configV3;
    configV3.net_type = YOLOV3;
    configV3.file_model_cfg = argv[1];
    configV3.file_model_weights = argv[2];
    configV3.calibration_image_list_file_txt = "../configs/calibration_images.txt";
    configV3.inference_precison = FP32;
    configV3.detect_thresh = 0.5;

    std::unique_ptr<Detector> detector(new Detector());
	detector->init(configV3);

    std::vector<BatchResult> batch_res;
	Timer timer;

    cv::VideoCapture cap(argv[4]);
    if(!cap.isOpened()){
        std::cerr << "Video file cannot be loaded" << std::endl;
        return 1;
    }
    
    int frame_width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int frame_height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);

    cv::VideoWriter writer("result.mp4", cv::VideoWriter::fourcc('m', 'p', '4', 'v'), 30, cv::Size(frame_width, frame_height));
    
    cv::Mat frame, tmp;
    int frame_count = 0;
    double total_fps = 0;

    while(cap.isOpened()){
        if(!cap.read(frame)){
            break;
        }
        frame_count++;
        tmp = frame.clone();
        timer.reset();
        detector->detect({frame}, batch_res);
        
        for(const auto &r: batch_res[0]){
            cv::rectangle(frame, r.rect, cv::Scalar(255, 0, 0), 2);
            cv::putText(frame, classnames[r.id], cv::Point(r.rect.x, r.rect.y - 5), cv::FONT_HERSHEY_COMPLEX, 0.5, cv::Scalar(0, 0, 255), 2);
        }

        double fps = 1000 * (1 / timer.elapsed());
        cv::putText(frame, "Inference FPS " + std::to_string(fps), cv::Point(20, 40), cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(0, 0, 255), 2);
        writer.write(frame);
        total_fps += fps;
    }
    cap.release();
    writer.release();

    std::cout << "Average Inference FPS " << (total_fps / frame_count) << std::endl;
    return 0;
}