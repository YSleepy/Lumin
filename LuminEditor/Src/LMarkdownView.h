#pragma once

#include <QQuickPaintedItem>

class QMarkdownTextEdit;

class LMarkdownView : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QString filePath READ getFilePath WRITE loadFile NOTIFY filePathChanged)
    Q_PROPERTY(bool readOnly READ isReadOnly WRITE setReadOnly NOTIFY readOnlyChanged)

public:
    explicit LMarkdownView(QQuickItem* parent = nullptr);
    ~LMarkdownView() override;

    Q_INVOKABLE void loadFile(const QString& path);
    Q_INVOKABLE void setMarkdownText(const QString& text);
    Q_INVOKABLE QString getMarkdownText() const;

    QString getFilePath() const { return m_filePath; }
    bool isReadOnly() const { return m_readOnly; }
    void setReadOnly(bool ro);

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
