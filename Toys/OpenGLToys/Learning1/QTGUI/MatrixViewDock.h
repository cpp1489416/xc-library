#pragma once

#include <QDockWidget>
#include <QtWidgets>
#include <glm/glm.hpp>

class MatrixViewDock : public QDockWidget
{
    Q_OBJECT

public:
    MatrixViewDock(QWidget *parent);
    ~MatrixViewDock();

    void AddMatrix(glm::mat4 *matrix, const char * name);

    private slots:
    void UpdateMatrix();
    void SetMatrixFromText();

private:
    QComboBox * mComboBox;
    QLineEdit * lineEdits[16];
};
