
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
	cd fifo_files && $(MAKE) clean;
	# cd ../sjf && $(MAKE) clean;
	# cd ../round_robin && $(MAKE) clean;
	cd ../;
	rm fifo;

fifo: ./fifo_files/main.o pcb.o processor.o
	cd fifo_files && $(MAKE)

