#ifndef _DETECTED_OBJECT_H
#define _DETECTED_OBJECT_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include <list>

//std::ostream operator<<(std::ostream& os, const cv::Scalar& in)
//{
//    os << in[0] << ", " << in[1] << ", " << in[2];
//    return os;
//}


class DetectedObject
{
public:
    DetectedObject(bool debug = false);

    cv::Point DetectLocation(const cv::Mat& image);

    // image must be hsv
    void UpdateROI(const cv::Mat& image);

    void OpenBB(const cv::Point& firstPoint); 
    void UpdateBB(const cv::Point& secondPoint);

    void CloseBB();

    void DrawBB(cv::Mat& image);



    static int uid;

    struct Blob
    {
        int id;
        cv::Rect box;
        cv::Point center;
        double size;
        double theta;
        std::vector<cv::Point> contour;
        double match;
        int seenCount;
        int matchid;
        double distance;
    };
    std::list<Blob> prevBlobs;
    typedef std::list<Blob> Blobs;
    typedef Blobs::iterator BlobsI;
    typedef Blobs::const_iterator BlobsCI;

private:

    cv::Rect mBoundingBox;
    cv::Point mFirst;
    cv::Point mSecond;
    bool mUpdatingROI;

    cv::Scalar mRangeMin;
    cv::Scalar mRangeMax;

    bool mDebug;

};

#endif
