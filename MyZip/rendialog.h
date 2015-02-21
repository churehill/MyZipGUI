#ifndef RENDIALOG_H
#define RENDIALOG_H

#include <QDialog>

namespace Ui {
class RenDialog;
}

class RenDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit RenDialog(QWidget *parent = 0);
    ~RenDialog();
    
private:
    Ui::RenDialog *ui;
};

#endif // RENDIALOG_H
