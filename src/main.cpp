// 14
// Массив данных с расписанием поездов:
// Расписание содержит номер поезда, дата отправления, тип  поезда, (скорый,
// пассажирский, товарный), время отправления,  время в пути (сравнение по полям
// – дата отправления,  время отправления, номер поезда, время в пути (по
// убыванию)) 14) 14, в, е, ж

// а) Сортировка выбором
// б) Сортировка пузырьком
// в) Сортировка простыми вставками
// г) Шейкер-сортировка
// д) Пирамидальная сортировка
// е) Быстрая сортировка
// ж) Сортировка слиянием

#include <fstream>
#include <iostream>
#include <vector>

struct Train {
  std::string data;
  std::string time;
  std::string no;
  std::string onRoad;
  std::string type;

  unsigned int dataVal = 0;
  unsigned int timeVal = 0;
  unsigned int noVal = 0;
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

// в) Сортировка простыми вставками
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

// е) Быстрая сортировка
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

// ж) Сортировка слиянием
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

  unsigned int searchTime = endTime - startTime;
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
  if (f.dataVal == s.dataVal && f.timeVal == s.timeVal && f.noVal == s.noVal && f.onRoadVal > s.onRoadVal) {
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
  if (f.dataVal == s.dataVal && f.timeVal == s.timeVal && f.noVal == s.noVal && f.onRoadVal < s.onRoadVal) {
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
