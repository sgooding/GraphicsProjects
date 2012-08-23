#ifndef _DataPacket_H
#define _DataPacket_H

#include <boost/thread/thread_time.hpp> // for system_time
#include <boost/date_time/posix_time/posix_time.hpp> // for to string

#include <string>

class DataPacket
{
    public:
    DataPacket() : mTimestamp(GetTime()), mPacketID(GetUniqueID())
    {
    }

    std::string GetTimestamp() const { return mTimestamp; }

    private:

    std::string GetTime()
    {
        using namespace boost;
        using namespace boost::posix_time;
        return( to_simple_string(get_system_time()) );
    }

    unsigned int GetUniqueID()
    {
        static int uniqueID(0);
        mMutex.lock();
        uniqueID++;
        mMutex.unlock();
        return uniqueID;
    }

    std::string mTimestamp;
    unsigned int mPacketID;
    boost::mutex mMutex;
 
};

#endif

