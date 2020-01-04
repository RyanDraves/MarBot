#include "../src/ip_sniffer.h"

bool callback(const Tins::PDU &pdu) {
    // Find the IP layer
    const Tins::IP &ip = pdu.rfind_pdu<Tins::IP>(); 
    // Find the TCP layer
    const Tins::TCP &tcp = pdu.rfind_pdu<Tins::TCP>(); 
    std::cerr << ip.src_addr() << ':' << tcp.sport() << " -> " 
         << ip.dst_addr() << ':' << tcp.dport() << std::endl;
    return true;
}

int main(int argc, char **argv) {
    Tins::Sniffer("wifi0").sniff_loop(callback);
}