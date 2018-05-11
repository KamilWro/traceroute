# Kamil Breczko (280 990)

CXXFLAGS = -std=c++11 -Werror -Wall -Wextra

CXX = g++

main : Packet.h main.o Traceroute.o Receiver.o Sender.o
	$(CXX) $(CXXFLAGS) -o traceroute main.o Traceroute.o Receiver.o Sender.o

main.o : main.cpp Traceroute.o
	$(CXX) -c $(CXXFLAGS) main.cpp -o  main.o

Traceroute.o : Traceroute.h Traceroute.cpp Receiver.o Sender.o
	$(CXX) -c $(CXXFLAGS) Traceroute.cpp -o Traceroute.o

Receiver.o : Receiver.cpp Receiver.h Packet.h
	$(CXX) -c $(CXXFLAGS) Receiver.cpp -o Receiver.o

Sender.o : Sender.cpp Sender.h
	$(CXX) -c $(CXXFLAGS) Sender.cpp -o Sender.o

clean:
	rm -rf *.o

distclean:
	rm -rf *.o traceroute .*.swp