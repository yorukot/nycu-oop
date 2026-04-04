#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
namespace MyNamespace {
    class vector {
    private:
        std::vector<int> coefficients;
    public:
        vector(std::vector<int> vec) {
            coefficients = vec;
        }
        vector() {
            coefficients = std::vector<int>();
        }

        int& at(int idx) {
            return coefficients.at(idx);
        }
        
        void push_back(int a) {
            coefficients.push_back(a);
        }

        int size() {
            return coefficients.size();
        }
        //Add the vector by other vector
        vector add_vec(vector vec) {
            vector ans;
            if (size() >= vec.size()) {
                ans = *this;
                for (int idx = 0; idx < vec.size(); idx++) {
                    ans.at(idx) += vec.at(idx);
                }
            }
            else {
                ans = vec;
                for (int idx = 0; idx < size(); idx++) {
                    ans.at(idx) += at(idx);
                }
            }
            return ans;
        }
        //Multiply the vector by a integer
        vector mult_int(int mul) {
            vector ans = vector(coefficients);

            for (int idx = 0; idx < size(); idx++) {
                ans.at(idx) *= mul;
            }

            return ans;
        }
        //Compute the dot product of this vector with another vector.
        int dot(vector vec) {
            int ans = 0;
            for (int i = 0; i < size();i++) {
                ans += at(i) * vec.at(i);
            }
            return ans;
        }
    };
    class Polynomial {
    private:
        vector coefficients; // a + b x + c x^2 + d x^3 ...
                             // (a,b,c,d ...)
    public:
        Polynomial() {
            coefficients = vector();
        }
        Polynomial(vector vec) {
            //TODO : Set coefficients 
            coefficients = vec;
            //
        }
        //Add the polynomial by other polynomial
        Polynomial plus(Polynomial other) {
            vector newPolynomialCoefficients;

            //TODO : Perform polynomial addition.
            //HINT: Use get_coefficients() and MyNamespace::vector::add_vec() .
            newPolynomialCoefficients = coefficients.add_vec(other.get_coefficients());

            //

            return Polynomial(newPolynomialCoefficients);
        }
        //Multiply the polynomial by x
        Polynomial times_x() {
            vector newPolynomialCoefficients = coefficients;

            newPolynomialCoefficients.push_back(coefficients.at(coefficients.size() - 1));
            for (int i = coefficients.size() - 1;i >= 1;i--) {
                newPolynomialCoefficients.at(i) = newPolynomialCoefficients.at(i - 1);
            }
            newPolynomialCoefficients.at(0) = 0;

            return Polynomial(newPolynomialCoefficients);
        }
        Polynomial times(Polynomial other) {
            vector newPolynomialCoefficients;

            //TODO : Perform polynomial multiplication
            //HINT: Use get_coefficients(), times_x(), and MyNamespace::vector::mult_int().
            //Multiply the polynomial by the n-th element of other using MyNamespace::vector::mult_int(), then apply times_x() n times.
            //You may use Polynomial() to change the class then you can use times_x()
            Polynomial ans;
            Polynomial shifted = *this;
            vector otherCoefficients = other.get_coefficients();

            for (int i = 0; i < otherCoefficients.size(); i++) {
                Polynomial term(shifted.get_coefficients().mult_int(otherCoefficients.at(i)));
                ans = ans.plus(term);
                shifted = shifted.times_x();
            }
            newPolynomialCoefficients = ans.get_coefficients();
            //

            return Polynomial(newPolynomialCoefficients);
        }

        int substitute(int x) {
            int ans;

            //TODO : Substitute a given value (x) for the variable in the polynomial, then compute the score.
            ans = 0;
            // 霍諾法: P(x)=2 + 3x + 4x^2 = P(x) = (4x + 3)x + 2
            for (int i = coefficients.size() - 1; i >= 0; i--) {
                ans = ans * x + coefficients.at(i);
            }

            return ans;
        }

        vector get_coefficients() {
            return coefficients;
        }
    };
    
    class Score {
    private:
        int score; //The score has been calculated (option 'D' or a polynomial after calculate)
        Polynomial polynomial; //If a score has not been calculated, it must be a polynomial, store it first.
        bool counted; //True if the score is valid
    public:
        Score() {
            score = 0;
            counted = true;
        }
        Score(int s) {
            score = s;
            counted = true;
        }
        Score(Polynomial p) {
            polynomial = p;
            score = 0;
            counted = false;
        }
        bool has_counted() {
            return counted;
        }
        int calculate(int x) {
            score = polynomial.substitute(x);
            counted = true;
            return score;
        }
        void print_score_str() {
            //TODO : Print a string based on the score.
            if (score >= 80) {
                std::cout << "I like programming" << std::endl;
            }
            else if (score >= 60) {
                std::cout << "Programming is fun" << std::endl;
            }
            else {
                std::cout << "I want to learn more..." << std::endl;
            }

            //
        }
    };

}
using namespace std;
//You can use it to get the coefficients of a polynomial or a vector
//Hint: poly = MyNamespace::Polynomial(scan_a_vector())
MyNamespace::vector scan_a_vector() {
    string input;
    MyNamespace::vector vec;

    while (true) {
        cin >> input;

        if (input == "|")
            break;

        vec.push_back(stoi(input));
    }

    return vec;
}


int main()
{
    int n;
    cin >> n;
    
    vector<MyNamespace::Score> scores;

    for (int i = 0; i < n; i++) {
        string opt;
        cin >> opt;

        if (opt == "+" || opt == "*") {
            MyNamespace::vector vec1 = scan_a_vector();
            MyNamespace::vector vec2 = scan_a_vector();
            MyNamespace::Polynomial poly1(vec1);
            MyNamespace::Polynomial poly2(vec2);
            if (opt == "+") {
                scores.push_back(MyNamespace::Score(poly1.plus(poly2)));
            }
            else {
                scores.push_back(MyNamespace::Score(poly1.times(poly2)));
            }
        }
        else if (opt == "D") {
            MyNamespace::vector vec1 = scan_a_vector();
            MyNamespace::vector vec2 = scan_a_vector();
            scores.push_back(MyNamespace::Score(vec1.dot(vec2)));
        }
        else if (opt == "x") {
            int x;
            cin >> x;
            for (std::size_t idx = 0; idx < scores.size(); idx++) {
                if (!scores.at(idx).has_counted()) {
                    scores.at(idx).calculate(x);
                }
            }
        }
    }

    //

    for (std::size_t i = 0; i < scores.size();i++) {
        scores.at(i).print_score_str();
    }

    return 0;
}

