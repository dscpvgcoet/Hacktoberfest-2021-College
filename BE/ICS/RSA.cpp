
/*  
*   Name : Omkar Gurav
*   Class : BE IT 
*   Assignment : Assignment 2 : Write a program in C++ to implement RSA algorithm for key generation and Cipher verification.
*   Date: 22 Sept 2021
*/


#include<iostream>
#include<math.h>
using namespace std;


class RSA
{
    public:

    double p, q, n, phi_n;
    double d, e, plain_text, encrypted_text, decrypted_text;
   

    void get_data();
    static bool check_prime_number(int a);
    static int gcd(int a, int b);
    void calculate_e();
    void calculate_d();
    void encrypt();
    void decrypt();
    static int mod(int a,int b,int c);

};


int RSA::mod(int a, int b, int c)
{
    // Using (ab % c) = ( (a % c)(b % c) ) % c

    int res = 1;     
 
    a = a % c;  
  
    if (a == 0) 
      return 0; 
 
    while (b > 0)
    {
        if (b%2 == 1)
            res = (res*a) % c;
 
        b = b/2; 
        a = (a*a) % c;
    }

    return res;
} 


bool RSA::check_prime_number(int a)
{
   
   if(a == 2)
   {
     return true;
   }
   else if( (a % 2 == 0) || (a == 1) )
   {
        return false;
   }
   
   for(int i = 3; i < sqrt(a) + 1; i = i+2) 
      if(a % i == 0)
        return false;

   return true;

}


void RSA::get_data()
{
    int flag = 1;


    while(flag)
    {

            cout << "\nEnter two prime numbers : ";
            cin >> p >> q;

            if( (check_prime_number(p)) && (check_prime_number(q)) )
            {
                n = p*q;
                cout << "\nn : " << n;

                phi_n = (p-1)*(q-1);
                cout << "\nphi_n : " << phi_n;

                while(flag)
                {
                    cout << "\n\nEnter plain text : ";
                    cin >> plain_text; 

                    if(plain_text >= n)
                    {
                        cout << "\n\nPlain text should be smaller than n !!! Enter again.";
                    }
                    else
                      flag = 0;
                    
                }

                flag = 0;
                
            }
            else
            {

            cout << "\nNumbers are not prime !!! Enter again.";
            
            }

    }

}


int RSA::gcd(int a, int b)
{
    if (b == 0)
    return a;
      
    return gcd(b, a%b);
}


void RSA::calculate_e()
{

    e = 2;

    while(e < phi_n)
    {
       if((gcd(e,phi_n) == 1))
         break;
       else
         e++;
    }
    
    cout << "\nPublic key (e,n) : (" << e << "," << n << ")" ;

}


void RSA::calculate_d()
{
     
    for(int i=1; i < phi_n; i++)
    {
        if(( (int)e*i) % (int)phi_n == 1)
          d = i;
    }

    cout << "\nPrivate key (d,n) : (" << d << "," << n << ")" ;

}


void RSA::encrypt()
{

  encrypted_text = mod(plain_text,e,n);

  cout << "\n\nEncrypted text : " << encrypted_text;

}


void RSA::decrypt()
{

  decrypted_text = mod(encrypted_text,d,n);
  cout << "\n\nDecrypted text : " << decrypted_text;

}


int main()
{
    RSA r;
    r.get_data();
    r.calculate_e();
    r.calculate_d();
    r.encrypt();
    r.decrypt();

}