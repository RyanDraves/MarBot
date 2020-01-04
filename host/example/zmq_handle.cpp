#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <vector>

using namespace std;

#include <zmqpp/context.hpp>
#include <zmqpp/socket.hpp>
#include <zmqpp/message.hpp>
#include <zmqpp/reactor.hpp>


#include <signal.h>

static volatile bool interrupted = false;


void my_signal_handler(int){
    cout << "signal" << endl;
    interrupted = true;
}

void producer_task(){

    try{

        zmqpp::context zmq_context;
        zmqpp::socket socket {
            zmq_context,
            zmqpp::socket_type::push
        };
        socket.bind( "tcp://*:4099" );

        int x = 0;

        while( !interrupted ){

            std::this_thread::sleep_for( std::chrono::seconds(1) );

            cout << "Message: " << x << endl;

            zmqpp::message request;
            request << "Message: " + std::to_string(x);
            request << x;
            socket.send(request, true);

            x++;

        }

    }catch( zmqpp::zmq_internal_exception& e ){

        cerr << "Exception: " << e.what() << endl;

    }catch( ... ){

        cerr << "Unknown Exception: " << endl;

    }


}


void consumer_task(){

    try{

        zmqpp::context zmq_context;

        zmqpp::socket socket_1 {
            zmq_context,
            zmqpp::socket_type::pull
        };
        socket_1.connect( "tcp://127.0.0.1:4099" );

        zmqpp::socket socket_2 {
            zmq_context,
            zmqpp::socket_type::pull
        };
        socket_2.connect( "tcp://127.0.0.1:4099" );


        zmqpp::reactor reactor;

        auto first_listener = [&socket_1](){
            zmqpp::message response;
            socket_1.receive(response, true);
            cout << "first_listener: " << response.get(0) << endl;
        };

        auto second_listener = [&socket_2](){
            zmqpp::message response;
            socket_2.receive(response, true);
            cout << "second_listener: " << response.get(0) << endl;
        };

        reactor.add( socket_1, first_listener );
        reactor.add( socket_2, second_listener );

        while(!interrupted){
            reactor.poll(1000);
        }

        //interrupted
        cout << "interrupted" << endl;

    }catch( zmqpp::zmq_internal_exception& e ){

        cerr << "Exception: " << e.what() << endl;

    }catch( ... ){

        cerr << "Unknown Exception: " << endl;

    }

}

void usage(){

    cout << "usage: test [producer|consumer]" << endl;

}



int main( int argc, char** argv ){

    signal(SIGINT, my_signal_handler);

    string task;

    vector<string> arguments;
    if( argc > 1 ){
        int count = 0;
        while( count < argc ){          
            if( count == 1 ) task = string(argv[1]);
            arguments.push_back( argv[count] );
            count++;
        }
    }else{
        usage();
        return 0;
    }


    if( task == "producer" ){
        std::thread producer_thread( producer_task );
        producer_thread.join();
    }else if( task == "consumer" ){
        std::thread consumer_thread( consumer_task );
        consumer_thread.join();
    }else{
        usage();
        return 0;
    }

    return 0;

}