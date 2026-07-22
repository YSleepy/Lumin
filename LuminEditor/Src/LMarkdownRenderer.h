#pragma once

#include <QObject>
#include <QString>
#include <QStringList>

// 简易 Markdown → HTML 渲染器
// 支持：标题(#)、加粗(**)、斜体(*)、代码块(```)、行内代码(`)、
//       无序列表(-/*)、有序列表(1.)、链接、图片、表格、分割线
class LMarkdownRenderer : public QObject
{
    Q_OBJECT

public:
    explicit LMarkdownRenderer(QObject* parent = nullptr);

    // 加载并渲染 markdown 文件
    Q_INVOKABLE QString LoadFile(const QString& path);

    // 直接渲染 markdown 字符串
    Q_INVOKABLE QString Render(const QString& markdown);

private:
    QString RenderLine(const QString& line, bool& inCodeBlock, QString& closeTags);
    QString EscapeHtml(const QString& text);
    QString ProcessInlineFormatting(const QString& text);
    QString RenderTable(const QStringList& lines, int& index);
    QString RenderCodeBlock(const QStringList& lines, int& index);
};
