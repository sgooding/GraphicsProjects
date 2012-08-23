
#include <iostream>
#include <stdlib.h>

#include "Producer.h"
#include "Consumer.h"

int main(int argn, char* argv[])
{
    Producer producer;

    while(1)
    {
        bool newData;
        boost::shared_ptr<DataPacket> data;
        producer.GetData(data,newData);
        if( !newData )
        {
            std::cout << "Producer: " <<(newData?"NEW":"OLD") << " " << std::setw(10) << std::setfill('0') << data->GetTimestamp() << std::endl; 
        }
        usleep(1e3);
    }

    return EXIT_SUCCESS;
}
