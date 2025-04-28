#include <iostream>
using namespace std;

// Hàm kiểm tra xem có thể vận chuyển tất cả gói hàng trong `days` ngày với sức chứa tàu `capacity` hay không.
bool canShipInDays(int a[], int n, int days, int capacity)
{
    int currentWeight = 0;
    int dayCount = 1;  // Bắt đầu với ngày đầu tiên

    for (int i = 0; i < n; i++)
    {
        if (currentWeight + a[i] > capacity)
        {
            dayCount++;  // Cần một ngày mới để vận chuyển gói hàng này
            currentWeight = a[i];  // Bắt đầu ngày mới với gói hàng này
            if (dayCount > days)
            {
                return false;  // Nếu vượt quá số ngày cho phép, trả về false
            }
        }
        else
        {
            currentWeight += a[i];  // Thêm gói hàng vào ngày hiện tại
        }
    }
    return true;  // Tất cả gói hàng có thể vận chuyển trong số ngày đã cho
}

// Hàm tìm sức chứa tàu tối thiểu có thể vận chuyển tất cả gói hàng trong `days` ngày.
int shipWithinDays(int a[], int n, int days)
{
    // Tìm sức chứa tối thiểu là trọng lượng gói hàng nặng nhất
    int left = a[0];
    for (int i = 1; i < n; i++)
    {
        if (a[i] > left)
        {
            left = a[i];
        }
    }

    // Tìm tổng tất cả các gói hàng (sức chứa tối đa)
    int right = 0;
    for (int i = 0; i < n; i++)
    {
        right += a[i];
    }

    // Dùng binary search để tìm sức chứa tàu tối thiểu
    while (left < right)
    {
        int mid = (right + left) / 2;

        if (canShipInDays(a, n, days, mid))
        {
            right = mid;  // Nếu sức chứa `mid` có thể vận chuyển trong `days` ngày, thử sức chứa nhỏ hơn
        }
        else
        {
            left = mid + 1;  // Nếu không thể, tăng sức chứa
        }
    }
    return left;  // Khi left == right, chúng ta tìm thấy sức chứa tối thiểu
}

int main()
{
    int a[10000];
    int n, days;

    // Nhập số lượng gói hàng và số ngày
    cin >> n;

    // Nhập trọng lượng các gói hàng
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    cin>>days;
    // Gọi hàm để tìm sức chứa tàu tối thiểu
    cout << shipWithinDays(a, n, days);
    return 0;
}



/*
canShipInDays:

Hàm này kiểm tra xem liệu với sức chứa tàu là capacity, chúng ta có thể vận chuyển tất cả các gói hàng trong số days ngày hay không.

Nếu việc vận chuyển vượt quá sức chứa trong một ngày, chúng ta bắt đầu ngày mới và cộng thêm số ngày cần thiết.

shipWithinDays:

Đây là hàm sử dụng binary search để tìm sức chứa tàu tối thiểu có thể vận chuyển tất cả các gói hàng trong số days ngày.

Chúng ta tìm ra sức chứa tối thiểu là max(a) (trọng lượng gói hàng nặng nhất) và sức chứa tối đa là tổng tất cả các gói hàng.

Sau đó, chúng ta tiến hành tìm kiếm nhị phân để thu hẹp phạm vi và tìm sức chứa tối thiểu.


Mảng a lưu trọng lượng các gói hàng.

Dùng cin để nhập các giá trị vào mảng và số ngày.

Nhập đầu vào:

Đầu vào gồm số lượng gói hàng n , dãy số trọng lượng của các gói hàng, và số ngày days.

Phân tích độ phức tạp:
Binary Search: Thực hiện tìm kiếm nhị phân trong phạm vi từ max(a) đến sum(a), do đó số lần tìm kiếm là O(log(S)), với S là tổng trọng lượng các gói hàng.

Kiểm tra khả năng vận chuyển (canShipInDays): Duyệt qua tất cả các gói hàng một lần, tức là O(n).*/
