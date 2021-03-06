#ifndef XML_VIEWER_H
#define XML_VIEWER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "XMLViewer.h"

class Ui_TreeViewer
{
public:
    QHBoxLayout *hboxLayout;
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout1;
    QPushButton *addButton;
    QPushButton *removeButton;
    QPushButton *updatevButton;
    QProgressBar *progressBar;
    XMLViewer *xml_viewer;
    QHBoxLayout *hboxLayout2;
    QCheckBox *trackingBox;
    QSpacerItem *spacerItem;

    void setupUi(QWidget *TreeViewer)
    {
    TreeViewer->setObjectName(QString::fromUtf8("TreeViewer"));
    TreeViewer->resize(QSize(605, 706).expandedTo(TreeViewer->minimumSizeHint()));
    hboxLayout = new QHBoxLayout(TreeViewer);
    hboxLayout->setSpacing(6);
    hboxLayout->setMargin(9);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    vboxLayout = new QVBoxLayout();
    vboxLayout->setSpacing(6);
    vboxLayout->setMargin(0);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setSpacing(6);
    hboxLayout1->setMargin(0);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    addButton = new QPushButton(TreeViewer);
    addButton->setObjectName(QString::fromUtf8("addButton"));

    hboxLayout1->addWidget(addButton);

    removeButton = new QPushButton(TreeViewer);
    removeButton->setObjectName(QString::fromUtf8("removeButton"));

    hboxLayout1->addWidget(removeButton);

    updatevButton = new QPushButton(TreeViewer);
    updatevButton->setObjectName(QString::fromUtf8("updatevButton"));

    hboxLayout1->addWidget(updatevButton);

    progressBar = new QProgressBar(TreeViewer);
    progressBar->setObjectName(QString::fromUtf8("progressBar"));
    progressBar->setEnabled(true);
    progressBar->setMaximum(100);
    progressBar->setValue(0);
    progressBar->setTextVisible(false);
    progressBar->setOrientation(Qt::Horizontal);

    hboxLayout1->addWidget(progressBar);


    vboxLayout->addLayout(hboxLayout1);

    xml_viewer = new XMLViewer(TreeViewer);
    xml_viewer->setObjectName(QString::fromUtf8("xml_viewer"));
    xml_viewer->setMinimumSize(QSize(0, 0));

    vboxLayout->addWidget(xml_viewer);

    hboxLayout2 = new QHBoxLayout();
    hboxLayout2->setSpacing(6);
    hboxLayout2->setMargin(0);
    hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
    trackingBox = new QCheckBox(TreeViewer);
    trackingBox->setObjectName(QString::fromUtf8("trackingBox"));

    hboxLayout2->addWidget(trackingBox);

    spacerItem = new QSpacerItem(441, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout2->addItem(spacerItem);


    vboxLayout->addLayout(hboxLayout2);


    hboxLayout->addLayout(vboxLayout);

    retranslateUi(TreeViewer);

    QMetaObject::connectSlotsByName(TreeViewer);
    } // setupUi

    void retranslateUi(QWidget *TreeViewer)
    {
    TreeViewer->setWindowTitle(QApplication::translate("TreeViewer", "Form", 0, QApplication::UnicodeUTF8));
    addButton->setText(QApplication::translate("TreeViewer", "Add tree...", 0, QApplication::UnicodeUTF8));
    removeButton->setText(QApplication::translate("TreeViewer", "Remove selected", 0, QApplication::UnicodeUTF8));
    updatevButton->setText(QApplication::translate("TreeViewer", "Visualize selected", 0, QApplication::UnicodeUTF8));
    xml_viewer->setToolTip(QApplication::translate("TreeViewer", "Function painter for Lignum", 0, QApplication::UnicodeUTF8));
    xml_viewer->setWhatsThis(QApplication::translate("TreeViewer", " Function painter for Lignum", 0, QApplication::UnicodeUTF8));
    trackingBox->setText(QApplication::translate("TreeViewer", "Tracking", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(TreeViewer);
    } // retranslateUi

};

namespace Ui {
    class TreeViewer: public Ui_TreeViewer {};
} // namespace Ui

#endif // XML_VIEWER_H
