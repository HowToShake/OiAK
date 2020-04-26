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

using namespace std;

struct BigInt {

    int size = 9;
    int base = (int)pow(10, size);

    vector<int> ZERO = Integer("0");
    vector<int> ONE = Integer("1");
    vector<int> TWO = Integer("2");

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

    vector<int> multiplyAFTER(vector<int>num1, vector<int>num2) {

        vector<int>zero = Integer("0");
        vector<int>one = Integer("1");

        if (compareEqual(num1, zero) || compareEqual(num2, zero)) {
            return zero;
        }
        if (compareEqual(num1, one)) {
            return num2;
        }
        if (compareEqual(num2, one)) {
            return num1;
        }



        int len1 = num1.size();
        int len2 = num2.size();

        vector<unsigned long long>result(len1 + len2, 0);

        int i_n1 = 0;
        int i_n2 = 0;

        for (int i = len1 - 1; i >= 0; i--) {
            unsigned long long carry = 0;
            unsigned long long n1 = num1[i];

            i_n2 = 0;

            for (int j = len2 - 1; j >= 0; j--) {
                unsigned long long n2 = num2[j];
                //cout << "DZIALAM" << i << endl;
                unsigned long long sum = n1 * n2 + result[i_n1 + i_n2] + carry;
                //cout << "DZIALAMxD" << i << endl;
                carry = sum / base;
                result[i_n1 + i_n2] = sum % base;

                i_n2++;

            }

            if (carry > 0) {
                result[i_n1 + i_n2] += carry;
            }

            i_n1++;

        }

        int i = result.size() - 1;
        while (i >= 0 && result[i] == 0)
            i--;

        string s = "";
        while (i >= 0)
            s += to_string(result[i--]);



        return Integer(s);
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
            if (compareEqual(num1Copy, ZERO) || compareEqual(num2Copy, ZERO)) {
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

            int a = rand() % 2000 + 1;
            //int a = 161;
            string A = to_string(a);
            //printVector(powerFastModulo(Integer(A), d, mod));
            if (!compareEqual(powerFastModulo(Integer(A), d, mod), one)) {


                for (int r = 0; r <= s; r++) {

                    vector<int>temporary = multiply(Integer(to_string(int(pow(2, r)))), d);
                    //printVector(temporary);
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

    vector<int> powerL(vector<int>num1, vector<int>num2, vector<int>mod) {
        vector<int> result = Integer("1");
        vector<int>zero = Integer("0");

        while (!compareEqual(num2, zero)) {

            if (num2[num2.size() - 1] % 2) {

                vector<int>mnoz = multiply(result, num1);
                result = modulo(mnoz, mod);

            }

            num2 = divide(num2, Integer("2"));
            num1 = modulo(multiply(num1, num1), mod);
        }
        return result;
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
            /*         cout << "\nPRZED X " << endl;
                     printVector(b);*/
                     //cout << "\n\n\n";
                     //printVector(b);
                     //cout << "\n\n\n";
            if (b[b.size() - 1] % 2 == 1) {
                //cout << "\nCOUNTER: " << counter<<endl;
                /*cout << "\nX " << endl;
                printVector(x);
                cout << "\nPRZED MNOZENIEM ";
                printVector(result);*/

                result = multiply(result, x);

                //cout << "\nPRZED MODULO ";
                //printVector(result);

                result = modulo(result, n);

                /*cout << "\nPO MODULO ";*/
                //printVector(result);

            }

            x = multiply(x, x);
            x = modulo(x, n);
            bCopy = divide(b, TWO);

            if (compareEqual(b, ZERO)) {
                additional = true;
            }

            counter++;
        } while (!compareGreater(ONE, bCopy));
        //cout << "\nMAIN COUNTER: " << counter<<endl;

        return result;
    }

    bool checkFermatPrime(int repeats, vector<int> num1) {
        vector<int> num1Decrement = substract(num1, ONE);
        for (int i = 0; i < repeats; i++) {
            int random = rand() % 5000 + 1;
            cout << "Random " << random << endl;
            if (compareEqual(powerFastModulo(Integer(to_string(random)), num1Decrement, num1), ONE)) {
                continue;
            }
            else {
                return false;
            }
        }
        return true;

    }

};

void test_timeMeasuring() {
    string przykladowe1[20] = { "5", "11", "439", "5987", "10247", "447849", "1234576", "84268541", "231576012", "1943678051", "63728958371", "917384758362", "8176284653218", "73640907618263", "836283651841090", "1234567891012134", "19587634582012307", "946305876310824657", "9584630125078946308", "16345203607948613527" };
    string przykladowe2[20] = { "8", "37", "128", "9876", "19584", "189441", "6585945", "19814194", "783429656", "9127654328", "92873456123", "543246264621", "1235312456123", "98723465972842", "189165419815466", "8298375690832412", "89723465879324659", "494916524900512351", "4293846985231563652", "65234619654524676521" };
    string przykladoMod[20] = { "4", "15", "123", "1235", "12521", "972351", "1289756", "87543876", "873245612", "8943521672", "89732456934", "987324687213", "9872346754286", "56814984890554", "687524752643893", "6728367859126582", "89012506782380591", "891265112895278106", "1281275381259625112", "12890759812579081201" };
    string jeden = "198265981267598236759236590832659812659821198265981267598236759236590832659812659821659821659803256980239823581956892350981298123692639623986129859286920119826598126759823675923659083265981265982165982165980325698023982358195689235098129812369263962398612985928692011982659812675982367592365908326598126598216598216598032569802398235819568923509812981236926396239861298592869201198265981267598236759236590832659812659821659821659803256980239823581956892350981298123692639623986129859286920119826598126759823675923659083265981265982165982165980325698023982358195689235098129812369263962398612985928692011982659812675982367592365908326598126598216598216598032569802398235819568923509812981236926396239861298592869201198265981267598236759236590832659812659821659821659803256980239823581956892350981298123692639623986129859286920119826598126759823675923659083265981265982165982165980325698023982358195689235098129812369263962398612985928692011982659812675982367592365908326598126598216598216598032569802398235819568923509812981236926396239861298592869201198265981267598236759236590832659812659821659821659803256980239823581956892350981298123692639623986129859286920119826598126759823675923659083265981265982165982165980325698023982358195689235098129812369263962398612985928692011982659812675982367592365908326598126598216598216598032569802398235819568923509812981236926396239861298592869201198265981267598236759236590832659812659821659821659803256980239823581956892350981298123692639623986129859286920119826598126759823675923659083265981265982165982165980325698023982358195689235098129812369263962398612985928692011982659812675982367592365908326598126598216598216598032569802398235819568923509812981236926396239861298592869201198265981267598236759236590832659812659821659821659803256980239823581956892350981298123692639623986129859286920119826598126759823675923659083265981265982165982165980325698023982358195689235098129812369263962398612985928692011982659812675982367592365908326598126598216598216598032569802398235819568923509812981236926396239861298592869201198265981267598236759236590832659812659821659821659803256980239823581956892350981298123692639623986129859286920119826598126759823675923659083265981265982165982165980325698023982358195689235098129812369263962398612985928692011982659812675982367592365908326598126598216598216598032569802398235819568923509812981236926396239861298592869201198265981267598236759236590832659812659821659821659803256980239823581956892350981298123692639623986129859286920119826598126759823675923659083265981265982165982165980325698023982358195689235098129812369263962398612985928692011982659812675982367592365908326598126598216598216598032569802398235819568923509812981236926396239861298592869201198265981267598236759236590832659812659821659821659803256980239823581956892350981298123692639623986129859286920119826598126759823675923659083265981265982165982165980325698023982358195689235098129812369263962398612985928692016598216598032569802398235819568923509812981236926396239861298592869201";
    string dwa = "1109857649086573675903876590481982659812675982367592365908326598126598211982659812675982367592365908326598126598216598216598032569802398235819568923509812981236926396239861298592869201198265981267598236759236590832659812659821659821659803256980239823581956892350981298123692639623986129859286920119826598126759823675923659083265981265982165982165980325698023982358195689235098129812369263962398612985928692011982659812675982367592365908326598126598216598216598032569802398235819568923509812981236926396239861298592869201198265981267598236759236590832659812659821659821659803256980239823581956892350981298123692639623986129859286920119826598126759823675923659083265981265982165982165980325698023982358195689235098129812369263962398612985928692011982659812675982367592365908326598126598216598216598032569802398235819568923509812981236926396239861298592869201198265981267598236759236590832659812659821659821659803256980239823581956892350981298123692639623986129859286920119826598126759823675923659083265981265982165982165980325698023982358195689235098129812369263962398612985928692011982659812675982367592365908326598126598216598216598032569802398235819568923509812981236926396239861298592869201198265981267598236759236590832659812659821659821659803256980239823581956892350981298123692639623986129859286920119826598126759823675923659083265981265982165982165980325698023982358195689235098129812369263962398612985928692011982659812675982367592365908326598126598216598216598032569802398235819568923509812981236926396239861298592869201198265981267598236759236590832659812659821659821659803256980239823581956892350981298123692639623986129859286920119826598126759823675923659083265981265982165982165980325698023982358195689235098129812369263962398612985928692011982659812675982367592365908326598126598216598216598032569802398235819568923509812981236926396239861298592869201198265981267598236759236590832659812659821659821659803256980239823581956892350981298123692639623986129859286920119826598126759823675923659083265981265982165982165980325698023982358195689235098129812369263962398612985928692011982659812675982367592365908326598126598216598216598032569802398235819568923509812981236926396239861298592869201198265981267598236759236590832659812659821659821659803256980239823581956892350981298123692639623986129859286920119826598126759823675923659083265981265982165982165980325698023982358195689235098129812369263962398612985928692011982659812675982367592365908326598126598216598216598032569802398235819568923509812981236926396239861298592869201198265981267598236759236590832659812659821659821659803256980239823581956892350981298123692639623986129859286920119826598126759823675923659083265981265982165982165980325698023982358195689235098129812369263962398612985928692011982659812675982367592365908326598126598216598216598032569802398235819568923509812981236926396239861298592869201198265981267598236759236590832659812659821659821659803256980239823581956892350981298123692639623986129859286920165982165980325698023982358195689235098129812369263962398612985928692011675309752130957239805671089679018657903769083476590123765981769347690476092096538";
    vector<int> bufor1;
    vector<int> bufor2;
    vector<int> bufor3;
    BigInt test = BigInt();

    const int ilosc_powtorzen = 1;

    long int czas[ilosc_powtorzen];
    unsigned long long suma = 0;

    for (int i = 0; i < 20; i++) {
        bufor1 = test.Integer(przykladowe1[i]);
        bufor2 = test.Integer(przykladowe2[i]);
        bufor3 = test.Integer(przykladoMod[i]);
        vector<int>vecJeden = test.Integer(jeden);
        vector<int>vecDwa = test.Integer(dwa);

        for (int j = 0; j < ilosc_powtorzen; j++) {

            //int s = test.findS(bufor1);
            //vector<int> d = test.findD(bufor1, s);

            auto start = chrono::steady_clock::now();

            //test.checkPrime(10, s, d, bufor1);
            test.printVector(test.substract(bufor1, bufor2));
            auto end = chrono::steady_clock::now();

            auto elapsed = chrono::duration_cast<chrono::microseconds>(end - start).count();
            czas[j] = elapsed;
        }


        cout << "SREDNI CZAS WYNOSI: ";
        for (int k = 0; k < ilosc_powtorzen; k++) {
            suma += czas[k];
        }
        cout << unsigned long long(suma / ilosc_powtorzen) << endl;

    }


}

void callPythonAKSFunction(string input1) {
    //cout << "Otrzymana liczba do Pythona: " << input1 << endl;

    Py_Initialize();

    PyObject* pModule = PyImport_ImportModule("AKS");
    PyObject* pValue;


    if (pModule) {
        PyObject* pFunc = PyObject_GetAttrString(pModule, "Aks");



        if (pFunc && PyCallable_Check(pFunc)) {

            pValue = PyObject_CallFunction(pFunc, "s", input1.c_str());
            //pValue = PyObject_CallFunction(pFunc,NULL);
        }
        else {
            cout << "ERROR: FUNCTION HEJKA()" << endl;
        }

    }
    else {
        cout << "ERROR: MODULE NOT IMPORTED" << endl;
    }

    Py_Finalize();
}

void callPythonMRFunction(string input1) {
    //cout << "Otrzymana liczba do Pythona: " << input1 << endl;

    Py_Initialize();

    PyObject* pModule = PyImport_ImportModule("Miller-Rabin");
    PyObject* pValue;


    if (pModule) {
        PyObject* pFunc = PyObject_GetAttrString(pModule, "MillerRabin");



        if (pFunc && PyCallable_Check(pFunc)) {

            pValue = PyObject_CallFunction(pFunc, "s", input1.c_str());
            //pValue = PyObject_CallFunction(pFunc,NULL);
        }
        else {
            cout << "ERROR: FUNCTION HEJKA()" << endl;
        }

    }
    else {
        cout << "ERROR: MODULE NOT IMPORTED" << endl;
    }

    Py_Finalize();
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
    while (program) {
        cout << "Podaj liczbe do przeprowadzenia testu pierwszosci: " << endl;
        cin >> input;
        x.num1 = x.Integer(input);

        if (x.compareEqual(x.modulo(x.num1, x.TWO), x.ZERO)) {
            cout << "\nPodana liczba musi byc nieparzysta!" << endl;

        }
        else {

            cout << "\nDostepne opcje: " << endl;
            cout << "0. - Wyjscie z programu." << endl;
            cout << "1. - Test pierwszosci Fermata (C++)." << endl;
            cout << "2. - Test pierwszosci Millera-Rabina (C++)." << endl;
            cout << "3. - Test pierwszosci Millera-Rabina (Python)." << endl;
            cout << "4. - Test pierwszosci Millera-Rabina w wersji deterministycznej (C++)." << endl;
            cout << "5. - Test pierwszosci AKS (Python)." << endl;
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
                int s = x.findS(x.num1);
                vector<int> d = x.findD(x.num1, s);

                bool isMillerRabinPrime = x.checkPrime(10, s, d, x.num1);
                printMessageIsPrime(isMillerRabinPrime);
                break;
            }
            case 3: {
                callPythonMRFunction(input);
                break;
            }
            case 4: {
                x.prepareValuesForMRAlgo(input);
                int s = x.findS(x.num1);
                vector<int> d = x.findD(x.num1, s);

                bool isDeterministicMRPrime = x.checkDeterministicPrime(s, d, x.num1);
                printMessageIsPrime(isDeterministicMRPrime);
                break;
            }
            case 5: {
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
            //
        }
        else {
            program = false;
        }

    }


}

int main() {

    menu();

    return 0;
}