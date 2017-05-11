CC = g++
PARA = -O3 -Wall -c -fmessage-length=0
HEAD = $(CC) $(PARA)
SOURCE = ./src/source/
LIBS = -lpthread

all: $(SOURCE)TemperatureGuardian.cpp
	$(HEAD) $(SOURCE)SPIConnectionHandler.cpp

	$(HEAD) $(SOURCE)SPIDataHandler.cpp

	$(HEAD) $(SOURCE)SensorHandler.cpp

	$(HEAD) $(SOURCE)Controller.cpp

	$(HEAD) $(SOURCE)RawDigitalValueServer.cpp

	$(HEAD) $(SOURCE)SensorWatchDog.cpp

	$(HEAD) $(SOURCE)TemperatureGuardian.cpp

	$(HEAD) $(SOURCE)XMLHandler.cpp

	$(HEAD) $(SOURCE)pugixml.cpp 

	$(HEAD) $(SOURCE)EMailSender.cpp

	$(HEAD) $(SOURCE)LogMsgWriter.cpp

	g++ -o TemperatureGuardian SensorHandler.o SPIConnectionHandler.o SPIDataHandler.o Controller.o RawDigitalValueServer.o SensorWatchDog.o TemperatureGuardian.o pugixml.o XMLHandler.o EMailSender.o LogMsgWriter $(LIBS)

#rm *.o

clean:
	rm *o TemperatureGuardian
