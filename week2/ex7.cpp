#include <iostream>
#include <algorithm> // Dùng để sắp xếp mảng
using namespace std;

void threeSum(int a[], int n) {
    // Sắp xếp mảng để dễ dàng tìm các triplets
    sort(a, a + n);

    // Duyệt qua mảng
    for (int i = 0; i < n - 2; i++) {
        // Tránh trùng lặp: nếu phần tử hiện tại giống phần tử trước đó, bỏ qua
        if (i > 0 && a[i] == a[i - 1]) continue;

        int left = i + 1, right = n - 1;

        // Dùng hai con trỏ để tìm hai số còn lại có tổng bằng -a[i]
        while (left < right) {
            int sum = a[i] + a[left] + a[right];

            if (sum == 0) {
                // In ra kết quả hợp lệ
                cout << "[" << a[i] << ", " << a[left] << ", " << a[right] << "]" << endl;

                // Tránh trùng lặp cho chỉ số `left` và `right`
                while (left < right && a[left] == a[left + 1]) left++;
                while (left < right && a[right] == a[right - 1]) right--;

                // Tiến tới các phần tử tiếp theo
                left++;
                right--;
            } else if (sum < 0) {
                // Nếu tổng nhỏ hơn 0, dịch con trỏ `left` về bên phải để tăng tổng
                left++;
            } else {
                // Nếu tổng lớn hơn 0, dịch con trỏ `right` về bên trái để giảm tổng
                right--;
            }
        }
    }
}

int main() {
    int a[10000] = {-1, 0, 1, 2, -1, -4}; // Mảng ví dụ
    int n = 6; // Kích thước mảng

    cout << "The triplets are:" << endl;
    threeSum(a, n);

    return 0;
}
