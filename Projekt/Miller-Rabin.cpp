#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <string>
#include <random>
#include <iterator>
#include <sstream>


using namespace std;



struct BigInt {

    int size = 9;

    vector<int> num1;
    vector<int> num2;
    vector<int> result;

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

            if (temp / pow(10, size) > 0) {
                carry = temp / pow(10, size);
                temp = temp % int(pow(10, size));
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

                if (temp / pow(10, size) > 0) {
                    carry = temp / pow(10, size);
                    temp = temp % int(pow(10, size));
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
                    temp = temp + int(pow(10, size));

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
                        temp = temp + int(pow(10, size));
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

        vector<int>zero = Integer("0");
        vector<int>one = Integer("1");

        if (compareEqual(num1V, zero) || compareEqual(num2V, zero)) {
            return zero;
        }
        if (compareEqual(num1V, one)) {
            return num2V;
        }
        if (compareEqual(num2V, one)) {
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
        if (compareEqual(num1, Integer("0"))) {
            return Integer("0");
        }

        if (compareEqual(num2, Integer("1"))) {
            return num1;
        }
        if (num1.size() == 1 && num2.size() == 1) {
            return Integer(to_string(num1[0] / num2[0]));
        }
        vector<int> num1Copy = num1;
        vector<int> num2Copy = num2;

        if (compareEqual(num2, Integer("0"))) {
            return num2;
        }

        while (compareGreater(num1Copy, num2Copy)) {
            num2Copy = transferNumberLeft(num2Copy);
            counter++;
        }

        num2Copy = transferNumberRight(num2Copy);

        if (compareEqual(num2Copy, num1Copy)) {
            return Integer("1");
        }


        string temp = "";


        while (counter > 0) {
            int times = 0;
            if (compareEqual(num1Copy, vector<int>(1, 0)) || compareEqual(num2Copy, vector<int>(1, 0))) {
                for (int i = counter; i >= 0; i--) {
                    temp += '0';
                    return Integer(temp);
                }
            }

            while (compareGreater(num1Copy, num2Copy) || compareEqual(num1Copy, num2Copy)) {
                num1Copy = substract(num1Copy, num2Copy);
                times++;
            }
            temp += to_string(times);
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

        vector<int>one = Integer("1");
        vector<int>zero = Integer("0");



        if (compareEqual(num2, one)) {
            return zero;
        }

        if (compareEqual(num1, zero)) {
            return zero;
        }
        if (compareEqual(num2, zero)) {
            return num1;
        }
        if (compareEqual(num1, num2)) {
            return zero;
        }

        if (compareEqual(num2, one)) {
            return zero;
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

        num2Copy = transferNumberRight(num2Copy);

        if (compareEqual(num2Copy, num1Copy)) {
            return zero;
        }


        string temp = "";

        while (counter > 0) {
            int times = 0;
            if (compareEqual(num1Copy, zero) || compareEqual(num2Copy, zero)) {
                for (int i = counter; i >= 0; i--) {
                    temp += '0';
                    return Integer(temp);
                }
            }

            while (compareGreater(num1Copy, num2Copy) || compareEqual(num1Copy, num2Copy)) {
                num1Copy = substract(num1Copy, num2Copy);
                times++;
            }

            temp += to_string(times);
            counter--;
            num2Copy = transferNumberRight(num2Copy);
        }
        return num1Copy;
    }

    vector<int> exponentiationBySquaring(vector<int>a, vector<int>power, vector<int>mod) {
        vector<int> result, counter, incrementer;

        counter = Integer("0");
        incrementer = Integer("1");
        result = Integer("1");


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
        incrementer = Integer("1");
        counter = Integer("1");
        check = Integer("0");
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
        vector<int> num1Decrement = substract(num1, Integer("1"));

        while (true) {
            string Power = "";
            int power = 0;
            power = int(pow(2, maxPow));

            Power = to_string(power);

            bool equal = compareEqual(modulo(num1Decrement, Integer(Power)), Integer("0"));
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
        vector<int> result = divide(num1, power(Integer("2"), Integer(to_string(s))));
        return result;
    }

    void printVector(vector<int>A) {
        for (int i = 0; i < A.size(); i++) {
            cout << A[i] << "";
        }
        cout << endl;
    }

    bool checkPrime(int repeats, int s, vector<int> d, vector<int> mod) {
        vector<int> one = Integer("1");
        vector<int>modDecrement = substract(mod, one);

        for (int i = 0; i < repeats; i++) {

            int a = 161;
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
        vector<int>result = Integer("1");
        vector<int> bCopy = b;

        bool run = true;
        bool additional = false;
        do {

            b = bCopy;

            x = modulo(x, n);

            if (b[b.size() - 1] & 1) {

                result = multiply(result, x);


                result = modulo(result, n);

            }

            x = multiply(x, x);


            if (compareEqual(b, Integer("0"))) {
                additional = true;
            }
            bCopy = divide(b, Integer("2"));

        } while (!compareGreater(Integer("1"), bCopy));

        return result;
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

    const int ilosc_powtorzen = 30;

    long int czas[ilosc_powtorzen];
    unsigned long long suma = 0;

    for (int i = 0; i < 10; i++) {
        bufor1 = test.Integer(przykladowe1[i]);
        bufor2 = test.Integer(przykladowe2[i]);
        bufor3 = test.Integer(przykladoMod[i]);
        vector<int>vecJeden = test.Integer(jeden);
        vector<int>vecDwa = test.Integer(dwa);

        for (int j = 0; j < ilosc_powtorzen; j++) {

            int s = test.findS(bufor1);
            vector<int> d = test.findD(bufor1, s);

            auto start = chrono::steady_clock::now();

            test.checkPrime(10, s, d, bufor1);

            auto end = chrono::steady_clock::now();

            auto elapsed = chrono::duration_cast<chrono::microseconds>(end - start).count();
            czas[j] = elapsed;
        }


        cout << "SREDNI CZAS WYNOSI: ";
        for (int k = 0; k < ilosc_powtorzen; k++) {
            suma += czas[k];
        }
        cout << float(suma / ilosc_powtorzen) << endl;

    }


}

int main()
{
    srand(time(NULL));
    BigInt x = BigInt();
    string input1;
    cout << "Podaj liczbe: " << endl;
    cin >> input1;
    x.num1 = x.Integer(input1);

    cout << "Podales: " << endl;
    x.printVector(x.num1);


    int s = x.findS(x.num1);
    cout << "S wynosi: " << s << endl;

    vector<int>D = x.findD(x.num1, s);
    cout << "D wynosi: ";
    x.printVector(D);


    if (x.checkPrime(10, s, D, x.num1)) {
        cout << "Liczba jest pierwsza." << endl;
    }
    else {
        cout << "Liczba nie jest pierwsza." << endl;
    }

    //test_timeMeasuring();

    return 0;
}


