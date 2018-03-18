# Kamil Breczko (280 990)

CXXFLAGS = -std=c++11 -Werror -Wall
CXX = g++

traceroute : traceroute.o receiver.o utils.o sender.o packet.h
	$(CXX) $(CXXFLAGS) -o traceroute traceroute.o receiver.o utils.o sender.o 

traceroute.o : traceroute.cpp receiver.o utils.o sender.o
	$(CXX) -c $(CXXFLAGS) traceroute.cpp -o  traceroute.o

receiver.o : receiver.cpp receiver.h sender.o packet.h
	$(CXX) -c $(CXXFLAGS) receiver.cpp -o receiver.o

sender.o : sender.cpp sender.h
	$(CXX) -c $(CXXFLAGS) sender.cpp -o sender.o

utils.o : utils.cpp utils.h packet.h
	$(CXX) -c $(CXXFLAGS) utils.cpp -o utils.o

clean:
	rm -rf *.o

distclean:
	rm -rf *.o traceroute .*.swp