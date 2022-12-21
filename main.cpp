// Aryan Mittal
// Fast Fourier Transform
// Last Modified: 10/21/2022

#include <iostream>
#include <vector>
#include <complex>
#include <cmath>

using namespace std;

const double pi = 3.14159265358979323846;

// Declaring a new Complex type that uses complex of type double
typedef complex<double> Complex;

// Setting complex number i
const Complex cI = (0, 1);

// Recursive Fast Fourier Transform - memory can be optimized by running FFT in place
void fft(vector<Complex>& A) {
    // vector<Complex> r;

    // Base case for recursion
    if (A.size() == 1) {
        return;
    }

    // Avoiding odd size number case
    int n = A.size() / 2;

    vector<Complex> even, odd;

    // Split A into two lists of even and odd indexes
    for (int i=0; i < A.size(); i++) {
        if (i % 2 == 0) {
            even.push_back(A[i]);
        } else {
            odd.push_back(A[i]);
        }
    }

    // Recursively call FFT on both arrays
    fft(even);
    fft(odd);

    // Complex w = 1;
    // Complex wn = exp((2 * pi * cI)/(A.size() * 1.0));

    // Combine the two and compute
    for (int i=0; i < n; i++) {
        Complex w = polar(1.0, -2 * pi * i / A.size()) * odd[i];
        A[i] = even[i] + w;
        A[i + n] = even[i] - w;
    }

}

// Simple print function
void printFFT(vector<Complex>& A) {
    for (int i=0; i < A.size(); i++) {
        cout << A[i] << " ";
    }
    cout << endl;
}


/* Main function with test cases
The program automatically runs any tests present in the "tests" vector
You can modify existing tests or create new tests by simply pushing back new vectors of coeffecients to pass
TEMPLATE: tests.push_back({Complex(0, 0)})

NOTE: The coeffecients are in the form of complex numbers Complex(r, i) where r is the real number and i is the imaginary. 
As coeffecients only have a real component, leave i as 0 for all inputs

Correctness was checked via this tool online: https://scistatcalc.blogspot.com/2013/12/fft-calculator.html
*/

int main() {
    vector<vector<Complex>> tests;

    /* TEST 1: Inputs are ALL zeroes
    Expected output: (0,0) (0,0) (0,0) (0,0)
    */
    tests.push_back({Complex(0, 0), Complex(0, 0), Complex(0, 0), Complex(0, 0)});

    /* TEST 2: Inputs are ALL 1s
    Expected output: (4,0) (0,0) (0,0) (0,0)
    */
    tests.push_back({Complex(1, 0), Complex(1, 0), Complex(1, 0), Complex(1, 0)});

    /* TEST 3: Alternate input between +1 and -1
    Expected output: (0,0) (0,0) (4,0) (0,0)
    */
    tests.push_back({Complex(1, 0), Complex(-1, 0), Complex(1, 0), Complex(-1, 0)});

    /* TEST 4: -1, 2, 3, 0
    Expected output: (4,0) (-4,-2) (0,0) (-4,2)
    */
    tests.push_back({Complex(-1, 0), Complex(2, 0), Complex(3, 0), Complex(0, 0)});

    /* TEST 5: 2,1,-1,5,0,3,0,-4
    Expected output: (6,0) (-5.77817,-3.94975) (3,-3) (9.77817,-5.94975) (-4,0) (9.77817,5.94975) (3,3) (-5.77817,3.94975) 
    */
    tests.push_back({Complex(2, 0), Complex(1, 0), Complex(-1, 0), Complex(5, 0), Complex(0, 0), Complex(3, 0), Complex(0, 0), Complex(-4, 0)});

    // Execute tests
    for (int i=0; i < tests.size(); i++) {
        cout << "TEST " << i + 1 << endl;
        fft(tests[i]);
        printFFT(tests[i]);
        cout << "--------------------" << endl;
    }

    return 0;
}

/* REFERENCES
https://rosettacode.org/wiki/Fast_Fourier_transform#C++
https://scistatcalc.blogspot.com/2013/12/fft-calculator.html
*/