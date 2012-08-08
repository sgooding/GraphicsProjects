#ifndef CV_PROPS_H
#define CV_PROPS_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include <iomanip>

namespace Props
{


void Print(std::ostream& os, const int& val)
{
    switch(val)
    {
        case CV_CAP_PROP_DC1394_OFF: os << "CV_CAP_PROP_DC1394_OFF        "; break; 
        case CV_CAP_PROP_DC1394_MODE_MANUAL: os << "CV_CAP_PROP_DC1394_MODE_MANUAL"; break;
        case CV_CAP_PROP_DC1394_MODE_AUTO: os << "CV_CAP_PROP_DC1394_MODE_AUTO"; break;
        case CV_CAP_PROP_DC1394_MODE_ONE_PUSH_AUTO: os << "CV_CAP_PROP_DC1394_MODE_ONE_PUSH_AUTO"; break;
        case CV_CAP_PROP_POS_MSEC: os << "CV_CAP_PROP_POS_MSEC"; break;
        case CV_CAP_PROP_POS_FRAMES: os << "CV_CAP_PROP_POS_FRAMES"; break;
        case CV_CAP_PROP_POS_AVI_RATIO: os << "CV_CAP_PROP_POS_AVI_RATIO"; break;
        case CV_CAP_PROP_FRAME_WIDTH: os << "CV_CAP_PROP_FRAME_WIDTH"; break;
        case CV_CAP_PROP_FRAME_HEIGHT: os << "CV_CAP_PROP_FRAME_HEIGHT"; break;
        case CV_CAP_PROP_FPS: os << "CV_CAP_PROP_FPS"; break;
        case CV_CAP_PROP_FOURCC: os << "CV_CAP_PROP_FOURCC"; break;
        case CV_CAP_PROP_FRAME_COUNT: os << "CV_CAP_PROP_FRAME_COUNT"; break;
        case CV_CAP_PROP_FORMAT: os << "CV_CAP_PROP_FORMAT"; break;
        case CV_CAP_PROP_MODE: os << "CV_CAP_PROP_MODE"; break;
        case CV_CAP_PROP_BRIGHTNESS: os << "CV_CAP_PROP_BRIGHTNESS"; break;
        case CV_CAP_PROP_CONTRAST: os << "CV_CAP_PROP_CONTRAST"; break;
        case CV_CAP_PROP_SATURATION: os << "CV_CAP_PROP_SATURATION"; break;
        case CV_CAP_PROP_HUE: os << "CV_CAP_PROP_HUE"; break;
        case CV_CAP_PROP_GAIN: os << "CV_CAP_PROP_GAIN"; break;
        case CV_CAP_PROP_EXPOSURE: os << "CV_CAP_PROP_EXPOSURE"; break;
        case CV_CAP_PROP_CONVERT_RGB: os << "CV_CAP_PROP_CONVERT_RGB"; break;
        case CV_CAP_PROP_WHITE_BALANCE_BLUE_U: os << "CV_CAP_PROP_WHITE_BALANCE_BLUE_U"; break;
        case CV_CAP_PROP_RECTIFICATION: os << "CV_CAP_PROP_RECTIFICATION"; break;
        case CV_CAP_PROP_MONOCROME: os << "CV_CAP_PROP_MONOCROME"; break;
        case CV_CAP_PROP_SHARPNESS: os << "CV_CAP_PROP_SHARPNESS"; break;
        case CV_CAP_PROP_AUTO_EXPOSURE: os << "CV_CAP_PROP_AUTO_EXPOSURE"; break;
        case CV_CAP_PROP_GAMMA: os << "CV_CAP_PROP_GAMMA"; break;
        case CV_CAP_PROP_TEMPERATURE: os << "CV_CAP_PROP_TEMPERATURE"; break;
        case CV_CAP_PROP_TRIGGER: os << "CV_CAP_PROP_TRIGGER"; break;
        case CV_CAP_PROP_TRIGGER_DELAY: os << "CV_CAP_PROP_TRIGGER_DELAY"; break;
        case CV_CAP_PROP_WHITE_BALANCE_RED_V: os << "CV_CAP_PROP_WHITE_BALANCE_RED_V"; break;
        case CV_CAP_PROP_ZOOM: os << "CV_CAP_PROP_ZOOM"; break;
        case CV_CAP_PROP_FOCUS: os << "CV_CAP_PROP_FOCUS"; break;
        case CV_CAP_PROP_GUID: os << "CV_CAP_PROP_GUID"; break;
        case CV_CAP_PROP_ISO_SPEED: os << "CV_CAP_PROP_ISO_SPEED"; break;
        case CV_CAP_PROP_MAX_DC1394: os << "CV_CAP_PROP_MAX_DC1394"; break;
        case CV_CAP_PROP_BACKLIGHT: os << "CV_CAP_PROP_BACKLIGHT"; break;
        case CV_CAP_PROP_PAN: os << "CV_CAP_PROP_PAN"; break;
        case CV_CAP_PROP_TILT: os << "CV_CAP_PROP_TILT"; break;
        case CV_CAP_PROP_ROLL: os << "CV_CAP_PROP_ROLL"; break;
        case CV_CAP_PROP_IRIS: os << "CV_CAP_PROP_IRIS"; break;
        case CV_CAP_PROP_SETTINGS: os << "CV_CAP_PROP_SETTINGS"; break;
    }
}

void PrintCameraParams(cv::VideoCapture& cap)
{
    for( int i = CV_CAP_PROP_DC1394_OFF; i <= CV_CAP_PROP_SETTINGS; i++ )
    {
        if( (int)cap.get(i) < 0 )
            continue;
        std::cout << std::setfill('-') << std::setw(50) << std::left;
        Print(std::cout,i);
        std::cout << std::right << "(" << cap.get(i) 
            << ")"<< std::endl;
    }
}
 
}

#endif
