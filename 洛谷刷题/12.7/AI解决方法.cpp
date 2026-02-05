#include <iostream>
#include <iomanip>
#include <cmath> // 用于 ceil 函数
using namespace std;

int main()
{
    int s, v;

    // 输入距离和速度
    cin >> s >> v;

    // 输入验证
    if (v <= 0)
    {
        cerr << "错误：速度必须大于0" << endl;
        return 1;
    }
    if (s <= 0)
    {
        cerr << "错误：距离必须大于0" << endl;
        return 1;
    }

    // 计算步行时间（向上取整）
    // 方法1: 使用 ceil 函数（需要转换为浮点数）
    // int walk_time = ceil(static_cast<double>(s) / v);

    // 方法2: 整数向上取整技巧 (a + b - 1) / b
    int walk_time = (s + v - 1) / v;

    // 加上额外10分钟
    int total_time_needed = walk_time + 10;

    // 计算最晚出发时间
    // 8:00 = 8 * 60 = 480分钟
    int latest_departure_minutes = 8 * 60 - total_time_needed;

    // 处理跨天情况（如果出发时间在前一天）
    if (latest_departure_minutes < 0)
    {
        latest_departure_minutes += 24 * 60; // 加上一天的分钟数
    }

    // 转换为小时和分钟
    int hour = latest_departure_minutes / 60;
    int minute = latest_departure_minutes % 60;

    // 输出，保持两位格式
    cout << setw(2) << setfill('0') << hour << ":"
         << setw(2) << setfill('0') << minute << endl;

    return 0;
}