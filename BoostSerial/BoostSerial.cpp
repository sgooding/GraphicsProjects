
#include <boost/asio.hpp>
#include <iostream>

using namespace::boost::asio;
using namespace std;

int main()
{
    serial_port_base::baud_rate BAUD(115200);
    io_service io;

    const char* PORT = "/dev/ttyUSB0";
    serial_port port(io,PORT);

    port.set_option(BAUD);

    if(!port.is_open())
    {
        cout << "Port NOT open" << endl;
        return EXIT_FAILURE;
    }

    unsigned char input = 0;
    while( input != 'q' )
    {
        std::cout << "Send Key: ";
        std::cin >> input;
    }

    return EXIT_SUCCESS;
}
