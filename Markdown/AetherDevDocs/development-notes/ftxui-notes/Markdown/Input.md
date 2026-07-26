# Input 
## 创建一个输入框

- Syntax: Input(&qwq, "qwq", qwqOptions)
- &qwq:指针类型，用于存储用户输入
- qwq:要显示的提示文字
- qwqOptions:设置样式，与另一种方式中的InputOption功能相似

## InputOption
- 基本结构：
```cpp
struct InputOption {
    StringRef content = "";              // 输入框内容
    StringRef placeholder = "";          // 占位符文本
    std::function<Element(InputState)> transform;  // 自定义渲染
    Ref<bool> password = false;          // 密码模式
    Ref<bool> multiline = true;          // 多行模式
    Ref<bool> insert = true;             // 插入/覆盖模式
    std::function<void()> on_change = []{};  // 内容改变回调
    std::function<void()> on_enter = []{};   // 回车键回调
    Ref<int> cursor_position = 0;        // 光标位置
};
```

- content-输入内容
- placeholder - 占位符
- password - 密码模式
- multiline - 多行模式
- on_change - 内容改变回调
- on_enter - 回车键回调
- transform - 自定义渲染
- insert - 插入/覆盖模式
- cursor_position - 光标位置
