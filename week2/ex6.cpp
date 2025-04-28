#include <iostream>
using namespace std;

string twoSumSorted(int a[], int n, int target)
{
    int left = 0, right = n - 1;

    while (left < right)
    {
        int sum = a[left] + a[right];
        if (sum == target)
        {
            return "YES";
        }
        else if (sum < target)
            {
            left++;  // Nếu tổng nhỏ hơn target, tăng left
            }
            else
            {
            right--;  // Nếu tổng lớn hơn target, giảm right
            }
    }

    return "NO";  // Không tìm thấy cặp số nào có tổng bằng target
}

int main() {
    int a[10000] = {1, 2, 3, 4, 6};
    int n = 5;
    int target = 5;

    cout << twoSumSorted(a, n, target) << endl;
    return 0;
}
/*Hàm twoSumSorted sử dụng phương pháp two-pointer để tìm hai số trong mảng có tổng bằng target. Một con trỏ bắt đầu từ đầu mảng (left) và một con trỏ bắt đầu từ cuối mảng (right).

Nếu tổng của hai số tại các con trỏ bằng target, trả về "YES". Nếu tổng nhỏ hơn target, di chuyển left sang phải. Nếu tổng lớn hơn target, di chuyển right sang trái.*/
