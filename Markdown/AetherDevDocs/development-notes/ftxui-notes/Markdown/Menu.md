# Menu
- ***定义一个菜单对象。它包含一个条目列表，其中一个被选中。***

## Syntax
- Menu(entries, selected, option)
- entries -> 类型：std::vector<std::string>*  必填  菜单项列表的*指针*，菜单会实时读取这里的数据
- selected -> 类型：int*  必填  选中索引的*指针*，菜单会修改这个值
- option -> 类型：MenuOption  非必填 菜单配置（样式、回调等），不传则使用默认配置
