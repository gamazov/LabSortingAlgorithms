/*!
\file
\brief https://github.com/gamazov/LabSortingAlgorithms
*/

#include <fstream>
#include <iostream>
#include <vector>

/*!
\fn void parseStr(std::string input, std::vector<std::string> &output, char sym)
\brief Находит в строке str элементы, разделенные символом sym, и записывает
результат в output \param[in] input Строка в которой производится поиск
\param[in,out] output Найденные подстроки
\param[in] sym Символ по которому нужно делить строку
*/

/*!
\fn void parseNo(Train &train)
\brief Преобразовывает строку no в беззнаковое чило для сравнения
\param[in,out] train Заполняемая структура
*/

/*!
\fn void parseData(Train &train)
\brief Преобразовывает строку data в беззнаковое чило для сравнения
\param[in,out] train Заполняемая структура
*/

/*!
\fn void parseTime(Train &train)
\brief Преобразовывает строку time в беззнаковое чило для сравнения
\param[in,out] train Заполняемая структура
*/

/*!
\fn void parseOnRoad(Train &train)
\brief Преобразовывает строку onRoad в беззнаковое чило для сравнения
\param[in,out] train Заполняемая структура
*/

/*!
\fn void parseFile(std::vector<Train> &schedules, char *fileName)
\brief Заполняетс все записи расписания, считывая данные из передаваемого файла
\param[in,out] schedules Заполняемое расписание
\param[in] fileName Файл в котором происходит поиск
*/

/*!
\fn void printSchedules(std::vector<Train> &schedules)
\brief Выводит все расписание
\param[in] schedules Расписание
*/

/*!
\fn void insertSort(std::vector<Train> &schedules)
\brief Сортировка вставками
\param[in,out] schedules Сортируемое расписание
*/

/*!
\fn int splittingByElem(std::vector<Train> &schedules, int start, int elemPos)
\brief Функция разделения
\param[in,out] schedules Сортируемое расписание
\param[in] start Начало сортируемого массива
\param[in] elemPos Найденный элемент
\return Возвращает индекс опорного элемента
*/

/*!
\fn void quickSort(std::vector<Train> &schedules, int start, int end)
\brief Быстрая сортировка
\param[in,out] schedules Сортируемое расписание
\param[in] start Начало сортируемого массива
\param[in] end Конец сортируемого массива
*/

/*!
\fn void merge(std::vector<Train> &schedules, int start, int end, int mid)
\brief Объединение массивов
\param[in,out] schedules Сортируемое расписание
\param[in] start Начало сортируемого массива
\param[in] end Конец сортируемого массива
\param[in] mid Середина сортируемого массива
*/

/*!
\fn void mergeSort(std::vector<Train> &schedules, int start, int end)
\brief Сортировка слиянием
\param[in,out] schedules Сортируемое расписание
\param[in] start Начало сортируемого массива
\param[in] end Конец сортируемого массива
*/

/*!
\fn bool comp(Train &first, Train &second)
\brief Компоратор для стандартной сортировки C++ std::sort()
\param[in] first Левый сравниваемый
\param[in] second Правый сравниваемый
\return Возвращает true - правый меньше левого, false - в противном случае
*/

/*!
\fn void printInfo(std::vector<Train> &schedules, std::string fileName)
\brief Сортирует, отображая затраченное время, и записывая отсортированное
расписание \param[in] schedules Сортируемое расписание \param[in] fileName Тип
сортировки и куда записывать
*/

/*!
\brief Описывает запись расписаня поездов
*/
struct Train {
  //! Дата отправления
  std::string data;
  //! Время отрпавления
  std::string time;
  //! Номер поезда
  std::string no;
  //! Время в пути
  std::string onRoad;
  //! Тип поезда
  std::string type;

  //! Дата, представленная в виде беззнакового числа для сравлнения
  unsigned int dataVal = 0;
  //! Время отправления, представленное в виде беззнакового числа для сравлнения
  unsigned int timeVal = 0;
  //! Номер, представленный в виде беззнакового числа для сравлнения
  unsigned int noVal = 0;
  //! Время в пути,  представленное в виде беззнакового числа для сравлнения
  unsigned int onRoadVal = 0;
};

void parseFile(std::vector<Train> &schedules, char *fileName);
void parseStr(std::string input, std::vector<std::string> &output, char sym);
void parseNo(Train &train);
void parseData(Train &train);
void parseTime(Train &train);
void parseOnRoad(Train &train);

bool operator==(Train &f, Train &s);
bool operator>(Train &f, Train &s);
bool operator<(Train &f, Train &s);
bool operator>=(Train &f, Train &s);
bool operator<=(Train &f, Train &s);

void printSchedules(std::vector<Train> &schedules);
void printInfo(std::vector<Train> &schedules, std::string fileName);

void bubbleSort(std::vector<Train> &schedules);
void insertSort(std::vector<Train> &schedules);
int splittingByElem(std::vector<Train> &schedules, int start, int elemPos);
void quickSort(std::vector<Train> &schedules, int start, int end);
void merge(std::vector<Train> &schedules, int start, int end, int mid);
void mergeSort(std::vector<Train> &schedules, int start, int end);

bool comp(Train &first, Train &second) { return first < second; }

int main(int argc, char *argv[]) {
  if (argc == 1) {
    std::cout << "No parametrs";
  }
  std::vector<Train> schedules, copy;
  parseFile(schedules, argv[1]);

#ifdef SORT
  printInfo(schedules, "sort.txt");
#endif // SORT
#ifdef INSERTSORT
  printInfo(schedules, "insertSort.txt");
#endif // INSERTSORT
#ifdef QUICKSORT
  printInfo(schedules, "quickSort.txt");
#endif // QUICKSORT
#ifdef MERGESORT
  printInfo(schedules, "mergeSort.txt");
#endif // MERGESORT

  return 0;
}

void insertSort(std::vector<Train> &schedules) {
  Train tmp = {};
  int i, j, n = static_cast<int>(schedules.size());
  for (i = 1; i < n; i++) {
    tmp = schedules[i];
    for (j = i - 1; j >= 0 && schedules[j] > tmp; j--) {
      schedules[j + 1] = schedules[j];
    }
    schedules[j + 1] = tmp;
  }
}

int splittingByElem(std::vector<Train> &schedules, int start, int elemPos) {
  int i = start;
  while (i < elemPos) {
    if (schedules[i] > schedules[elemPos] && i == elemPos - 1) {
      std::swap(schedules[i], schedules[elemPos]);
      elemPos--;
    } else {
      if (schedules[i] > schedules[elemPos]) {
        std::swap(schedules[elemPos - 1], schedules[elemPos]);
        std::swap(schedules[i], schedules[elemPos]);
        elemPos--;
      } else {
        i++;
      }
    }
  }
  return elemPos;
}
void quickSort(std::vector<Train> &schedules, int start, int end) {
  if (start < end) {
    int elemPos = splittingByElem(schedules, start, end);

    quickSort(schedules, start, elemPos - 1);
    quickSort(schedules, elemPos, end);
  }
}

void merge(std::vector<Train> &schedules, int start, int end, int mid) {
  Train *tmp = new Train[end - start + 1];
  int i = start, j = mid + 1, k = 0;

  while ((i <= mid) && (j <= end)) {
    if (schedules[i] <= schedules[j]) {
      tmp[k] = schedules[i];
      i++;
    } else {
      tmp[k] = schedules[j];
      j++;
    }
    k++;
  }
  if (i > mid) {
    for (int h = j; h <= end; h++) {
      tmp[k] = schedules[h];
      k++;
    }
  } else {
    for (int h = i; h <= mid; h++) {
      tmp[k] = schedules[h];
      k++;
    }
  }
  for (int h = 0; h <= end - start; h++) {
    schedules[h + start] = tmp[h];
  }
  delete[] tmp;
}
void mergeSort(std::vector<Train> &schedules, int start, int end) {
  if (start < end) {
    long mid = (start + end) / 2;
    mergeSort(schedules, start, mid);
    mergeSort(schedules, mid + 1, end);
    merge(schedules, start, end, mid);
  }
}

void parseFile(std::vector<Train> &schedules, char *fileName) {
  std::ifstream fin;
  fin.open(fileName);

  char buf[100] = "";
  while (1) {
    fin.getline(buf, 100);
    if (strlen(buf) == 0) {
      break;
    }
    Train train = {};
    std::string str = buf;

    std::vector<std::string> parsedStrs = {};
    parseStr(str, parsedStrs, ' ');
    train.no = parsedStrs[0];
    train.data = parsedStrs[1];
    train.type = parsedStrs[2];
    train.time = parsedStrs[3];
    train.onRoad = parsedStrs[4];

    parseNo(train);
    parseData(train);
    parseTime(train);
    parseOnRoad(train);

    schedules.push_back(train);
  }

  fin.close();
}

void parseStr(std::string input, std::vector<std::string> &output, char sym) {
  unsigned int pos = 0;
  while (input.find(sym, 0) != std::string::npos) {
    pos = input.find(sym, 0);
    output.push_back(input.substr(0, pos));

    input.erase(0, pos + 1);
  }
  output.push_back(input);
}

void parseNo(Train &train) { train.noVal = std::stoi(train.no); }

void parseData(Train &train) {
  std::vector<std::string> parsedStrs = {};
  parseStr(train.data, parsedStrs, '.');

  train.dataVal = 10000 * std::stoi(parsedStrs[2]) +
                  100 * std::stoi(parsedStrs[1]) + std::stoi(parsedStrs[0]);
}

void parseTime(Train &train) {
  std::vector<std::string> parsedStrs = {};
  parseStr(train.time, parsedStrs, ':');

  train.timeVal = std::stoi(parsedStrs[0] + parsedStrs[1] + parsedStrs[2]);
}

void parseOnRoad(Train &train) {
  std::vector<std::string> parsedStrs = {};
  parseStr(train.onRoad, parsedStrs, ':');

  train.onRoadVal = std::stoi(parsedStrs[0] + parsedStrs[1] + parsedStrs[2]);
}

void printInfo(std::vector<Train> &schedules, std::string fileName) {
  unsigned int startTime, endTime;
  startTime = clock();

  if (fileName == "sort.txt") {
    sort(schedules.begin(), schedules.end(), comp);
  }
  if (fileName == "insertSort.txt") {
    insertSort(schedules);
  }
  if (fileName == "quickSort.txt") {
    quickSort(schedules, 0, static_cast<int>(schedules.size()) - 1);
  }
  if (fileName == "mergeSort.txt") {
    mergeSort(schedules, 0, static_cast<int>(schedules.size()) - 1);
  }

  endTime = clock();

  std::ofstream fout(fileName);
  for (size_t i = 0; i < schedules.size(); i++) {
    fout << i << ": " << schedules[i].no << " " << schedules[i].data << " "
         << schedules[i].type << " " << schedules[i].time << " "
         << schedules[i].onRoad << std::endl;
  }
  fout.close();

  unsigned int searchTime = (endTime - startTime) / CLOCKS_PER_SEC;
  std::cout << "Время выполнения " << fileName << " для " << schedules.size()
            << ": " << searchTime << std::endl;
}

bool operator==(Train &f, Train &s) {
  if (f.dataVal == s.dataVal && f.timeVal == s.timeVal && f.noVal == s.noVal &&
      f.onRoadVal == s.onRoadVal) {
    return true;
  }
  return false;
}

bool operator>(Train &f, Train &s) {
  if (f.dataVal > s.dataVal) {
    return true;
  }
  if (f.dataVal == s.dataVal && f.timeVal > s.timeVal) {
    return true;
  }
  if (f.dataVal == s.dataVal && f.timeVal == s.timeVal && f.noVal > s.noVal) {
    return true;
  }
  if (f.dataVal == s.dataVal && f.timeVal == s.timeVal && f.noVal == s.noVal &&
      f.onRoadVal > s.onRoadVal) {
    return true;
  }
  return false;
}

bool operator<(Train &f, Train &s) {
  if (f.dataVal < s.dataVal) {
    return true;
  }
  if (f.dataVal == s.dataVal && f.timeVal < s.timeVal) {
    return true;
  }
  if (f.dataVal == s.dataVal && f.timeVal == s.timeVal && f.noVal < s.noVal) {
    return true;
  }
  if (f.dataVal == s.dataVal && f.timeVal == s.timeVal && f.noVal == s.noVal &&
      f.onRoadVal < s.onRoadVal) {
    return true;
  }
  return false;
}

bool operator>=(Train &f, Train &s) {
  if (f == s) {
    return true;
  }
  if (f > s) {
    return true;
  }
  return false;
}

bool operator<=(Train &f, Train &s) {
  if (f == s) {
    return true;
  }
  if (f < s) {
    return true;
  }
  return false;
}

void printSchedules(std::vector<Train> &schedules) {
  std::cout << std::endl;
  for (size_t i = 0; i < schedules.size(); i++) {
    std::cout << i << ": " << schedules[i].no << " " << schedules[i].data << " "
              << schedules[i].type << " " << schedules[i].time << " "
              << schedules[i].onRoad << std::endl;
  }
}
