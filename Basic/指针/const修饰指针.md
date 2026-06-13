# const修饰指针

## const修饰指针的三种情况

### 1. **常量指针（const修饰指针指向的内容）**
```cpp
const int* p;  // 或 int const* p;
```
- **特点**：指针**指向的内容**不可修改，但**指针本身**可以指向其他地址
- **记忆口诀**："常量指针" → 指向的内容是常量
- **示例**：
```cpp
int a = 10, b = 20;
const int* p = &a;  // p指向a

// *p = 30;  // ❌ 错误：不能通过p修改a的值
p = &b;     // ✅ 正确：p可以改为指向b

a = 30;     // ✅ 正确：a本身不是const，可以直接修改
```

### 2. **指针常量（const修饰指针本身）**
```cpp
int* const p;
```
- **特点**：**指针本身**的指向不可修改，但**指向的内容**可以修改
- **记忆口诀**："指针常量" → 指针本身是常量
- **示例**：
```cpp
int a = 10, b = 20;
int* const p = &a;  // p必须初始化

*p = 30;    // ✅ 正确：可以修改a的值
// p = &b;  // ❌ 错误：p不能指向其他地址
```

### 3. **常量指针常量（既修饰指针又修饰内容）**
```cpp
const int* const p;
```
- **特点**：**指针本身**的指向和**指向的内容**都不可修改
- **记忆口诀**：双const → 双不可变
- **示例**：
```cpp
int a = 10, b = 20;
const int* const p = &a;  // p必须初始化

// *p = 30;  // ❌ 错误：不能修改a的值
// p = &b;   // ❌ 错误：不能改变指向
```

## 对比表格

| 类型 | 语法 | 指针指向可改？ | 指向内容可改？ | 记忆口诀 |
|------|------|---------------|---------------|----------|
| **常量指针** | `const int* p` | ✅ 可以 | ❌ 不可以 | "指向常量的指针" |
| **指针常量** | `int* const p` | ❌ 不可以 | ✅ 可以 | "指针是常量" |
| **常量指针常量** | `const int* const p` | ❌ 不可以 | ❌ 不可以 | "都不可变" |

## 判断技巧

**从左往右读法**：
```cpp
const int* p;     // 读作：p是一个指针，指向const int（常量整数）
int* const p;     // 读作：p是一个const指针，指向int
const int* const p; // 读作：p是一个const指针，指向const int
```

**星号(*)分界法**：
- const在`*`**左边** → 修饰**指向的内容**
- const在`*`**右边** → 修饰**指针本身**

## 实际应用场景

### 1. **常量指针：保护函数参数不被修改**
```cpp
// 函数内不能修改str的内容
void printString(const char* str) {
    // *str = 'A';  // ❌ 编译错误
    cout << str;
}
```

### 2. **指针常量：固定指向某个资源**
```cpp
int data = 100;
int* const dataPtr = &data;  // 指针始终指向data

class Database {
public:
    Database* const getInstance() {
        static Database* const instance = new Database();
        return instance;  // 返回固定指针
    }
};
```

### 3. **常量指针常量：只读访问固定资源**
```cpp
const int MAX_SIZE = 100;
const int* const maxPtr = &MAX_SIZE;  // 完全只读

// 常用于硬件寄存器访问
const volatile uint32_t* const STATUS_REG = (uint32_t*)0x40021000;
```

## 练习：判断指针类型
```cpp
int a = 10, b = 20;

// 判断以下哪些正确：
const int* p1 = &a;
// p1 = &b;     // ✅
// *p1 = 30;    // ❌

int* const p2 = &a;
// p2 = &b;     // ❌
// *p2 = 30;    // ✅

const int* const p3 = &a;
// p3 = &b;     // ❌
// *p3 = 30;    // ❌
```

记住关键点：
- **谁在const前面谁就是常量**
- **const * 可改指向，* const 可改内容**