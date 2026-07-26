# Tab

## 一个组件列表，一次只绘制并与其交互一个。|selector| 提供所选组件的索引。这对于实现选项卡很有用。 

- Syntax:Tab(Component children, int* selector)
- Example:
```cpp
int tab_drawn = 0;
auto container = Container::Tab({
  children_1,
  children_2,
  children_3,
  children_4,
}, &tab_drawn);
```
- selcetor是第几项就渲染children中的第几项
