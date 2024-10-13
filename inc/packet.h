#ifndef PACKET_H
#define PACKET_H

#include <ncurses.h>
#include <pcap.h>
#include <arpa/inet.h>
#include <netinet/ether.h>
#include <cstring>

extern WINDOW *windows[];

void packet_handler(u_char *user, const struct pcap_pkthdr *header, const u_char *packet);
void get_packet() ;
void packet_to_float(const u_char *packet);
void save_packet(const u_char *packet);

#endif