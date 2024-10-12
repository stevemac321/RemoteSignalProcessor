
#include "common.h"

// Conversion factor for 12-bit ADC with 3.3V reference voltage
#define ADC_REF_VOLTAGE 3.3f
#define ADC_RESOLUTION 4096.0f

// MAC address of the microcontroller (same format as Wireshark)
#define TARGET_MAC "00:80:e1:00:00:00"

bool packet_captured = false;
uint8_t packet_array[PACKET_LENGTH];
float float_array[TOTAL_FLOATS];  // Array to hold the 32 floats

// Function to handle each captured packet
void packet_handler(u_char *user, const struct pcap_pkthdr *header, const u_char *packet) 
{
    (void)user;
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
        mvwprintw(windows[0], 4, 1, "Source MAC: %s | Destination MAC: %s | Packet length: %d bytes | Timestamp: %ld.%06ld",
            src_mac, dst_mac, header->len, header->ts.tv_sec, header->ts.tv_usec);
        wrefresh(windows[0]);
    }
    save_packet(packet);
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

    struct pcap_if *alldevs, *dev;
    if (pcap_findalldevs(&alldevs, errbuf) == -1) {
        fprintf(stderr, "Could not find devices: %s\n", errbuf);
        return;
    }
    if (alldevs == NULL) {
        fprintf(stderr, "No devices found.\n");
        return;
    }
    dev = alldevs;

    // Open device for live capture
    handle = pcap_open_live(dev->name, BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "Could not open device %s: %s\n", dev->name, errbuf);
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
    
     while (!packet_captured) {
        int ret = pcap_loop(handle, 1, packet_handler, NULL);
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
    pcap_freealldevs(alldevs);
}
/*
Conversion Formula:

The raw ADC values are converted to voltage using the formula:
Voltage = (Raw ADC Value / 4096) × 3.3
This converts the 0-4095 ADC range to a corresponding 0-3.3V range.
Additional Conversion Step:
*/
void packet_to_float(const u_char *packet) 
{
    if(packet == NULL) {
        printf("error, packet is NULL\n");
        return;
    }
    float *dest_ptr = float_array;  // Pointer to float array's first element
    const uint8_t *src_ptr = packet; // Pointer to packet array's first element

    // Iterate over the total number of floats
    for (int i = 0; i < TOTAL_FLOATS; i++) {
        // Copy 4 bytes from packet (source) to float_array (destination)
        memcpy(dest_ptr, src_ptr, sizeof(float));

        // Convert the raw ADC value to voltage:
        *dest_ptr = (*dest_ptr / ADC_RESOLUTION) * ADC_REF_VOLTAGE;

        // Move to the next float in destination
        dest_ptr++;

        // Move 4 bytes ahead in source
        src_ptr += sizeof(float);
    }
}
void save_packet(const u_char *packet) 
{
    for(int i=0; i < PACKET_LENGTH; i++) {
        packet_array[i] = packet[i];
    }
}
