#include "LMarkdownView.h"
#include "qmarkdowntextedit.h"

#include <QFile>
#include <QFileInfo>
#include <QPainter>
#include <QQuickWindow>

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

    // QML 组件初始化完成后创建底层 widget
    m_editor = new QMarkdownTextEdit(nullptr, true);
    m_editor->setReadOnly(m_readOnly);

    // 将 widget 嵌入到 QQuickWindow 的 native widget 层级中
    QQuickWindow* w = window();
    if (w)
    {
        QWidget* host = QWidget::find(w->winId());
        if (host)
        {
            m_editor->setParent(host);
            m_editor->setWindowFlags(Qt::SubWindow);
            m_editor->show();
            syncGeometry();
        }
    }

    // 延迟加载初始文件
    if (!m_filePath.isEmpty())
        loadContent();
}

void LMarkdownView::loadFile(const QString& path)
{
    m_filePath = path;
    if (m_editor)
        loadContent();
}

void LMarkdownView::setMarkdownText(const QString& text)
{
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
        m_editor->setGeometry(
            globalPos.x(),
            globalPos.y(),
            static_cast<int>(width()),
            static_cast<int>(height()));
    }
}

void LMarkdownView::loadContent()
{
    if (!m_editor || m_filePath.isEmpty())
        return;

    QFile file(m_filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        m_editor->setPlainText(QString::fromUtf8(file.readAll()));
    }
}
