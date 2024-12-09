#include "common.h"

int main()
{
    char buffer[PACKET_LEN];
    memset(buffer, 0, PACKET_LEN);

    ipheader *ip = (ipheader *)buffer;
    udpheader *udp = (udpheader *)(buffer + sizeof(ipheader));

    // add data
    char *data = (char *)udp + sizeof(udpheader);
    int data_len = strlen(CLIENT_IP);
    strncpy(data, CLIENT_IP, data_len);

    // create udp header

    udp->udp_sport = htons(CLIENT_PORT); 
    udp->udp_dport = htons(SERVER_PORT); 
    udp->udp_ulen = htons(sizeof(udpheader) + data_len); 

    // create ip header

    ip->iph_ver = 4; 
    ip->iph_ihl = sizeof(ipheader) / 4; 
    ip->iph_tos = 0; 
    ip->iph_len = htons(sizeof(ipheader) + sizeof(udpheader) + data_len); 
    ip->iph_ident = htons(rand() % 65536); 
    ip->iph_flag = 0; 
    ip->iph_offset = 0; 
    ip->iph_ttl = 64; 
    ip->iph_protocol = IPPROTO_UDP; 
    ip->iph_chksum = 0; 
    ip->iph_sourceip.s_addr = inet_addr(SPOOF_IP); 
    ip->iph_destip.s_addr = inet_addr(SERVER_IP); 

    // send packet
    send_raw_ip_packet(ip);
    return 0;
}