#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    this->setFixedWidth(200);

    QVBoxLayout* layout = new QVBoxLayout;

    auto example1 = new XB::AutoScrollingLabel;
    example1->setText("Short text");
    layout->addWidget(example1);
    auto example2 = new XB::AutoScrollingLabel;
    example2->setText("Very long text which requires to be animated");
    example2->setFrameShape(QFrame::Box);
    layout->addWidget(example2);
    auto example3 = new XB::AutoScrollingLabel;
    example3->setText("Very long text which requires to be animated");
    example3->setAnimationTimeout(20);
    example3->setTextSpacer(" <|> ");
    example3->setAnimateOnMouseOver(false);
    layout->addWidget(example3);

    QWidget* w = new QWidget;
    w->setLayout(layout);
    setCentralWidget(w);
}

MainWindow::~MainWindow()
{
}
