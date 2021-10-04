/*
*__________  _________   _____        .___                                 __   
*\______   \/   _____/  /  _  \     __| _/____  ___________ ___.__._______/  |_ 
* |       _/\_____  \  /  /_\  \   / __ |/ __ \/ ___\_  __ <   |  |\____ \   __\
* |    |   \/        \/    |    \ / /_/ \  ___|  \___|  | \/\___  ||  |_> >  |  
* |____|_  /_______  /\____|__  / \____ |\___  >___  >__|   / ____||   __/|__|  
*        \/        \/         \/       \/    \/    \/       \/     |__|         
*
*This code presents the implementation of the RSA decryption algorithm, for
*the alphabet capital leters.
*Considering that depending on the parameters of the public and private
*key an overflow can be generated affecting the results,an implementation 
*capable of operating with large numbers was made (more than '64-bits' which 
*is the maximum size available in variables such as long double or uint64)
*
*The general idea was based on the book "The large integer case study in c++"
*where it is suggested to work with the numbers treating them as strings.
*Book of reference https://secure-media.collegeboard.org/apc/ap01.pdf.lr_7928.pdf
*
*  @file   Decrypt.cpp
*  @author Sebastián Sierra Alarcón
*  @version 1.1 4/10/21
*/

#include <iostream>
#include <string.h>
#include <cmath>
#include <sstream>
#include <vector>

using namespace std;


/**
 * Function to perfom module operation (remainder of a division)
 * @param a   <uint64_t> divisor of the operation
 *        str <string>  dividend of the operation
 * @return <string> Module str % a
**/
string Modulo(uint64_t a, string str)
{
    //First make a string to chart conversion to iterate over the number
    char b[str.length()+1];
    for (int x = 0; x < sizeof(b); x++) { 
    b[x] = str[x];
     }
    // Initialize result
    int mod = 0;
    // calculating mod of b with a to make
    for (int i = 0; i < strlen(b); i++)
        //make consecutive module operation along the digits
        mod = (mod * 10 + b[i] - '0') % a;
    str=to_string(mod);
    return str; // return module
}


/** Multiplies of two numbers defines as strings
*@param num1 <string> First operan of the multiplication 
*       num2 <string> Second operand
*@result result of the multiplication in string format to avoid overflow
**/
string multiply(string num1, string num2)
{
    int i_n1 = 0;
    int i_n2 = 0;
    int N1size = num1.size();
    int N2size = num2.size();
    //If one of the operands is zero then the result is zero
    if (N1size == 0 || N2size == 0)
    return "0";
    // the result number in vectorin reverse order
    vector<int> result(N1size + N2size, 0);
    // Go from right to left in num1
    for (int i=N1size-1; i>=0; i--)
    {
        int carry = 0;
        int n1 = num1[i] - '0';
        i_n2 = 0;        
        for (int j=N2size-1; j>=0; j--)
        {
            // Take current digit of second number
            // Multiply with current digit of first number
            // and add result to previously stored result
            // at current position.
            int n2 = num2[j] - '0';
            int sum = n1*n2 + result[i_n1 + i_n2] + carry;
            // Carry for next iteration
            carry = sum/10;
            // Save result
            result[i_n1 + i_n2] = sum % 10;
            i_n2++;
        }
        // store carry in next cell
        if (carry > 0)
            result[i_n1 + i_n2] += carry;
        // To shift position to left after every
        // multiplication of a digit in num1.
        i_n1++;
    }
    //'0's from the right are ignored
    int i = result.size() - 1;
    while (i>=0 && result[i] == 0)
    i--;
    //result string
    string s = "";
    while (i >= 0)
        s += to_string(result[i--]);
 
    return s;
}
 

/**
 * Function to perfom pow operation (for this consecutive multiplications are implemented
 * in orther to handle string values)
 * @param exp  <uint64_t> exponent 
 *        base <string>  base of the operation
 * @return <string> power function
**/
string longpow(string base, uint64_t exp)
{
    uint64_t i;
    //Initialize the result (1 is the default resault in case of x^{0})
    string ResultM="1";
    //Iteration of multiplication
    for (i=1; i<=exp; i++){
        ResultM=multiply(ResultM,base);
    }
    return ResultM; 
}


/**
 * Function to convert the capitals leters in the specific ASCII values based on the table
 * that was given. For this the corresponding ascii value is add in such way that the letter A is
 * equals to 129 and Z to 154.
 * @param y <char> letter to calculate ascii value
 * @return <int> number associated for each letter in ascii
 **/
int convertVAL(string y)
{
    int x = stoi(y);
    return x==27 ?  32 : x+64;
}


/**
 * Function for visual purposes
 **/
void Ultimateprint1()
{
    printf("---------------------------------------------------------");
    cout<<"\n";
    printf("-----------------RSA Decrypt Algorithm-------------------");
    cout<<"\n";
    printf("---------------------------------------------------------");
    cout<<"\n";
    printf("-");
    cout<<"    Write the Encript message separate by comas (,)    ";
    printf("-");
    cout<<"\n";
    printf("-");
    cout<<"        then write the private key to decrypt          ";
    printf("-");
    cout<<"\n";
    printf("---------------------------------------------------------");
    cout<<"\n";
    printf("---------------------------------------------------------");
    cout<<endl;
}


/**
 * Main function to message decrypt based.
 * At thw end you see the message decrypt all in capital letters.
 * @return print the decrypt message
 **/
int main()
{
    //Define variables
    vector<int>arr;
    char str[500];
    // public key parameters n or e should be integers (as big as you want)
    uint64_t d=0;
    uint64_t n=0;
    uint64_t i=0;
    string potencia="";
    string result="";
    string data="";


    Ultimateprint1();
    cout<<"- Msg : ";
    cin.getline(str, 500, '\n');
    cout << "- (integer) n: "; cin>>n;
    cout << "- (integer) d: "; cin>>d;
    stringstream ss((string)str);
    //Shift
    while(ss>>i)
    {
        arr.push_back(i);
        ss.ignore(1);
    }
    
    //Decrypt conversion
    // value^{d} % n
    cout<<"\n";
    printf("-----------------------Your Msg is:---------------------");
    cout<<"\n";
    for (size_t i = 0; i < arr.size(); ++i) {
        
        // convert value to string
        data=to_string(arr[i]);
        //for each value
        potencia=longpow(data,d);
        result=Modulo(n,potencia);
        // CHar convertion to display de result
        cout<<(char)convertVAL(result);

    }
    cout<<"\n";
    printf("---------------------------------------------------------");
    cout<<"\n";
    printf("---------------------------------------------------------");
    cout<<"\n";
    cout << endl;
    cin.get();


}