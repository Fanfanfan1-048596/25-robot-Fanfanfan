# 个人账本管理系统

## 项目概述

本项目实现了一个基于命令行的个人账本管理系统，采用现代C++开发，支持账务记录的增删改查、多维度统计分析及数据持久化存储。

### 核心功能
- 账务数据的增删改查
- 按日期/金额排序
- 多维度统计（日/月/年）
- 数据持久化存储

## 系统设计与实现思路

### 1. 整体架构
采用分层架构设计，各层职责明确：
1. 核心层 (Core)
   - Transaction: 账务记录基础类
   - Constants: 系统常量定义
   
2. 数据层 (Data)
   - AccountBook: 账本管理类，负责数据组织
   - FileManager: 文件操作管理，处理持久化
   
3. 统计层 (Stats)
   - StatisticsCalculator: 统计基类
   - DailyCalculator: 日统计实现
   - MonthlyCalculator: 月统计实现
   - YearlyCalculator: 年统计实现
   
4. 界面层 (UI)
   - Menu: 交互界面类

### 2. 核心设计思路

#### 2.1 数据结构选择
- 使用`std::vector`存储Transaction对象
  - 优点：支持动态增长、随机访问、内存连续
  - 权衡：查找效率为O(n)，但考虑到个人账本数据量通常不大，可以接受

#### 2.2 统计功能实现
- 采用模板方法模式
  - 基类定义统计流程框架
  - 派生类实现具体统计算法
- 使用策略模式处理不同维度统计
  - 便于扩展新的统计维度
  - 符合开闭原则

#### 2.3 持久化存储
- 采用CSV文件存储
  - 优点：可读性好，便于导出和编辑
  - 兼容Excel等办公软件
  - 支持数据迁移和共享

### 3. 技术特点

#### 3.1 现代C++特性运用
- 智能指针管理资源
- auto类型推导
- 范围for循环
- lambda表达式
- STL算法库

#### 3.2 设计模式应用
- 模板方法模式：统计功能实现
- 策略模式：统计维度扩展
- 单例模式：文件管理器

## 编译部署

### 环境要求
- Linux操作系统
- CMake 3.10+
- C++17支持
- GCC/Clang编译器

### 编译步骤

1. 克隆项目(推荐SSH地址)
> PS：根目录下要有一个空的data目录
```bash
git clone ...
cd ./account-management
```

1. 创建构建目录并编译
```bash
# 不包含测试的构建
mkdir build && cd build
cmake ..
make

# 包含测试的构建
mkdir build && cd build
cmake -DBUILD_TESTS=ON ..
make
```

1. 运行程序
```bash
./account_manager
```

## 使用说明

### 主菜单功能
1. 添加账务记录
2. 删除账务记录
3. 修改账务记录
4. 查询账务记录
5. 显示所有记录
6. 排序账务记录
7. 统计账务情况
8. 保存并退出

### 操作示例
```
=== 个人账本管理系统 ===
1. 添加账务记录
2. 删除账务记录
...
请选择操作 (1-8): 1

请输入日期 (YYYY-MM-DD): 2024-01-15
请输入名称: 工资
请输入金额: 5000
添加成功!
```

### 注意事项
- 日期格式：YYYY-MM-DD
- 金额格式：收入为正数，支出为负数
- 退出时自动保存数据
- 数据以CSV格式存储在build/data/accounts.csv
- 可直接用Excel打开查看数据

## 代码结构
```
account-management
├── CMakeLists.txt
├── data
├── include
│   ├── core
│   │   ├── Constants.hpp
│   │   └── Transaction.hpp
│   ├── data
│   │   ├── AccountBook.hpp
│   │   └── FileManager.hpp
│   ├── stats
│   │   ├── DailyCalculator.hpp
│   │   ├── MonthlyCalculator.hpp
│   │   ├── StatisticsCalculator.hpp
│   │   └── YearlyCalculator.hpp
│   └── ui
│       └── Menu.hpp
├── src
│   ├── core
│   │   └── Transaction.cpp
│   ├── data
│   │   ├── AccountBook.cpp
│   │   └── FileManager.cpp
│   ├── main.cpp
│   ├── stats
│   │   ├── DailyCalculator.cpp
│   │   ├── MonthlyCalculator.cpp
│   │   ├── StatisticsCalculator.cpp
│   │   └── YearlyCalculator.cpp
│   └── ui
│       └── Menu.cpp
└── test
    ├── CMakeLists.txt
    └── test_main.cpp
```

## 技术亮点

### 1. 代码设计
- 良好的模块化和封装
- 清晰的分层架构
- 统一的错误处理机制
- 完整的单元测试

### 2. 现代C++实践
- RAII资源管理
- 智能指针内存管理
- STL算法库的广泛使用
- 函数式编程特性应用

## 存在的不足与优化方向

### 1. 性能优化方面
- 可引入索引结构提升查询效率
- 考虑大数据量下的分页加载
- 优化文件读写性能

### 2. 功能扩展方面
- 添加图形化UI
- 实现多用户支持
- 添加数据备份功能
- 支持更多数据导出格式

### 3. 代码改进点
- 增强异常处理机制
- 添加日志系统
- 引入配置文件
- 支持插件化扩展

## 总结

虽然只是一个大作业，但是项目本身也算是有合理的架构设计，也有一些现代C++特性的运用，实现了一个功能完整、可扩展的个人账本管理系统。虽然还存在不少优化空间，但勉强满足了个人财务管理的需求。感兴趣者可以大致参考，或是基于此进行改进。
