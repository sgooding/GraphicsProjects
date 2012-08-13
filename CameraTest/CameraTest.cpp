#include <iostream>
#include <opencv2/opencv.hpp>
#include <sstream>
#include "CVProps.h"
#include "DetectedObject.h"
#include "tserial.h" 


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
    char key(waitKey(30));
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

double ReadIR(Tserial& serial)
{
    int nbytes = serial.getNbrOfBytes();
    std::stringstream ss; 
    for(int i = 0; i < nbytes; i++)
    {
        ss << serial.getChar();
    }
    double distance;
    while(ss.good())
    {
        std::string str;
        std::getline(ss,str);
        if(!str.empty())
        {
            std::stringstream test(str);
            test >> distance;
        }
    }
    return distance;
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
    namedWindow("raw");
    cvSetMouseCallback("raw",onMouseRaw,(void*)(&object));
    
    Tserial irsensor;
    irsensor.connect("COM6", 115200, spNONE);

    Tserial hport;
    hport.connect("COM8", 115200, spNONE);

    for(;;)
    {
        double distance(ReadIR(irsensor));
        std::cout << "IR: " << distance << " cm" <<  std::endl;

        //if( distance > 50 )
        //{
         //   hport.
        //} else if( distance <= 50 )
        //{
        
        int stop[] = { 1,0,1,0 };
        int forward[] = { 2,20,2,20 };
        int reverse[] = { 0,20,0,20 };

        char buff[7];
        if( distance > 80.0 )
        {
            buff[0] = 'H';
            buff[1] = 'B';
            buff[2] = (char)((int)0);
            buff[3] = (char)((int)90);
            buff[4] = (char)((int)2);
            buff[5] = (char)((int)90);
            buff[6] = '\0';
            std::cout << "GO" << std::endl;
        }
        else if( distance < 80.0 && distance > 20 )
        {
            buff[0] = 'H';
            buff[1] = 'B';
            buff[2] = (char)((int)0);
            buff[3] = (char)((int)0);
            buff[4] = (char)((int)2);
            buff[5] = (char)((int)0);
            buff[6] = '\0';
            std::cout << "Slow" << std::endl;
        }
        else  // stop
        {

            buff[0] = 'H';
            buff[1] = 'B';
            buff[2] = (char)((int)1);
            buff[3] = (char)((int)0);
            buff[4] = (char)((int)1);
            buff[5] = (char)((int)0);
            buff[6] = '\0';
            std::cout << "STOP" << std::endl;
        }

        char fl[2];
        fl[0] = 'F';
        fl[1] = 'L';
        hport.sendArray(fl,2);
        hport.sendArray(fl,2);


        {
            int nbytes = hport.getNbrOfBytes();
            std::stringstream ss; 
            for(int i = 0; i < nbytes; i++)
            {
                ss << hport.getChar();
            }
            std::cout << "Received : " << ss.str() << std::endl;
            if( ss.str().find("AUTO") !=std::string::npos )
            {
                std::cout << "Sending Command: " << buff << std::endl;
                hport.sendArray(buff,7);
            }

            {
                int nbytes = hport.getNbrOfBytes();
                std::stringstream ss; 
                for(int i = 0; i < nbytes; i++)
                {
                    ss << hport.getChar();
                }
                std::cout << "Received Command: " << std::endl;
                std::cout << ss.str() << std::endl;
            }

        }
        //}


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
    
    //motorport.disconnect();
    hport.disconnect();
        
    return 0;
}
