#include<iostream>
#include<vector>
#include <string>
using namespace std;

class Number
{
private:
    vector<int> data;

public:
    Number(int n)
    {
        data.resize(n);
    }

    void set_data(int index, int value)
    {
        data[index] = value;
    }

    void greatest_common_divisor(int index1, int index2)
    {
        //TODO
        int x = data[index1];
        int y = data[index2];

        // 輾轉相除法
        while (y != 0)
        {
            int r = x % y;
            x = y;
            y = r;
        }

        cout << x << endl;

        //compute the gcd of data[index1] and data[index2]

        //use for loop(s) or while loops(s) or both

        //use cout in this function

        //
    }

    void prime_sum(int index)
    {
        //TODO
        static bool prepared = false;
        static vector<int> prefix_sum(100001, 0);

        // 先預處理所有質數和
        if (!prepared)
        {
            vector<int> is_prime(100001, 1);
            is_prime[0] = 0;
            is_prime[1] = 0;

            for (int i = 2; i * i <= 100000; i++)
            {
                if (is_prime[i])
                {
                    for (int j = i * i; j <= 100000; j += i)
                    {
                        is_prime[j] = 0;
                    }
                }
            }

            for (int i = 1; i <= 100000; i++)
            {
                prefix_sum[i] = prefix_sum[i - 1];
                if (is_prime[i])
                {
                    prefix_sum[i] += i;
                }
            }

            prepared = true;
        }

        int limit = data[index];
        if (limit <= 1)
        {
            cout << 0 << endl;
        }
        else
        {
            cout << prefix_sum[limit - 1] << endl;
        }

        //compute the sum of all prime numbers lower than data[index]

        //use for loop(s) or while loops(s) or both

        //use cout in this function

        //
    }

    void binary_conversation(int index)
    {
        //TODO
        int value = data[index];
        string binary = "";

        // 從低位一路往前組字串
        if (value == 0)
        {
            binary = "0";
        }
        else
        {
            while (value > 0)
            {
                char bit = char('0' + (value % 2));
                binary = bit + binary;
                value /= 2;
            }
        }

        cout << binary << endl;

        //Convert data[index] to binary

        //use for loop(s) or while loops(s) or both

        //use cout in this function

        //
    }

    void sort_data()
    {
        //TODO
        int n = data.size();

        // 氣泡排序
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < n - 1 - i; j++)
            {
                if (data[j] > data[j + 1])
                {
                    int temp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = temp;
                }
            }
        }

        //sort the elements of data in ascending order

        //use for loop(s) or while loops(s) or both
        
        //don't cout in this function

        //
    }
    
};

int main()
{
    int n;

    cin >> n;

    Number number(n);

    for (int i = 0; i < n; i++)
    {
        //TODO
        int value;
        cin >> value;
        number.set_data(i, value);

        //use set_data() to process the input

        //
    }

    char c;
    int a, b;

    while (cin >> c)
    {
        //TODO
        if (c == 'g')
        {
            cin >> a >> b;
            number.greatest_common_divisor(a, b);
        }
        else if (c == 'p')
        {
            cin >> a;
            number.prime_sum(a);
        }
        else if (c == 'b')
        {
            cin >> a;
            number.binary_conversation(a);
        }
        else if (c == 's')
        {
            number.sort_data();
        }

        //process the remaining input

        //
    }
}