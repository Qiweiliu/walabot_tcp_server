#include "WalabotAPI.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include "SensorSampleCode.h"
#include <fstream>
#include<time.h>
#include "walabot.h"
using namespace std;

//#define CHECK_WALABOT_RESULT(result, func_name)					\
//{																\
//	if (result != WALABOT_SUCCESS)								\
//	{															\
//		unsigned int extended = Walabot_GetExtendedError();		\
//		const char* errorStr = Walabot_GetErrorString();		\
//		std::cout << std::endl << "Error at " __FILE__ << ":"	\
//                  << std::dec << __LINE__ << " - "				\
//				  << func_name << " result is 0x" << std::hex	\
//                  << result << std::endl;						\
//																\
//		std::cout << "Error string: " << errorStr << std::endl; \
//																\
//		std::cout << "Extended error: 0x" << std::hex			\
//                  << extended << std::endl << std::endl;		\
//																\
//		std::cout << "Press enter to continue ...";				\
//		std::string dummy;										\
//		std::getline(std::cin, dummy);							\
//		return;													\
//	}															\
//}

WALABOT_RESULT res;
double* signal;
double* timeAxis;
int numSamples;

double* SensorCode_SampleCode()
{
	// --------------------
	// Variable definitions
	// --------------------

	APP_STATUS appStatus;
	double calibrationProcess;
	bool mtiMode = true;

	res = Walabot_GetStatus(&appStatus, &calibrationProcess);
	if (res != 0) {
	
		res = Walabot_SetSettingsFolder("C:/ProgramData/Walabot/WalabotSDK");
		//CHECK_WALABOT_RESULT(res, "Walabot_SetSettingsFolder");

		res = Walabot_ConnectAny();
		//CHECK_WALABOT_RESULT(res, "Walabot_ConnectAny");

		res = Walabot_SetProfile(PROF_SENSOR);
		//CHECK_WALABOT_RESULT(res, "Walabot_SetProfile");

		int numPairs = 0;
		AntennaPair* AntennaPair;
		res = Walabot_GetAntennaPairs(&AntennaPair, &numPairs);
		//CHECK_WALABOT_RESULT(res, "Walabot_GetAntennaPairs");
		double start = 0;
		double end = 0;
		double ress = 0;
		Walabot_GetArenaR(&start, &end, &ress);

		Walabot_Start();
		//CHECK_WALABOT_RESULT(res, "Walabot_Start");
	}
		
	res = Walabot_GetStatus(&appStatus, &calibrationProcess);
	//CHECK_WALABOT_RESULT(res, "Walabot_GetStatus");

	res = Walabot_Trigger();
	//CHECK_WALABOT_RESULT(res, "Walabot_Trigger");

	Walabot_GetSignal(1, 18, &signal, &timeAxis, &numSamples);

	double* signals = new double[numSamples+1];
	signals[0] = numSamples;
	for (int i = 1; i < numSamples+1; i++) {
		signals[i] = signal[i];
	}	
		return signals;
}

void disconnect() {
	res = Walabot_Stop();
	//CHECK_WALABOT_RESULT(res, "Walabot_Stop");
	res = Walabot_Disconnect();
	//CHECK_WALABOT_RESULT(res, "Walabot_Disconnect");
}