# Button

## 由于我在使用Button组件的时候触发了SIGSEGV地址边界错误，于是写下此篇

- Syntax:Component Button (ButtonOption option) 	
- Example:
```cpp
auto screen = ScreenInteractive::FitComponent();
Component button = Button({
  .label = "Click to quit",
  .on_click = screen.ExitLoopClosure(),
});
screen.Loop(button)
```

- 而我只写了.label,并没有写.on_click，而编辑器未提示我，于是造成了内存边界的问题
- [详细参数](https://arthursonzogni.github.io/FTXUI/zh-CH/group__component.html#structftxui_1_1ButtonOption)

