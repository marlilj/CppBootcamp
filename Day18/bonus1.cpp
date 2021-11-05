#include <iostream>
#include <iomanip>
#include <pcap.h>
#include <net/ethernet.h>

static int packetCount = 0;

void packetHandler(u_char *userData, const struct pcap_pkthdr* pkthdr, const u_char* packet) {
  std::cout << ++packetCount << " packet(s) captured" << std::endl;
}

int main() {
    int dev;
    pcap_t *descr;
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_if_t *alldevsp;

    pcap_t *handle = pcap_open_offline("one_packe_dump.pcap", errbuf);
    struct pcap_pkthdr* header;
    const u_char* packet;
    int result = pcap_next_ex(handle, &header, &packet);

    if (result == PCAP_ERROR_BREAK) {
        std::cout << "Couldn't read file" << std::endl;
    } else {
        const struct ether_header* ethernet_header = reinterpret_cast<const struct ether_header*>(packet);
        std::cout << ethernet_header << std::endl;
        std::cout << "Source MAC: ";
        for (int i = 0; i < ETH_ALEN; ++i) {
            std::cout << std::setfill('0') << std::setw(2) << std::hex << std::uppercase 
                << static_cast<int>(ethernet_header->ether_shost[i]);
            if (i < ETH_ALEN - 1) std::cout << ":";
        }
        std::cout << std::endl;

        std::cout << "Destination MAC: ";
        for (int i = 0; i < ETH_ALEN; ++i) {
            std::cout << std::setfill('0') << std::setw(2) << std::hex << std::uppercase 
                << static_cast<int>(ethernet_header->ether_dhost[i]);
            if (i < ETH_ALEN - 1) std::cout << ":";
        }
        std::cout << std::endl;
    }

    pcap_close(handle);

    // dev = pcap_findalldevs(&alldevsp, errbuf);
    // if (dev == PCAP_ERROR) {
    //     std::cout << "pcap_findalldevs() failed: " << errbuf << std::endl;
    //     return 1;
    // }

    // pcap_if_t *loopPointer = alldevsp;
    // while(loopPointer != NULL) {
    //     std::cout << loopPointer->name << std::endl;
    //     std::cout << loopPointer->description << std::endl;
    //     std::cout << std::endl;
    //     loopPointer = loopPointer->next;
    // }

    // descr = pcap_open_live(alldevsp->name, BUFSIZ, 0, -1, errbuf);
    // if (descr == NULL) {
    //     std::cout << "pcap_open_live() failed: " << errbuf << std::endl;
    //     return 1;
    // }

    // if (pcap_loop(descr, 10, packetHandler, NULL) < 0) {
    //     std::cout << "pcap_loop() failed: " << pcap_geterr(descr);
    //     return 1;
    // }

    // std::cout << "capture finished" << std::endl;

    return 0;
}
