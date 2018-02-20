/** @file my_pcap_capture.c
 * Implements libpcap to either loop through a pcap file or capture packets on an interface. Non-promiscous mode is used. 
 * 
 * Usage:
 * my_pcap_capture file <filepath>
 * my_pcap_capture live <interface>
 * Ctrl-C to interrupt.
 * 
 */


#include <stdio.h>
#include <signal.h>
#include <pcap.h>
#include <string.h>

#include "options_processor.h"
#include "err_processor.h"


static struct s_options v_options; /**< Contains option parameters tat configure the application. */
static unsigned int v_total_packets = 0; /**< Counter for number of packets processed. */
static pcap_t *v_pcap_handler = NULL; /**< libpcap handler. */
static char v_pcap_err_buf[PCAP_ERRBUF_SIZE]; /**< libpcap error buffer. */


/** Catches interrupt and prepares application exit.
 * @param p_signal signal caught.
 */
static void handle_interrupt(int p_signal);

/** Loops through a pcap file.
 */
static void process_file();

/** Captures packets on an interface.
 */
static void interface_capture();

/** Event handler for pcap_loop, called when processing a packet.
 * @param p_user Pointer to user-defined address.
 * @param p_hdr Contains libpcap packet header data.
 * @param p_data Contains packet payload.
 */
static void process_packet(u_char *p_user, const struct pcap_pkthdr *p_hdr, const u_char *p_data);



int main(int argc, char *argv[])
{
	signal(SIGINT, handle_interrupt); /* Register signal handler. */
	
	if(process_params(argc, argv, &v_options) == -1) {/* Process command-line params. Options are written into v_options. */
		fprintf(stderr, get_err_msg());
		return -1;
	}

	if(v_options.capture_type == FILE_CAPTURE) /* */
		process_file();
	else
		interface_capture();
	
	printf("No. of packets: %u\n", v_total_packets);
	return 0;
}



/** Use libpcap to open a pcap file and loop though the packets.
 */
static void process_file()
{
	if((v_pcap_handler = pcap_open_offline(v_options.target, v_pcap_err_buf)) == NULL) {
		fprintf(stderr, "%s\n", v_pcap_err_buf);
		return;
	}

	pcap_loop(v_pcap_handler, 0, process_packet, NULL);
	pcap_close(v_pcap_handler);
}



/** Use libpcap to listen on an interface and loop though the packets.
 */
static void interface_capture()
{
	/* This is an endless loop. So requires an interrupt handler to stop the capture. */
	if((v_pcap_handler = pcap_open_live(v_options.target, 65535, 0, 1000, v_pcap_err_buf)) == NULL) {
		fprintf(stderr, "%s\n", v_pcap_err_buf);
		return;
	}

	pcap_loop(v_pcap_handler, 0, process_packet, NULL);
	pcap_close(v_pcap_handler);	
}



/** Process each packet read by libpcap. Implements libpcap's pcap_handler.
 * @param p_user Pointer to pcap_loop() that implemented this handler.
 * @param p_hdr Pointer to packet timestamps and lengths.
 * @param p_data First bytes of data in the packet.
 */
static void process_packet(u_char *p_user, const struct pcap_pkthdr *p_hdr, const u_char *p_data)
{
	++v_total_packets;
}



/** Implements interrupt handler to catch Ctrl-C.
 *  @param p_option The caught signal.
 */
static void handle_interrupt(int p_option)
{
	if(v_pcap_handler != NULL) {
		fprintf(stderr, "Caught interrupt. Exit.\n");
		pcap_breakloop(v_pcap_handler);
	}
}