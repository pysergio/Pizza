#include "../include/pizza.h"

int  diviz(int x, int nbr) {
    for (int i = x + 1; i <= nbr; i++) {
        if (nbr % i == 0)
            return (i);
    }
    return (0);
}

bool    ReadingPizzaFile::validation(int x, int y) {
    for (int i = 0; i < list.getSize(); i++) {
        if (list[i].x + list[i].divx >= x && list[i].y + list[i].divy >= y)
            return (false);
    }
    return (true);
}


bool   ReadingPizzaFile::valid(int x, int y, int n, int divl) {
    int sum;

    sum = 0;
    for (int i = x; i < divl + x; i++) {
        for (int j = y; j < n / divl + y; j++) {
            if (validation(i, j) == false) {
                return(false);
            }
            sum += pizzaMatrix[i][j];
        }
    }
    if (sum >= min && sum <= n - min)
        return (true);
    else
        return (false);
}

void   ReadingPizzaFile::backTrack(int x, int y, bool n) {
    int     divl;
    bool    q;
    int     n;

    if (n == true){
        n = min * 2;
        q = true;
        divl = 0;
        Slice   slice;
        slice.x = x;
        slice.y = y;
        while (q) {
            divl = diviz(divl, n);
            if (valid(x, y, divl, n) == true)
                q == false;
            if (n == divl && n < max) {
                n++;
                divl = 0;
            }
			if (n > max)
				backTrack(x, y, n);
        }
        list.push_back(slice);
    }
}

void    ReadingPizzaFile::algorithm() {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (validation(i, j) == true) {
                //introduction section in list...
            }          
        }
    }
}