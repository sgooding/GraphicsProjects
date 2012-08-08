#include <iostream>
#include <opencv2/opencv.hpp>
#include <sstream>
#include "CVProps.h"

static const bool realtime(true);
static const char* testimage("traffic_cones.jpg");
    
using namespace cv; 

Rect gBoundingBox;
Point gFirst;
Point gSecond;

void onMouseRaw(int event, int x, int y, int flags, void* params)
{

    std::cout << event << ", " << flags << std::endl; 

    if( flags == 1 && event == 1)
    {
        gFirst = Point(x,y);
    }
    else if (flags == 1 )
    {
        gSecond = Point(x,y);
    }
}

void onMouse(int event, int x, int y, int flags, void* params)
{
    
    //if( event == CV_EVENT_LBUTTONUP )
    {
        Mat* hsv = (Mat*)(params);
        Vec3b p = hsv->at<Vec3b>(Point(x,y));
        std::stringstream ss; ss << x <<", "<<y<< " : " ; 
        ss << (int)p[0] << ", " << (int)p[1] << ", " << (int)p[2];
        displayOverlay("hsv",ss.str());
    //    displayStatusBar("hsv",ss.str());
    }

}

int SetupCapture(VideoCapture*& cap)
{
    cap = new VideoCapture(0);
    if(!cap->isOpened())
    {
        std::cerr << "Failed to open capture." << std::endl;
        return -1;
    }
    cap->set(CV_CAP_PROP_FRAME_WIDTH,320);
    cap->set(CV_CAP_PROP_FRAME_HEIGHT,240);
    return 0;
}

int main(int argc, char* argv[])
{
    VideoCapture* cap(NULL);
    if( realtime) 
    {
        if( SetupCapture(cap) != 0 )
        {
            return -1;
        } 
        Props::PrintCameraParams(*cap);
    }

    //SimpleBlobDetector detector;
    Mat frame;
    if( !cap)
    {
        frame=imread(testimage);
    }
    Mat hsv;
    namedWindow("thresh");
    int minHue,maxHue,minSat,maxSat,minVal,maxVal;
    createTrackbar("minHue","thresh",&minHue, 180);
    createTrackbar("maxHue","thresh",&maxHue, 180);
    createTrackbar("minSat","thresh",&minSat, 255);
    createTrackbar("maxSat","thresh",&maxSat, 255);
    createTrackbar("minVal","thresh",&minVal, 255);
    createTrackbar("maxVal","thresh",&maxVal, 255);
    namedWindow("hsv");
    cvSetMouseCallback("hsv",onMouse,(void*)(&hsv));
    namedWindow("raw");
    cvSetMouseCallback("raw",onMouseRaw,(void*)(&frame));
    for(;;)
    {
        if(cap)
        {
            *(cap) >> frame;
        }
        //frame.resize(3*frame.rows/8);
        Rect roi(gFirst,gSecond);
        rectangle(frame,roi,Scalar(0,255,0));

       imshow("raw",frame);
        //blur(frame,frame,Size(3,3));
        cvtColor(frame,hsv,CV_BGR2HSV);


        Mat roi_frame(hsv, roi);
        Scalar avg,stdev;
        meanStdDev(roi_frame,avg,stdev);
        std::cout << "avg:" << avg[0] << " : " << stdev[0] << std::endl;
        Scalar sigma;
        sqrt(stdev,sigma);
        sigma *= 2.0;
        Scalar range_min(0,0,0);
        Scalar range_max(180,255,255);
        for( int i = 0; i < 3; i++ )
        {
        range_min[i] = max( avg[i] - sigma[i], range_min[i] );
        range_max[i] = min( avg[i] + sigma[i], range_max[i] );
        std::cout << i << " " << range_min[i] << "-" << range_max[i] << std::endl;
        }

 


        Mat thresh(frame.rows,frame.cols,8,1);
        //inRange(hsv,Scalar(minHue,minSat,minVal),Scalar(maxHue,maxSat,maxVal),thresh);
        inRange(hsv,range_min,range_max,thresh);
        //erode(thresh,thresh, Mat());
        //dilate(thresh,thresh,Mat());

        //thresh = ( hsv > Scalar(20,100,100) && hsv < Scalar(30,100,100) );
        
        //vector<KeyPoint> keypoints;
        //detector.detect(frame,keypoints);
        //drawKeypoints(frame,keypoints,frame);
        //imshow("hsv",hsv);
        vector<Mat> hsv_split;
        split(hsv,hsv_split);
        imshow("hsv",hsv_split[0]);
        imshow("thresh",thresh);


        char key(waitKey(30));
        if(key=='q') break;
        if(key=='s')
        {
            imwrite(testimage,frame);
        }
        if(key=='r')
        {
            if(cap)
            {
                delete cap;
                cap = NULL;
                frame=imread(testimage);
            }
            else
            {
                if( SetupCapture(cap) != 0 )
                {
                    delete cap;
                    cap = NULL;
                }
            }
        }
    }


    if(cap)
    {
        delete cap;
    }
        
    return 0;
}
