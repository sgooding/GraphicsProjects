#include "DetectedObject.h"
#include <vector>
#include <list>
#include <algorithm>

using namespace cv;

int DetectedObject::uid = 0;

DetectedObject::DetectedObject(bool debug) : mFirst(1,1), mSecond(1,1), mUpdatingROI(false), mDebug(debug)
{
}

void
DetectedObject::DrawBB(cv::Mat& image)
{
    if(!mDebug)
        return;

    if(mUpdatingROI)
    {
        Rect roi(mFirst,mSecond);
        rectangle(image,roi,Scalar(0,255,0));
    }

}

void DetectedObject::OpenBB(const cv::Point& firstPoint) 
{
    mUpdatingROI = true;
    mFirst = firstPoint;
}

void DetectedObject::UpdateBB(const cv::Point& secondPoint)
{
    if( !mUpdatingROI )
        return;

    mSecond = secondPoint;
}

void DetectedObject::CloseBB()
{
    mUpdatingROI = false;
}

Point
DetectedObject::DetectLocation(const Mat& image)
{
    if(mUpdatingROI)
        return Point(1,1);

    Mat thresh(image.rows,image.cols,CV_8UC3);
    inRange(image,mRangeMin,mRangeMax,thresh);
    std::cout << " ********************** " << std::endl;
    for(int i = 0; i < 3; i++ )
    {
    //std::cout << "Using: " << mRangeMin[i] << " -> " << mRangeMax[i] << std::endl;
    }

    std::vector<std::vector<Point> > contours;
    erode(thresh, thresh, Mat());
    dilate(thresh, thresh, Mat());
    findContours(thresh, contours,0,CV_RETR_LIST);
    //drawContours(thresh,contours,-1,Scalar(255));


    std::list<Blob> blobs;
    for( size_t i = 0; i < contours.size(); i++ )
    {
        Moments object = moments(contours[i]);

        float u20 = object.m20/object.m00;
        float u02 = object.m02/object.m00;
        float u11 = object.m11/object.m00;
        float theta = 999;
        if( abs(u20-u02) > 0.0001 )
        {
            theta = .5*atan((2.0*u11)/(u20-u02))*180.0/M_PI;
        }
        Rect rect = boundingRect(contours[i]);

        uid++;

        Blob blob = {uid, rect, Point(object.m01/object.m00,object.m10/object.m00), object.m00, theta, contours[i], 999999.0,0, -1, 999999.0};
        if( blobs.empty() )
        {
            blobs.push_front(blob);
        } else if( blobs.front().size > blob.size )
        {
            blobs.push_back(blob);
        } else
        {
            blobs.push_front(blob);
        }
    }

    std::list<BlobsI> b_d;
    for( BlobsI b = blobs.begin(); b != blobs.end(); ++b )
    {
        for( BlobsI bn = b; bn != blobs.end(); ++bn )
        {
            if( b->box.contains(bn->box.tl()) && b->box.contains(bn->box.br()) )
            {
                b_d.push_back(bn);
                //std::cout << "Erasing:" << bn->size << std::endl;
            }
        }
    }
    b_d.sort(CompareBlobs());
    b_d.unique(EqualBlobs());
    for(std::list<BlobsI>::iterator bi = b_d.begin(); bi != b_d.end(); ++bi)
    {
        std::cout << "Erasing : " << (*bi)->id << std::endl;
    }
    for(std::list<BlobsI>::iterator bi = b_d.begin(); bi != b_d.end(); ++bi)
    {
        blobs.erase(*(bi));

    }

    if( !prevBlobs.empty() )
    {
        for( BlobsI p = prevBlobs.begin(); p != prevBlobs.end(); ++p )
        {
            for( BlobsI b = blobs.begin(); b != blobs.end(); ++b )
            {
                double m_val=matchShapes(p->contour, b->contour, CV_CONTOURS_MATCH_I1,0.0);
                if( m_val < b->match )
                {
                    b->match = m_val;
                    b->matchid = p->id;
                    b->distance = norm(b->center - p->center);
                }
            }
        }
    }

    if( !prevBlobs.empty() )
    {
        for( BlobsI b = blobs.begin(); b != blobs.end(); )
        {
            if( ( std::abs(b->distance ) > b->box.width ) || 
                 ( std::abs(b->distance ) > b->box.height )   )
            {
                blobs.erase(b++);
            }
            else
            {
                ++b;
            }
        }
    }

    if( blobs.empty() ) 
    {
        prevBlobs = blobs;
        return Point(-1,-1); 
    }
    for( BlobsI b = blobs.begin(); b != blobs.end(); ++b )
    {
        if( prevBlobs.empty() )
        {
            break;
        }
        for( BlobsI p = prevBlobs.begin(); p !=prevBlobs.end(); ++p )
        {
            if( b->matchid == p->id )
            {
                b->seenCount += p->seenCount + 1;
            }

        }
    }



    prevBlobs = blobs;

    if(mDebug)
    {
        if( blobs.empty() ) 
        {
            return Point(-1,-1);
        }
        float color(255.0);
        float colorsdx( color/(blobs.size()+1));
        for( BlobsCI b = blobs.begin(); b != blobs.end(); b++ )
        {
            std::cout << b->seenCount << " : " << b->size << " : " << b->theta << std::endl; 
            if( b->seenCount >= 1 )
            {
                rectangle(thresh,b->box,Scalar((unsigned char)color));
            }
            color -= colorsdx;
        }
        imshow("thresh",thresh);
    }


    return blobs.front().center;
}

// image must be hsv
void 
DetectedObject::UpdateROI(const Mat& image)
{
    if(!mUpdatingROI)
    {
        return;
    }

    //imshow("goin",image);
    Rect roi(mFirst,mSecond);
    Mat roi_frame(image, roi);
    Scalar avg,stdev;
    meanStdDev(roi_frame,avg,stdev);
    std::cout << "avg:" << avg[0] << " : " << stdev[0] << std::endl;
    std::cout << "std" << std::endl;
    Scalar range_min(0.0,0.0,0.0);
    Scalar range_max(180.0,255.0,255.0);
    std::cout << "range" << std::endl;
    for( int i = 0; i < 3; i++ )
    {
        range_min[i] = max( (float)avg[i] - stdev[i], range_min[i] );
        range_max[i] = min( (float)avg[i] + stdev[i], range_max[i] );
        range_min[i] = std::floor(range_min[i] + 0.5);
        range_max[i] = std::floor(range_max[i] + 0.5);
        std::cout << range_min[i] << " -> " << range_max[i] << std::endl;
    }
    mRangeMin = range_min;
    mRangeMax = range_max;
}

