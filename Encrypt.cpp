/*
*__________  _________   _____                                               __   
*\______   \/   _____/  /  _  \     ____   ____   ___________ ___.__._______/  |_ 
* |       _/\_____  \  /  /_\  \  _/ __ \ /    \_/ ___\_  __ <   |  |\____ \   __\
* |    |   \/        \/    |    \ \  ___/|   |  \  \___|  | \/\___  ||  |_> >  |  
* |____|_  /_______  /\____|__  /  \___  >___|  /\___  >__|   / ____||   __/|__|  
*        \/        \/         \/       \/     \/     \/       \/     |__|         
*
*This code presents the implementation of the RSA encryption algorithm, for
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
*  @file   Encrypt.cpp
*  @author Sebastián Sierra Alarcón
*  @version 1.1 3/10/21
*/

#include <iostream>
#include <cmath>
#include <vector>
#include <string.h>
using namespace std;


/**
 * Function to convert the capitals leters in the specific values of tables that was given 
 * for this the corresponding ascii value is substracted in such way that the letter A is
 * equals to 1 and Z to 26, additionaly Space is set on 27
 * @param x <char> letter to convert in specific table
 * @return <string> number associated for each letter store as string
 **/
string returnVAL(char x)
{
    return to_string((int)x==32 ?  27 : int(x)-64);
    
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// Functions to handle strings operations
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

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
 * Function for visual purposes
 **/
void Ultimateprint1()
{
    printf("---------------------------------------------------------");
    cout<<"\n";
    printf("-----------------RSA Encript Algorithm-------------------");
    cout<<"\n";
    printf("---------------------------------------------------------");
    cout<<"\n";
    printf("-");
    cout<<"    Write the message to Encript use capital letters   ";
    printf("-");
    cout<<"\n";
    printf("-");
    cout<<"      then write the public key to use to encrypt      ";
    printf("-");
    cout<<"\n";
    printf("---------------------------------------------------------");
    cout<<"\n";
    printf("---------------------------------------------------------");
    cout<<endl;
}




/**
 * Main function to encrypt a message write in capital letters based on the RSA algorithm 
 * @return print the encript message separated by comas.
 **/
int main()
{
    // Define variables
    vector<string>arr;
    char conv[100],str[500];
    // public key parameters n or e should be integers (as big as you want) 
    uint64_t n=1;
    uint64_t e=0;
    int longitud=0;
    string potencia="";
    string result="";

    // Input message to encript and parameters
    Ultimateprint1();
    cout<<"- Msg: ";
    cin.getline(str, 500, '\n');

    cout << "- (integer) n: "; cin>>n;
    cout << "- (integer) e: "; cin>>e;
    // Get len of the input msg
    longitud=strlen(str);    
    // Store the message in a string vector
    for (int i=0; i< longitud; i++)
    {   
        //if an unknow value is presented at the entrance
        if((int)str[i]<65 || (int)str[i]>91)
        {
            if((int)str[i]!=32)
            {
                printf("---------------------------------------------------------");
                cout<<" \nWarning: Use only Capital Letters"<<endl;
                printf("---------------------------------------------------------");
                return 0;
            }
        }
        arr.push_back(returnVAL(str[i]));
    }
    cout<<"\n";
    printf("-----------------Your Encrypt Msg is:--------------------");
    cout<<"\n";
    // Encript conversion
    // E=value^{e} % n
    for (size_t i = 0; i < arr.size(); ++i) {
        //for each value
        potencia=longpow(arr[i],e);
        result=Modulo(n,potencia);
        cout<<result<<",";
    }
    cout<<"\n";
    printf("---------------------------------------------------------");
    cout<<"\n";
    printf("---------------------------------------------------------");
    cout<<"\n";
    cout << endl;
    cin.get();
}


