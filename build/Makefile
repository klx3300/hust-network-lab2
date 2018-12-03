__fake_main__: sr

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
pktbuffer.o: ../util/pktbuffer.cc ../util/pktbuffer.h
	@echo "   g++   pktbuffer.o"
	@g++ -c -g -std=gnu++14 -o pktbuffer.o ../util/pktbuffer.cc
gbn_send.o: ../goback/Sender.cc ../goback/Sender.h
	@echo "   g++   gbn_send.o"
	@g++ -c -g -std=gnu++14 -o gbn_send.o ../goback/Sender.cc
gbn_recv.o: ../goback/Receiver.cc ../goback/Receiver.h
	@echo "   g++   gbn_recv.o"
	@g++ -c -g -std=gnu++14 -o gbn_recv.o ../goback/Receiver.cc
sr_send.o: ../sr/Sender.cc ../sr/Sender.h
	@echo "   g++   sr_send.o"
	@g++ -c -g -std=gnu++14 -o sr_send.o ../sr/Sender.cc
sr_recv.o: ../sr/Receiver.cc ../sr/Receiver.h
	@echo "   g++   sr_recv.o"
	@g++ -c -g -std=gnu++14 -o sr_recv.o ../sr/Receiver.cc
sw_main.o: ../main.cc
	@echo "   g++   sw_main.o"
	@g++ -c -g -std=gnu++14 -o sw_main.o ../main.cc
gbn: sw_main.o gbn_recv.o gbn_send.o fmt.o util.o ../lib/libnetsim.a 
	@echo "   LD   gbn"
	@g++ -lpthread -no-pie -o gbn sw_main.o gbn_recv.o gbn_send.o fmt.o util.o ../lib/libnetsim.a 
sr: sw_main.o sr_recv.o sr_send.o fmt.o util.o pktbuffer.o ../lib/libnetsim.a 
	@echo "   LD   sr"
	@g++ -lpthread -no-pie -o sr sw_main.o sr_recv.o sr_send.o fmt.o util.o pktbuffer.o ../lib/libnetsim.a 
clean:
	@echo "  CLEAN   all files."
	-@rm sw_recvr.o sw_sendr.o fmt.o util.o pktbuffer.o gbn_send.o gbn_recv.o sr_send.o sr_recv.o sw_main.o gbn sr  2>/dev/null >/dev/null || true
