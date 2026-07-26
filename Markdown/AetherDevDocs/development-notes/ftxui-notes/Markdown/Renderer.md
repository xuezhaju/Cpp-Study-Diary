# Renderer(包装器)

- 作用：装饰或者说是包装一个component对象
- 将组件Component转换为元素Element

## Syntax
- Renderer(component, function)
- 第一项为所依赖的component,也可以理解为所要装饰的对象
- 第二项为需要实现的函数体
- 返回值必须为Element,如果为Component类型，则用 Component -> Render()转换成Element
- 如果需要依赖许多component类型，则可以使用容器，auto container = Container::Vertical({menu, input, button});
- Renderer 之所以用lambda语法，不仅仅是因为lambda语法简洁，更是因为在需要实时渲染的环境下，需要一直接受每帧的变化的画面
```执行流程
程序启动
    ↓
创建 Renderer（Lambda 被存储，但不执行）
    ↓
screen.Loop(renderer) 启动事件循环
    ↓
用户按键 → state 改变
    ↓
FTXUI 调用 Lambda ← 【Lambda 在这里执行】
    ↓
生成新的 Element
    ↓
屏幕更新
```

