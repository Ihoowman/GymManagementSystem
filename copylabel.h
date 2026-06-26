#pragma once
#include <QLabel>
#include <QMouseEvent>
#include <QGuiApplication>
#include <QClipboard>
#include <QTimer>

class ClickCopyLabel : public QLabel {
    Q_OBJECT
public:
    explicit ClickCopyLabel(QWidget *parent = nullptr) : QLabel(parent) {
        setCursor(Qt::PointingHandCursor);
    }

    void setCopyText(const QString& t) { m_copyText = t; }

protected:
    void mousePressEvent(QMouseEvent *e) override {
        if (e->button() == Qt::LeftButton) {
            const QString toCopy = m_copyText.isEmpty() ? text() : m_copyText;
            QGuiApplication::clipboard()->setText(toCopy);

            const QString old = this->text();
            setText("Copied!");
            QTimer::singleShot(650, this, [this, old]{ setText(old); });
            e->accept();
            return;
        }
        QLabel::mousePressEvent(e);
    }

private:
    QString m_copyText;
};
