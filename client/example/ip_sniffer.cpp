#include "../src/ip_sniffer.h"

using namespace Tins;
using namespace std;


bool callback(const Tins::PDU &pdu) {
    // cerr << "\n";
    // Find the IP layer
    const Tins::IP &ip = pdu.rfind_pdu<Tins::IP>();
    // Find the TCP layer
    const Tins::TCP &tcp = pdu.rfind_pdu<Tins::TCP>();
    if (tcp.sport() != 22 && tcp.dport() != 22) {
        std::cout << ip.src_addr() << ':' << tcp.sport() << " -> "
            << ip.dst_addr() << ':' << tcp.dport() << "\n";
    }
    return true;
}
/*
int main(int argc, char **argv) {
    Tins::SnifferConfiguration config;
    config.set_filter("ip 192.168.1.143");
    config.set_promisc_mode(true);
//    config.set_snap_len(400);
    Tins::Sniffer("wlan0").sniff_loop(callback);
}*/
bool doo(PDU &some_pdu) {
    // Search for it. If there is no IP PDU in the packet,
    // the loop goes on
    const IP &ip = some_pdu.rfind_pdu<IP>(); // non-const works as well
    std::cout << "Destination address: " << ip.dst_addr() << std::endl;
    // Just one packet please
    return false;
}

int main() {
    NetworkInterface iface = NetworkInterface::default_interface();
    SnifferConfiguration config;
    config.set_immediate_mode(true);
    config.set_promisc_mode(true);
    config.set_filter("portrange 0-65535");
    cerr << iface.name() << endl;
    Sniffer sniffer(iface.name(), config);
    sniffer.sniff_loop(callback);
}

/*#include <tins/tcp_ip/stream_follower.h>

using Tins::TCPIP::Stream;
using Tins::TCPIP::StreamFollower;

// New stream is seen
void on_new_stream(Stream& stream) {
	cerr << "new stream\n";
}

// A stream was terminated. The second argument is the reason why it was terminated
void on_stream_terminated(Stream& stream, StreamFollower::TerminationReason reason) {
	cerr << "terminated stream\n";
}

int main() {
// Create our follower
Tins::TCPIP::StreamFollower follower;

// Set the callback for new streams. Note that this is a std::function, so you
// could use std::bind and use a member function for this
follower.new_stream_callback(&on_new_stream);

// Now set up the termination callback. This will be called whenever a stream is 
// stopped being followed for some of the reasons explained above
follower.stream_termination_callback(&on_stream_terminated);

NetworkInterface iface = NetworkInterface::default_interface();
SnifferConfiguration config;
config.set_immediate_mode(true);
config.set_promisc_mode(true);
config.set_filter("ip src 192.168.1.143");
cerr << iface.name() << endl;
Sniffer sniffer(iface.name(), config);

// And start sniffing, forwarding all packets to our follower
sniffer.sniff_loop([&](PDU& pdu) {
    cerr << "wtf\n";
    follower.process_packet(pdu);
    return true;
});
return 0;
}*/

