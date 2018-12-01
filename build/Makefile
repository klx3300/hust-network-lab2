__fake_main__: gbn

sw_recvr.o: ../stopwait/StopWaitRdtReceiver.cc ../stopwait/StopWaitRdtReceiver.h
	@echo "   g++   sw_recvr.o"
	@g++ -c -g -std=gnu++14 -o sw_recvr.o ../stopwait/StopWaitRdtReceiver.cc
sw_sendr.o: ../stopwait/StopWaitRdtSender.cc ../stopwait/StopWaitRdtSender.h
	@echo "   g++   sw_sendr.o"
	@g++ -c -g -std=gnu++14 -o sw_sendr.o ../stopwait/StopWaitRdtSender.cc
fmt.o: ../format/format.cc ../format/format.h
	@echo "   g++   fmt.o"
	@g++ -c -g -std=gnu++14 -o fmt.o ../format/format.cc
util.o: ../util/util.cc ../util/util.h
	@echo "   g++   util.o"
	@g++ -c -g -std=gnu++14 -o util.o ../util/util.cc
gbn_send.o: ../goback/Sender.cc ../goback/Sender.h
	@echo "   g++   gbn_send.o"
	@g++ -c -g -std=gnu++14 -o gbn_send.o ../goback/Sender.cc
gbn_recv.o: ../goback/Receiver.cc ../goback/Receiver.h
	@echo "   g++   gbn_recv.o"
	@g++ -c -g -std=gnu++14 -o gbn_recv.o ../goback/Receiver.cc
sw_main.o: ../main.cc
	@echo "   g++   sw_main.o"
	@g++ -c -g -std=gnu++14 -o sw_main.o ../main.cc
gbn: sw_main.o gbn_recv.o gbn_send.o fmt.o util.o ../lib/libnetsim.a 
	@echo "   LD   gbn"
	@g++ -lpthread -no-pie -o gbn sw_main.o gbn_recv.o gbn_send.o fmt.o util.o ../lib/libnetsim.a 
clean:
	@echo "  CLEAN   all files."
	-@rm sw_recvr.o sw_sendr.o fmt.o util.o gbn_send.o gbn_recv.o sw_main.o gbn  2>/dev/null >/dev/null || true
