#include "LMarkdownView.h"
#include "qmarkdowntextedit.h"

#include <QFile>
#include <QFileInfo>
#include <QPainter>
#include <QQuickWindow>
#include <QDebug>

#ifdef Q_OS_WIN
#include <Windows.h>
#endif

LMarkdownView::LMarkdownView(QQuickItem* parent)
    : QQuickPaintedItem(parent)
{
    setAcceptedMouseButtons(Qt::AllButtons);
    setFlag(QQuickItem::ItemHasContents, true);
    setFlag(QQuickItem::ItemIsFocusScope, true);
}

LMarkdownView::~LMarkdownView()
{
    delete m_editor;
}

void LMarkdownView::componentComplete()
{
    QQuickPaintedItem::componentComplete();

    qDebug() << "LMarkdownView::componentComplete";
    qDebug() << "  Initial filePath:" << m_filePath;

    // QML 组件初始化完成后创建底层 widget
    m_editor = new QMarkdownTextEdit(nullptr, true);
    m_editor->setReadOnly(m_readOnly);

    // 获取 QQuickWindow 并将 QWidget 嵌入
    QQuickWindow* w = window();
    qDebug() << "  QQuickWindow:" << w;
    if (w)
    {
        // 创建一个原生窗口容器
        m_editor->setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);
        m_editor->setAttribute(Qt::WA_NativeWindow);
        m_editor->setAttribute(Qt::WA_DontCreateNativeAncestors);

        // 将 widget 的原生窗口作为 QML 窗口的子窗口
        WId widgetWinId = m_editor->winId();
        if (widgetWinId) {
            qDebug() << "  Setting QWidget as child of QQuickWindow";
            m_editor->setParent(nullptr);
            m_editor->show();

            // 使用 Windows API 设置父子关系
#ifdef Q_OS_WIN
            HWND qmlHwnd = (HWND)w->winId();
            HWND widgetHwnd = (HWND)widgetWinId;
            SetParent(widgetHwnd, qmlHwnd);
#endif
            syncGeometry();
        }
    }

    // 延迟加载初始文件
    if (!m_filePath.isEmpty())
        loadContent();
}

void LMarkdownView::loadFile(const QString& path)
{
    qDebug() << "LMarkdownView::loadFile" << path;

    // 避免重复加载同一文件
    if (m_filePath == path) {
        qDebug() << "  File already loaded, skipping";
        return;
    }

    m_filePath = path;
    if (m_editor)
        loadContent();
    emit filePathChanged();
}

void LMarkdownView::setMarkdownText(const QString& text)
{
    qDebug() << "LMarkdownView::setMarkdownText - length:" << text.length();
    if (m_editor)
        m_editor->setPlainText(text);
}

QString LMarkdownView::getMarkdownText() const
{
    return m_editor ? m_editor->toPlainText() : QString();
}

void LMarkdownView::setReadOnly(bool ro)
{
    m_readOnly = ro;
    if (m_editor)
        m_editor->setReadOnly(ro);
    emit readOnlyChanged();
}

void LMarkdownView::paint(QPainter* painter)
{
    // widget 自行渲染
    Q_UNUSED(painter);
}

void LMarkdownView::geometryChange(const QRectF& newGeometry, const QRectF& oldGeometry)
{
    QQuickPaintedItem::geometryChange(newGeometry, oldGeometry);
    syncGeometry();
}

void LMarkdownView::syncGeometry()
{
    if (!m_editor)
        return;

    QPointF scenePos = mapToScene(QPointF(0, 0));
    QQuickWindow* w = window();
    if (w)
    {
        QPoint globalPos = w->mapToGlobal(scenePos.toPoint());
        QRect newGeom(globalPos.x(), globalPos.y(), static_cast<int>(width()), static_cast<int>(height()));
        qDebug() << "LMarkdownView::syncGeometry - setting geometry to:" << newGeom;
        m_editor->setGeometry(newGeom);
    }
}

void LMarkdownView::loadContent()
{
    if (!m_editor || m_filePath.isEmpty())
    {
        qDebug() << "LMarkdownView::loadContent - skipped (editor:" << m_editor << "path:" << m_filePath << ")";
        return;
    }

    qDebug() << "LMarkdownView::loadContent - loading:" << m_filePath;

    QFile file(m_filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString content = QString::fromUtf8(file.readAll());
        qDebug() << "  Loaded" << content.length() << "characters";
        m_editor->setPlainText(content);
    }
    else
    {
        qDebug() << "  Failed to open file:" << file.errorString();
    }
}
