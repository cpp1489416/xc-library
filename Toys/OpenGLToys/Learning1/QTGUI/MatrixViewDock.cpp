#include "MatrixViewDock.h"

namespace
{
    class WWidget : public QWidget
    {
    public:
        QSize sizeHint() const override { return QSize(10, 10); }
    };
}

MatrixViewDock::MatrixViewDock(QWidget *parent)
    : QDockWidget(parent)
{
    setWindowTitle("Matrixes");

    WWidget *mainWidget = new WWidget;
    setWidget(mainWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainWidget->setLayout(mainLayout);

    mComboBox = new QComboBox;
    mainLayout->addWidget(mComboBox);

    QHBoxLayout *lineLayout;
    for (int i = 0; i < 16; ++i)
    {
        if (i % 4 == 0)
        {
            lineLayout = new QHBoxLayout;
        }

        lineEdits[i] = new QLineEdit();
        lineLayout->addWidget(lineEdits[i], 10, Qt::AlignmentFlag::AlignJustify);
        lineEdits[i]->setGeometry(0, 0, 10, 10);
        if (i % 4 == 0)
        {
            mainLayout->addLayout(lineLayout);
        }
    }
    
    QPushButton *updateButton = new QPushButton("Update Matrix");
    mainLayout->addWidget(updateButton);
    connect(updateButton, &QPushButton::clicked, this, &MatrixViewDock::UpdateMatrix);

    QPushButton *setButton = new QPushButton("Set Matrix");
    mainLayout->addWidget(setButton);
    connect(setButton, &QPushButton::clicked, this, &MatrixViewDock::SetMatrixFromText);

    mainLayout->addStretch();   
    connect(mComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(UpdateMatrix()));

    //QTimer *timer = new QTimer(this);
    //connect(timer, &QTimer::timeout, this, &MatrixViewDock::UpdateMatrix);
    //timer->start(1000);
}

MatrixViewDock::~MatrixViewDock()
{
}

void MatrixViewDock::AddMatrix(glm::mat4 * matrix, const char * name)
{
//    mComboBox->addItem(name, QVariant::fromValue((void *)matrix));
}

void MatrixViewDock::SetMatrixFromText()
{
  /*  glm::mat4 * curMat = (glm::mat4 *)mComboBox->currentData().value<void *>();
    float vals[16];
    for (int i = 0; i < 16; i++)
    {
        QLineEdit *le = lineEdits[i];
        vals[i] = le->text().toFloat();
        (*curMat)(i / 4, i % 4) = vals[i];
    }
    */
}

void MatrixViewDock::UpdateMatrix()
{
    /*
    glm::mat4 * curMat = (glm::mat4 *)mComboBox->currentData().value<void *>();

    for (int i = 0; i < 16; i++)
    {
        QLineEdit *le = lineEdits[i];
        le->setText(QString::number((*curMat)(i / 4, i % 4)));
    }
    */
}
