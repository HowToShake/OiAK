#include <Python.h>
#include <conio.h>
#include <stdio.h>     
#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <string>
#include <random>
#include <cmath>
#include <iomanip>
#include <fstream>

using namespace std;

struct BigInt {

    int size = 9;
    int base = (int)pow(10, size);

    vector<int> ZERO = Integer("0");
    vector<int> ONE = Integer("1");
    vector<int> TWO = Integer("2");
    vector<int> THREE = Integer("3");

    vector<int> num1;
    vector<int> num2;
    vector<int> result;

    vector<int> vectorForSection[3] = { Integer("18446744073709551616"), Integer("318665857834031151167461"), Integer("3317044064679887385961981") };
    unsigned long long numSection[13] = { 0, 2047, 1373653 , 9080191 , 25326001 , 3215031751 , 4759123141 , 1122004669633 ,2152302898747, 3474749660383 ,  341550071728321, 3825123056546413051 };

    vector<int> numbersToMR;
    int amountOfNumbersToMr;

    void prepareValuesForMRAlgo(string num1) {
        int numberLength = num1.length();

        //Przedziały mieszczące się w unsigned long long.
        if (numberLength <= 19) {

            //Liczby 19 cyfrowe do 3825123056546413051
            unsigned long long input = stoull(num1);
            if (input < numSection[11]) {
                if (input > numSection[0] && input < numSection[1]) {
                    numbersToMR.push_back(2);
                    amountOfNumbersToMr = 1;
                }
                else if (input >= numSection[1] && input < numSection[2]) {
                    numbersToMR.push_back(2);
                    numbersToMR.push_back(3);
                    amountOfNumbersToMr = 2;
                }
                else if (input >= numSection[2] && input < numSection[3]) {
                    numbersToMR.push_back(31);
                    numbersToMR.push_back(73);
                    amountOfNumbersToMr = 2;
                }
                else if (input >= numSection[3] && input < numSection[4]) {
                    numbersToMR.push_back(2);
                    numbersToMR.push_back(3);
                    numbersToMR.push_back(5);
                    amountOfNumbersToMr = 3;
                }
                else if (input >= numSection[4] && input < numSection[5]) {
                    numbersToMR.push_back(2);
                    numbersToMR.push_back(3);
                    numbersToMR.push_back(5);
                    numbersToMR.push_back(7);
                    amountOfNumbersToMr = 4;
                }
                else if (input >= numSection[5] && input < numSection[6]) {
                    numbersToMR.push_back(2);
                    numbersToMR.push_back(7);
                    numbersToMR.push_back(61);
                    amountOfNumbersToMr = 3;
                }
                else if (input >= numSection[6] && input < numSection[7]) {
                    numbersToMR.push_back(2);
                    numbersToMR.push_back(13);
                    numbersToMR.push_back(23);
                    numbersToMR.push_back(1662803);
                    amountOfNumbersToMr = 4;
                }
                else if (input >= numSection[7] && input < numSection[8]) {
                    numbersToMR.push_back(2);
                    numbersToMR.push_back(3);
                    numbersToMR.push_back(5);
                    numbersToMR.push_back(7);
                    numbersToMR.push_back(11);
                    amountOfNumbersToMr = 5;
                }
                else if (input >= numSection[8] && input < numSection[9]) {
                    numbersToMR.push_back(2);
                    numbersToMR.push_back(3);
                    numbersToMR.push_back(5);
                    numbersToMR.push_back(7);
                    numbersToMR.push_back(11);
                    numbersToMR.push_back(13);
                    amountOfNumbersToMr = 6;
                }
                else if (input >= numSection[9] && input < numSection[10]) {
                    numbersToMR.push_back(2);
                    numbersToMR.push_back(3);
                    numbersToMR.push_back(5);
                    numbersToMR.push_back(7);
                    numbersToMR.push_back(11);
                    numbersToMR.push_back(13);
                    numbersToMR.push_back(17);
                    amountOfNumbersToMr = 7;
                }
                else if (input >= numSection[10] && input < numSection[11]) {
                    numbersToMR.push_back(2);
                    numbersToMR.push_back(3);
                    numbersToMR.push_back(5);
                    numbersToMR.push_back(7);
                    numbersToMR.push_back(11);
                    numbersToMR.push_back(13);
                    numbersToMR.push_back(17);
                    numbersToMR.push_back(19);
                    numbersToMR.push_back(23);
                    amountOfNumbersToMr = 9;
                }
            }
            //Liczby 19 cyfrowe mniejsze od 20 cyfrowych. MAX 999'999'999'999'999'999'9
            else {
                numbersToMR.push_back(2);
                numbersToMR.push_back(3);
                numbersToMR.push_back(5);
                numbersToMR.push_back(7);
                numbersToMR.push_back(11);
                numbersToMR.push_back(13);
                numbersToMR.push_back(17);
                numbersToMR.push_back(19);
                numbersToMR.push_back(23);
                numbersToMR.push_back(29);
                numbersToMR.push_back(31);
                numbersToMR.push_back(37);
                amountOfNumbersToMr = 12;
            }
        }

        //Przedziały spoza rozmiaru ULL. MIN 100'000'000'000'000'000'00
        else {

            vector<int> input = Integer(num1);

            if (compareGreater(input, vectorForSection[2])) {
                int randInt = rand() % 9999 + 1;
                for (int i = 0; i < 20; i++) {
                    numbersToMR.push_back(randInt);
                }
                amountOfNumbersToMr = 20;
            }
            else if (compareGreater(input, vectorForSection[1])) {
                numbersToMR.push_back(2);
                numbersToMR.push_back(3);
                numbersToMR.push_back(5);
                numbersToMR.push_back(7);
                numbersToMR.push_back(11);
                numbersToMR.push_back(13);
                numbersToMR.push_back(17);
                numbersToMR.push_back(19);
                numbersToMR.push_back(23);
                numbersToMR.push_back(29);
                numbersToMR.push_back(31);
                numbersToMR.push_back(37);
                numbersToMR.push_back(41);
                amountOfNumbersToMr = 13;
            }
            else if (compareGreater(input, vectorForSection[0])) {
                numbersToMR.push_back(2);
                numbersToMR.push_back(3);
                numbersToMR.push_back(5);
                numbersToMR.push_back(7);
                numbersToMR.push_back(11);
                numbersToMR.push_back(13);
                numbersToMR.push_back(17);
                numbersToMR.push_back(19);
                numbersToMR.push_back(23);
                numbersToMR.push_back(29);
                numbersToMR.push_back(31);
                numbersToMR.push_back(37);
                amountOfNumbersToMr = 12;
            }
            else if (compareGreater(input, Integer("10000000000000000000"))) {
                numbersToMR.push_back(2);
                numbersToMR.push_back(3);
                numbersToMR.push_back(5);
                numbersToMR.push_back(7);
                numbersToMR.push_back(11);
                numbersToMR.push_back(13);
                numbersToMR.push_back(17);
                numbersToMR.push_back(19);
                numbersToMR.push_back(23);
                numbersToMR.push_back(29);
                numbersToMR.push_back(31);
                numbersToMR.push_back(37);
                amountOfNumbersToMr = 12;
            }
        }


    }

    vector<int> Integer(string s) {
        vector <int> result;

        int full = s.size() / size;
        int rest = s.size() % size;

        for (int i = s.size() - size; i >= 0; i -= size) {
            int v = 0;
            for (int j = 0; j < size; j++) {
                int a = s[j + i] - '0';
                v *= 10;
                v += a;
            }
            result.push_back(v);


        }

        if (rest != 0) {
            int r = 0;
            for (int i = 0; i < rest; i++) {
                r *= 10;
                int a = s[i] - '0';
                r += a;
            }
            result.push_back(r);
        }

        reverse(result.begin(), result.end());

        return result;
    }

    string ToString(vector<int>a) {
        string example = "";
        int temporary = 0;

        for (int i = a.size() - 1; i > 0; i--) {
            string tempStr = to_string(a[i]);

            while (tempStr.length() < 9) {
                tempStr = "0" + tempStr;
            }
            example = tempStr + example;


        }
        example = to_string(a[0]) + example;


        return example;
    }

    void reduceLeadingZeros(vector<int>& a) {

        while (a[0] == 0) {
            a.erase(a.begin());
        }
    }

    bool compareGreater(vector<int> num1, vector<int> num2) {
        if (num1.size() > num2.size()) {

            return true;
        }
        else if (num1.size() < num2.size()) {

            return false;
        }
        else {
            for (int i = 0; i < num1.size(); i++) {
                if (num1[i] > num2[i]) {

                    return true;
                }
                else if (num1[i] < num2[i]) {

                    return false;
                }
            }

            return false;

        }



    }

    bool compareEqual(vector<int> num1, vector<int> num2) {


        if (num1.size() != num2.size()) {
            return false;
        }
        else {
            for (int i = 0; i < num1.size(); i++) {
                if (num1[i] != num2[i]) {
                    return false;
                }
            }
            return true;
        }
    }

    vector<int> transferNumberLeft(vector<int> num1) {
        int carry = 0;
        for (int i = num1.size() - 1; i >= 0; i--) {
            int value = num1[i];

            int value2 = value / (pow(10, size - 1));
            value = value % int(pow(10, size - 1)) * 10;
            value = value + carry;

            carry = value2;
            num1[i] = value;

        }
        if (carry) {
            num1.insert(num1.begin(), carry);
        }

        return num1;

    }

    vector<int> transferNumberRight(vector<int> num1) {
        int carry = 0;
        for (int i = 0; i < num1.size(); i++) {
            int value = num1[i];

            int value2 = value % 10;
            value = value / 10;
            value = value + carry * (pow(10, size - 1));

            carry = value2;
            num1[i] = value;

        }


        if (num1.size() > 1) {
            reduceLeadingZeros(num1);
        }

        return num1;
    }

    vector<int> add(vector<int> num1, vector<int> num2) {
        int max_len = num1.size();
        int min_len = num2.size();
        bool num1bigger = true;
        if (num2.size() > num1.size()) {
            max_len = num2.size();
            min_len = num1.size();
            num1bigger = false;
        }



        max_len++;

        vector<int>result;

        for (int i = 0; i < max_len; i++) {
            result.push_back(0);
        }

        //adding
        int carry = 0;
        for (int i = 0; i < min_len; i++) {


            int temp = num1[num1.size() - 1 - i] + num2[num2.size() - 1 - i] + carry;
            carry = 0;

            if (temp / base > 0) {
                carry = temp / base;
                temp = temp % base;
            }
            result[max_len - 1 - i] = temp;


        }


        // carry
        if (num1.size() != num2.size()) {
            for (int i = min_len + 1; i < max_len; i++) {

                int temp = 0;
                if (num1bigger) {
                    temp = num1[num1.size() - i] + carry;
                }
                else {
                    temp = num2[num2.size() - i] + carry;
                }

                carry = 0;

                if (temp / base > 0) {
                    carry = temp / base;
                    temp = temp % base;
                }
                result[result.size() - i] = temp;

            }
        }

        result[0] = carry;

        reduceLeadingZeros(result);
        return  result;
    }

    vector<int> substract(vector<int> num1, vector<int> num2) {


        vector<int>result;
        result.push_back(0);
        if (compareEqual(num1, num2)) {
            result[0] = 0;
            return result;
        }
        else if (!compareGreater(num1, num2)) {
            result[0] = -1;
            return result;
        }
        else {
            result.pop_back();
            int max_len = num1.size();
            int min_len = num2.size();
            bool num1bigger = true;
            if (num2.size() > num1.size()) {
                max_len = num2.size();
                min_len = num1.size();
                num1bigger = false;
            }

            max_len++;

            for (int i = 0; i < max_len; i++) {
                result.push_back(0);
            }

            //subtracting
            int carry = 0;
            for (int i = 0; i < min_len; i++) {
                int temp = num1[num1.size() - 1 - i] - num2[num2.size() - 1 - i] + carry;
                carry = 0;

                if (temp < 0) {
                    carry = -1;
                    temp = temp + base;

                }

                result[max_len - 1 - i] = temp;

            }

            // carry
            if (num1.size() != num2.size()) {
                for (int i = min_len + 1; i < max_len; i++) {
                    int temp = 0;
                    if (num1bigger) {
                        temp = num1[num1.size() - i] + carry;
                    }
                    else {
                        temp = -num2[num2.size() - i] + carry;
                    }

                    carry = 0;

                    if (temp < 0) {
                        carry = -1;
                        temp = temp + base;
                    }

                    result[max_len - i] = temp;
                }
            }
            else {
                result[0] = carry;
            }

            reduceLeadingZeros(result);

            return  result;

        }
    }

    vector<int> multiply(vector<int>num1V, vector<int>num2V) {

        if (compareEqual(num1V, ZERO) || compareEqual(num2V, ZERO)) {
            return ZERO;
        }
        if (compareEqual(num1V, ONE)) {
            return num2V;
        }
        if (compareEqual(num2V, ONE)) {
            return num1V;
        }


        string num1, num2;

        num1 = ToString(num1V);
        num2 = ToString(num2V);

        vector<int> res;
        int len1 = num1.size();
        int len2 = num2.size();
        if (len1 == 0 || len2 == 0)
            return res;


        vector<int> result(len1 + len2, 0);


        int i_n1 = 0;
        int i_n2 = 0;

        for (int i = len1 - 1; i >= 0; i--)
        {
            int carry = 0;
            int n1 = num1[i] - '0';


            i_n2 = 0;


            for (int j = len2 - 1; j >= 0; j--)
            {

                int n2 = num2[j] - '0';

                int sum = n1 * n2 + result[i_n1 + i_n2] + carry;


                carry = sum / 10;


                result[i_n1 + i_n2] = sum % 10;

                i_n2++;
            }


            if (carry > 0)
                result[i_n1 + i_n2] += carry;


            i_n1++;
        }


        int i = result.size() - 1;
        while (i >= 0 && result[i] == 0)
            i--;

        if (i == -1)
            return res;


        string s = "";

        while (i >= 0)
            s += std::to_string(result[i--]);


        res = Integer(s);

        return res;
    }

    vector<int> divide(vector<int>num1, vector<int>num2) {

        int counter = 0;
        if (compareEqual(num1, ZERO)) {
            //cout << "Pierwsza liczba to zero" << endl;
            return ZERO;
        }

        if (compareEqual(num2, ONE)) {
            //cout << "Druga liczba to 1" << endl;
            return num1;
        }
        if (num1.size() == 1 && num2.size() == 1) {
            //cout << "Liczby sa jednakowej dlugosci" << endl;
            return Integer(to_string(num1[0] / num2[0]));
        }

        if (compareEqual(num1, num2)) {
            return ONE;
        }
        vector<int> num1Copy = num1;
        vector<int> num2Copy = num2;

        if (compareEqual(num2, ZERO)) {
            //cout << "Druga liczba to zero" << endl;
            return num2;
        }

        while (compareGreater(num1Copy, num2Copy)) {
            num2Copy = transferNumberLeft(num2Copy);
            counter++;
        }
        
        num2Copy = transferNumberRight(num2Copy);

        if (compareEqual(num2Copy, num1Copy)) {
            return ONE;
        }


        string temp = "";


        while (counter > 0) { // BYŁO: counter > 0
            int times = 0;
            if (compareEqual(num1Copy,ZERO) || compareEqual(num2Copy, ZERO)) { 
               // cout << "\n\nCOUNTER " << counter << endl;
                for (int i = counter; i > 0; i--) {
                    temp += '0';
                    
                }
                return Integer(temp);
            }

            while (compareGreater(num1Copy, num2Copy) || compareEqual(num1Copy, num2Copy)) {
                num1Copy = substract(num1Copy, num2Copy);
                times++;
            }
            
            temp += to_string(times);
           // cout << "TEMP: " << temp << endl;
            counter--;
            num2Copy = transferNumberRight(num2Copy);
    
        }

        if (temp == "") {
            temp = "0";
        }

        return Integer(temp);
    }

    vector<int> modulo(vector<int>num1, vector<int>num2) {

        int counter = 0;

        if (compareEqual(num2, ONE)) {
            return ZERO;
        }

        if (compareEqual(num1, ZERO)) {
            return ZERO;
        }
        if (compareEqual(num2, ZERO)) {
            return num1;
        }
        if (compareEqual(num1, num2)) {
            return ZERO;
        }

        if (compareEqual(num2, ONE)) {
            return ZERO;
        }

        if (compareGreater(num2, num1)) {
            return num1;
        }
        if (num1.size() == 1 && num2.size() == 1) {
            return Integer(to_string(num1[0] % num2[0]));
        }
        vector<int> num1Copy = num1;
        vector<int> num2Copy = num2;


        while (compareGreater(num1Copy, num2Copy)) {
            num2Copy = transferNumberLeft(num2Copy);
            counter++;
        }
        //cout << "COUNTER: " << counter << endl;
        num2Copy = transferNumberRight(num2Copy);

        if (compareEqual(num2Copy, num1Copy)) {
            return ZERO;
        }


        string temp = "";

        while (counter > 0) {

            int times = 0;
            if (compareEqual(num1Copy, ZERO) || compareEqual(num2Copy, ZERO)) {
                for (int i = counter; i >= 0; i--) {
                    temp += '0';
                    return num1Copy;
                }
            }

            while (compareGreater(num1Copy, num2Copy) || compareEqual(num1Copy, num2Copy)) {
               /* cout << "\n\n\n";
                for (int i = 0; i < num1Copy.size(); i++) {
                    cout << num1Copy[i] << " ";
                }
                cout << "\nNUM2 " << endl;
                for (int i = 0; i < num2Copy.size(); i++) {
                    cout << num2Copy[i] << " ";
                }*/
                //cout << endl;
                num1Copy = substract(num1Copy, num2Copy);
                times++;
            }

            temp += to_string(times);
            counter--;
            
            num2Copy = transferNumberRight(num2Copy);
            
            
            
        }

        //cout << "OSTATNIE" << endl;
     
        return num1Copy;
    }

    vector<int> exponentiationBySquaring(vector<int>a, vector<int>power, vector<int>mod) {
        vector<int> result, counter, incrementer;

        counter = ZERO;
        incrementer = ONE;
        result = ONE;


        a = modulo(a, mod);

        while (compareGreater(power, counter)) {
            result = multiply(result, a);
            result = modulo(result, mod);
            counter = add(counter, incrementer);


        }

        return result;
    }

    vector<int> power(vector<int>num1, vector<int>num2) {
        vector<int> counter, result, incrementer, check;
        incrementer = ONE;
        counter = ONE;
        check = ZERO;
        result = num1;

        if (compareEqual(num2, check)) {
            return counter;
        }

        while (compareGreater(num2, counter)) {
            result = multiply(result, num1);
            counter = add(counter, incrementer);
        }
        return result;

    }

    int findS(vector<int>num1) {

        int maxPow = 0;
        vector<int> num1Decrement = substract(num1, ONE);

        while (true) {
            string Power = "";
            int power = 0;
            power = int(pow(2, maxPow));

            Power = to_string(power);

            bool equal = compareEqual(modulo(num1Decrement, Integer(Power)), ZERO);
            if (equal) {
                maxPow++;
                continue;
            }
            else {
                break;
            }

        }
        maxPow--;
        return maxPow;
    }

    vector<int> findD(vector<int> num1, int s) {
        vector<int> result = divide(num1, power(TWO, Integer(to_string(s))));
        return result;
    }

    void printVector(vector<int>A) {
        for (int i = 0; i < A.size(); i++) {
            cout << A[i] << " ";
        }
        cout << endl;
    }

    bool checkPrime(int repeats, int s, vector<int> d, vector<int> mod) {
        vector<int> one = ONE;
        vector<int>modDecrement = substract(mod, one);
        for (int i = 0; i < repeats; i++) {
            int a = generateRandom(mod);
            string A = to_string(a);
            if (!compareEqual(powerFastModulo(Integer(A), d, mod), one)) {
                for (int r = 0; r <= s; r++) {
                    vector<int>temporary = multiply(Integer(to_string(int(pow(2, r)))), d);
                    if (!compareEqual(powerFastModulo(Integer(A), temporary, mod), modDecrement)) {
                        if (r == (s - 1)) {
                            return false;
                        }
                    }
                    else {
                        break;
                    }
                }
            }
        }
        return true;
    }

    bool checkDeterministicPrime(int s, vector<int> d, vector<int> mod) {
        vector<int> one = ONE;
        vector<int>modDecrement = substract(mod, one);
        prepareValuesForMRAlgo(ToString(mod));

        for (int i = 0; i < amountOfNumbersToMr; i++) {


            int a = numbersToMR[i];
            string A = to_string(a);

            if (!compareEqual(powerFastModulo(Integer(A), d, mod), one)) {


                for (int r = 0; r <= s; r++) {

                    vector<int>temporary = multiply(Integer(to_string(int(pow(2, r)))), d);

                    if (!compareEqual(powerFastModulo(Integer(A), temporary, mod), modDecrement)) {
                        if (r == (s - 1)) {
                            return false;
                        }
                    }
                    else {

                        break;
                    }


                }


            }



        }
        return true;
    }

    vector<int> powerFastModulo(vector<int>a, vector<int>b, vector<int>n) {
        vector<int> x = a;
        vector<int> result = ONE;
        vector<int> bCopy = b;

        bool run = true;
        bool additional = false;
        int counter = 0;
        do {

            b = bCopy;

            if (b[b.size() - 1] % 2 == 1) {

                result = multiply(result, x);

                result = modulo(result, n);

            }

            x = multiply(x, x);
            x = modulo(x, n);
            bCopy = divide(b, TWO);

            if (compareEqual(b, ZERO)) {
                additional = true;
            }
            
            counter++;
        } while (!compareGreater(ONE, bCopy));     
        return result;
    }

    bool checkFermatPrime(int repeats, vector<int> num1) {

        vector<int> num1Decrement = substract(num1, ONE);

        for (int i = 0; i < repeats; i++) {
            int random = generateRandom(num1);
            if (compareEqual(powerFastModulo(Integer(to_string(random)), num1Decrement, num1), ONE)) {
                continue;
            }
            else {
                return false;
            }
        }
        return true;

    }

    int generateRandom(vector<int> num1) {
        int len = num1.size();
        int temp = 0;
        if (len == 1) {
            temp = num1[0];
            int random = rand() % (temp-2) + 2;
            return random;
        }
        else {
            return rand() % 5000 + 1;
        }
    }
};


void callPythonAKSFunction(string input1) {
    //cout << "Otrzymana liczba do Pythona: " << input1 << endl;

    Py_Initialize();    

    PyObject* pModule = PyImport_ImportModule("AKS");
    PyObject* pValue;
    
    
    if (pModule) {
        PyObject* pFunc = PyObject_GetAttrString(pModule, "Aks");
        
        
       
        if (pFunc && PyCallable_Check(pFunc)) {
            
            pValue = PyObject_CallFunction(pFunc,"s",input1.c_str());
            //pValue = PyObject_CallFunction(pFunc,NULL);
        }
        else {
            cout << "ERROR: FUNCTION HEJKA()"<<endl;
        }
       
    }
    else {
        cout << "ERROR: MODULE NOT IMPORTED" << endl;
    }

    Py_Finalize();
}

bool callPythonMRFunction(string input1) {
    Py_Initialize();

    PyObject* pModule = PyImport_ImportModule("MillerRabin");
    PyObject* pValue;
    bool wasResultTrue = false;


    if (pModule) {
        PyObject* pFunc = PyObject_GetAttrString(pModule, "MillerRabin");



        if (pFunc && PyCallable_Check(pFunc)) {

            pValue = PyObject_CallFunction(pFunc, "s", input1.c_str());
            wasResultTrue = PyObject_IsTrue(pValue);
            
        }
        else {
            cout << "ERROR: FUNCTION()" << endl;
        }

    }
    else {
        cout << "ERROR: MODULE NOT IMPORTED" << endl;
    }
    
    Py_Finalize();

    return wasResultTrue;
}

bool callPythonMRDeterministicFunction(string input1) {
    Py_Initialize();

    PyObject* pModule = PyImport_ImportModule("MillerRabinDeterministic");
    PyObject* pValue;
    bool wasResultTrue = false;


    if (pModule) {
        PyObject* pFunc = PyObject_GetAttrString(pModule, "MillerRabinDeterministic");



        if (pFunc && PyCallable_Check(pFunc)) {

            pValue = PyObject_CallFunction(pFunc, "s", input1.c_str());
            wasResultTrue = PyObject_IsTrue(pValue);
        }
        else {
            cout << "ERROR: FUNCTION()" << endl;
        }

    }
    else {
        cout << "ERROR: MODULE NOT IMPORTED" << endl;
    }

    Py_Finalize();
    return wasResultTrue;
}

bool callPythonFermatFunction(string input1) {
    Py_Initialize();

    PyObject* pModule = PyImport_ImportModule("Fermat");
    PyObject* pValue;
    bool wasResultTrue = false;

    if (pModule) {
        PyObject* pFunc = PyObject_GetAttrString(pModule, "fermat");



        if (pFunc && PyCallable_Check(pFunc)) {

            pValue = PyObject_CallFunction(pFunc, "s", input1.c_str());
            wasResultTrue = PyObject_IsTrue(pValue);
        }
        else {
            cout << "ERROR: FUNCTION()" << endl;
        }

    }
    else {
        cout << "ERROR: MODULE NOT IMPORTED" << endl;
    }

    Py_Finalize();
    return wasResultTrue;
}

void printMessageIsPrime(bool result) {
    if (result == true) {
        cout << "Liczba jest pierwsza." << endl;
    }
    else {
        cout << "Liczba nie jest pierwsza." << endl;
    }
}

void menu() {
    srand(time(NULL));
    BigInt x = BigInt();
    string input;

    bool program = true;
    while(program){
    cout << "Podaj liczbe do przeprowadzenia testu pierwszosci: " << endl;
    cin >> input;
    x.num1 = x.Integer(input);

    if (x.compareEqual(x.modulo(x.num1, x.TWO), x.ZERO)) {
        cout << "\nPodana liczba musi byc nieparzysta!" << endl;
        
    }else{

    cout << "\nDostepne opcje: " << endl;
    cout << "0. - Wyjscie z programu." << endl;
    cout << "1. - Test pierwszosci Fermata (C++)." << endl;
    cout << "2. - Test pierwszosci Fermata (Python)." << endl;
    cout << "3. - Test pierwszosci Millera-Rabina (C++)." << endl;
    cout << "4. - Test pierwszosci Millera-Rabina (Python)." << endl;
    cout << "5. - Test pierwszosci Millera-Rabina w wersji deterministycznej (C++)." << endl;
    cout << "6. - Test pierwszosci Millera-Rabina w wersji deterministycznej (Python)." << endl;
    cout << "7. - Test pierwszosci AKS (Python)." << endl;
    cout << "\nProsze wybrac opcje: " << endl;
    int wybor;
    cin >> wybor;
    cout << "\n\n";
    switch (wybor) {
    case 0: {
        cout << "Dzikuje za skorzystanie z programu." << endl;
        exit(0);
        break;
    }
    case 1: {
        bool isFermatPositive = x.checkFermatPrime(10, x.num1);
        printMessageIsPrime(isFermatPositive);
        break;
    }
    case 2: {
        bool isFermatPositive = callPythonFermatFunction(input);
        printMessageIsPrime(isFermatPositive);
        break;
    }
    case 3: {
        int s = x.findS(x.num1);
        vector<int> d = x.findD(x.num1, s);

        bool isMillerRabinPrime = x.checkPrime(10, s, d, x.num1);
        printMessageIsPrime(isMillerRabinPrime);
        break;
    }
    case 4: {
        bool isMillerRabinPythonPrime = callPythonMRFunction(input);
        printMessageIsPrime(isMillerRabinPythonPrime);
        break;
    }
    case 5: {
        x.prepareValuesForMRAlgo(input);
        int s = x.findS(x.num1);
        vector<int> d = x.findD(x.num1, s);

        bool isDeterministicMRPrime = x.checkDeterministicPrime(s, d, x.num1);
        printMessageIsPrime(isDeterministicMRPrime);
        break;
    }
    case 6: {
        bool isMRDETPrime = callPythonMRDeterministicFunction(input);
        printMessageIsPrime(isMRDETPrime);
        break;
    }
    case 7: {
        cout << "Uwaga! Podany algorytm powoduje bledy w momencie uruchomiania go poprzez konsole systemowe. \n"
            << "Zwiazane jest to z uzyciem tzw. multiprocessingu w algorytmie. \n"
            << "W celu prawidlowego sprawdzenia liczby zalecamy uruchomienie skryptu z powloki Python w wersji "
            << "co najmniej 3.8. \n" << endl;
        cout << "Jesli chcesz kontynuowac uruchomienie programu w powloce systemowej wybierz 't'.\nJesli chcesz wrocic do menu wyboru algorytmu wybierz 'n'." << endl;

        bool poprawny_znak = true;
        while (poprawny_znak) {
            char wybor;
            cin >> wybor;

            if (wybor == 't') {
                callPythonAKSFunction(input);
                poprawny_znak = false;
            }
            else if (wybor == 'n') {
                poprawny_znak = false;
            }
            else {
                cout << "Prosze wybrac odpowiednia opcje." << endl;
            }
        }

    }
    }
    }
    cout << "\n\nW celu wprowadzenia nowej liczby wciśnij 't'.\n";
    cout << "W celu wyjscia z programu wybierz dowolny znak. \n";
    char powtorz;
    cin >> powtorz;
    if (powtorz == 't') {
       
    }
    else {
        program = false;
    }

    }
    

}

void test_timeMeasuring() {
    srand(time(NULL));
    string exaplesNotPrime[40] = { "9", "65", "363", "1003", "32045", "499999", "1234573", "84268541", "231576015", "1943678051", "63728958373", "917384758367", "8176284653219", "73640907618261", "836283651841015", "1234567891012139", "19587634582012307", "946305876310824655", "9584630125078946301", "16345203607948613523", "135301852344706746049", "1111111111111111111111", "14390600632080526061859", "111111333333555555777777", "1428571428571428571428573", "10011110011011110110110011", "339341355381394398413415437", "2775577757352755375573357273", "81873842574213466006829740415", "999999777777555555333333111111", "1317313773719779779173773137133", "11111111111111111111111111111111", "432162695486262963136144381497589", "1298074214633706907132624091455649", "59999999999999999999999999999999997", "119665765800843104737370354851986949", "22537211232223552133332272923531222223112175722333721931322254123743221133522349", "9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999913", "999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999823", "3737373737373737373737373737373737373737373737373737373737373737373737373743434343434343434343434343434343434343411343434343434343434343434343434343434343434111" };//Od 1 do 36, 80-cyfrowa, 100-cyfrowa, 120-cyfrowa, 160-cyfrowa

    string examplesPrime[40] =   { "7", "59", "241", "2113", "31513", "281719", "4441939", "10000019", "181111181", "2232232273", "99999999977", "101111111111", "1169769749219", "15307263442931", "231917131175321", "1311753223571113", "15125111011152151", "102598800232111471", "6787988999657777797", "74041360822451971987", "777777775555552323323", "1079180598685959785401", "35452590104031691935943", "699999999986868668888861", "3333322225555555777777777", "49162536496481100121144169", "718281828459040954828182817", "1596165317111770183018911953", "42424864624626642462642424223", "691701709719727733739743751757", "7019385211055596446229489549303", "29998887776665554443332221110009", "433826412254338305779643383474369", "6339968890136139283151942797098461", "89423567665158371901674138556551281", "357315397211233277367389457479547569" ,"22537211232223552133332272923531222223112175722333721931322254123743221133522347", "7777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777771", "100127631001285310012921100129311001299910013141100132871001347310013287100131411001299910012931100129211001285310012763", "3737373737373737373737373737373737373737373737373737373737373737373737373743434343434343434343434343434343434343434343434343434343434343434343434343434343434343"}; //Od 1 do 36, 80-cyfrowa, 100-cyfrowa, 120-cyfrowa, 160-cyfrowa
                                                                                                                                                                                   
    string exampleMixed[40] =    { "3", "17", "561", "1729", "41041", "293339", "1289751", "87543873", "234030131", "8943521671", "89732456937", "987324687213", "1246888642073", "90442568793803", "687524752643893", "1436697831295441", "89012506782380591", "891265112895278105", "4954039956700380001", "12890759812579081201", "111111110111011111113", "1001303203318050290393", "81402749386839761113321", "111111333333555555777777", "1428571428571428571428573", "34181543186513112112641339", "339341355381394398413415437", "2775577757352755375573357273", "18276412521634351272910001331", "999999777777555555333333111111", "1317313773719779779173773137137", "11111111111111111111111111111111", "432162695486262963136144381497589", "1298074214633706907132624091455649", "59999999999999999999999999999999997", "119665765800843104737370354851986949", "22537211232223552133332272923531222223112175722333721931322254123743221133522349", "9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999913", "999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999823", "3737373737373737373737373737373737373737373737373737373737373737373737373743434343434343434343434343434343434343411343434343434343434343434343434343434343434111" };//2,3,4,16,19 - Carmichaela, 1,2,6,9,14,22 - pierwsze, reszta nie pierwsza.
    
    BigInt test = BigInt();

    const int repeats = 20;
    const int repeats_inside_algo = 20;

    int mode = 3;

    
    //Mode 1 == NotPrime, mode 2 == Prime, mode 3 == exampleMixed;
    //cout << "\n\nTEST FOR NOT PRIMARY NUMBERS\n" << endl;
    if (mode == 1) {

        //MillerRabin C++ Values
        long int time_MR_C[repeats];
        unsigned long long sum_MR_C = 0;
        bool wasResultTrue_MR_C = false;
        int correct_results_MR_C = 0;
        float results_in_percentage_MR_C[40];
        unsigned long long avarage_MR_C_time[40];

        //MillerRabin Python Values
        long int time_MR_Python[repeats];
        unsigned long long sum_MR_Python = 0;
        bool wasResultTrue_MR_Python = false;
        int correct_results_MR_Python = 0;
        float results_in_percentage_MR_Python[40];
        unsigned long long avarage_MR_Python_time[40];

        //Fermat C++ Values
        long int time_Fermat_C[repeats];
        unsigned long long sum_Fermat_C = 0;
        bool wasResultTrue_Fermat_C = false;
        int correct_results_Fermat_C = 0;
        float results_in_percentage_Fermat_C[40];
        unsigned long long avarage_Fermat_C_time[40];

        //Fermat Python Values
        long int time_Fermat_Python[repeats];
        unsigned long long sum_Fermat_Python = 0;
        bool wasResultTrue_Fermat_Python = false;
        int correct_results_Fermat_Python = 0;
        float results_in_percentage_Fermat_Python[40];
        unsigned long long avarage_Fermat_Python_time[40];

        //MillerRabinDet c++ Values
        long int time_MR_DET_C[repeats];
        unsigned long long sum_MR_DET_C = 0;
        bool wasResultTrue_MR_DET_C = false;
        int correct_results_MR_DET_C = 0;
        float results_in_percentage_MR_DET_C[40];
        unsigned long long avarage_MR_DET_C_time[40];

        //MillerRabinDet Python Values
        long int time_MR_DET_Python[repeats];
        unsigned long long sum_MR_DET_Python = 0;
        bool wasResultTrue_MR_DET_Python = false;
        int correct_results_MR_DET_Python = 0;
        float results_in_percentage_MR_DET_Python[40];
        unsigned long long avarage_MR_DET_Python_time[40];

        for (int i = 0; i < 40; i++) {

            vector<int> notPrimeNumber = test.Integer(exaplesNotPrime[i]);
            correct_results_MR_C = 0;
            correct_results_MR_Python = 0;
            correct_results_Fermat_C = 0;
            correct_results_Fermat_Python = 0;
            correct_results_MR_DET_C = 0;
            correct_results_MR_DET_Python = 0;


            //MILLER RABIN C++
            for (int j = 0; j < repeats; j++) {

                auto start = chrono::steady_clock::now();

                int s = test.findS(notPrimeNumber);
                vector<int> d = test.findD(notPrimeNumber, s);
                wasResultTrue_MR_C = test.checkPrime(repeats_inside_algo, s, d, notPrimeNumber);

                auto end = chrono::steady_clock::now();
                auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start).count();

                time_MR_C[j] = elapsed;

                if (!wasResultTrue_MR_C) {
                    correct_results_MR_C++;
                }

            }
            for (int k = 0; k < repeats; k++) {
                sum_MR_C += time_MR_C[k];
            }

            avarage_MR_C_time[i] = unsigned long long(sum_MR_C / repeats);
            //cout << "\n\nSREDNI CZAS WYNOSI: "<< avarage_MR_C_time[i] << endl;

            results_in_percentage_MR_C[i] = float(correct_results_MR_C)/repeats * 100;
            //cout << "Poprawnosc wynikow: " << results_in_percentage_MR_C[i] <<"%"<< endl;



            //MILLER RABIN Python
            for (int j = 0; j < repeats; j++) {

                auto start = chrono::steady_clock::now();

                wasResultTrue_MR_Python = callPythonMRFunction(exaplesNotPrime[i]);

                auto end = chrono::steady_clock::now();
                auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start).count();

                time_MR_Python[j] = elapsed;

                if (!wasResultTrue_MR_Python) {
                    correct_results_MR_Python++;
                }

            }
            for (int k = 0; k < repeats; k++) {
                sum_MR_Python += time_MR_Python[k];
            }
            avarage_MR_Python_time[i] = unsigned long long(sum_MR_Python / repeats);
            results_in_percentage_MR_Python[i] = float(correct_results_MR_Python) / repeats * 100;


             //Fermat C++
            for (int j = 0; j < repeats; j++) {

                auto start = chrono::steady_clock::now();

                wasResultTrue_Fermat_C = test.checkFermatPrime(repeats_inside_algo, notPrimeNumber);

                auto end = chrono::steady_clock::now();
                auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start).count();

                time_Fermat_C[j] = elapsed;

                if (!wasResultTrue_Fermat_C) {
                    correct_results_Fermat_C++;
                }

            }
            for (int k = 0; k < repeats; k++) {
                sum_Fermat_C += time_Fermat_C[k];
            }
            avarage_Fermat_C_time[i] = unsigned long long(sum_Fermat_C / repeats);  
            results_in_percentage_Fermat_C[i] = float(correct_results_Fermat_C) / repeats * 100;
     

            //FERMAT PYTHON
            for (int j = 0; j < repeats; j++) {

                auto start = chrono::steady_clock::now();

                wasResultTrue_Fermat_Python = callPythonFermatFunction(exaplesNotPrime[i]);

                auto end = chrono::steady_clock::now();
                auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start).count();

                time_Fermat_Python[j] = elapsed;

                if (!wasResultTrue_Fermat_Python) {
                    correct_results_Fermat_Python++;
                }

            }
            for (int k = 0; k < repeats; k++) {
                sum_Fermat_Python += time_Fermat_Python[k];
            }
            avarage_Fermat_Python_time[i] = unsigned long long(sum_Fermat_Python / repeats);
            results_in_percentage_Fermat_Python[i] = float(correct_results_Fermat_Python) / repeats * 100;




            //MILLER RABIN DETERMINISTIC C++
            for (int j = 0; j < repeats; j++) {

                auto start = chrono::steady_clock::now();

                int s = test.findS(notPrimeNumber);
                vector<int> d = test.findD(notPrimeNumber, s);
                wasResultTrue_MR_DET_C = test.checkDeterministicPrime(s, d, notPrimeNumber);

                auto end = chrono::steady_clock::now();
                auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start).count();

                time_MR_DET_C[j] = elapsed;

                if (!wasResultTrue_MR_DET_C) {
                    correct_results_MR_DET_C++;
                }

            }
            for (int k = 0; k < repeats; k++) {
                sum_MR_DET_C += time_MR_DET_C[k];
            }
            avarage_MR_DET_C_time[i] = unsigned long long(sum_MR_DET_C / repeats);
            results_in_percentage_MR_DET_C[i] = float(correct_results_MR_DET_C) / repeats * 100;




             //MILLER RABIN DET Python
            for (int j = 0; j < repeats; j++) {

                auto start = chrono::steady_clock::now();

                wasResultTrue_MR_DET_Python = callPythonMRDeterministicFunction(exaplesNotPrime[i]);

                auto end = chrono::steady_clock::now();
                auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start).count();

                time_MR_DET_Python[j] = elapsed;

                if (!wasResultTrue_MR_DET_Python) {
                    correct_results_MR_DET_Python++;
                }

            }
            for (int k = 0; k < repeats; k++) {
                sum_MR_DET_Python += time_MR_DET_Python[k];
            }
            avarage_MR_DET_Python_time[i] = unsigned long long(sum_MR_DET_Python / repeats);
            results_in_percentage_MR_DET_Python[i] = float(correct_results_MR_DET_Python) / repeats * 100;
     
          
            /*
            if (i == 0) 
                cout << "Len" << setw(20) << "MR(C) T[ms]" << setw(20) << "MR(C) %" << setw(20) << "MR(P) T[ms]" << setw(20) << "MR(P) %" << setw(20) << "F(C) T[ms]" << setw(20) << "F(C) %" << setw(20) << "F(P) T[ms]" << setw(20) << "F(P) %" << setw(20) << "MRD(C) T[ms]" << setw(20) << "MRD(C) %" << setw(20) << "MRD(P) T[ms]" << setw(20) << "MRD(P) %" << endl;
            cout << exaplesNotPrime[i].length() << setw(20)<< avarage_MR_C_time[i] << setw(20) << results_in_percentage_MR_C[i] << setw(20) << avarage_MR_Python_time[i] << setw(20) << results_in_percentage_MR_Python[i] << setw(20) << avarage_Fermat_C_time[i] << setw(20) << results_in_percentage_Fermat_C[i]<< setw(20) << avarage_Fermat_Python_time[i] << setw(20) << results_in_percentage_Fermat_Python[i]<< setw(20) << avarage_MR_DET_C_time[i] << setw(20) << results_in_percentage_MR_DET_C[i] << setw(20) << avarage_MR_DET_Python_time[i] << setw(20) << results_in_percentage_MR_DET_Python[i]<<endl;
            */

            if (i == 0)
                cout << "Len" << ";" << "MR(C) T[ms]" << ";" << "MR(C) %" << ";" << "MR(P) T[ms]" << ";" << "MR(P) %" << ";" << "F(C) T[ms]" << ";" << "F(C) %" << ";" << "F(P) T[ms]" << ";" << "F(P) %" << ";" << "MRD(C) T[ms]" << ";" << "MRD(C) %" << ";" << "MRD(P) T[ms]" << ";" << "MRD(P) %" << endl;
            cout << exaplesNotPrime[i].length() << ";" << avarage_MR_C_time[i] << ";" << results_in_percentage_MR_C[i] << ";" << avarage_MR_Python_time[i] << ";" << results_in_percentage_MR_Python[i] << ";" << avarage_Fermat_C_time[i] << ";" << results_in_percentage_Fermat_C[i] << ";" << avarage_Fermat_Python_time[i] << ";" << results_in_percentage_Fermat_Python[i] << ";" << avarage_MR_DET_C_time[i] << ";" << results_in_percentage_MR_DET_C[i] << ";" << avarage_MR_DET_Python_time[i] << ";" << results_in_percentage_MR_DET_Python[i] << endl;


            

         
      

        }
        
    }
   // mode = 2;
    //cout << "\n\nTEST FOR PRIMARY NUMBERS\n" << endl;
    if (mode == 2) {


        //MillerRabin C++ Values
        long int time_MR_C[repeats];
        unsigned long long sum_MR_C = 0;
        bool wasResultTrue_MR_C = false;
        int correct_results_MR_C = 0;
        float results_in_percentage_MR_C[40];
        unsigned long long avarage_MR_C_time[40];

        //MillerRabin Python Values
        long int time_MR_Python[repeats];
        unsigned long long sum_MR_Python = 0;
        bool wasResultTrue_MR_Python = false;
        int correct_results_MR_Python = 0;
        float results_in_percentage_MR_Python[40];
        unsigned long long avarage_MR_Python_time[40];

        //Fermat C++ Values
        long int time_Fermat_C[repeats];
        unsigned long long sum_Fermat_C = 0;
        bool wasResultTrue_Fermat_C = false;
        int correct_results_Fermat_C = 0;
        float results_in_percentage_Fermat_C[40];
        unsigned long long avarage_Fermat_C_time[40];

        //Fermat Python Values
        long int time_Fermat_Python[repeats];
        unsigned long long sum_Fermat_Python = 0;
        bool wasResultTrue_Fermat_Python = false;
        int correct_results_Fermat_Python = 0;
        float results_in_percentage_Fermat_Python[40];
        unsigned long long avarage_Fermat_Python_time[40];

        //MillerRabinDet c++ Values
        long int time_MR_DET_C[repeats];
        unsigned long long sum_MR_DET_C = 0;
        bool wasResultTrue_MR_DET_C = false;
        int correct_results_MR_DET_C = 0;
        float results_in_percentage_MR_DET_C[40];
        unsigned long long avarage_MR_DET_C_time[40];

        //MillerRabinDet Python Values
        long int time_MR_DET_Python[repeats];
        unsigned long long sum_MR_DET_Python = 0;
        bool wasResultTrue_MR_DET_Python = false;
        int correct_results_MR_DET_Python = 0;
        float results_in_percentage_MR_DET_Python[40];
        unsigned long long avarage_MR_DET_Python_time[40];

        for (int i = 0; i < 40; i++) {
            vector<int> primeNumber = test.Integer(examplesPrime[i]);
            
            correct_results_MR_C = 0;
            correct_results_MR_Python = 0;
            correct_results_Fermat_C = 0;
            correct_results_Fermat_Python = 0;
            correct_results_MR_DET_C = 0;
            correct_results_MR_DET_Python = 0;


            //MILLER RABIN C++
            for (int j = 0; j < repeats; j++) {

                auto start = chrono::steady_clock::now();

                int s = test.findS(primeNumber);
                vector<int> d = test.findD(primeNumber, s);
                wasResultTrue_MR_C = test.checkPrime(repeats_inside_algo, s, d, primeNumber);

                auto end = chrono::steady_clock::now();
                auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start).count();

                time_MR_C[j] = elapsed;

                if (wasResultTrue_MR_C) {
                    correct_results_MR_C++;
                }

            }
            for (int k = 0; k < repeats; k++) {
                sum_MR_C += time_MR_C[k];
            }

            avarage_MR_C_time[i] = unsigned long long(sum_MR_C / repeats);
            results_in_percentage_MR_C[i] = float(correct_results_MR_C) / repeats * 100;


            //MILLER RABIN Python
            for (int j = 0; j < repeats; j++) {

                auto start = chrono::steady_clock::now();

                wasResultTrue_MR_Python = callPythonMRFunction(examplesPrime[i]);

                auto end = chrono::steady_clock::now();
                auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start).count();

                time_MR_Python[j] = elapsed;

                if (wasResultTrue_MR_Python) {
                    correct_results_MR_Python++;
                }

            }
            for (int k = 0; k < repeats; k++) {
                sum_MR_Python += time_MR_Python[k];
            }
            avarage_MR_Python_time[i] = unsigned long long(sum_MR_Python / repeats);
            results_in_percentage_MR_Python[i] = float(correct_results_MR_Python) / repeats * 100;


            //Fermat C++
            for (int j = 0; j < repeats; j++) {

                auto start = chrono::steady_clock::now();

                wasResultTrue_Fermat_C = test.checkFermatPrime(repeats_inside_algo, primeNumber);

                auto end = chrono::steady_clock::now();
                auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start).count();

                time_Fermat_C[j] = elapsed;

                if (wasResultTrue_Fermat_C) {
                    correct_results_Fermat_C++;
                }

            }
            for (int k = 0; k < repeats; k++) {
                sum_Fermat_C += time_Fermat_C[k];
            }
            avarage_Fermat_C_time[i] = unsigned long long(sum_Fermat_C / repeats);
            results_in_percentage_Fermat_C[i] = float(correct_results_Fermat_C) / repeats * 100;


            //FERMAT PYTHON
            for (int j = 0; j < repeats; j++) {

                auto start = chrono::steady_clock::now();

                wasResultTrue_Fermat_Python = callPythonFermatFunction(examplesPrime[i]);

                auto end = chrono::steady_clock::now();
                auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start).count();

                time_Fermat_Python[j] = elapsed;

                if (wasResultTrue_Fermat_Python) {
                    correct_results_Fermat_Python++;
                }

            }
            for (int k = 0; k < repeats; k++) {
                sum_Fermat_Python += time_Fermat_Python[k];
            }
            avarage_Fermat_Python_time[i] = unsigned long long(sum_Fermat_Python / repeats);
            results_in_percentage_Fermat_Python[i] = float(correct_results_Fermat_Python) / repeats * 100;




            //MILLER RABIN DETERMINISTIC C++
            for (int j = 0; j < repeats; j++) {

                auto start = chrono::steady_clock::now();

                int s = test.findS(primeNumber);
                vector<int> d = test.findD(primeNumber, s);
                wasResultTrue_MR_DET_C = test.checkDeterministicPrime(s, d, primeNumber);

                auto end = chrono::steady_clock::now();
                auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start).count();

                time_MR_DET_C[j] = elapsed;

                if (wasResultTrue_MR_DET_C) {
                    correct_results_MR_DET_C++;
                }

            }
            for (int k = 0; k < repeats; k++) {
                sum_MR_DET_C += time_MR_DET_C[k];
            }
            avarage_MR_DET_C_time[i] = unsigned long long(sum_MR_DET_C / repeats);
            results_in_percentage_MR_DET_C[i] = float(correct_results_MR_DET_C) / repeats * 100;




            //MILLER RABIN DET Python
            for (int j = 0; j < repeats; j++) {

                auto start = chrono::steady_clock::now();

                wasResultTrue_MR_DET_Python = callPythonMRDeterministicFunction(examplesPrime[i]);

                auto end = chrono::steady_clock::now();
                auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start).count();

                time_MR_DET_Python[j] = elapsed;

                if (wasResultTrue_MR_DET_Python) {
                    correct_results_MR_DET_Python++;
                }

            }
            for (int k = 0; k < repeats; k++) {
                sum_MR_DET_Python += time_MR_DET_Python[k];
            }
            avarage_MR_DET_Python_time[i] = unsigned long long(sum_MR_DET_Python / repeats);
            results_in_percentage_MR_DET_Python[i] = float(correct_results_MR_DET_Python) / repeats * 100;


        /*
           if (i == 0)
                cout << "Len" << setw(20) << "MR(C) T[ms]" << setw(20) << "MR(C) %" << setw(20) << "MR(P) T[ms]" << setw(20) << "MR(P) %" << setw(20) << "F(C) T[ms]" << setw(20) << "F(C) %" << setw(20) << "F(P) T[ms]" << setw(20) << "F(P) %" << setw(20) << "MRD(C) T[ms]" << setw(20) << "MRD(C) %" << setw(20) << "MRD(P) T[ms]" << setw(20) << "MRD(P) %" << endl;
            cout << exaplesNotPrime[i].length() << setw(20) << avarage_MR_C_time[i] << setw(20) << results_in_percentage_MR_C[i] << setw(20) << avarage_MR_Python_time[i] << setw(20) << results_in_percentage_MR_Python[i] << setw(20) << avarage_Fermat_C_time[i] << setw(20) << results_in_percentage_Fermat_C[i] << setw(20) << avarage_Fermat_Python_time[i] << setw(20) << results_in_percentage_Fermat_Python[i] << setw(20) << avarage_MR_DET_C_time[i] << setw(20) << results_in_percentage_MR_DET_C[i] << setw(20) << avarage_MR_DET_Python_time[i] << setw(20) << results_in_percentage_MR_DET_Python[i] << endl;
       */
            if (i == 0)
                cout << "Len" << ";" << "MR(C) T[ms]" << ";" << "MR(C) %" << ";" << "MR(P) T[ms]" << ";" << "MR(P) %" << ";" << "F(C) T[ms]" << ";" << "F(C) %" << ";" << "F(P) T[ms]" << ";" << "F(P) %" << ";" << "MRD(C) T[ms]" << ";" << "MRD(C) %" << ";" << "MRD(P) T[ms]" << ";" << "MRD(P) %" << endl;
            cout << exaplesNotPrime[i].length() << ";" << avarage_MR_C_time[i] << ";" << results_in_percentage_MR_C[i] << ";" << avarage_MR_Python_time[i] << ";" << results_in_percentage_MR_Python[i] << ";" << avarage_Fermat_C_time[i] << ";" << results_in_percentage_Fermat_C[i] << ";" << avarage_Fermat_Python_time[i] << ";" << results_in_percentage_Fermat_Python[i] << ";" << avarage_MR_DET_C_time[i] << ";" << results_in_percentage_MR_DET_C[i] << ";" << avarage_MR_DET_Python_time[i] << ";" << results_in_percentage_MR_DET_Python[i] << endl;
            
            
        }
        
        
    }
    //mode = 3;
    cout << "\n\nTEST FOR MIXED NUMBERS\n" << endl;
    if (mode == 3) {
        //MillerRabin C++ Values
        long int time_MR_C[repeats];
        unsigned long long sum_MR_C = 0;
        bool wasResultTrue_MR_C = false;
        int correct_results_MR_C = 0;
        float results_in_percentage_MR_C[40];
        unsigned long long avarage_MR_C_time[40];

        //MillerRabin Python Values
        long int time_MR_Python[repeats];
        unsigned long long sum_MR_Python = 0;
        bool wasResultTrue_MR_Python = false;
        int correct_results_MR_Python = 0;
        float results_in_percentage_MR_Python[40];
        unsigned long long avarage_MR_Python_time[40];

        //Fermat C++ Values
        long int time_Fermat_C[repeats];
        unsigned long long sum_Fermat_C = 0;
        bool wasResultTrue_Fermat_C = false;
        int correct_results_Fermat_C = 0;
        float results_in_percentage_Fermat_C[40];
        unsigned long long avarage_Fermat_C_time[40];

        //Fermat Python Values
        long int time_Fermat_Python[repeats];
        unsigned long long sum_Fermat_Python = 0;
        bool wasResultTrue_Fermat_Python = false;
        int correct_results_Fermat_Python = 0;
        float results_in_percentage_Fermat_Python[40];
        unsigned long long avarage_Fermat_Python_time[40];

        //MillerRabinDet c++ Values
        long int time_MR_DET_C[repeats];
        unsigned long long sum_MR_DET_C = 0;
        bool wasResultTrue_MR_DET_C = false;
        int correct_results_MR_DET_C = 0;
        float results_in_percentage_MR_DET_C[40];
        unsigned long long avarage_MR_DET_C_time[40];

        //MillerRabinDet Python Values
        long int time_MR_DET_Python[repeats];
        unsigned long long sum_MR_DET_Python = 0;
        bool wasResultTrue_MR_DET_Python = false;
        int correct_results_MR_DET_Python = 0;
        float results_in_percentage_MR_DET_Python[40];
        unsigned long long avarage_MR_DET_Python_time[40];

        for (int i = 0; i < 40; i++) {
            vector<int> mixedNumber = test.Integer(exampleMixed[i]);

            correct_results_MR_C = 0;
            correct_results_MR_Python = 0;
            correct_results_Fermat_C = 0;
            correct_results_Fermat_Python = 0;
            correct_results_MR_DET_C = 0;
            correct_results_MR_DET_Python = 0;


            //MILLER RABIN C++
            for (int j = 0; j < repeats; j++) {

                auto start = chrono::steady_clock::now();

                int s = test.findS(mixedNumber);
                vector<int> d = test.findD(mixedNumber, s);
                wasResultTrue_MR_C = test.checkPrime(repeats_inside_algo, s, d, mixedNumber);

                auto end = chrono::steady_clock::now();
                auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start).count();

                time_MR_C[j] = elapsed;

                if (wasResultTrue_MR_C) {
                    correct_results_MR_C++;
                }

            }
            for (int k = 0; k < repeats; k++) {
                sum_MR_C += time_MR_C[k];
            }

            avarage_MR_C_time[i] = unsigned long long(sum_MR_C / repeats);
            results_in_percentage_MR_C[i] = float(correct_results_MR_C) / repeats * 100;


            //MILLER RABIN Python
            for (int j = 0; j < repeats; j++) {

                auto start = chrono::steady_clock::now();

                wasResultTrue_MR_Python = callPythonMRFunction(exampleMixed[i]);

                auto end = chrono::steady_clock::now();
                auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start).count();

                time_MR_Python[j] = elapsed;

                if (wasResultTrue_MR_Python) {
                    correct_results_MR_Python++;
                }

            }
            for (int k = 0; k < repeats; k++) {
                sum_MR_Python += time_MR_Python[k];
            }
            avarage_MR_Python_time[i] = unsigned long long(sum_MR_Python / repeats);
            results_in_percentage_MR_Python[i] = float(correct_results_MR_Python) / repeats * 100;


            //Fermat C++
            for (int j = 0; j < repeats; j++) {

                auto start = chrono::steady_clock::now();

                wasResultTrue_Fermat_C = test.checkFermatPrime(repeats_inside_algo, mixedNumber);

                auto end = chrono::steady_clock::now();
                auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start).count();

                time_Fermat_C[j] = elapsed;

                if (wasResultTrue_Fermat_C) {
                    correct_results_Fermat_C++;
                }

            }
            for (int k = 0; k < repeats; k++) {
                sum_Fermat_C += time_Fermat_C[k];
            }
            avarage_Fermat_C_time[i] = unsigned long long(sum_Fermat_C / repeats);
            results_in_percentage_Fermat_C[i] = float(correct_results_Fermat_C) / repeats * 100;


            //FERMAT PYTHON
            for (int j = 0; j < repeats; j++) {

                auto start = chrono::steady_clock::now();

                wasResultTrue_Fermat_Python = callPythonFermatFunction(exampleMixed[i]);

                auto end = chrono::steady_clock::now();
                auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start).count();

                time_Fermat_Python[j] = elapsed;

                if (wasResultTrue_Fermat_Python) {
                    correct_results_Fermat_Python++;
                }

            }
            for (int k = 0; k < repeats; k++) {
                sum_Fermat_Python += time_Fermat_Python[k];
            }
            avarage_Fermat_Python_time[i] = unsigned long long(sum_Fermat_Python / repeats);
            results_in_percentage_Fermat_Python[i] = float(correct_results_Fermat_Python) / repeats * 100;




            //MILLER RABIN DETERMINISTIC C++
            for (int j = 0; j < repeats; j++) {

                auto start = chrono::steady_clock::now();

                int s = test.findS(mixedNumber);
                vector<int> d = test.findD(mixedNumber, s);
                wasResultTrue_MR_DET_C = test.checkDeterministicPrime(s, d, mixedNumber);

                auto end = chrono::steady_clock::now();
                auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start).count();

                time_MR_DET_C[j] = elapsed;

                if (wasResultTrue_MR_DET_C) {
                    correct_results_MR_DET_C++;
                }

            }
            for (int k = 0; k < repeats; k++) {
                sum_MR_DET_C += time_MR_DET_C[k];
            }
            avarage_MR_DET_C_time[i] = unsigned long long(sum_MR_DET_C / repeats);
            results_in_percentage_MR_DET_C[i] = float(correct_results_MR_DET_C) / repeats * 100;

            


            //MILLER RABIN DET Python
            for (int j = 0; j < repeats; j++) {

                auto start = chrono::steady_clock::now();

                wasResultTrue_MR_DET_Python = callPythonMRDeterministicFunction(exampleMixed[i]);

                auto end = chrono::steady_clock::now();
                auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start).count();

                time_MR_DET_Python[j] = elapsed;

                if (wasResultTrue_MR_DET_Python) {
                    correct_results_MR_DET_Python++;
                }

            }
            for (int k = 0; k < repeats; k++) {
                sum_MR_DET_Python += time_MR_DET_Python[k];
            }
            avarage_MR_DET_Python_time[i] = unsigned long long(sum_MR_DET_Python / repeats);
            results_in_percentage_MR_DET_Python[i] = float(correct_results_MR_DET_Python) / repeats * 100;


           
            if (i == 0)
                cout << "Len" << setw(20) << "MR(C) T[ms]" << setw(20) << "MR(C) %" << setw(20) << "MR(P) T[ms]" << setw(20) << "MR(P) %" << setw(20) << "F(C) T[ms]" << setw(20) << "F(C) %" << setw(20) << "F(P) T[ms]" << setw(20) << "F(P) %" << setw(20) << "MRD(C) T[ms]" << setw(20) << "MRD(C) %" << setw(20) << "MRD(P) T[ms]" << setw(20) << "MRD(P) %" << endl;
            cout << exaplesNotPrime[i].length() << setw(20) << avarage_MR_C_time[i] << setw(20) << results_in_percentage_MR_C[i] << setw(20) << avarage_MR_Python_time[i] << setw(20) << results_in_percentage_MR_Python[i] << setw(20) << avarage_Fermat_C_time[i] << setw(20) << results_in_percentage_Fermat_C[i] << setw(20) << avarage_Fermat_Python_time[i] << setw(20) << results_in_percentage_Fermat_Python[i] << setw(20) << avarage_MR_DET_C_time[i] << setw(20) << results_in_percentage_MR_DET_C[i] << setw(20) << avarage_MR_DET_Python_time[i] << setw(20) << results_in_percentage_MR_DET_Python[i] << endl;
        /*
            if (i == 0)
                cout << "Len" << ";" << "MR(C) T[ms]" << ";" << "MR(C) %" << ";" << "MR(P) T[ms]" << ";" << "MR(P) %" << ";" << "F(C) T[ms]" << ";" << "F(C) %" << ";" << "F(P) T[ms]" << ";" << "F(P) %" << ";" << "MRD(C) T[ms]" << ";" << "MRD(C) %" << ";" << "MRD(P) T[ms]" << ";" << "MRD(P) %" << endl;
            cout << exaplesNotPrime[i].length() << ";" << avarage_MR_C_time[i] << ";" << results_in_percentage_MR_C[i] << ";" << avarage_MR_Python_time[i] << ";" << results_in_percentage_MR_Python[i] << ";" << avarage_Fermat_C_time[i] << ";" << results_in_percentage_Fermat_C[i] << ";" << avarage_Fermat_Python_time[i] << ";" << results_in_percentage_Fermat_Python[i] << ";" << avarage_MR_DET_C_time[i] << ";" << results_in_percentage_MR_DET_C[i] << ";" << avarage_MR_DET_Python_time[i] << ";" << results_in_percentage_MR_DET_Python[i] << endl;
            */

        }
    }


}


int main(){

    menu();
   
    //test_timeMeasuring();

    return 0;
}