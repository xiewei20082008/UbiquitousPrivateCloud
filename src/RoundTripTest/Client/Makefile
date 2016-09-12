Client: RoundTripClient.o MainClient.o
	g++ -o Client RoundTripClient.o MainClient.o

MainClient.o: MainClient.cc ../DefaultValue.h
	g++ -c MainClient.cc

RoundTripClient.o: RoundTripClient.h RoundTripClient.cc ../DefaultValue.h
	g++ -c RoundTripClient.cc

clean:
	rm *.o Client
	