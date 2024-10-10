#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/ether.h>
#include "common.h"

// MAC address of the microcontroller (same format as Wireshark)
#define TARGET_MAC "00:80:e1:00:00:00"
 bool packet_captured = false;

// Function to handle each captured packet
void packet_handler(u_char *user, const struct pcap_pkthdr *header, const u_char *packet) {
    struct ether_header *eth_header;

    // Parse Ethernet header
    eth_header = (struct ether_header *)packet;

    // Convert MAC address to human-readable form
    char src_mac[18];
    char dst_mac[18];
    snprintf(src_mac, sizeof(src_mac), "%02x:%02x:%02x:%02x:%02x:%02x",
             eth_header->ether_shost[0], eth_header->ether_shost[1], eth_header->ether_shost[2],
             eth_header->ether_shost[3], eth_header->ether_shost[4], eth_header->ether_shost[5]);

    snprintf(dst_mac, sizeof(dst_mac), "%02x:%02x:%02x:%02x:%02x:%02x",
             eth_header->ether_dhost[0], eth_header->ether_dhost[1], eth_header->ether_dhost[2],
             eth_header->ether_dhost[3], eth_header->ether_dhost[4], eth_header->ether_dhost[5]);

    // Check if the packet source or destination MAC matches the target MAC address
    if (strcmp(src_mac, TARGET_MAC) == 0 || strcmp(dst_mac, TARGET_MAC) == 0) {
        int col = TOTAL_FLOATS + 3;
        mvwprintw(windows[0], col++, 1, "Packet captured:\n");
        mvwprintw(windows[0], col++, 1,"Source MAC: %s\n", src_mac);
        mvwprintw(windows[0], col++, 1,"Destination MAC: %s\n", dst_mac);
        mvwprintw(windows[0], col++, 1,"Packet length: %d bytes\n", header->len);
        mvwprintw(windows[0], col++, 1, "Timestamp: %ld.%06ld\n", header->ts.tv_sec, header->ts.tv_usec);
        mvwprintw(windows[0], col++, 1, "----\n");
        wrefresh(windows[0]);   
    }

    packet_to_float(packet);
    
}

// Function to start packet capture
void get_packet() {
    pcap_t *handle;
    char errbuf[PCAP_ERRBUF_SIZE];
    struct bpf_program fp;
    char filter_exp[64];

    // Define filter to match packets involving the microcontroller MAC address
    snprintf(filter_exp, sizeof(filter_exp), "ether host %s", TARGET_MAC);

    // Open the default network device for packet capture
    char *dev = pcap_lookupdev(errbuf);
    if (dev == NULL) {
        fprintf(stderr, "Could not find default device: %s\n", errbuf);
        return;
    }

    //printf("Using device: %s\n", dev);

    // Open device for live capture
    handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "Could not open device %s: %s\n", dev, errbuf);
        return;
    }

    // Compile and apply the BPF filter
    if (pcap_compile(handle, &fp, filter_exp, 0, PCAP_NETMASK_UNKNOWN) == -1) {
        fprintf(stderr, "Could not parse filter %s: %s\n", filter_exp, pcap_geterr(handle));
        return;
    }
    if (pcap_setfilter(handle, &fp) == -1) {
        fprintf(stderr, "Could not install filter %s: %s\n", filter_exp, pcap_geterr(handle));
        return;
    }

    // Capture packets using pcap_loop
     // The '1' captures only one packet for demonstration purposes
    
     int count = 0;
     while (!packet_captured) {
        int ret = pcap_loop(handle, 1, packet_handler, NULL);
        count++;
        if (ret < 0) {
            // If ret is negative, it indicates an error or the loop was explicitly broken
            fprintf(stderr, "Error capturing packet: %s\n", pcap_geterr(handle));
            break;
        }
        packet_captured = true;
    }
    
    // Close the capture device and free resources
    pcap_freecode(&fp);
    pcap_close(handle);
}

void packet_to_float(const u_char *packet) {
    if(packet == NULL) {
        printf("error, packet is NULL\n");
        return;
    }
    float *dest_ptr = float_array;  // Pointer to float array's first element
    const uint8_t *src_ptr = packet; // Pointer to pkt92 array's first element

    // Iterate over the total number of floats
    for (int i = 0; i < TOTAL_FLOATS; i++) {
        // Copy 4 bytes from pkt92 (source) to float_array (destination)
        memcpy(dest_ptr, src_ptr, sizeof(float));

        // Move to the next float in destination
        dest_ptr++;

        // Move 4 bytes ahead in source
        src_ptr += sizeof(float);
    }
}
