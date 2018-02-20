CC = gcc
OPT = -O2 -Wall
LIB = -lpcap

all: my_pcap_capture

my_pcap_capture: my_pcap_capture.c options_processor.o err_processor.o
	$(CC) $(OPT) -o my_pcap_capture my_pcap_capture.c *.o $(LIB)

options_processor.o: options_processor.c options_processor.h
	$(CC) $(OPT) options_processor.c -c

error_processor.o: err_processor.c err_processor.h
	$(CC) $(OPT) err_processor.c -c

clean:
	rm -rf my_pcap_capture
	rm -rf *.o