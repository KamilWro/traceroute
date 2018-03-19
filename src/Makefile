# Kamil Breczko (280 990)

CXXFLAGS = -std=c++11 -Werror -Wall -Wextra

CXX = g++

main : packet.h main.o traceroute.o receiver_icmp.o sender_icmp.o
	$(CXX) $(CXXFLAGS) -o traceroute main.o traceroute.o receiver_icmp.o sender_icmp.o

main.o : main.cpp traceroute.o
	$(CXX) -c $(CXXFLAGS) main.cpp -o  main.o

traceroute.o : traceroute.h traceroute.cpp receiver_icmp.o sender_icmp.o
	$(CXX) -c $(CXXFLAGS) traceroute.cpp -o traceroute.o

receiver_icmp.o : receiver_icmp.cpp receiver_icmp.h receiver.h packet.h
	$(CXX) -c $(CXXFLAGS) receiver_icmp.cpp -o receiver_icmp.o

sender_icmp.o : sender_icmp.cpp sender_icmp.h sender.h
	$(CXX) -c $(CXXFLAGS) sender_icmp.cpp -o sender_icmp.o

clean:
	rm -rf *.o

distclean:
	rm -rf *.o traceroute .*.swp