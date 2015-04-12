CFLAGS = -O2 -Wall
CPPFLAGS = -O2 -std=c++11 -Wall

%: %.c
	gcc $(CFLAGS) $< -o $@

%: %.cpp
	g++ $(CPPFLAGS) $< -o $@

