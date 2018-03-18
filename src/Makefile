# Kamil Breczko (280 990)

CXXFLAGS = -std=c++11 -Werror -Wall
CXX = g++

main : packet.h main.o traceroute.o receiver.o sender.o
	$(CXX) $(CXXFLAGS) -o traceroute main.o traceroute.o receiver.o sender.o

main.o : main.cpp traceroute.o
	$(CXX) -c $(CXXFLAGS) main.cpp -o  main.o

traceroute.o : traceroute.h traceroute.cpp packet.h receiver.o sender.o
	$(CXX) -c $(CXXFLAGS) traceroute.cpp -o traceroute.o

receiver.o : receiver.cpp receiver.h packet.h
	$(CXX) -c $(CXXFLAGS) receiver.cpp -o receiver.o

sender.o : sender.cpp sender.h
	$(CXX) -c $(CXXFLAGS) sender.cpp -o sender.o

clean:
	rm -rf *.o

distclean:
	rm -rf *.o traceroute .*.swp