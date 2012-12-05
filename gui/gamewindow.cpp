#include "gamewindow.h"

GameWindow::GameWindow(QWidget *parent) : QPlainTextEdit(parent) {
    mainWindow = (MainWindow*)parent;       
    windowManager = mainWindow->getWindowManager();
    settings = ClientSettings::Instance();

    this->loadSettings();
    this->buildContextMenu();

    this->setFocusPolicy(Qt::NoFocus);

    this->setReadOnly(true);
    this->document()->setMaximumBlockCount(500);

    connect(this, SIGNAL(copyAvailable(bool)), this, SLOT(enableCopy(bool)));

    /* workaround for bottom margin */
    setViewportMargins(0, 0, 0, -DEFAULT_MAIN_FONT_SIZE);
}

void GameWindow::showEvent(QShowEvent* event) {
    QPlainTextEdit::showEvent(event);

    QColor fontColor = settings->getParameter("GameWindow/fontColor",
        QColor(DEFAULT_MAIN_FONT_COLOR)).value<QColor>();

    QPalette p = this->viewport()->palette();
    p.setColor(QPalette::Text, fontColor);

    this->viewport()->setPalette(p);
}

void GameWindow::loadSettings() {
    QFont font = settings->getParameter("GameWindow/font",
        QFont(DEFAULT_MAIN_FONT, DEFAULT_MAIN_FONT_SIZE)).value<QFont>();       
    this->setFont(font);
}

void GameWindow::buildContextMenu() {
    menu = new QMenu(this);

    copyAct = new QAction(tr("&Copy\t"), this);
    menu->addAction(copyAct);
    copyAct->setEnabled(false);
    connect(copyAct, SIGNAL(triggered()), this, SLOT(copySelected()));

    menu->addSeparator();

    selectAct = new QAction(tr("&Select All\t"), this);
    menu->addAction(selectAct);
    connect(selectAct, SIGNAL(triggered()), this, SLOT(selectAll()));
}

void GameWindow::contextMenuEvent(QContextMenuEvent *event) {
    menu->exec(event->globalPos());
}

void GameWindow::resizeEvent(QResizeEvent *event) {
    windowManager->paintNavigationDisplay();
    QPlainTextEdit::resizeEvent(event);
}

void GameWindow::enableCopy(bool enabled) {
    copyAct->setEnabled(enabled);
}

void GameWindow::copySelected() {
    this->copy();

    QTextCursor textCursor = this->textCursor();
    textCursor.clearSelection();
    this->setTextCursor(textCursor);
}

GameWindow::~GameWindow() {
}
