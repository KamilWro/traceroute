# traceroute

Program traceroute, wyświetla adresy IP routerów na ścieżce do docelowego adresu IP. Program działa w trybie 
tekstowym i jego jedynym argumentem jest adres IP komputera docelowego. Program wysyła pakiety ICMP echo request
o coraz większych wartościach TTL (podobnie jak robi to wywołanie traceroute -I). 

Dla każdej wartości TTL z [1,30] program wykonuje następujące operacje:
 - [x] wysyła 3 pakiety ICMP echo  request z ustalonym TTL (jeden za drugim, bez czekania na odpowiedź).
 - [x] odbiera z gniazda odpowiedzi na te pakiety, ale nie czeka na ich nadejście dłużej niż sekundę.
 - [x] wyświeta  adres  IP  routera,  od  którego  nadejdą  komunikaty  i  średni  czas  odpowiedzi w milisekundach. 
      - W przypadku braku odpowiedzi od jakiegokolwiek routera wyświetla "*". 
      - W  przypadku  odpowiedzi  od  więcej  niż  jednego  routera wyświetla wszystkie adesy ip. 
      - W przypadku nieotrzymania trzech odpowiedzi w ustalonym czasie zamiast średniego czasu odpowiedzi wyświetla "???".

#### Przykład użycia:

`sudo ./traceroute 8.8.8.8`

Program wymaga uprawnień administratora ze względu na wykorzystanie gniazd surowych.
