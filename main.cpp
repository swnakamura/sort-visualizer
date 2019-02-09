#include "main.hpp"
#include <opencv2/opencv.hpp>

ColoredSort::ColoredSort(int sz) : sz(sz) {
    REP(i, sz) { current_state.push_back((i * 255) / sz); }
    random_shuffle(current_state.begin(), current_state.end());
    cv::Mat buf(1, current_state.size(), CV_32SC1, current_state.data());
    v.push_back(buf);
}

void ColoredSort::insertionSort() {
    REP(i, sz - 1) {
        if (current_state[i] > current_state[i + 1]) {
            int j = i;
            while (current_state[j] > current_state[j + 1]) {
                swap(current_state[j], current_state[j + 1]);
                j--;
            }
            cv::Mat buf(1, current_state.size(), CV_32SC1,
                        current_state.data());
            v.push_back(buf);
        }
    }
}

void ColoredSort::mergeSort(int begin, int end) {
    if (begin + 1 == end)
        return;
    int mid = (begin + end) / 2;
    this->mergeSort(begin, mid);
    this->mergeSort(mid, end);

    int idx = 0, lidx = begin, ridx = mid;
    int buf[end - begin];

    while (idx <= end - begin) {
        if (lidx == mid) {
            buf[idx++] = current_state[ridx++];
        } else if (ridx == end || current_state[lidx] < current_state[ridx]) {
            buf[idx++] = current_state[lidx++];
        } else {
            buf[idx++] = current_state[ridx++];
        }
    }

    for (int i = begin; i < end; i++) {
        current_state[i] = buf[i - begin];
    }
    cv::Mat bufarray(1, current_state.size(), CV_32SC1, current_state.data());
    v.push_back(bufarray);
    return;
}

void ColoredSort::bubbleSort() {
    REP(i, sz - 1) {
        for (int j = 0; j < sz - 1; j++) {
            if (current_state[j] > current_state[j + 1]) {
                swap(current_state[j], current_state[j + 1]);
                cv::Mat buf(1, current_state.size(), CV_32SC1,
                            current_state.data());
                v.push_back(buf);
            }
        }
    }
}

void ColoredSort::save_result(char *filename) {
    cv::imwrite(filename, this->v);
}

void ColoredSort::rotate90() {
    double angle = 90;
    cv::Mat dst;
    cv::Point2f pt(v.cols / 2., v.rows / 2.);
    cv::Mat r = getRotationMatrix2D(pt, angle, 1.0);
    warpAffine(v, dst, r, cv::Size(v.cols, v.rows));
}

int main(int argc, char **argv) {
    ColoredSort cs = ColoredSort(atoi(argv[1]));
    cs.bubbleSort();
    // cs.insertionSort();
    // cs.mergeSort(0, atoi(argv[1]));
    cs.save_result("test.png");
}
