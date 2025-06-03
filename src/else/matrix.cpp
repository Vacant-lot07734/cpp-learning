//
// Created by Vacant lot on 2025/4/22.
//
// 1 2 3
// 4 5 6
// 7 8 9
#include<vector>
#include<iostream>
using namespace std;

template<size_t m, size_t n >
// using matrix = vector<m,vector<int>(n)>; error
using matrix = std::array<std::array<int, n>, m>;

template<size_t m, size_t k, size_t n>
auto matrix_mul(const matrix<m, k> &a, const matrix<k, n> &b) {
    matrix<m, n> ret{};
    for (size_t i = 0; i < m; ++i ) {
        for (size_t r = 0; r < k; ++r ) {
            if (a[i][r] == 0) continue;
            for (int j = 0; j < n; ++j ) {
                ret[i][j] += a[i][r] * b[r][j];
            }
        }
    }
    return ret;
}

void func1(vector<vector<int> > &matrix) {
    // 1 2 3 6 9 8 7 4 5
    int left = 0, right = matrix[0].size() - 1, top = 0, bottom = matrix.size() - 1;
    while (left <= right && top <= bottom) {
        for (int col = left; col <= right; col++) {
            std::cout << matrix[left][col] << " ";
        }
        top++;
        for (int row = top; row <= bottom; row++) {
            std::cout << matrix[row][right] << " ";
        }
        right--;
        for (int col = right; col >= left; col--) {
            std::cout << matrix[bottom][col] << " ";
        }
        bottom--;
        for (int row = bottom; row >= top; row--) {
            std::cout << matrix[row][left] << " ";
        }
        left++;
    }
}
// 1 2 3
// 4 5 6
// 7 8 9
void func2(vector<vector<int> > &matrix) {
    // 1 2 4 7 5 3 6 8 9
    int end = matrix[0].size() + matrix.size() - 2;
    int dir = -1, x = 0, y = 0;
    for (int i = 0; i <= end; i++) {
        while (x >= 0 && y >= 0 && x < matrix.size() && y < matrix[0].size()) {
            std::cout<<matrix[x][y]<<" ";
            x-=dir;
            y+=dir;
        }
        if (dir == -1) {
            x = min((int)matrix.size() - 1, x);
            y = i + 1 - x;
        }
        else {
            y = min((int) matrix[0].size() - 1, y);
            x = i + 1 - y;
        }
        dir = -dir;
    }
}