#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Функция вывода бюллетеней
void printVotes(const vector<vector<int>>& votes, const vector<string>& candidates) {
    cout << "Предпочтения избирателей:\n";
    for (int i = 0; i < votes.size(); i++) {
        cout << "Избиратель " << i + 1 << ": ";
        for (int j = 0; j < votes[i].size(); j++) {
            cout << candidates[votes[i][j]];
            if (j != votes[i].size() - 1) cout << " > ";
        }
        cout << endl;
    }
    cout << endl;
}using namespace std;

// Функция вывода предпочтений избирателей
void printVotes(const vector<vector<int>>& votes, const vector<string>& candidates) {
    cout << "Предпочтения избирателей:\n";
    for (int i = 0; i < votes.size(); i++) { // перебор всех избирателей
        cout << "Избиратель " << i + 1 << ": ";
        for (int j = 0; j < votes[i].size(); j++) { // перебор кандидатов в голосе
            cout << candidates[votes[i][j]];
            if (j != votes[i].size() - 1) cout << " > "; // формат вывода
        }
        cout << endl;
    }
    cout << endl;
}

// Метод Борда (начисление очков по позициям)
void bordaVoting(const vector<vector<int>>& votes, const vector<string>& candidates) {
    int n = candidates.size(); // количество кандидатов
    vector<int> scores(n, 0);  // массив очков

    // начисление очков:
    // 1 место — n-1 очков, 2 место — n-2, ..., последнее — 0
    for (const auto& vote : votes) {
        for (int i = 0; i < n; i++) {
            scores[vote[i]] += (n - 1 - i);
        }
    }

    // вывод результатов
    cout << "Результаты по методу Борда:\n";
    for (int i = 0; i < n; i++) {
        cout << candidates[i] << ": " << scores[i] << " очков\n";
    }

    // поиск победителя (максимальное число очков)
    int winner = 0;
    for (int i = 1; i < n; i++) {
        if (scores[i] > scores[winner]) {
            winner = i;
        }
    }

    cout << "Победитель по Борда: " << candidates[winner] << endl << endl;
}

// Поиск позиции кандидата в голосе
int findPosition(const vector<int>& vote, int candidate) {
    for (int i = 0; i < vote.size(); i++) {
        if (vote[i] == candidate) return i; // возвращаем позицию кандидата
    }
    return -1;
}

// Метод Кондорсе (попарные сравнения)
void condorcetVoting(const vector<vector<int>>& votes, const vector<string>& candidates) {
    int n = candidates.size(); // количество кандидатов
    bool foundWinner = false;  // найден ли победитель

    cout << "Попарные сравнения Кондорсе:\n";

    // матрица: сколько раз кандидат i побеждает кандидата j
    vector<vector<int>> matrix(n, vector<int>(n, 0));

    // заполнение матрицы
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;

            for (const auto& vote : votes) {
                // если кандидат i выше кандидата j в предпочтении
                if (findPosition(vote, i) < findPosition(vote, j)) {
                    matrix[i][j]++;
                }
            }
        }
    }

    // вывод попарных сравнений
    for (int i = 0; i < n; i++) {
        cout << candidates[i] << ": ";
        for (int j = 0; j < n; j++) {
            if (i != j) {
                cout << "против " << candidates[j] << " = " << matrix[i][j] << "  ";
            }
        }
        cout << endl;
    }
    cout << endl;

    // поиск победителя Кондорсе
    // кандидат должен выиграть у всех остальных
    for (int i = 0; i < n; i++) {
        bool isWinner = true;

        for (int j = 0; j < n; j++) {
            if (i == j) continue;

            // если i не выигрывает у j — он не победитель
            if (matrix[i][j] <= matrix[j][i]) {
                isWinner = false;
                break;
            }
        }

        // если найден победитель
        if (isWinner) {
            cout << "Победитель по Кондорсе: " << candidates[i] << endl;
            foundWinner = true;
            break;
        }
    }

    // если победителя нет (цикл предпочтений)
    if (!foundWinner) {
        cout << "Победителя по Кондорсе нет (возможен цикл предпочтений)." << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Rus"); 
    // список кандидатов
    vector<string> candidates = {"A", "B", "C"};

    // предпочтения избирателей (ранжирование)
    vector<vector<int>> votes = {
        {0, 1, 2}, // A > B > C
        {0, 1, 2}, // A > B > C
        {1, 2, 0}, // B > C > A
        {1, 2, 0}, // B > C > A
        {2, 0, 1}  // C > A > B
    };

    // вывод предпочтений
    printVotes(votes, candidates);

    // расчёт по методу Борда
    bordaVoting(votes, candidates);

    // расчёт по методу Кондорсе
    condorcetVoting(votes, candidates);

    return 0; 
}
