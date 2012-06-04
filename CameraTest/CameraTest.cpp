#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char* argv[])
{
    using namespace cv; 
    VideoCapture cap(0);
    if(!cap.isOpened())
    {
        std::cerr << "Failed to open capture." << std::endl;
        return -1;
    }

    namedWindow("capture",0);
    Mat frame;
    Ptr<FeatureDetector> detector(new SimpleBlobDetector());
    

    for(;;)
    {
        cap >> frame;
        frame.resize(3*frame.rows/4);
        vector<KeyPoint> keypoints;
        detector->detect(frame,keypoints);
        std::cout << "KeyPoints = " << keypoints.size() << std::endl;
        drawKeypoints(frame,keypoints,frame);
        imshow("capture",frame);


        if(waitKey(30)>=0) break;
    }
        
    return 0;
}
