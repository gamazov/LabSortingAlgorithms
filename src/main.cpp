/*!
\file
\brief https://github.com/gamazov/LabSortingAlgorithms
\author Mazov Grigiriy
*/

#include <fstream>
#include <iostream>
#include <vector>

/*!
\fn void parseStr(std::string input, std::vector<std::string> &output, char sym)
\brief Finds elements separated by the sym symbol in the string str and writes the result to output
\param[in] input The string in which the search is performed
\param[in,out] output Found substrings
\param[in] sym The character by which to divide the string
*/

/*!
\fn void parseNo(Train &train)
\brief Converts the string no to an unsigned number for comparison
\param[in,out] train Structure to be filled in
*/

/*!
\fn void parseData(Train &train)
\brief Converts the data string to an unsigned number for comparison
\param[in,out] train Structure to be filled in
*/

/*!
\fn void parseTime(Train &train)
\brief Converts the string time to an unsigned number for comparison
\param[in,out] train Structure to be filled in
*/

/*!
\fn void parseOnRoad(Train &train)
\brief Converts the string on Road to an unsigned number for comparison
\param[in,out] train Structure to be filled in
*/

/*!
\fn void parseFile(std::vector<Train> &schedules, char *fileName)
\brief All schedule entries are filled in by reading data from the transmitted file
\param[in,out] schedules Schedule to be filled in
\param[in] fileName The file in which the search takes place
*/

/*!
\fn void printSchedules(std::vector<Train> &schedules)
\brief Displays the entire schedule
\param[in] schedules Schedule
*/

/*!
\fn void insertSort(std::vector<Train> &schedules)
\brief Insert sort
\param[in,out] schedules Sortable schedule
*/

/*!
\fn int splittingByElem(std::vector<Train> &schedules, int start, int elemPos)
\brief Separation function
\param[in,out] schedules Sortable schedule
\param[in] start The beginning of the sorted array
\param[in] elemPos Found element
\return Returns the index of the reference element
*/

/*!
\fn void quickSort(std::vector<Train> &schedules, int start, int end)
\brief Quick sort
\param[in,out] schedules Sortable schedule
\param[in] start The beginning of the sorted array
\param[in] end End of the sorted array
*/

/*!
\fn void merge(std::vector<Train> &schedules, int start, int end, int mid)
\brief Combining arrays
\param[in,out] schedules Sortable schedule
\param[in] start The beginning of the sorted array
\param[in] end End of the sorted array
\param[in] mid The middle of the sorted array
*/

/*!
\fn void mergeSort(std::vector<Train> &schedules, int start, int end)
\brief Merge sort(
\param[in,out] schedules Sortable schedule
\param[in] start The beginning of the sorted array
\param[in] end End of the sorted array
*/

/*!
\fn bool comp(Train &first, Train &second)
\brief Comparator for std::sort()
\param[in] first Left compared
\param[in] second Right compared
\return Returns true - the right is smaller than the left, false - otherwise
*/

/*!
\fn void printInfo(std::vector<Train> &schedules, std::string fileName)
\brief Sorts by displaying the time spent and recording the sorted schedule
\param[in] schedules Sortable schedule
\param[in] fileName Type of sorting and where to write
*/

/*!
\brief Describes the recording of the train schedule
*/
struct Train {
  //! Departure date
  std::string data;
  //! Departure time
  std::string time;
  //! Train number
  std::string no;
  //! Travel time
  std::string onRoad;
  //! Type of train
  std::string type;

  //! Date represented as an unsigned number for comparison
  unsigned int dataVal = 0;
  //! Departure time, represented as an unsigned number for comparison
  unsigned int timeVal = 0;
  //! A number represented as an unsigned number for comparison
  unsigned int noVal = 0;
  //! Travel time, represented as an unsigned number for comparison
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

void insertSort(std::vector<Train> &schedules);
int splittingByElem(std::vector<Train> &schedules, int start, int elemPos);
void quickSort(std::vector<Train> &schedules, int start, int end);
void merge(std::vector<Train> &schedules, int start, int end, int mid);
void mergeSort(std::vector<Train> &schedules, int start, int end);

int main(int argc, char *argv[]) {
  if (argc == 1) {
    std::cout << "No parametrs";
    return 1;
  }
  std::vector<Train> schedules;
  parseFile(schedules, argv[1]);

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
    fout << schedules[i].no << " " << schedules[i].data
      << " " << schedules[i].type << " " << schedules[i].time
      << " " << schedules[i].onRoad << std::endl;
  }
  fout.close();

  unsigned int searchTime = 1000.0 * (endTime - startTime) / CLOCKS_PER_SEC;
  std::cout << "Execution time for " << schedules.size()
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
    std::cout << i << ": " << schedules[i].no << " " << schedules[i].data
      << " " << schedules[i].type << " " << schedules[i].time
      << " " << schedules[i].onRoad << std::endl;
  }
}
