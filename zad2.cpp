#include <iostream>
#include <vector>
#include <random>

using namespace std;

// Генерация вектора случайных чисел
vector<int> Generate_Vector(int n) {
    random_device generator; // генератор случайных чисел
    vector<int> nums; // вектор для хранения чисел
    for (int i = 0; i < n; ++i) { // цикл заполнения
        int randnums = 10 + generator() % 90; // число в диапазоне 10–99
        nums.push_back(randnums); // добавление элемента в вектор
    }
    return nums; // возврат вектора
}

// Поиск двух минимальных чисел и суммы остатков
int find_mins(vector<int> nums, int& min1, int& min2) {
    for (auto randnums : nums) { // перебор элементов массива
        if (randnums < min1) { // найден новый минимум
            min2 = min1; 
            min1 = randnums;
        } else if (randnums < min2 && randnums != min1) {
            min2 = randnums; // обновление второго минимального
        }
    }

    int sumost = 0; // сумма остатков
    for (auto elem : nums) {
        sumost += (elem % min1); // остаток от деления на минимальный элемент
    }

    return sumost;
}

// Поиск самой длинной возрастающей последовательности
vector<int> FindLongSeq(vector<int> nums) {
    vector<int> LongSeq; // самая длинная последовательность
    vector<int> CurrentSeq; // текущая последовательность

    for(int i = 0; i < nums.size(); ++i) {

        if (CurrentSeq.empty() || nums[i] > CurrentSeq.back()) {
            CurrentSeq.push_back(nums[i]); // продолжаем последовательность
        } else {

            if (CurrentSeq.size() > LongSeq.size()) {
                LongSeq = CurrentSeq; // сохраняем более длинную
            }

            CurrentSeq.clear(); // начинаем новую последовательность
            CurrentSeq.push_back(nums[i]);
        }
    }

    if (CurrentSeq.size() > LongSeq.size()) {
        LongSeq = CurrentSeq;
    }

    return LongSeq;
}

// Формирование и вывод массива таблицей
void matrix(int n) {
    cout << "Массив: " << endl;

    n *= 8; // общее количество элементов
    int count = 2;

    vector<int> nums3(n); // массив

    nums3[0] = 2000; // первый элемент
    cout << nums3[0] << " ";

    for (int i = 1; i < n; ++i) {

        nums3[i] = nums3[i-1] + 10; // увеличение на 10
        cout << nums3[i] << " ";

        if (count % 8 == 0) { // каждые 8 элементов новая строка
            cout << endl;
        }

        count++;
    }
}

// Перегрузка оператора вывода vector
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& vec) {

    for (const auto& element : vec) {
        os << element << " ";
    }

    return os;
}


int main(){

    srand(time(0)); // инициализация генератора
    setlocale(LC_ALL, "Rus");
    random_device generator;
    
    // Блок 1 — генерация случайного массива
    int n = 0;

    while (n > 10 || n <= 0) {
        cout << "1. Введите размерность массива рандомных чисел(не больше 10): ";
        cin >> n;
    }

    vector<int> nums = Generate_Vector(n); // создание массива

    cout << "Вектор рандомных чисел: " << nums << endl << endl;

    // Блок 2 — поиск минимальных элементов
    int min1 = 1000, min2 = 1000;

    int sumost = find_mins(nums, min1, min2);

    cout << "2. Минимальные числа: " << min1 << " " << min2 << endl
         << "Сумма остатков: " << sumost << endl << endl;

    // Блок 3 — ввод массива и поиск последовательности
    n = 0;

    while (n > 10 || n <= 0) {
        cout << "3. Введите размерность массива чисел(не больше 10): ";
        cin >> n;
    }

    vector<int> nums2(n); // массив пользователя

    cout << "Введите массив чисел: ";

    for (int i = 0; i < n; ++i) {
        cin >> nums2[i];
    }

    vector<int> LongSeq = FindLongSeq(nums2);

    cout << "Самая длинная последовательность массива: ";

    for (int i : LongSeq) {
        cout << i << " ";
    }

    cout << endl << endl;

    n = 0;

    while(n <= 0 || n > 10) {
        cout << "4. Введите кол-во столбцов в массиве(Не больше 10): ";
        cin >> n;
    }

    matrix(n); // вывод массива

    return 0;
}
