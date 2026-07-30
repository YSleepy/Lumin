# Lumin Editor - Markdown 测试

这是一个测试 Markdown 文件，用于验证 Markdown 编辑器的功能。

## 功能特性

- **左侧编辑器**: 支持实时编辑 Markdown 文本
- **右侧预览**: 自动渲染 Markdown 内容
- **分割线拖拽**: 可以调整左右面板的宽度比例

## 代码示例

```cpp
class LMarkdownView : public QQuickPaintedItem {
    Q_OBJECT
public:
    explicit LMarkdownView(QQuickItem* parent = nullptr);
    void loadFile(const QString& path);
};
```

## 数学公式

支持 LaTeX 风格的数学公式：

- 行内公式: $E = mc^2$
- 块级公式:

$$
\int_{a}^{b} f(x) dx = F(b) - F(a)
$$

## 列表

### 无序列表
- 第一项
- 第二项
  - 嵌套项 1
  - 嵌套项 2
- 第三项

### 有序列表
1. 步骤一
2. 步骤二
3. 步骤三

## 表格

| 功能 | 状态 | 备注 |
|------|------|------|
| 文件打开 | ✅ | 支持 .md 和 .markdown |
| 实时预览 | ✅ | 300ms 防抖 |
| 语法高亮 | ✅ | QMarkdownTextEdit |
| 保存文件 | 🚧 | 待实现 |

## 引用

> "好的代码是自解释的。"
> 
> — 某位智者

## 链接和图片

- [Lumin 项目](https://github.com/yourusername/lumin)
- ![示例图片](path/to/image.png)

---

**测试完成！** 🎉
