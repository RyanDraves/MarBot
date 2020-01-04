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
    Tins::SnifferConfiguration config;
    config.set_filter("port 4099");
    config.set_promisc_mode(true);
    config.set_snap_len(400);
    Tins::Sniffer("wlan0", config).sniff_loop(callback);
}