#include <iostream>
#include <utility>
#include <vector>
#include <list>
#include <array>

std::vector<std::vector<int>> multiplication_table(int n){
  std::vector<std::vector<int>> table;
  table.resize(n);
  for (int row = 0; row < n; row++) {
    table.at(row).resize(n);
    table.at(row).at(0) = row + 1;
    for (int index = 1; index < n; index++) {
      table.at(row).at(index) = table.at(row).at(0) + table.at(row).at(index - 1);
    }
  }
  return std::move(table);
}

void show_matrix(const std::vector<std::vector<int>> &mat) {
  for(const auto &row : mat) {
    std::cout << "[";
    for (const auto &el : row){
      std::cout << " " << el << " ";
    }
    std::cout << "]" << std::endl;
  }
}

std::string duplicate_encoder(const std::string& word){
  std::string new_string;
  std::string low_string;
  for (const auto &let : word){
    low_string += static_cast<char>(tolower(let));
  }

  for (const auto &let : low_string) {
    auto index = low_string.find(let);
    if (low_string.find(let, index + 1) == std::string::npos) {
        new_string += "(";
    }
    else {
      new_string += ")";
    }
  }
  return std::move(new_string);
}

struct PeakData {
  std::vector<int> pos, peaks;
  friend std::ostream& operator<< (std::ostream &out, const PeakData &peak_data){

    // Вывод позиций
    out << "Positions: [";
    for (const auto &p : peak_data.pos){
      out << ' ' << p << ' ';
    }
    out << "] ";
    
    // Вывод пиков 
    out << "Peaks: [";
    for (const auto &p : peak_data.peaks){
      out << ' ' << p << ' ';
    }
    out << ']';
    
    return out;
  }
};

PeakData pick_peaks(const std::vector<int> &v) {
  PeakData result;

  auto size = v.size();
  if (size == 0) return result;

  int status = 0;
  for (int i = 0; i < size - 1; i++){
    if (status == 0){
      if (v.at(i) < v.at(i + 1)){
        status = 1;
      }
    } else if (status == 1) {
      if (v.at(i) > v.at(i + 1)) {
        result.pos.emplace_back(i);
        result.peaks.emplace_back(v.at(i));
        status = 0;
      } else if (v.at(i) == v.at(i + 1)){
        result.pos.emplace_back(i);
        result.peaks.emplace_back(v.at(i));
        status = 2;
      }
    } else {
      if (v.at(i) < v.at(i + 1)) {
        result.pos.resize(result.pos.size() - 1);
        result.peaks.resize(result.peaks.size() - 1);
        status = 0;
      } else if (v.at(i) > v.at(i + 1)) {
        status = 0;
      }
    }
  }
  if (status == 2) {
    result.pos.resize(result.pos.size() - 1);
    result.peaks.resize(result.peaks.size() - 1);
  }
  return result;
}

int FindOutlier(const std::vector<int>& arr) {
  int cu = 0;
  for (int index = 0; index < 3; index++){
    if (arr.at(index) % 2 == 0){
      cu++;
    }
    else {
      cu--;
    }
  }
  for (const auto &el : arr){
    if (cu > 0){
      if (el % 2 != 0){
        return el;
      }
    }
    else {
      if (el % 2 == 0){
        return el;
      }
    }
  }
  return 0;
}

std::vector<int> race(int v1, int v2, int g){
  if (v1 >= v2)
    return std::vector{-1, -1, -1};

  int time = static_cast<int>(static_cast<double>(g) / static_cast<double>(v2 - v1) * 3600);

  int sec = time % 60;
  int min = ((time - sec) / 60) % 60;
  int h =  (time - sec - min) / 3600;

  return {h, min, sec};
}

std::ostream& operator<<(std::ostream &out, const std::vector<int> &data){
  out << "vector<int>: [";
  for (const auto &el : data){
    out << " " << el << " ";
  }
  out << "]";
  return out;
}

std::ostream& operator<<(std::ostream &out, const std::list<int> &data){
  out << "list<int>: [";
  for (const auto &el : data){
    out << " " << el << " ";
  }
  out << "]";
  return out;
}

int countSmileys(const std::vector<std::string>& arr) {
  int cu = 0;
  for (const auto &el: arr){
    auto el_size = el.size();
    if (el_size > 3 or el_size < 2)
      continue;
    if (el.at(0) != ':' and el.at(0) != ';')
      continue;
    if (el_size == 2){
      if (el.at(1) != 'D' and el.at(1) != ')')
        continue;
    } else {
      if (el.at(2) != 'D' and el.at(2) != ')')
        continue;
      if (el.at(1) != '-' and el.at(1) != '~')
        continue;
    }
    cu++;
  }
  return cu;
}

int dblLinear(int n){
    std::vector<int> u {1};
    int pt2 = 0, pt3 = 0;

    for(int i = 1; i <= n; i++){
      u.emplace_back(std::min(2 * u.at(pt2) + 1, 3 * u.at(pt3) + 1));
      if(u.at(i) == 2 * u[pt2] + 1) pt2++;
      if(u.at(i) == 3 * u[pt3] + 1) pt3++;
    }

    return u.at(n);
}

std::string range_extraction(const std::vector<int> &args) {
  std::string result;
  int size = static_cast<int>(args.size());
  for (int index = 0; index < size; index++){
    if (index + 2 < size){
      if (args.at(index) + 1 == args.at(index + 1) &&
          args.at(index + 1) + 1 == args.at(index + 2)){
        result += std::to_string(args.at(index)) + '-';
        index += 2;
        for (; index < size; index++){
          if (index + 1 < size) {
            if (args.at(index) + 1 != args.at(index + 1)){
              result += std::to_string(args.at(index)) + ',';
              break;
            }
          } else {
            result += std::to_string(args.at(index));
            break;
          }
        }
      } else {
        result += std::to_string(args.at(index)) + ',';
      }
    } else {
      if (index + 1 < size){
        result += std::to_string(args.at(index)) + ',' + std::to_string(args.at(index + 1));
        break;
      } else {
        result += std::to_string(args.at(index));
        break;
      }
    }
  }
  return result;
}

std::vector<int> snail(const std::vector<std::vector<int>> &snail_map) {
  int n_row = static_cast<int>(snail_map.size());
  int n_col = static_cast<int>(snail_map.at(0).size());

  int k = 0;
  int l = 0;

  std::vector<int> result;

  while(k < n_row && l < n_col){

    // Перемещение в право
    for (int index = l; index < n_col; index++)
      result.emplace_back(snail_map.at(k).at(index));
    k++;

    // Перемещение вниз
    for (int index = k; index < n_row; ++index)
      result.emplace_back(snail_map.at(index).at(n_col - 1));
    --n_col;

    // Перемещения влево
    if (k < n_row)
    {
      for (int index = n_col - 1; index >= l; --index)
        result.emplace_back(snail_map.at(n_row - 1).at(index));
      --n_row;
    }

    // Перемещение вверх
    if (l < n_col)
    {
      for (int index = n_row - 1; index >= k; --index)
        result.emplace_back(snail_map.at(index).at(l));
      ++l;
    }

  }
  return result;
}

int zeroes (int base, int number) {
  // Вводим переменную для хранения максимального количества нулей
  int noz = -1;
  // Переприсваиваем основания системы счисления
  int j = base;

  // Расскладываем основание на простые множители
  // base = (i1)^p1 + (i2)^p2 + ...
  // Количество нулей в факториале находится по формуле
  // min(1/p1(n/i1 + n/(i1*i1) + ..), ...)

  for (int i = 2; i <= base; i++) {
    if (j % i == 0) {
      // Разложение основания
      int p = 0;
      while (j % i == 0) {
        j = j / i;
        p++;
      }
      // Считаем то что в скобках
      long c = 0;
      long z = number / i;
      while (z > 0) {
        c += z;
        z = z / i;
      }
      if (noz == -1)
        // Начальное количество нулей
        noz = static_cast<int>(c / p);
      else
        // Выбираем меньшее
        noz = std::min(noz, static_cast<int>(c / p));
    }
  }
  return noz;
}

std::pair<double, double> get_args(size_t &index, std::string &arg){
  std::string num;
  size_t end_ind = index + 1;
  for (; end_ind < arg.size(); end_ind++){
    if (isalnum(arg.at(end_ind)) || (end_ind == index + 1 && arg.at(end_ind) == '-') || arg.at(end_ind) == '.'){
      num += arg.at(end_ind);
    } else {
      break;
    }
  }
  double right = std::stod(num, nullptr);
  num.clear();
  int st_ind = static_cast<int>(index) - 1;
  for (; st_ind >= 0; st_ind--){
    if (arg.at(st_ind) == '-') {
      num += arg.at(st_ind);
      st_ind--;
      break;
    } else if (isalnum(arg.at(st_ind)) || arg.at(st_ind) == '.') {
      num += arg.at(st_ind);
    } else {
      break;
    }
  }
  st_ind++;
  std::reverse(num.begin(), num.end());
  arg.erase(st_ind, static_cast<int>(end_ind) - st_ind);
  double left = std::stod(num, nullptr);
  index = st_ind;
  return {left, right};
}

void calc_br(std::string &arg){
  // Поиск умножения либо деления
  while(true) {
    auto dev = arg.find('/');
    auto mul = arg.find('*');
    if (dev != std::string::npos && mul != std::string::npos) {
      if (dev < mul) {
        std::pair<double, double> args;
        args = get_args(dev, arg);
        std::string res = std::to_string(args.first / args.second);
        res.erase ( res.find_last_not_of('0') + 1, std::string::npos );
        arg.insert(dev, res);
      } else {
        std::pair<double, double> args;
        args = get_args(mul, arg);
        std::string res = std::to_string(args.first * args.second);
        res.erase ( res.find_last_not_of('0') + 1, std::string::npos );
        arg.insert(mul, res);
      }
    } else if (dev != std::string::npos) {
      std::pair<double, double> args;
      args = get_args(dev, arg);
      std::string res = std::to_string(args.first / args.second);
      res.erase ( res.find_last_not_of('0') + 1, std::string::npos );
      arg.insert(dev, res);
    } else if (mul != std::string::npos) {
      std::pair<double, double> args;
      args = get_args(mul, arg);
      std::string res = std::to_string(args.first * args.second);
      res.erase ( res.find_last_not_of('0') + 1, std::string::npos );
      arg.insert(mul, res);
    } else {
      break;
    }
  }

  // Поиск сложения либо  вычитания
  while (true){
    auto sub = arg.find('-', 1);
    auto add = arg.find('+');
    if (sub != std::string::npos && add != std::string::npos){
      if (sub < add){
        std::pair<double, double> args;
        args = get_args(sub, arg);
        std::string res = std::to_string(args.first - args.second);
        res.erase ( res.find_last_not_of('0') + 1, std::string::npos );
        arg.insert(sub, res);
      } else {
        std::pair<double, double> args;
        args = get_args(add, arg);
        std::string res = std::to_string(args.first + args.second);
        res.erase ( res.find_last_not_of('0') + 1, std::string::npos );
        arg.insert(add, res);
      }
    } else if (sub != std::string::npos){
      std::pair<double, double> args;
      args = get_args(sub, arg);
      std::string res = std::to_string(args.first - args.second);
      res.erase ( res.find_last_not_of('0') + 1, std::string::npos );
      arg.insert(sub, res);
    } else if (add != std::string::npos) {
      std::pair<double, double> args;
      args = get_args(add, arg);
      std::string res = std::to_string(args.first + args.second);
      res.erase ( res.find_last_not_of('0') + 1, std::string::npos );
      arg.insert(add, res);
    } else {
      break;
    }
  }
}

double calc(std::string expression) {
  // Удаление пробелов
  expression.erase(std::remove(expression.begin(), expression.end(), ' '), expression.end());

  // Поиск скобок
  while(true){
    auto end_br = expression.find(')');
    if (end_br != std::string::npos){
      auto st_br = expression.rfind('(', end_br);
      std::string arg = expression.substr(st_br + 1, end_br - st_br - 1);

      calc_br(arg);

      if (st_br != 0) {
        if (expression.at(st_br - 1) == '-'){
          if (arg.at(0) == '-') {
            if (st_br != 1) {
              if (isalnum(expression.at(st_br - 2)) || expression.at(st_br - 2) == '.'){
                expression.at(st_br - 1) = '+';
                arg.erase(0, 1);
              } else {
                expression.erase(st_br - 1, 1);
                arg.erase(0, 1);
                st_br--;
                end_br--;
              }
            } else {
              expression.erase(st_br - 1, 1);
              arg.erase(0, 1);
              st_br--;
              end_br--;
            }
          }
        }
      }
      expression.erase(st_br, end_br - st_br + 1);
      expression.insert(st_br, arg);
    } else {
      calc_br(expression);
      break;
    }
  }
  return std::stod(expression, nullptr);
}

[[maybe_unused]] void revers(std::string &str){
  auto size = str.size();
  auto stop = (size / 2);
  for (size_t i = 0; i < stop; i++){
    std::swap(str.at(i), str.at(size - i - 1));
  }
}

int main(int argc, char* argv[]) {
  {
    // Создание матриц
    std::cout << "Multiplication table: " << std::endl;
    show_matrix(multiplication_table(3));
  }

  {
    // Кодирование строки
    std::cout << "Duplicate encoder: " << duplicate_encoder("Supralapsarian") << std::endl;
  }

  {
    // Поиск пиков
    std::cout << "Pick peaks: " << pick_peaks({3, 2, 3, 6, 4, 1, 2, 3, 2, 1, 2, 3}) << std::endl;
  }

  {
    // Поиск выбросов
    std::cout << "Find outlier: " <<  FindOutlier({160, 3, 1719, 19, 11, 13, -21}) << std::endl;
  }

  {
    // Расчет времени гонки
    std::cout << "Race: " << race(80, 91, 37) << std::endl;
  }

  {
    // Подсчет верных смайликов
    std::cout << "Count smileys:" << countSmileys({":)", ";(", ";}", ":-D"}) << std::endl;
  }

  {
    // Поиск элемента последовательности
    std::cout << "Find el: " << dblLinear(1000) << std::endl;
  }

  {
    // Извлечение диапозона
    std::cout << "Range extraction: " << range_extraction({1, 2, 3, 4, 5, 10}) << std::endl;
  }

  {
    // Змейка
    std::cout << "Snail: " << snail({{1, 2, 3, 4}, {12, 13, 14, 5}, {11, 16, 15, 6}, {10, 9, 8, 7}}) << std::endl;
  }

  {
    // Подсчет нулей в факториале
    std::cout << "Zeros in fact 10(2): " << zeroes(10, 2) << std::endl;
  }
  {
    // Калькулятор
    std::cout << "calc: " << calc("(-(-32 - 30) * -31 / -(-40 * 2 / -4)) / - 30") << std::endl;
  }

  return 0;
}