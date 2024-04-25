#include <iostream>
#include <vector>

const int size = 8;

class BinaryCalculator{
private:
    std::vector<int> number1;
    std::vector<int> number2;
    int size = 0;
    std::vector<int> result;
    
    std::vector<int> addBinary(const std::vector<int>& a, const std::vector<int>& b) {
        int carry = 0;

        for (int i = a.size() - 1; i >= 0; --i) {
            int sum = a[i] + b[i] + carry;
            result.insert(result.begin(), sum % 2);
            carry = sum / 2;
        }
        
        /*
        if (carry > 0) {
            result.insert(result.begin(), carry);
        }*/
        
        if ((a[0] == b[0]) && (result[0] != a[0])) {
            std::cout << "Overflow detected in addition!" << std::endl;
        } else if (result.size() > 8 && (a[0] == b[0] && result[1]!=a[0])){
            std::cout << "Overflow again in addition!" << std::endl;
        } else if (result.size() > 8) {
            result.erase(result.begin());
        }

        return result;
    }

    std::vector<int> subtractBinary(const std::vector<int>& minuend, const std::vector<int>& subtrahend) {
        std::vector<int> complementB;
        for (int i = 0; i < 8; i++) {
            complementB.push_back((subtrahend[i] == 0) ? 1 : 0);
        }
        std::vector<int> one = {0, 0, 0, 0, 0, 0, 0, 1};
        complementB = addBinary(complementB, one);
            
        std::cout << "compB: ";
        for (int i = 0; i < complementB.size(); i++) {
            std::cout << complementB[i];
        }
        std::cout << std::endl;
            
        result = addBinary(minuend, complementB);
        
        return result;
    }

    std::vector<int> multiplyBinary(std::vector<int> num1, std::vector<int> num2) {
        std::vector<int> temp(size, 0);

        for (int i = size-1; i >= 0; i--) {
            if (num2[i] == 1) {
                temp = num1;
                for (int j = 0; j < 7 - i; j++) {
                    temp.push_back(0);
                    temp.erase(temp.begin());
                }
                /*show_vector(temp);*/
                result = addBinary(result, temp);
            }
        }
        
        if ((num1[0] == num2[0]) && (result[0] = 1)) {
                std::cout << "Overflow mult!" << std::endl;
            } else if ((num1[0] != num2[0]) && (result[0] = 0)) {
                std::cout << "Overflow mult2!" << std::endl;
            }


        return result;
    }

    
    
public:
    BinaryCalculator(int bits) : size(bits) {}
    
    void check_input(int num){
        if (num < -128 || num > 127) {
                std::cerr << "Error: Number out of range for 8-bit binary representation." << std::endl;
                exit(1);
            }
    }

    void input_numbers (int num1, int num2){
        if (num1 < 0) {
            num1 = 256 + num1; // Преобразуем отрицательное число в дополнительный код
        }
        
        for (int i = 0; i <= 7; i++) {
            number1.insert(number1.begin(), num1 % 2);
            /*number1[i] = num1 % 2;*/ // Записываем остаток от деления на 2
            num1 /= 2; // Делаем целочисленное деление на 2
        }
        
        
        if (num2 < 0) {
            num2 = 256 + num2; // Преобразуем отрицательное число в дополнительный код
        }

        for (int i = size-1; i >= 0; i--) {
            number2.insert(number2.begin(), num2 % 2); // Записываем остаток от деления на 2
            num2 /= 2; // Делаем целочисленное деление на 2
        }
        
        show_vector(number1);
        std::cout << std::endl;
        show_vector(number2);

    }
    
    void performOperation(char operation){ //не видит нум1 и нум2 потому что на входе их нет
        switch (operation) {
            case '+':
                std::cout << "\nBinary result: ";
                result = addBinary(number1, number2);
                break;
            case '-':
                std::cout << "\nBinary result: ";
                result = subtractBinary(number1, number2);
                break;
            case '*':
                std::cout << "\nBinary result: ";
                result = multiplyBinary(number1, number2);
                break;
            default:
                std::cout << "Invalid operation!" << std::endl;
        }
    }

    void displayResults() {
        int decimalNumber = 0;
        int signBit = result[0]; // Знаковый бит (0 для положительных, 1 для отрицательных)
        int power = 1; // Начальная степень двойки

        for (int i = result.size() - 1; i >= 1; --i) {
            decimalNumber += result[i] * power;
            power *= 2; // Увеличиваем степень двойки для следующего бита
        }

        if (signBit == 1) {
            decimalNumber -= power; // Если число отрицательное, вычитаем значение знакового бита
        }
        show_vector(result);
        std::cout << std::endl;
        std::cout << decimalNumber << std::endl;
    }
    
    void show_vector(const std::vector<int> &a) {
        for(int i = 0; i < a.size(); i++){
                std::cout << a[i];
        }
    }
};




int main() {
    int num1 = 0, num2 = 0;
    char operation = ' ';
    
    BinaryCalculator calc(size);
    std::cout << "Enter the first number: ";
    std::cin >> num1;
    calc.check_input(num1);
    std::cout << "Enter the second number: ";
    std::cin >> num2;
    calc.check_input(num2);
    std::cout << "Enter the operation (+ for addition, - for subtraction, * for multiplication): ";
    std::cin >> operation;
    
    calc.input_numbers(num1, num2);
    calc.performOperation(operation);
    calc.displayResults();
    
    return 0;
}
