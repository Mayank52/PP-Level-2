#include <bits/stdc++.h>
using namespace std;

//GCD : Euclid's Algorithm
int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

const long MOD = 1000000007; //10^9 + 7
//Modular Multiplication (a*b)
long long modMul(long a, long long b)
{
    return (a % MOD * b % MOD) % MOD;
}

//Modular Addition (a+b)
long long modAdd(long long a, long long b)
{
    return (a % MOD + b % MOD) % MOD;
}

//Modular Exponentiation (a^b)
/*
For (a^b)%p
here, p = prime number
We use 10^9 + 7 for int values

if a>> , then use a%p
if b>> , then use b%(p-1)

This is done using Fermat's Little Theorem

Take a,b as string inputs
Convert them to numbers using MOD for every digit
Then use Fast exponentiation to get a^b using MOD at every step

Fast Exponentiation has Time Complexity: O(logb)
*/
const long MOD = 1e9 + 7;
long long pow(long long a, long long b)
{
    if (a == 0)
        return 0;
    if (b == 0)
        return 1;

    long long smallAns = (pow(a, b / 2));
    smallAns = ((smallAns % MOD) * (smallAns % MOD)) % MOD;

    return b % 2 == 0 ? smallAns : ((smallAns % MOD * a % MOD) % MOD);
}
void modPower()
{
    //take input as string
    string aVal, bVal;
    cin >> aVal >> bVal;

    //convert the string to int while using MOD for every digit
    long long a = 0, b = 0;
    for (int i = 0; i < aVal.size(); i++)
    {
        a = ((a * 10) % MOD + (aVal[i] - '0')) % MOD;
    }
    for (int i = 0; i < bVal.size(); i++)
    {
        b = ((b * 10) % (MOD - 1) + (bVal[i] - '0')) % (MOD - 1);
    }

    //use fast exponentiation using MOD
    cout << pow(a, b) << endl;
}

//Reduce a fraction to simplest form
/*
For a fraction a/b
Find gcd(a,b)
Then do 
a1 = a/gcd
b1 = b/gcd

Simplest fraction: a1/b1

Eg: 3/6
gcd(3,6) = 3
a1 = 3/3 = 1
b1 = 6/3 = 2

Simplest fraction : 1/2
*/
void reduceFraction(int num, int den)
{
    //find gcd(numerator, denominator)
    int div = gcd(num, den);

    //simplest numerator
    num = num / div;
    //simplest denominator
    den = den / div;
}

// Sieve of Eratosthenes (Standard Algo)
/*
To Find Prime numbers till n
Time: O(n*log(logn)) which is nearly O(n)
Space: O(n)

Time Complexity:
= N/2 + N/3 + N/5 + .......
= N(1/2 + 1/3 1/5 + ......)
= N(loglogn)

It is only valid for n<=10^8
Because we cannot make an array greater than 10^8.
So, loglog(10^8) = log(26) = 6
So, O(Nloglogn) = O(6N)
So, it is nearly linear
*/
vector<int> sieveOfEratosthenes(int n)
{
    vector<bool> nums(n + 1, false); //false: prime, true: non prime
    //for numbers 2 to sqrt(n)
    for (int i = 2; i * i <= n; i++)
    {
        //if this has not been marked, then mark its multiple
        //also it is a prime number
        if (!nums[i])
        {
            //start from its next multiple after itself
            for (int j = 2 * i; j <= n; j += i)
                nums[j] = true;
        }
    }

    vector<int> primes;
    for (int i = 2; i <= n; i++)
        if (!nums[i])
            primes.push_back(i);

    return primes;
}

//Segmented Sieve
/*
Approach:
Since the maximum allowed size of array is 10^8, for inputs greater than that we can use segmented sieve
In this,
1. Calculate all primes till root(n) using Sieve of Erastothenes
2. Using those primes calculate the primes is range [m,n].
   Make an array of size n-m+1, then using the primes till root(n) find all primes in that range using sieve algo.
We only need to check for numbers in range n, m
So for each prime, we start marking false from ceil(m / num) * num,
Eg: In [21, 50], 
We get primes till root(50) = [2,3,5,7]
For these primes,we use sieve algo and mark al their multiples
For table of 2 we will start checking from
ceil(21 / 2) * 2 = 11*2 = 22

Eg: input is m = 10^6, n = 10^9
Now we find primes till root(10^9) i.e 10^(4.5) using normal Sieve
Then using those we find the primes in range given

Also, in case m is less than root n, we will have to include the req primes in result as well
Like m = 4, n = 50

*/
vector<int> segmentedSieve(int m, int n)
{
    //get primes till root(n)
    vector<int> primestillRootN = sieveOfEratosthenes(sqrt(n));

    //make nums array of size n-m+1
    vector<bool> nums(n - m + 1, false); //true: non-prime, false: prime

    //for all primes found, run the sieve algo
    //To map the numbers in range m,n to 0 indexing for array, use [j-m]
    for (int i = 0; i < primestillRootN.size(); i++)
    {
        double num = primestillRootN[i];
        for (int j = ceil(m / num) * num; j <= n; j += num)
        {
            if (j - m >= 0)
                nums[j - m] = true;
        }
    }

    vector<int> res;
    //if m < root(n)
    if (m <= sqrt(n))
    {
        //include all till root(n) that are in range
        for (int ele : primestillRootN)
            if (ele >= m)
                res.push_back(ele);
        //now from our array start from the first number after root(n)
        //Eg: In [4, 50], we included 5,7 already, so we start from 8
        for (int i = sqrt(n) - m + 1; i < nums.size(); i++)
            if (!nums[i])
                res.push_back(i + m);
    }
    //else just include all marked prime
    else
    {
        for (int i = 0; i < nums.size(); i++)
            if (!nums[i])
                res.push_back(i + m);
    }

    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    return 0;
}