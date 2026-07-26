# strtime

- C 库函数 size_t strftime(char *str, size_t maxsize, const char *format, const struct tm *timeptr) 根据 format 中定义的格式化规则，格式化结构 timeptr 表示的时间，并把它存储在 str 中。

- 下面是 strftime() 函数的声明。
```cpp
size_t strftime(char *str, size_t maxsize, const char *format, const struct tm *timeptr)
```

## 参数
- str -- 这是指向目标数组的指针，用来复制产生的 C 字符串。
- maxsize -- 这是被复制到 str 的最大字符数。
- format -- 这是 C 字符串，包含了普通字符和特殊格式说明符的任何组合。这些格式说明符由函数替换为表示 tm 中所指定时间的相对应值。格式说明符是：[见文章](https://www.runoob.com/cprogramming/c-function-strftime.html)
- timeptr -- 这是指向 tm 结构的指针，该结构包含了一个被分解为以下各部分的日历时间：
```cpp
struct tm {
   int tm_sec;         /* 秒，范围从 0 到 59                */
   int tm_min;         /* 分，范围从 0 到 59                */
   int tm_hour;        /* 小时，范围从 0 到 23                */
   int tm_mday;        /* 一月中的第几天，范围从 1 到 31                    */
   int tm_mon;         /* 月份，范围从 0 到 11                */
   int tm_year;        /* 自 1900 起的年数                */
   int tm_wday;        /* 一周中的第几天，范围从 0 到 6                */
   int tm_yday;        /* 一年中的第几天，范围从 0 到 365                    */
   int tm_isdst;       /* 夏令时                        */    
};
```

## 返回值
- 如果产生的 C 字符串小于 size 个字符（包括空结束字符），则会返回复制到 str 中的字符总数（不包括空结束字符），否则返回零。
