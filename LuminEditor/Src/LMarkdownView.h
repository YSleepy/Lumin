#pragma once

#include <QQuickPaintedItem>

class QMarkdownTextEdit;

class LMarkdownView : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QString filePath READ GetFilePath WRITE LoadFile NOTIFY filePathChanged)
    Q_PROPERTY(bool readOnly READ IsReadOnly WRITE SetReadOnly NOTIFY readOnlyChanged)

public:
    explicit LMarkdownView(QQuickItem* parent = nullptr);
    ~LMarkdownView() override;

    Q_INVOKABLE void LoadFile(const QString& path);
    Q_INVOKABLE void SetMarkdownText(const QString& text);
    Q_INVOKABLE QString GetMarkdownText() const;

    QString GetFilePath() const { return m_filePath; }
    bool IsReadOnly() const { return m_readOnly; }
    void SetReadOnly(bool ro);

    void paint(QPainter* painter) override;

signals:
    void filePathChanged();
    void readOnlyChanged();

protected:
    void componentComplete() override;
    void geometryChange(const QRectF& newGeometry, const QRectF& oldGeometry) override;

private:
    void syncGeometry();
    void loadContent();

    QMarkdownTextEdit* m_editor = nullptr;
    QString m_filePath;
    bool m_readOnly = true;
};
