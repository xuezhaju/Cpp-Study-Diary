
---

## 📊 FTXUI 完整组件与 DOM 元素速查表（修正版）

| 模块 | 组件 / 元素 | 用途 / 作用 | 基本语法与示例 |
| :--- | :--- | :--- | :--- |
| **screen** | `Screen` | 字符网格画布，最底层的绘图目标。 | `auto screen = Screen::Create(Dimension::Full());` |
| **screen** | `Pixel` | 屏幕上的单个字符像素，包含字符、颜色和样式。 | `Pixel('A', Color::Red)`（内部使用，很少直接构造） |
| **screen** | `Terminal` | 检测终端尺寸和特性。 | `Terminal::Size()` |
| **dom** | `text("...")` | 显示一段静态文本。 | `text("Hello FTXUI")` |
| **dom** | `vtext("...")` | 垂直显示文本（每个字符换行）。 | `vtext("垂直")` |
| **dom** | `paragraph("...")` | 自动换行的段落文本（根据容器宽度）。 | `paragraph("长文本...")` |
| **dom** | `paragraphAlignLeft/Right/Center/Justify` | 设置段落对齐方式。 | `paragraphAlignCenter("居中文本")` |
| **dom** | `hbox({...})` | **水平布局**，将多个元素排成一行。 | `hbox({text("A"), text("B")})` |
| **dom** | `vbox({...})` | **垂直布局**，将多个元素排成一列。 | `vbox({text("Top"), text("Bottom")})` |
| **dom** | `dbox({...})` | **堆叠布局**，子元素重叠绘制（类似 CSS 的 `position: absolute`）。 | `dbox({background, foreground})` |
| **dom** | `gridbox({...})` | 网格布局（类似表格，所有单元格大小一致）。 | `gridbox({{text("A"), text("B")}, {text("C"), text("D")}})` |
| **dom** | `flexbox({...}, config)` | 弹性盒子布局，支持换行和复杂排列。 | `flexbox({text("A"), text("B")}, FlexboxConfig().SetGap(1))` |
| **dom** | `gauge(float)` | 进度条，值范围 0.0 到 1.0。 | `gauge(0.75)` |
| **dom** | `gaugeDirection(dir)` | 指定进度条方向（上/下/左/右）。 | `gauge(0.5) \| gaugeDirection(GaugeDirection::Down)` |
| **dom** | `separator()` | 绘制分隔线（垂直或水平，根据上下文）。 | `vbox({text("上"), separator(), text("下")})` |
| **dom** | `separatorEmpty()` | 绘制空白分隔线（占据空间但不可见）。 | `vbox({text("上"), separatorEmpty(), text("下")})` |
| **dom** | `Canvas(width, height)` | 字符画布，可绘制图形（点、线、圆等）。 | `Canvas(10, 5); canvas.DrawPointCircle(5, 2, 2);` |
| **dom** | `canvas(&canvas)` | 将画布转换为 Element。 | `canvas(&my_canvas)` |
| **dom** | `Table` | 创建数据表格（比 gridbox 更强大，支持样式化）。 | `Table table({{"Name","Age"}, {"Alice","30"}});` |
| **dom** | `Table.Select` | 选择表格区域进行样式化。 | `table.SelectAll().Border(...)` |
| **dom** | `window("标题", element)` | **窗口组件**，带标题栏的边框容器。 | `window("设置", text("内容"))` |
| **dom** | `border` | 添加边框。 | `text("内容") \| border` |
| **dom** | `borderEmpty` | 添加空边框（占位，不可见）。 | `text("内容") \| borderEmpty` |
| **dom** | `borderRounded` | 添加圆角边框。 | `text("内容") \| borderRounded` |
| **dom** | `borderDouble` | 添加双线边框。 | `text("内容") \| borderDouble` |
| **dom** | `borderLight` | 添加轻边框（细线）。 | `text("内容") \| borderLight` |
| **dom** | `borderHeavy` | 添加重边框（粗线）。 | `text("内容") \| borderHeavy` |
| **dom** | `flex` | 使元素在容器中尽可能伸展（`flex_grow(1) \| flex_shrink(1)`）。 | `text("中间") \| flex` |
| **dom** | `flex_grow(n)` | 设置元素在容器中的拉伸系数（空间富余时膨胀）。 | `text("内容") \| flex_grow(2)` |
| **dom** | `flex_shrink(n)` | 设置元素在容器中的收缩系数（空间不够时压缩）。 | `text("内容") \| flex_shrink(1)` |
| **dom** | `notflex` | 移除元素的 flex 属性（恢复默认大小）。 | `text("内容") \| notflex` |
| **dom** | `frame` | 创建可滚动的视口（内容超出时可滚动）。 | `text("长内容...") \| frame` |
| **dom** | `vscroll_indicator` | 显示垂直滚动条指示器（需配合 `frame`）。 | `element \| vscroll_indicator` |
| **dom** | `hscroll_indicator` | 显示水平滚动条指示器（需配合 `frame`）。 | `element \| hscroll_indicator` |
| **dom** | `size(WIDTH/HEIGHT, LESS_THAN/EQUAL/GREATER_THAN, N)` | 限制元素尺寸。 | `element \| size(HEIGHT, LESS_THAN, 10)` |
| **dom** | `filler()` | 可伸缩的空白填充元素（类似 `flex` 但只填充空白）。 | `hbox({text("左"), filler(), text("右")})` |
| **dom** | `flexible(Element)` | 创建一个可伸缩的元素（同 `flex`）。 | `flexible(text("伸缩"))` |
| **dom** | `color(Color::Name)` | 设置文本前景色。 | `text("彩色") \| color(Color::Red)` |
| **dom** | `bgcolor(Color::Name)` | 设置文本背景色。 | `text("高亮") \| bgcolor(Color::Blue)` |
| **dom** | `bold` | 粗体。 | `text("粗体") \| bold` |
| **dom** | `italic` | 斜体。 | `text("斜体") \| italic` |
| **dom** | `dim` | 暗淡文本。 | `text("暗淡") \| dim` |
| **dom** | `underlined` | 下划线。 | `text("下划线") \| underlined` |
| **dom** | `strikethrough` | 删除线。 | `text("删除") \| strikethrough` |
| **dom** | `blink` | 闪烁（取决于终端支持）。 | `text("闪烁") \| blink` |
| **dom** | `inverted` | 反转前景色和背景色。 | `text("反转") \| inverted` |
| **dom** | `hyperlink(url)` | 添加可点击链接（终端支持）。 | `text("链接") \| hyperlink("https://example.com")` |
| **dom** | `decorator(Decorator)` | 组合多个装饰器。 | `decorator(bold \| color(Color::Red))` |
| **dom** | `linear_gradient(colors)` | 创建颜色渐变。 | `text("渐变") \| linear_gradient({Color::Red, Color::Blue})` |
| **dom** | `reflect(box)` | 获取元素位置和尺寸（用于调试）。 | `element \| reflect(my_box)` |
| **component** | `Button(label, callback)` | 按钮，点击触发回调。 | `Button("点我", [&]{ value++; })` |
| **component** | `Input(&string, placeholder)` | 单行文本输入框。 | `Input(&username, "输入用户名")` |
| **component** | `Input(&string, placeholder, validator)` | 带验证器的输入框。 | `Input(&num, "数字", [](char c){ return isdigit(c); })` |
| **component** | `Checkbox(label, &bool)` | 复选框，状态绑定 bool。 | `Checkbox("同意", &agreed)` |
| **component** | `Menu(&entries, &selected)` | 单选菜单。 | `Menu(&options, &option_selected)` |
| **component** | `Menu(&entries, &selected, MenuOption)` | 带选项配置的菜单（如 `on_enter` 回调）。 | `Menu(&options, &selected, MenuOption{.entries = ..., .on_enter = ...})` |
| **component** | `Tab(tabs, &selected)` | 标签页容器，按索引显示子组件。 | `Tab({comp1, comp2}, &tab_index)` |
| **component** | `Toggle(&entries, &selected)` | 切换按钮组（类似单选按钮，水平排列）。 | `Toggle(&options, &selected)` |
| **component** | `Slider(&value, min, max, step)` | 滑块，选择数值范围。 | `Slider(&volume, 0, 100, 1)` |
| **component** | `Radiobox(&entries, &selected)` | 单选按钮组（垂直排列）。 | `Radiobox(&options, &selected)` |
| **component** | `Dropdown(&entries, &selected)` | 下拉选择菜单。 | `Dropdown(&options, &selected)` |
| **component** | `MenuEntry(label, &selected)` | 菜单条目（用于自定义菜单）。 | `MenuEntry("选项", &is_selected)` |
| **component** | `Maybe(component, &show)` | 条件显示组件（根据 bool 变量控制显隐）。 | `Maybe(my_component, &visible)` |
| **component** | `Container::Horizontal({...})` | 水平容器，管理子组件焦点（左右切换）。 | `Container::Horizontal({Button1, Button2})` |
| **component** | `Container::Vertical({...})` | 垂直容器，管理子组件焦点（上下切换）。 | `Container::Vertical({Input1, Input2})` |
| **component** | `Container::Tab(tabs, &selected)` | 标签容器，切换子组件。 | `Container::Tab({comp1, comp2}, &index)` |
| **component** | `Container::Stacked({...})` | 堆叠容器，子组件重叠显示（事件同时处理）。 | `Container::Stacked({background, foreground})` |
| **component** | `Renderer(component, lambda)` | 渲染器，定义组件的外观。 | `Renderer(container, [&]{ return container->Render() \| border; });` |
| **component** | `Renderer(lambda)` | 无状态渲染器（纯静态界面）。 | `Renderer([&]{ return text("静态内容"); })` |
| **component** | `CatchEvent(component, handler)` | 捕获事件处理函数。 | `CatchEvent(comp, [&](Event e){ return handleEvent(e); })` |
| **component** | `ResizableSplit(left, right)` | 可拖拽分割器，用户可调整左右/上下面板比例。 | `ResizableSplit(left_panel, right_panel)` |
| **component** | `ScreenInteractive` | 交互屏幕，运行主循环。 | `auto screen = ScreenInteractive::FitComponent();` |
| **component** | `ScreenInteractive::Loop` | 启动交互主循环。 | `screen.Loop(component);` |
| **component** | `ScreenInteractive::ExitLoopClosure` | 获取退出循环的闭包（用于按钮/菜单的退出回调）。 | `auto exit = screen.ExitLoopClosure();` |
| **component** | `ScreenInteractive::TerminalOutput` | 使用当前终端作为输出（`App::TerminalOutput()` 的替代）。 | `auto screen = ScreenInteractive::TerminalOutput();` |
| **component** | `Event` | 表示一个用户输入事件（键盘/鼠标/终端）。 | `Event::Character('a')`, `Event::Mouse{...}` |
| **component** | `Event::Special` | 特殊键事件（方向键、功能键等）。 | `Event::ArrowUp`, `Event::Tab` |
| **component** | `Event::Mouse` | 鼠标事件（点击、滚动等）。 | `Event::Mouse{ .button = Mouse::Left, .motion = Mouse::Pressed }` |

---

## 📝 主要补充和纠正

| 序号 | 补充/纠正内容 |
|:---:|:---|
| 1 | **新增 `dbox`**：堆叠布局容器，子元素重叠绘制 |
| 2 | **新增 `window`**：带标题栏的边框容器 |
| 3 | **新增 `ResizableSplit`**：可拖拽分割器组件 |
| 4 | **修正 `flexbox`**：需要传入 `FlexboxConfig()` 配置 |
| 5 | **补充 `ScreenInteractive::TerminalOutput`**：与 `App::TerminalOutput()` 等价 |
| 6 | **补充 `Event::Special` 和 `Event::Mouse`**：事件类型的细分 |
| 7 | **修正 `Container::Stacked`**：说明"事件同时处理"的特性 |
| 8 | **补充 `gaugeDirection`**：明确需要 `gaugeDirection()` 装饰器 |
| 9 | **修正 `Screen` 的 Pixel**：说明是内部使用，很少直接构造 |
| 10 | **补充 `paragraphAlign` 系列**：明确对齐方式 |
| 11 | **补充 `flex_grow` / `flex_shrink` 说明**：明确"空间富余/不够时"的行为 |
| 12 | **新增 `linear_gradient`**：颜色渐变效果 |

---

## 🔥 常用组合模式（补充）

```cpp
// 1. 带滚动条的可滚动区域
auto scrollable = content | vscroll_indicator | frame | size(HEIGHT, LESS_THAN, 20);

// 2. 可拖拽分割的左右面板
auto split = ResizableSplit(left_panel, right_panel);
split.SetRatio(0.3);  // 左面板占 30%

// 3. 带退出按钮的窗口
auto exit = screen.ExitLoopClosure();
auto comp = Container::Vertical({
    Renderer([&] { return window("标题", text("内容")) | border; }),
    Button("退出", exit),
});

// 4. 条件显示组件
bool show_advanced = false;
auto advanced = Maybe(advanced_panel, &show_advanced);
```
