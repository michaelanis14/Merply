/*
Name: QtRpt
Version: 1.5.5
Web-site: http://www.qtrpt.tk
Programmer: Aleksey Osipov
E-mail: aliks-os@ukr.net
Web-site: http://www.aliks-os.tk

Copyright 2012-2015 Aleksey Osipov

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef EDITFLDDLG_H
#define EDITFLDDLG_H

#include <QDialog>
#include <QTextCharFormat>
#include "FldPropertyDlg.h"
#include "TContainerField.h"
#include "selectcolor.h"
#include "Barcode.h"

namespace Ui {
    class EditFldDlg;
}

class TContainerField;


class EditFldDlg : public QDialog
{
    Q_OBJECT

public:
    explicit EditFldDlg(QWidget *parent = 0);
    ~EditFldDlg();
    int showText(TContainerField *cont);
    int showTextRich(TContainerField *cont);
    int showImage(TContainerField *cont);
    int showDiagram(TContainerField *cont);
    int showBarcode(TContainerField *cont);
    int showCrosstab(TContainerField *cont);

protected:

private:
    Ui::EditFldDlg *ui;
    bool boolImage;  //Proccess TextFiled as a Image
    TContainerField *m_cont;
    QString m_cond_printing;
    QString m_cond_higlighting;
    QString m_imgFormat;

private slots:
    void loadImage();
    void saveImage();
    void openProperty();
    void conditionalToggled(bool value);
    void backGroundToggled(bool value);
    void conditionChanged(const QString &text);
    void chooseColor();
    void encodeHighLightingString();
    void decodeHighLightingString();
    void autoFillData(bool value);
    void selectGraphColor();
    void moveRow();
    void itemSelectionChanged();
    void removeRow();
    void addRow();
    void setScaledContents(bool value);
    void update_preview();
    void textDirection();

};

#endif // EDITFLDDLG_H
