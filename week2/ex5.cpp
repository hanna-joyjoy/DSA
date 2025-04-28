#include <iostream>
using namespace std;

int minSubArrayLen(int target, int a[], int n)
{
    int left = 0, sum = 0, minLen = 1000000;

    for (int right = 0; right < n; ++right)
    {
        sum += a[right];

        // Khi tổng của đoạn con >= target, cố gắng thu nhỏ đoạn con
        while (sum >= target)
        {
            minLen = min(minLen, right - left + 1);
            sum -= a[left];
            left++;
        }
    }

    return (minLen == 1000000) ? 0 : minLen;
}

int main() {
    int target = 7;
    int a[10000] = {2, 3, 1, 2, 4, 3}; // Mảng dữ liệu
    int n = 6;  // Kích thước mảng

    cout << "Minimal length of subarray: " << minSubArrayLen(target, a, n) << endl;
    return 0;
}

/*Hàm minSubArrayLen sẽ tính toán độ dài tối thiểu của một subarray (đoạn con) có tổng lớn hơn hoặc bằng target bằng cách sử dụng phương pháp sliding window.

Chúng ta sẽ tăng right (di chuyển cửa sổ sang phải) và sau đó thu hẹp cửa sổ từ bên trái (left) khi tổng của cửa sổ đã đủ lớn.*/
