proj4.x : bet.cpp bet.h
        g++ -std=c++11 bet.cpp proj4_driver.cpp -o proj4.x

clean :
        rm -f *.o *.x core.*
