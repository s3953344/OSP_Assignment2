
##
 # startup code provided by Paul Miller for COSC1114 - Operating Systems
 # Principles
 ##

# provide make targets here to build the two programs

# makefile structure:
# targets (file to make): prerequisites	//needs to exist for commands to work
# 	command
# 	command
# 	etc...

.default: all

all: fifo sjf rr
 
clean:
	rm -rf ppd *.o *.dSYM;
	cd fifo_files && $(MAKE) clean;
	cd sjf_files && $(MAKE) clean;
	# cd ../round_robin && $(MAKE) clean;
	# cd ../;
	rm -f fifo;

fifo: ./fifo_files/main.o pcb.o processor.o schedules.o
	cd fifo_files && $(MAKE)

sjf: ./sjf_files/main.o pcb.o processor.o schedules.o
	cd sjf_files && $(MAKE)

