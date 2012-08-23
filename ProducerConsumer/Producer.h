#ifndef Producer_H_
#define Producer_H_

#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread_time.hpp> // for system_time
#include <boost/date_time/posix_time/posix_time.hpp> // for to string
#include <boost/shared_ptr.hpp>
#include "DataPacket.h"

class Producer
{
    public:

    Producer():mProducerThread(&Producer::ProduceDataThread,this), mNewData(false)
    {

    }

    void GetData( boost::shared_ptr<DataPacket>& data, bool& newData )
    {
        mMutex.lock();
        newData = mNewData;
        data = mData;
        mData.reset();
        mNewData = false;
        mMutex.unlock();
    }

    private:

    void ProduceDataThread() : mNewData(false)
    {

        static int counter = 0;
        while(1)
        {
            // read data
            counter++;

            mMutex.lock();
            mData.reset(new DataPacket());
            mNewData = true;
            mMutex.unlock();

            usleep(2e3);
        }
    }

    boost::thread mProducerThread;
    boost::mutex mMutex;

    boost::shared_ptr<DataPacket> mData;
    bool mNewData;

};


#endif
