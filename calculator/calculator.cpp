#include <iostream>
#include <vector>
#include <string>
#include <numeric>

void print_help(const char* prog) {
    std::cout << "Использование: " << prog << " [опции] <операнды...>\n"
              << "Опции:\n"
              << "  -o, --operation <name>   summa (сумма), sub (вычитание)\n"
              << "  -h, --help               справка\n"
              << "Позиционные аргументы: 3–5 целых чисел (int)\n"
              << "Для sub: результат = первый операнд минус все остальные\n";
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        print_help(argv[0]);
        return 0;
    }

    std::string op;
    std::vector<int> nums;

    for (int i = 1; i < argc; ++i) {
        std::string a = argv[i];

        if (a == "-h" || a == "--help") {
            print_help(argv[0]);
            return 0;
        }

        if (a == "-o" || a == "--operation") {
            if (i + 1 >= argc) {
                std::cerr << "Ошибка: после -o/--operation требуется имя операции.\n";
                return 1;
            }
            op = argv[++i];
            continue;
        }

        // Парсим строго целое число
        try {
            size_t pos;
            int v = std::stoi(a, &pos);
            if (pos != a.size()) {
                throw 0; // если есть лишние символы после числа
            }
            nums.push_back(v);
        } catch (...) {
            std::cerr << "Ошибка: не целый аргумент '" << a << "'\n";
            return 1;
        }
    }

    if (op.empty()) {
        std::cerr << "Ошибка: операция не задана. Используйте -o или --operation.\n";
        return 1;
    }

    if (nums.size() < 3 || nums.size() > 5) {
        std::cerr << "Ошибка: требуется от 3 до 5 операндов, передано: "
                  << nums.size() << "\n";
        return 1;
    }

    int res = 0;

    if (op == "summa") {
        res = std::accumulate(nums.begin(), nums.end(), 0);
    } else if (op == "sub") {
        res = nums[0];
        for (size_t i = 1; i < nums.size(); ++i)
            res -= nums[i];
    } else {
        std::cerr << "Ошибка: неизвестная операция '" << op << "'.\n";
        return 1;
    }

    std::cout << res << "\n";
    return 0;
}

