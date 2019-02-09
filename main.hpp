#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/types.hpp>

#define REP(i, n) for (int i = 0, i##_len = (n); i < i##_len; ++i)
using namespace std;

class ColoredSort {
  public:
    ColoredSort(int sz);
    void bubbleSort();
    void insertionSort();
    void mergeSort(int begin, int end);
    void save_result(char *filename);
    void rotate90();

  private:
    const int sz;
    cv::Mat v;
    vector<int> current_state;
};
