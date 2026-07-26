
## 📚 FTXUI 中 `Render()` 完全指南

---

### 一、什么是 `Render()`？

| 项目 | 说明 |
|------|------|
| **定义** | `ComponentBase` 类的**成员方法** |
| **作用** | 把组件的**当前状态**转换成 **Element**（屏幕画面） |
| **返回值** | `Element`（DOM 元素树） |
| **调用者** | FTXUI 框架自动调用 + 你手动调用 |

---

### 二、调用场景

| 场景 | 谁调用 | 示例 |
|------|--------|------|
| **框架刷新屏幕** | FTXUI 自动 | `screen.Loop(renderer)` 内部自动调用 `renderer->Render()` |
| **子组件嵌入** | 你手动 | `left_menu_->Render()` 把子组件画出来 |
| **自定义渲染** | 你手动 | 在 Renderer 的 Lambda 中调用子组件的 `Render()` |

---

### 三、代码中的 `Render()`

#### 1. 自动调用（你看不到）
```cpp
screen.Loop(renderer);  // ← 框架内部会反复调用 renderer->Render()
```

#### 2. 手动调用（你写出来）
```cpp
auto renderer = Renderer(container, [&] {
    return vbox({
        left_menu_->Render(),   // ← 手动调用
        right_menu_->Render(),  // ← 手动调用
        text("Hello"),
    });
});
```

---

### 四、执行时机

| 触发条件 | 说明 |
|----------|------|
| 程序启动 | 首次显示界面 |
| 用户按键 | 上下左右、Enter 等 |
| 状态变化 | `selected`、`text` 等变量改变 |
| 动画帧 | 需要持续更新画面时 |
| 终端窗口变化 | 大小调整等 |

---

### 五、`Render()` 的特点

| 特点 | 说明 |
|------|------|
| **纯函数** | 只读取状态，**不修改**状态 |
| **每次重建** | 每次都创建新的 Element 树 |
| **可缓存** | 性能优化时可以缓存结果 |
| **递归调用** | 父组件调用子组件的 `Render()` |

---

### 六、错误用法 ❌

```cpp
// ❌ 在 Render() 里修改状态
Element Render() {
    selected++;  // 导致无限循环！
    return text("Hello");
}

// ❌ 在 Render() 里做耗时操作
Element Render() {
    auto data = ReadFile("big.txt");  // 每次都读文件，卡顿！
    return text(data);
}
```

---

### 七、正确用法 ✅

```cpp
// ✅ 只读取状态
Element Render() {
    return text("选中：" + std::to_string(selected));
}

// ✅ 调用子组件的 Render()
Element Render() override {
    return vbox({
        menu_->Render(),   // 子组件自己画自己
        text("状态正常"),
    });
}

// ✅ 条件渲染
Element Render() {
    if (selected == 0) {
        return text("请选择一个选项");
    }
    return menu_->Render();
}
```

---

### 八、执行流程

```
用户操作（按键/鼠标）
    ↓
组件处理事件，更新状态
    ↓
FTXUI 标记"需要重绘"
    ↓
框架调用 Renderer 的 Render()  ← 自动
    ↓
Renderer 的 Lambda 执行
    ├─ 读取最新状态
    ├─ 调用子组件的 Render()  ← 手动
    ├─ 构建 Element 树
    └─ 返回 Element
    ↓
屏幕刷新，显示新画面
```

---

### 九、一句话总结

> **`Render()` 就是把"数据"变成"画面"的方法，FTXUI 会在需要时自动调用它，你只需要在自定义渲染中调用子组件的 `Render()` 来把它们画出来。**

---

### 十、核心记忆点

```
Render() = 画图工具

输入：当前状态（selected、text 等变量）
输出：Element（屏幕画面）
规则：只读不改，纯函数
调用：框架自动 + 你手动（子组件）
频率：每次刷新都执行
```

---

