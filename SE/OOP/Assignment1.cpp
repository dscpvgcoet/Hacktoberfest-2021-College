/*  
*   Name : Shyam Lokhande
*   Class : SE Comp
*   Assignment : Assignment 1 : Implement a class Complex which represents the Complex Number data type.
*                                Implement the following operations:
*                               1. Constructor (including a default constructor which creates the complex number 0+0i).
*                               2. Overloaded operator+ to add two complex numbers.
*                               3. Overloaded operator* to multiply two complex numbers.
*                               4. Overloaded << and >> to print and read Complex Numbers.
*   Date: 05 October 2021
*/

#include<iostream>                  //including header files
using namespace std;               //declaring the scope of program

class complex                     //class name "complex"
{
    public:
    float real,img;        
    complex(){
        real=0;
        img=0;              //default constructor
    }

    complex operator+ (complex);
    complex operator* (complex);
    friend ostream &operator<<(ostream &,complex&);
    friend istream &operator<<(istream &,complex&);
};

complex complex:: operator + (complex obj){//+ operator overloading
    complex temp;
    temp.real=real+obj.real;
    temp.img=img+obj.img;
    return (temp);
}
 
istream &operator >> (istream &is,complex &obj){
    is>>obj.real;
    is>>obj.img;
    return is;
}
 
ostream &operator<<(ostream &outt,complex &obj){
    outt<<""<<obj.real;
    outt<<"+"<<obj.img<<"i";
    return outt;
}
 
complex complex :: operator * (complex obj){ //* operator overloading
    complex temp;
    temp.real=real*obj.real-img*obj.img;
    temp.img=real*obj.img+img*obj.real;
    return (temp);
}


int main()
{
    complex a,b,c,d,e;
    cout<<"\nEnter first complex number";
    cout<<"\nEnter real and imaginary : ";
    cin>>a;
    cout<<"\nEnter second complex number";
    cout<<"\nEnter real and imaginary : ";
    cin>>b;
    cout<<"\n\tArithmetic operations=>";
    c=a+b;
    cout<<"\n\tAddition = ";
    cout<<c;
    d=a*b;
    cout<<"\n\tMultiplication = ";
    cout<<d;
    cout<<endl;
    return 0;
}
