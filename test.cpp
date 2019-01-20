#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <cstring>
#include <ctime>

using namespace std;

int  diviz(int nbr)
{
    int tot;

    tot = 0;
    for (int i = 1; i <= nbr; i++) {
        if (nbr % i == 0)
            tot++;
    }
    return (tot);
}


main(int argc, char const *argv[])
{
    //int min, max;
    int    sum;
    int    *array;
    clock_t start;
    double duration;
    double duration1;

    sum = 0;
    start = clock();
    for (int i = 6; i <= 1000; i++)
        sum += diviz(i);
    duration = (clock() - start);
    cout << duration << "calculare" << endl;
    
    array = new int[sum];
    for (int i = 0; i < sum; i++){
        array[i] = i;
    }

duration = 0;
    int aux;
    clock_t start1 = clock();
    for (int i = 0; i <= sum; i++)
        aux = array[i];
    duration1 = (clock() - start1);
    cout << duration1 << "citire" << endl;
    return 0;
}
