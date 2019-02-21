/*
 * Name: Grill Matthias
 * Class: 5BHIF
 */
#ifndef ADDROUTEDIALOG_H
#define ADDROUTEDIALOG_H

#include <QDialog>
#include "dbmanager.h"

namespace Ui
{
class AddRouteDialog;
}

class AddRouteDialog : public QDialog
{
    Q_OBJECT

  public:
    explicit AddRouteDialog(QWidget *parent = 0);
    ~AddRouteDialog();

  private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

  private:
    Ui::AddRouteDialog *ui;
    QFont font{"Helvetica", 16, QFont::Bold};
    void initGUI();
};

#endif // ADDROUTEDIALOG_H
