# hash code Pizza
###### Practice Problem for Hash Code

This is the solutin for the Practice Round in Google Hash Code 2019 developed by the team Academy+MD.
The problem statement is in the file "[pizza.pdf](/pizza.pdf)".

**1. Compile project**
```
g++ -o HashPizza HashPizza.cpp
```
**2. Runing project**
To run program fallow the command below. The input files you can find on dir `/in`.
```
~$./HashPizza.exe <optional "-fsna" - free spaces not allowed, "-pmask" for printing mask> <pizza input file *in>
```
**3. Program description**
1. Using the differnece betwen **H** and **L** it creating an _bidimensional array_ **divs** of posible shapes of slice wich are described by _length_ and _height_.
2. Creating the zero filled _bidimensional array_ **mask** for filling it with **sliceId** when will solve the pizza.
3. Algorithm 
* One direction Brute-force with skiping free spaces: add the foud shape(solution) as a _Object_ **Slice** at the end of _linked list_ **list** or skip the point if can't apply any shape according to **H** and **L** condition.
* Backtracking Brute-force: add the foud shape(solution) as a _Object_ **Slice** at the end of _linked list_ **list** or go back and try to find another shape(solution).
4. Also you can set wich output you want to receive, see the _class_ **Pizza** methods.

## Score: 929519 points