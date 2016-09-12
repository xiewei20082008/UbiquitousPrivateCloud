Server:	RoundTripServer.o MainServer.o
	g++ -o Server RoundTripServer.o MainServer.o

MainServer.o: MainServer.cc ../DefaultValue.h
	g++ -c MainServer.cc

RoundTripServer.o: RoundTripServer.h RoundTripServer.cc ../DefaultValue.h
	g++ -c RoundTripServer.cc

clean:
	rm *.o server
