__fake_main__: stopwait

sw_recvr.o: ../stopwait/StopWaitRdtReceiver.cc ../stopwait/StopWaitRdtReceiver.h
	@echo "   g++   sw_recvr.o"
	@g++ -c -g -std=gnu++14 -o sw_recvr.o ../stopwait/StopWaitRdtReceiver.cc
sw_sendr.o: ../stopwait/StopWaitRdtSender.cc ../stopwait/StopWaitRdtSender.h
	@echo "   g++   sw_sendr.o"
	@g++ -c -g -std=gnu++14 -o sw_sendr.o ../stopwait/StopWaitRdtSender.cc
sw_main.o: ../main.cc
	@echo "   g++   sw_main.o"
	@g++ -c -g -std=gnu++14 -o sw_main.o ../main.cc
stopwait: sw_main.o sw_recvr.o sw_sendr.o ../lib/libnetsim.a 
	@echo "   LD   stopwait"
	@g++ -lpthread -no-pie -o stopwait sw_main.o sw_recvr.o sw_sendr.o ../lib/libnetsim.a 
clean:
	@echo "  CLEAN   all files."
	-@rm sw_recvr.o sw_sendr.o sw_main.o stopwait  2>/dev/null >/dev/null || true
