#include <iostream>
#include <vector>

const int size = 8;

class BinaryCalculator{
private:
    std::vector<int> binNumber1;
    std::vector<int> binNumber2;
    int size = 0; //дефолтное значение, сюда передается 8 из глобальной size через BinaryCalculator calc(size); (конструктор класса)
    std::vector<int> result;
    
    void show_vector(const std::vector<int> &vec) {
        for(int i = 0; i < vec.size(); i++){
                std::cout << vec[i];
        }
    }
    
    std::vector<int> addBinary(const std::vector<int> &num1, const std::vector<int> &num2) {
        std::vector<int> result;
        int carry = 0;

        for (int i = num1.size() - 1; i >= 0; --i) {
            int sum = num1[i] + num2[i] + carry;
            result.insert(result.begin(), sum % 2);
            carry = sum / 2;
        }
        
        /*
        if (carry > 0) {
            result.insert(result.begin(), carry);
        }*/
        
        /*if (!num1.empty() && !num2.empty() && !result.empty()) {
            if ((num1[0] == num2[0]) && (result[0] != num1[0])) {
                std::cout << "Overflow detected in addition!" << std::endl;
            } else if (result.size() > 8 && (num1[0] == num2[0] && result[1]!=num1[0])){
                std::cout << "Overflow again in addition!" << std::endl;
            } else if (result.size() > 8) {
                result.erase(result.begin());
            }
        }*/
        return result;
    }

    std::vector<int> subtractBinary(const std::vector<int> &minuend, const std::vector<int> &subtrahend) {
        std::vector<int> result;
        std::vector<int> complementB;
        for (int i = 0; i < 8; i++) {
            complementB.push_back((subtrahend[i] == 0) ? 1 : 0);
        }
        
        std::vector<int> one = {0, 0, 0, 0, 0, 0, 0, 1};
        complementB = addBinary(complementB, one);
            
        return result = addBinary(minuend, complementB);
        
    }

    std::vector<int> multiplyBinary(std::vector<int> num1, std::vector<int> num2) {
        std::vector<int> result1(size, 0);
        std::vector<int> temp(size, 0);

        for (int i = size-1; i >= 0; --i) {
            if (num2[i] == 1) {
                temp = num1;
                for (int j = 0; j < 7 - i; ++j) {
                    temp.push_back(0);
                    temp.erase(temp.begin());
                }
                result1 = addBinary(result1, temp);
            }
        }
        /*
        if (!num1.empty() && !num2.empty() && !result1.empty()) {
            if ((num1[0] == num2[0]) && (result1[0] = 1)) {
                std::cout << "Overflow mult!" << std::endl;
            } else if ((num1[0] != num2[0]) && (result1[0] = 0)) {
                std::cout << "Overflow mult2!" << std::endl;
            }
        }*/
        return result1;
    }

    
    
public:
    BinaryCalculator(int bits) : size(bits) {}
    
    int check_input(){
        int number = 0;
        while (true) {
            std::cout << "Enter a number in the range [-128, 127]: ";
            std::cin >> number;

            if (number >= -128 && number <= 127) {
                return number;
            } else {
                std::cout << "Number is not in range [-128, 127]. Try again." << std::endl;
            }
        }
    }
    

    void convertNumbers (int num1, int num2){
        if (num1 < 0) {
            num1 = 256 + num1; // Преобразуем отрицательное число в дополнительный код
        }
        
        for (int i = 0; i <= 7; i++) {
            binNumber1.insert(binNumber1.begin(), num1 % 2); // Записываем остаток от деления на 2
            num1 /= 2; // Делаем целочисленное деление на 2
        }
        
        
        if (num2 < 0) {
            num2 = 256 + num2; // Преобразуем отрицательное число в дополнительный код
        }

        for (int i = size-1; i >= 0; i--) {
            binNumber2.insert(binNumber2.begin(), num2 % 2); // Записываем остаток от деления на 2
            num2 /= 2; // Делаем целочисленное деление на 2
        }
        
        std::cout<<"Binary representation of first number: ";
        show_vector(binNumber1);
        std::cout << std::endl;
        std::cout<<"Binary representation of second number: ";
        show_vector(binNumber2);

    }
    
    void performOperation(char operation){ //не видит нум1 и нум2 потому что на входе их нет
        switch (operation) {
            case '+':
                std::cout << "\nBinary result: ";
                result = addBinary(binNumber1, binNumber2);
                break;
            case '-':
                std::cout << "\nBinary result: ";
                result = subtractBinary(binNumber1, binNumber2);
                break;
            case '*':
                std::cout << "\nBinary result: ";
                result = multiplyBinary(binNumber1, binNumber2);
                break;
            default:
                std::cout << "Invalid operation!" << std::endl;
        }
    }

    void displayResults() {
        int decimalNumber = 0;
        int power = 1; // Начальная степень двойки

        for (int i = result.size() - 1; i >= 1; --i) {
            decimalNumber += result[i] * power;
            power *= 2; // Увеличиваем степень двойки для следующего бита
        }
        if (!result.empty()) {
            int signBit = result[0];
            if (signBit == 1) {
                decimalNumber -= power; // Если число отрицательное, вычитаем значение знакового бита
            }
        }
        show_vector(result);
        std::cout << std::endl;
        std::cout << "Decimal result: " << decimalNumber << std::endl;
    }
    
};


int main() {
    BinaryCalculator calc(size);
    
    int num1 = calc.check_input();
    int num2 = calc.check_input();
    char operation = ' ';
    
    std::cout << "Enter the operation (+ for addition, - for subtraction, * for multiplication): ";
    std::cin >> operation;
    
    calc.convertNumbers(num1, num2);
    calc.performOperation(operation);
    calc.displayResults();
    
    return 0;
}
