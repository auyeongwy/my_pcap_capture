CC = gcc
OPT = -O2 -Wall
LIB = -lpcap

all: my_pcap_capture

my_pcap_capture: my_pcap_capture.c options_processor.o mpc_output.o
	$(CC) $(OPT) -o my_pcap_capture my_pcap_capture.c *.o $(LIB)

options_processor.o: options_processor.c options_processor.h
	$(CC) $(OPT) options_processor.c -c

mpc_output.o: mpc_output.c mpc_output.h
	$(CC) $(OPT) mpc_output.c -c

clean:
	rm -rf my_pcap_capture
	rm -rf *.o