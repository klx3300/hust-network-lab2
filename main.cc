

#include "simu/Base.h"
#include "simu/Global.h"
#include "simu/RdtSender.h"
#include "simu/RdtReceiver.h"
#include "stopwait/StopWaitRdtSender.h"
#include "stopwait/StopWaitRdtReceiver.h"


int main(int argc, char* argv[])
{
	RdtSender *ps = new StopWaitRdtSender();
	RdtReceiver * pr = new StopWaitRdtReceiver();
	pns->init();
	pns->setRtdSender(ps);
	pns->setRtdReceiver(pr);
	pns->setInputFile("input.txt");
	pns->setOutputFile("output.txt");
	pns->start();

	delete ps;
	delete pr;
	delete pUtils;
	delete pns;
	
	return 0;
}

