/* Design and Analysis of Algorithms Lab
 * Yatish Kelkar TE IT 8001
 * Assignment 1 : Minmax from array using divide and conquer
 * 08/03/21
*/

#include<iostream>
#include<stdlib.h>
#define SIZE 100

using namespace std;


class DivideAndConquer {
    private:
        int array[SIZE];
        int maxElement, minElement, sizeOfArray;

    public:

        void getData();
        void findMinMax(int, int);
        void displayResult();
        int getSize();
        void displayArray(int, int);
};

void DivideAndConquer :: getData () {
    
    cout << "\n\nEnter the size of the array : " ;
    cin >> sizeOfArray;

    cout << "\n\nEnter the array elements : " << endl ;

    for(int i = 0; i < sizeOfArray; i++) {
        cout << "\n" << i << "th element : ";
        cin >> array[i];
    }

    cout << "\nArray is : ";

    for(int i = 0; i < sizeOfArray; i++) 
        cout << "  [" << array[i] << "]";

}

void DivideAndConquer :: findMinMax (int start, int end) {

    int tempMin, tempMax, midPoint;

    if(start == end) {
        minElement = array[start];
        maxElement = array[start];
    }
    else if(start == end - 1) {
        if(array[start] < array[end]) {
            minElement = array[start];
            maxElement = array[end];
        } else {
            minElement = array[end];
            maxElement = array[start];
        }
    } 
    else {
        
        midPoint = (start + end)/2;

        findMinMax(start, midPoint);

        tempMin = minElement;
        tempMax = maxElement;

        findMinMax(midPoint+1, end);

        if(maxElement < tempMax)
            maxElement = tempMax;

        if(minElement > tempMin)
            minElement = tempMin;
    }
}

void DivideAndConquer :: displayResult () {
    cout << "\n\nThe minimum element in array is : " << minElement ;
    cout << "\n\nThe maximum element in array is : " << maxElement ;
}

int DivideAndConquer :: getSize () {
    return sizeOfArray;
}

void DivideAndConquer :: displayArray (int start, int end) {
    cout << "\nArray is : ";

    for(int i = start; i <= end; i++) 
        cout << "  [" << array[i] << "]";
}

int main() {

    DivideAndConquer DAC;

    DAC.getData();
    DAC.findMinMax(0, DAC.getSize()-1);
    DAC.displayResult();

    return 0;
}

/*
OUTPUT 


Enter the size of the array : 5


Enter the array elements :

0th element : 23

1th element : 11

2th element : 45

3th element : 87

4th element : 91

Array is :   [23]  [11]  [45]  [87]  [91]

The minimum element in array is : 11

The maximum element in array is : 91



TIME COMPLEXITY OF ALGORITHM IS O(n)

*/