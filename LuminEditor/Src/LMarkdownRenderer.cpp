#include "LMarkdownRenderer.h"

#include <QFile>
#include <QRegularExpression>
#include <QFileInfo>
#include <QDir>

LMarkdownRenderer::LMarkdownRenderer(QObject* parent)
    : QObject(parent)
{
}

QString LMarkdownRenderer::LoadFile(const QString& path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return QString("<p style='color:red'>无法打开文件: %1</p>").arg(EscapeHtml(path));

    QString content = QString::fromUtf8(file.readAll());
    return Render(content);
}

QString LMarkdownRenderer::Render(const QString& markdown)
{
    QStringList lines = markdown.split('\n');
    QString html;
    html += "<html><head><style>"
            "body { font-family: 'Microsoft YaHei', sans-serif; font-size: 14px; "
            "  color: #ccc; background: #1e1e1e; padding: 16px 24px; line-height: 1.8; }"
            "h1 { font-size: 22px; border-bottom: 2px solid #444; padding-bottom: 8px; margin-top: 24px; }"
            "h2 { font-size: 18px; border-bottom: 1px solid #444; padding-bottom: 6px; margin-top: 20px; }"
            "h3 { font-size: 16px; margin-top: 16px; }"
            "code { background: #2d2d2d; padding: 2px 6px; border-radius: 3px; font-family: Consolas, monospace; font-size: 13px; }"
            "pre { background: #2d2d2d; padding: 12px 16px; border-radius: 4px; overflow-x: auto; }"
            "pre code { background: none; padding: 0; }"
            "a { color: #569cd6; }"
            "table { border-collapse: collapse; width: 100%; margin: 12px 0; }"
            "th, td { border: 1px solid #444; padding: 6px 12px; text-align: left; }"
            "th { background: #333; }"
            "blockquote { border-left: 3px solid #569cd6; padding-left: 12px; color: #999; margin: 8px 0; }"
            "hr { border: none; border-top: 1px solid #444; margin: 20px 0; }"
            "ul, ol { padding-left: 24px; }"
            "img { max-width: 100%; }"
            "</style></head><body>";

    bool inCodeBlock = false;
    QString closeTags;

    for (int i = 0; i < lines.size(); ++i)
    {
        QString line = lines[i];

        // Code block
        if (line.trimmed().startsWith("```"))
        {
            if (!inCodeBlock)
            {
                inCodeBlock = true;
                html += "<pre><code>";
                // Capture language hint (optional)
                continue;
            }
            else
            {
                inCodeBlock = false;
                html += "</code></pre>\n";
                continue;
            }
        }

        if (inCodeBlock)
        {
            html += EscapeHtml(line) + "\n";
            continue;
        }

        // Table
        if (line.contains('|') && i + 1 < lines.size() && lines[i + 1].contains("---"))
        {
            QStringList tableLines;
            tableLines.append(line);
            ++i;
            tableLines.append(lines[i]); // separator line
            while (i + 1 < lines.size() && lines[i + 1].contains('|'))
            {
                ++i;
                tableLines.append(lines[i]);
            }
            html += RenderTable(tableLines, i);
            continue;
        }

        // Headers
        QRegularExpression h1Re("^# (.+)$");
        QRegularExpression h2Re("^## (.+)$");
        QRegularExpression h3Re("^### (.+)$");
        QRegularExpression h4Re("^#### (.+)$");
        auto h1 = h1Re.match(line);
        auto h2 = h2Re.match(line);
        auto h3 = h3Re.match(line);
        auto h4 = h4Re.match(line);

        if (h1.hasMatch()) { html += "<h1>" + ProcessInlineFormatting(h1.captured(1)) + "</h1>\n"; continue; }
        if (h2.hasMatch()) { html += "<h2>" + ProcessInlineFormatting(h2.captured(1)) + "</h2>\n"; continue; }
        if (h3.hasMatch()) { html += "<h3>" + ProcessInlineFormatting(h3.captured(1)) + "</h3>\n"; continue; }
        if (h4.hasMatch()) { html += "<h4>" + ProcessInlineFormatting(h4.captured(1)) + "</h4>\n"; continue; }

        // Horizontal rule
        if (line.trimmed() == "---" || line.trimmed() == "***" || line.trimmed() == "___")
        {
            html += "<hr>\n";
            continue;
        }

        // Blockquote
        if (line.trimmed().startsWith("> "))
        {
            QString quote = line.trimmed().mid(2);
            html += "<blockquote>" + ProcessInlineFormatting(quote) + "</blockquote>\n";
            continue;
        }

        // Unordered list
        QRegularExpression ulRe("^(\\s*)[-*] (.+)$");
        auto ulMatch = ulRe.match(line);
        if (ulMatch.hasMatch())
        {
            html += "<li>" + ProcessInlineFormatting(ulMatch.captured(2)) + "</li>\n";

            // Check if next line is not a list item → close <ul>
            if (i + 1 >= lines.size() || !lines[i + 1].contains(QRegularExpression("^\\s*[-*] ")))
                html += "<br>";
            continue;
        }

        // Ordered list
        QRegularExpression olRe("^(\\s*)\\d+\\. (.+)$");
        auto olMatch = olRe.match(line);
        if (olMatch.hasMatch())
        {
            html += "<li>" + ProcessInlineFormatting(olMatch.captured(2)) + "</li>\n";
            if (i + 1 >= lines.size() || !lines[i + 1].contains(QRegularExpression("^\\s*\\d+\\. ")))
                html += "<br>";
            continue;
        }

        // Empty line → paragraph break
        if (line.trimmed().isEmpty())
        {
            if (!closeTags.isEmpty())
            {
                html += closeTags + "\n";
                closeTags.clear();
            }
            continue;
        }

        // Regular paragraph
        html += "<p>" + ProcessInlineFormatting(line) + "</p>\n";
    }

    if (!closeTags.isEmpty())
        html += closeTags + "\n";

    html += "</body></html>";
    return html;
}

QString LMarkdownRenderer::EscapeHtml(const QString& text)
{
    QString result = text;
    result.replace('&', "&amp;");
    result.replace('<', "&lt;");
    result.replace('>', "&gt;");
    result.replace('"', "&quot;");
    return result;
}

QString LMarkdownRenderer::ProcessInlineFormatting(const QString& text)
{
    QString result = text;

    // Images ![alt](url)
    QRegularExpression imgRe("!\\[([^\\]]*)\\]\\(([^)]+)\\)");
    result.replace(imgRe, "<img src='\\2' alt='\\1'>");

    // Links [text](url)
    QRegularExpression linkRe("\\[([^\\]]+)\\]\\(([^)]+)\\)");
    result.replace(linkRe, "<a href='\\2'>\\1</a>");

    // Bold **text**
    QRegularExpression boldRe("\\*\\*(.+?)\\*\\*");
    result.replace(boldRe, "<b>\\1</b>");

    // Italic *text*
    QRegularExpression italicRe("\\*(.+?)\\*");
    result.replace(italicRe, "<i>\\1</i>");

    // Inline code `text`
    QRegularExpression codeRe("`([^`]+)`");
    result.replace(codeRe, "<code>\\1</code>");

    return result;
}

QString LMarkdownRenderer::RenderTable(const QStringList& lines, int& index)
{
    QString html = "<table>\n";

    // Header row
    QStringList headers = lines[0].split('|', Qt::SkipEmptyParts);
    html += "<tr>";
    for (const auto& h : headers)
        html += "<th>" + ProcessInlineFormatting(h.trimmed()) + "</th>";
    html += "</tr>\n";

    // Skip separator line (index 1)
    // Data rows
    for (int i = 2; i < lines.size(); ++i)
    {
        QStringList cells = lines[i].split('|', Qt::SkipEmptyParts);
        html += "<tr>";
        for (const auto& c : cells)
            html += "<td>" + ProcessInlineFormatting(c.trimmed()) + "</td>";
        html += "</tr>\n";
    }

    html += "</table>\n";
    return html;
}
