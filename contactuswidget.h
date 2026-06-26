#include <QWidget>
#include <QPushButton>
#include <QFrame>
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QGraphicsOpacityEffect>

class ContactUsWidget : public QWidget {
    Q_OBJECT
public:
    explicit ContactUsWidget(QWidget *parent = nullptr)
        : QWidget(parent)
    {
        setObjectName("contactRoot");

        panel = new QFrame;
        panel->setObjectName("contactPanel");
        panel->setFrameShape(QFrame::NoFrame);


        auto *grid = new QGridLayout(panel);
        grid->setContentsMargins(14, 14, 14, 14);
        grid->setHorizontalSpacing(12);
        grid->setVerticalSpacing(8);

        auto addRow = [&](int r, const QString &k, QWidget *v){
            auto *lk = new QLabel(k);
            lk->setObjectName("labelKey");
            lk->setMinimumWidth(80);
            grid->addWidget(lk, r, 0, Qt::AlignTop);
            grid->addWidget(v,  r, 1, Qt::AlignTop);
        };

        auto *phone = new QLabel(R"(<a href="tel:+989123456789">+98 912 345 6789</a>)");
        phone->setTextFormat(Qt::RichText);
        phone->setTextInteractionFlags(Qt::TextBrowserInteraction);
        phone->setOpenExternalLinks(true);

        auto *email = new QLabel(R"(<a href="mailto:info@example.com">info@example.com</a>)");
        email->setTextFormat(Qt::RichText);
        email->setTextInteractionFlags(Qt::TextBrowserInteraction);
        email->setOpenExternalLinks(true);

        auto *addr = new QLabel("Shiraz, Qasrodasht");
        auto *hours = new QLabel("Sat–Thu: 9:00–18:00");

        addRow(0, "Phone",   phone);
        addRow(1, "Email",   email);
        addRow(2, "Address", addr);
        addRow(3, "Hours",   hours);


        opacity = new QGraphicsOpacityEffect(panel);
        panel->setGraphicsEffect(opacity);


        panel->setMaximumHeight(0);
        opacity->setOpacity(0.0);
        panel->setVisible(false);

        auto *root = new QVBoxLayout(this);
        root->setContentsMargins(16, 16, 16, 16);
        root->setSpacing(12);
        root->addWidget(panel);

        setStyleSheet(R"(
            #contactRoot {
                background: #0b0f19;
                border: 1px solid rgba(255,255,255,0.10);
                border-radius: 16px;
                color: white;
                font-family: "Segoe UI", Arial;
            }
            QPushButton {
                padding: 12px 14px;
                border-radius: 12px;
                border: 0;
                color: white;
                font-weight: 700;
                background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                                            stop:0 #7c3aed, stop:1 #06b6d4);
            }
            QPushButton:pressed { background: #5b21b6; }
            QPushButton:focus { outline: none; }

            #contactPanel {
                background: rgba(255,255,255,0.06);
                border: 1px solid rgba(255,255,255,0.10);
                border-radius: 12px;
            }
            QLabel { color: rgba(255,255,255,0.92); }
            #labelKey { color: rgba(255,255,255,0.68); font-weight: 700; }
            QLabel a { color: #a5f3fc; text-decoration: none; }
            QLabel a:hover { text-decoration: underline; }
        )");

        heightAnim = new QPropertyAnimation(panel, "maximumHeight", this);
        heightAnim->setDuration(320);
        heightAnim->setEasingCurve(QEasingCurve::OutCubic);

        opacityAnim = new QPropertyAnimation(opacity, "opacity", this);
        opacityAnim->setDuration(220);
        opacityAnim->setEasingCurve(QEasingCurve::OutCubic);

        group = new QParallelAnimationGroup(this);
        group->addAnimation(heightAnim);
        group->addAnimation(opacityAnim);

    }
public slots:
    void setOpen(bool open)
    {
        group->stop();

        if (open) {
            panel->setVisible(true);

            int target = panel->sizeHint().height();

            heightAnim->setStartValue(panel->maximumHeight());
            heightAnim->setEndValue(target);

            opacityAnim->setStartValue(opacity->opacity());
            opacityAnim->setEndValue(1.0);

        } else {
            heightAnim->setStartValue(panel->maximumHeight());
            heightAnim->setEndValue(0);

            opacityAnim->setStartValue(opacity->opacity());
            opacityAnim->setEndValue(0.0);
        }

        group->start();
    }
private:
    QFrame *panel{};
    QGraphicsOpacityEffect *opacity{};
    QPropertyAnimation *heightAnim{};
    QPropertyAnimation *opacityAnim{};
    QParallelAnimationGroup *group{};
};
