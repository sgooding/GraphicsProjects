#include <iostream>
#include <opencv2/opencv.hpp>
#include <sstream>
#include "CVProps.h"
#include "DetectedObject.h"


static const bool realtime(true);
static const char* testimage("traffic_cones.jpg");
    
using namespace cv; 


typedef VideoCapture* VideoCapturePtr; 



void onMouseRaw(int event, int x, int y, int flags, void* params)
{
    DetectedObject* object = (DetectedObject*)params;

    std::cout << event << ", " << flags << std::endl; 

    if( flags == 1 && event == 1)
    {
        object->OpenBB(Point(x,y));
    }
    
    if (event == 0 && flags == 1 )
    {
        object->UpdateBB(Point(x,y));
    } 

    if(event == 4 && flags == 1)
    {
        object->CloseBB();
    }
}

void onMouse(int event, int x, int y, int flags, void* params)
{
    
    //if( event == CV_EVENT_LBUTTONUP )
    {
        ///Mat* hsv = (Mat*)(params);
        ///Vec3b p = hsv->at<Vec3b>(Point(x,y));
        ///std::stringstream ss; ss << x <<", "<<y<< " : " ; 
        ///ss << (int)p[0] << ", " << (int)p[1] << ", " << (int)p[2];
        ///displayOverlay("hsv",ss.str());
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

bool UpdateKey(VideoCapturePtr& cap, Mat frame)
{
    char key(waitKey(100));
    if(key=='q'){ return false; }
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

    return true;
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

    bool debug = true;
    DetectedObject object(debug);


    Mat hsv;
    namedWindow("thresh");
    namedWindow("raw");
    cvSetMouseCallback("raw",onMouseRaw,(void*)(&object));


    for(;;)
    {
        if(cap)
        {
            *(cap) >> frame;
        }

        object.DrawBB(frame);

        imshow("raw",frame);

        cvtColor(frame,hsv,CV_BGR2HSV);

        object.UpdateROI(hsv);

        Point found = object.DetectLocation(hsv);
        
        //vector<Mat> hsv_split;
        //split(hsv,hsv_split);

        //imshow("hsv",hsv_split[0]);

        if(!UpdateKey(cap,frame))
        {
            std::cout << "GoodBye" << std::endl;
            break;
        }

    }


    if(cap)
    {
        delete cap;
    }
        
    return 0;
}
